// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_message_transmitter_impl.h  (66 lines)
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

#pragma once


#include "ofh_message_transmitter_metrics_collector.h"
#include "ocudu/ofh/ethernet/ethernet_frame_pool.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter.h"
#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_timing_parameters.h"


namespace ocudu {
namespace ofh {

/// \brief Transmits enqueued Open Fronthaul messages through an Ethernet transmitter.
///
/// Message transmission is managed according the given transmission window.

/// \brief Transmits enqueued Open Fronthaul messages through an Ethernet transmitter.
///
/// Message transmission is managed according the given transmission window.
class message_transmitter_impl : public ota_symbol_boundary_notifier
{
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// Downlink Control-Plane ethernet frame pool.
  /// Downlink Control-Plane ethernet frame pool.
  std::shared_ptr<ether::eth_frame_pool> pool_dl_cp;
  /// Uplink Control-Plane ethernet frame pool.
  /// Uplink Control-Plane ethernet frame pool.
  std::shared_ptr<ether::eth_frame_pool> pool_ul_cp;
  /// Downlink User-Plane ethernet frame pool.
  /// Downlink User-Plane ethernet frame pool.
  std::shared_ptr<ether::eth_frame_pool> pool_dl_up;
  /// Ethernet transmitter.
  /// Ethernet transmitter.
  std::unique_ptr<ether::transmitter> eth_transmitter;
  /// Metrics collector.
  /// Metrics collector.
  message_transmitter_metrics_collector metrics_collector;
  /// Internal representation of timing parameters.
  /// Internal representation of timing parameters.
  const tx_window_timing_parameters timing_params;


public:
  message_transmitter_impl(ocudulog::basic_logger&                logger_,
                           const tx_window_timing_parameters&     timing_params_,
                           bool                                   are_metrics_enabled,
                           std::unique_ptr<ether::transmitter>    eth_transmitter,
                           std::shared_ptr<ether::eth_frame_pool> pool_dl_cp_,
                           std::shared_ptr<ether::eth_frame_pool> pool_ul_cp_,
                           std::shared_ptr<ether::eth_frame_pool> pool_dl_up_);

  // See interface for documentation.

  // See interface for documentation.
  void on_new_symbol(const slot_symbol_point_context& symbol_point_context) override;

  /// Returns the Ethernet transmitter of this Open Fronthaul message transmitter.

  /// Returns the Ethernet transmitter of this Open Fronthaul message transmitter.
  ether::transmitter& get_ethernet_transmitter();

  /// Returns the metrics collector of this message transmitter implementation.

  /// Returns the metrics collector of this message transmitter implementation.
  message_transmitter_metrics_collector& get_metrics_collector();


private:
  /// Transmits the given frame burst.
  /// Transmits the given frame burst.
  void transmit_frame_burst(span<span<const uint8_t>> frame_burst);

  /// Enqueues pending frames that match the given interval into the output buffer.

  /// Enqueues pending frames that match the given interval into the output buffer.
  void enqueue_messages_into_burst(const ether::frame_pool_interval&                                    interval,
                                   ofh::message_type                                                    type,
                                   ofh::data_direction                                                  direction,
                                   static_vector<ether::scoped_frame_buffer, ether::MAX_TX_BURST_SIZE>& frame_burst,
                                   std::shared_ptr<ether::eth_frame_pool>&                              pool);
};


} // namespace ofh
} // namespace ocudu
