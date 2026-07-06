// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_data_flow_uplane_uplink_data_impl.cpp  (98 lines)
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

#include "ofh_data_flow_uplane_uplink_data_impl.h"
#include "../support/uplane_bound_check_helpers.h"
#include "ocudu/instrumentation/traces/ofh_traces.h"
#include "ocudu/ofh/serdes/ofh_message_decoder_properties.h"


using namespace ocudu;
using namespace ofh;


data_flow_uplane_uplink_data_impl::data_flow_uplane_uplink_data_impl(
    const data_flow_uplane_uplink_data_impl_config&  config,
    data_flow_uplane_uplink_data_impl_dependencies&& dependencies) :
  logger(*dependencies.logger),
  ul_cplane_context_repo(std::move(dependencies.ul_cplane_context_repo)),
  uplane_decoder(std::move(dependencies.uplane_decoder)),
  rx_symbol_writer(config.ul_eaxc, config.sector, *dependencies.logger, dependencies.ul_context_repo),
  notification_sender(*dependencies.logger, dependencies.ul_context_repo, dependencies.notifier),
  sector_id(config.sector),
  metrics_collector(config.are_metrics_enabled)
{
  ocudu_assert(ul_cplane_context_repo, "Invalid control plane repository");
  ocudu_assert(uplane_decoder, "Invalid User-Plane decoder");
}


void data_flow_uplane_uplink_data_impl::decode_type1_message(unsigned eaxc, span<const uint8_t> message)
{
  trace_point decode_tp = ofh_tracer.now();


  uplane_message_decoder_results results;
  if (!uplane_decoder->decode(results, message)) {
    metrics_collector.increase_dropped_messages();
    return;
  }
  ofh_tracer << trace_event("ofh_receiver_uplane_decode", decode_tp);


  if (should_uplane_packet_be_filtered(eaxc, results)) {
    metrics_collector.increase_dropped_messages();


    return;
  }


  if (!rx_symbol_writer.write_to_resource_grid(eaxc, results)) {
    metrics_collector.increase_dropped_messages();


    return;
  }


  notification_sender.notify_received_symbol(results.params.slot, results.params.symbol_id);
}


bool data_flow_uplane_uplink_data_impl::should_uplane_packet_be_filtered(
    unsigned                              eaxc,
    const uplane_message_decoder_results& results) const
{
  if (OCUDU_UNLIKELY(results.params.filter_index == filter_index_type::reserved ||
                     is_a_prach_message(results.params.filter_index))) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet for slot '{}' and symbol '{}' as decoded "
                "filter index value '{}' is not valid",
                sector_id,
                results.params.slot,
                results.params.symbol_id,
                to_value(results.params.filter_index));


    return true;
  }


  const uplane_message_params& params  = results.params;
  ul_cplane_context            context = ul_cplane_context_repo->get(params.slot, eaxc);

  // Check if the filter index is valid.

  // Check if the filter index is valid.
  if (OCUDU_UNLIKELY(params.filter_index != context.filter_index)) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as the expected filter index '{}' does "
                "not match with value '{}' for slot '{}', symbol '{}' and eAxC '{}'",
                sector_id,
                to_value(context.filter_index),
                to_value(params.filter_index),
                params.slot,
                params.symbol_id,
                eaxc);
    return true;
  }

  // Check if the symbol index is valid.

  // Check if the symbol index is valid.
  if (OCUDU_UNLIKELY(!is_symbol_index_in_cplane_valid(context, params.symbol_id))) {
    logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as the symbol index '{}' is invalid for "
                "slot '{}', and eAxC '{}'",
                sector_id,
                params.symbol_id,
                params.slot,
                eaxc);
    return true;
  }

  // Check if the PRB ranges are valid.

  // Check if the PRB ranges are valid.
  return !are_uplane_prb_fields_valid(results, context, sector_id, logger);
}
