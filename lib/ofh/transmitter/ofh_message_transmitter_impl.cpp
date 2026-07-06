// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_message_transmitter_impl.cpp  (125 lines)
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

#include "ofh_message_transmitter_impl.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/instrumentation/traces/ofh_traces.h"


using namespace ocudu;
using namespace ofh;


message_transmitter_impl::message_transmitter_impl(ocudulog::basic_logger&                logger_,
                                                   const tx_window_timing_parameters&     timing_params_,
                                                   bool                                   are_metrics_enabled,
                                                   std::unique_ptr<ether::transmitter>    transmitter,
                                                   std::shared_ptr<ether::eth_frame_pool> pool_dl_cp_,
                                                   std::shared_ptr<ether::eth_frame_pool> pool_ul_cp_,
                                                   std::shared_ptr<ether::eth_frame_pool> pool_dl_up_) :
  logger(logger_),
  pool_dl_cp(std::move(pool_dl_cp_)),
  pool_ul_cp(std::move(pool_ul_cp_)),
  pool_dl_up(std::move(pool_dl_up_)),
  eth_transmitter(std::move(transmitter)),
  metrics_collector(are_metrics_enabled),
  timing_params(timing_params_)
{
  ocudu_assert(eth_transmitter, "Invalid Ethernet transmitter");
  ocudu_assert(pool_dl_cp, "Invalid Control-Plane downlink frame pool");
  ocudu_assert(pool_ul_cp, "Invalid Control-Plane uplink frame pool");
  ocudu_assert(pool_dl_up, "Invalid User-Plane downlink frame pool");
}


void message_transmitter_impl::transmit_frame_burst(span<span<const uint8_t>> frame_burst)
{
  if (frame_burst.empty()) {
    return;
  }


  eth_transmitter->send(frame_burst);


  if (OCUDU_UNLIKELY(logger.debug.enabled())) {
    logger.debug("Sending an Ethernet frame burst of size '{}'", frame_burst.size());
  }
}


void message_transmitter_impl::enqueue_messages_into_burst(
    const ether::frame_pool_interval&                                    interval,
    ofh::message_type                                                    type,
    ofh::data_direction                                                  direction,
    static_vector<ether::scoped_frame_buffer, ether::MAX_TX_BURST_SIZE>& read_frames,
    std::shared_ptr<ether::eth_frame_pool>&                              pool)
{
  trace_point pool_access_tp = ofh_tracer.now();


  unsigned prev_size = read_frames.size();
  pool->enqueue_pending_into_burst(interval, read_frames);


  ofh_tracer << trace_event("ofh_tx_pool_access", pool_access_tp);


  if ((read_frames.size() - prev_size) == 0) {
    return;
  }


  if (OCUDU_UNLIKELY(logger.debug.enabled())) {
    logger.debug("Enqueueing '{}' frame(s) of type '{}-{}' in interval '{}_{}':{}_{} for tx burst",
                 read_frames.size() - prev_size,
                 (type == message_type::control_plane) ? "control-plane" : "user-plane",
                 (direction == data_direction::downlink) ? "downlink" : "uplink",
                 interval.start.get_slot(),
                 interval.start.get_symbol_index(),
                 interval.end.get_slot(),
                 interval.end.get_symbol_index());
  }
}


void message_transmitter_impl::on_new_symbol(const slot_symbol_point_context& symbol_point_context)
{
  // Creates and starts the execution time measurer.
  // Creates and starts the execution time measurer.
  time_execution_measurer meas(metrics_collector.enabled());


  trace_point                                                         tp = ofh_tracer.now();
  static_vector<ether::scoped_frame_buffer, ether::MAX_TX_BURST_SIZE> read_frames;

  // Enqueue pending DL Control-Plane messages.

  // Enqueue pending DL Control-Plane messages.
  ether::frame_pool_interval interval_cp_dl{symbol_point_context.symbol_point + timing_params.sym_cp_dl_end,
                                            symbol_point_context.symbol_point + timing_params.sym_cp_dl_start};
  enqueue_messages_into_burst(
      interval_cp_dl, message_type::control_plane, data_direction::downlink, read_frames, pool_dl_cp);

  // Enqueue pending UL Control-Plane messages.

  // Enqueue pending UL Control-Plane messages.
  ether::frame_pool_interval interval_cp_ul{symbol_point_context.symbol_point + timing_params.sym_cp_ul_end,
                                            symbol_point_context.symbol_point + timing_params.sym_cp_ul_start};
  enqueue_messages_into_burst(
      interval_cp_ul, message_type::control_plane, data_direction::uplink, read_frames, pool_ul_cp);

  // Enqueue pending User-Plane messages.

  // Enqueue pending User-Plane messages.
  ether::frame_pool_interval interval_up{symbol_point_context.symbol_point + timing_params.sym_up_dl_end,
                                         symbol_point_context.symbol_point + timing_params.sym_up_dl_start};
  enqueue_messages_into_burst(interval_up, message_type::user_plane, data_direction::downlink, read_frames, pool_dl_up);

  // Construct burst of byte buffers ready to be transmitted.

  // Construct burst of byte buffers ready to be transmitted.
  static_vector<span<const uint8_t>, ether::MAX_TX_BURST_SIZE> frame_burst;


  for (const auto& frame : read_frames) {
    frame_burst.emplace_back(frame->data());
  }

  // Transmit the data.

  // Transmit the data.
  trace_point tp_ether = ofh_tracer.now();
  transmit_frame_burst(frame_burst);


  ofh_tracer << trace_event("ofh_ether_tx", tp_ether);
  ofh_tracer << trace_event("ofh_message_transmitter", tp);


  metrics_collector.update_stats(meas.stop());
}


ether::transmitter& message_transmitter_impl::get_ethernet_transmitter()
{
  return *eth_transmitter;
}


message_transmitter_metrics_collector& message_transmitter_impl::get_metrics_collector()
{
  return metrics_collector;
}
