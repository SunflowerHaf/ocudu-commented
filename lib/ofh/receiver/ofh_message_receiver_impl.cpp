// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_message_receiver_impl.cpp  (185 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#include "ofh_message_receiver_impl.h"
#include "../support/logger_utils.h"
#include "ofh_rx_window_checker.h"
#include "ocudu/instrumentation/traces/ofh_traces.h"


using namespace ocudu;
using namespace ofh;


message_receiver_impl::message_receiver_impl(const message_receiver_config&  config,
                                             message_receiver_dependencies&& dependencies) :
  logger(*dependencies.logger),
  sector_id(config.sector),
  nof_symbols(config.nof_symbols),
  scs(config.scs),
  vlan_params(config.vlan_params),
  ul_prach_eaxc(config.prach_eaxc),
  ul_eaxc(config.ul_eaxc),
  warn_unreceived_frames_on_first_rx_message(config.warn_unreceived_frames ==
                                             warn_unreceived_ru_frames::after_traffic_detection),
  window_checker(*dependencies.window_checker),
  window_handler(*dependencies.window_handler),
  seq_id_checker(std::move(dependencies.seq_id_checker)),
  vlan_decoder(std::move(dependencies.eth_frame_decoder)),
  ecpri_decoder(std::move(dependencies.ecpri_decoder)),
  data_flow_uplink(std::move(dependencies.data_flow_uplink)),
  data_flow_prach(std::move(dependencies.data_flow_prach)),
  metrics_collector(config.are_metrics_enabled,
                    data_flow_uplink->get_metrics_collector(),
                    data_flow_prach->get_metrics_collector()),
  enable_log_warnings_for_lates(config.enable_log_warnings_for_lates)
{
  ocudu_assert(vlan_decoder, "Invalid VLAN decoder");
  ocudu_assert(ecpri_decoder, "Invalid eCPRI decoder");
  ocudu_assert(data_flow_uplink, "Invalid uplink IQ data flow");
  ocudu_assert(data_flow_prach, "Invalid uplink PRACH IQ data flow");
  ocudu_assert(seq_id_checker, "Invalid sequence id checker");
}


void message_receiver_impl::on_new_frame(ether::unique_rx_buffer buffer)
{
  process_new_frame(std::move(buffer));
}


void message_receiver_impl::process_new_frame(ether::unique_rx_buffer buffer)
{
  span<const uint8_t> payload = buffer.data();

  // Creates and starts the execution time measurer.

  // Creates and starts the execution time measurer.
  time_execution_measurer meas(metrics_collector.enabled());


  ether::vlan_frame_params eth_params;
  span<const uint8_t>      ecpri_pdu = vlan_decoder->decode(payload, eth_params);
  if (OCUDU_UNLIKELY(ecpri_pdu.empty() || should_ethernet_frame_be_filtered(eth_params))) {
    return;
  }


  ecpri::packet_parameters ecpri_params;
  span<const uint8_t>      ofh_pdu = ecpri_decoder->decode(ecpri_pdu, ecpri_params);
  if (OCUDU_UNLIKELY(ofh_pdu.empty() || should_ecpri_packet_be_filtered(ecpri_params))) {
    return;
  }

  // Command the rx windown handler to start logging unreceived RU frames.

  // Command the rx windown handler to start logging unreceived RU frames.
  if (OCUDU_UNLIKELY(warn_unreceived_frames_on_first_rx_message)) {
    window_handler.start_logging_unreceived_messages();
    warn_unreceived_frames_on_first_rx_message = false;
  }

  // Verify the sequence identifier.

  // Verify the sequence identifier.
  const ecpri::iq_data_parameters& ecpri_iq_params = std::get<ecpri::iq_data_parameters>(ecpri_params.type_params);
  unsigned                         eaxc            = ecpri_iq_params.pc_id;
  int nof_skipped_seq_id = seq_id_checker->update_and_compare_seq_id(eaxc, (ecpri_iq_params.seq_id >> 8));
  // Drop the message when it is from the past.
  // Drop the message when it is from the past.
  if (OCUDU_UNLIKELY(nof_skipped_seq_id < 0)) {
    metrics_collector.increase_dropped_messages();


    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet for eAxC value '{}' as sequence "
                "identifier field is from the past",
                sector_id,
                eaxc);
    return;
  }
  if (OCUDU_UNLIKELY(nof_skipped_seq_id > 0)) {
    metrics_collector.update_skipped_messages(nof_skipped_seq_id);


    log_conditional_warning(logger,
                            enable_log_warnings_for_lates,
                            "Sector#{}: potentially lost '{}' messages sent by the RU",
                            sector_id,
                            nof_skipped_seq_id);
  }


  std::optional<slot_symbol_point> slot_point = uplane_peeker::peek_slot_symbol_point(ofh_pdu, nof_symbols, scs);
  if (OCUDU_UNLIKELY(!slot_point)) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as the slot could not be peeked",
                sector_id);
    return;
  }

  // Fill the reception window statistics.

  // Fill the reception window statistics.
  window_checker.update_rx_window_statistics(*slot_point);

  // Peek the filter index and check that it is valid.

  // Peek the filter index and check that it is valid.
  std::optional<filter_index_type> filter_type = uplane_peeker::peek_filter_index(ofh_pdu);
  if (OCUDU_UNLIKELY(!filter_type)) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane message as the filter index could not be peeked",
                sector_id);
    return;
  }


  trace_point decode_tp = ofh_tracer.now();
  if (is_a_prach_message(*filter_type)) {
    data_flow_prach->decode_type1_message(eaxc, ofh_pdu);
    metrics_collector.update_prach_stats(meas.stop());
    ofh_tracer << trace_event("ofh_receiver_decode_prach", decode_tp);
    return;
  }


  data_flow_uplink->decode_type1_message(eaxc, ofh_pdu);
  metrics_collector.update_uplink_stats(meas.stop());
  ofh_tracer << trace_event("ofh_receiver_decode_data", decode_tp);
}


bool message_receiver_impl::should_ecpri_packet_be_filtered(const ecpri::packet_parameters& ecpri_params) const
{
  if (OCUDU_UNLIKELY(ecpri_params.header.msg_type != ecpri::message_type::iq_data)) {
    logger.info(
        "Sector#{}: dropped received Open Fronthaul User-Plane packet as decoded eCPRI message type is not for IQ data",
        sector_id);


    return true;
  }


  const auto& ecpri_iq_params = std::get<ecpri::iq_data_parameters>(ecpri_params.type_params);
  if (OCUDU_UNLIKELY(
          (std::find(ul_eaxc.begin(), ul_eaxc.end(), ecpri_iq_params.pc_id) == ul_eaxc.end()) &&
          (std::find(ul_prach_eaxc.begin(), ul_prach_eaxc.end(), ecpri_iq_params.pc_id) == ul_prach_eaxc.end()))) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as decoded eAxC value '{}' is not "
                "configured in reception",
                sector_id,
                ecpri_iq_params.pc_id);


    return true;
  }


  return false;
}


bool message_receiver_impl::should_ethernet_frame_be_filtered(const ether::vlan_frame_params& eth_params) const
{
  if (OCUDU_UNLIKELY(eth_params.mac_src_address != vlan_params.mac_src_address)) {
    logger.debug("Sector#{}: dropped received Ethernet frame as source MAC addresses do not match (detected={:02X}, "
                 "expected={:02X})",
                 sector_id,
                 span<const uint8_t>(eth_params.mac_src_address),
                 span<const uint8_t>(vlan_params.mac_src_address));


    return true;
  }


  if (OCUDU_UNLIKELY(eth_params.mac_dst_address != vlan_params.mac_dst_address)) {
    logger.debug(
        "Sector#{}: dropped received Ethernet frame as destination MAC addresses do not match match (detected={:02X}, "
        "expected={:02X})",
        sector_id,
        span<const uint8_t>(eth_params.mac_dst_address),
        span<const uint8_t>(vlan_params.mac_dst_address));


    return true;
  }


  if (OCUDU_UNLIKELY(eth_params.eth_type != vlan_params.eth_type)) {
    logger.info("Sector#{}: dropped received Ethernet frame as decoded Ethernet type is '{}' but expected '{}'",
                sector_id,
                eth_params.eth_type,
                vlan_params.eth_type);


    return true;
  }


  return false;
}
