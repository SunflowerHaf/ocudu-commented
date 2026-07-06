// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_uplink_request_handler_impl.h  (101 lines)
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


#include "../support/prach_context_repository.h"
#include "../support/uplink_context_repository.h"
#include "../support/uplink_notified_grid_symbol_repository.h"
#include "ofh_data_flow_cplane_scheduling_commands.h"
#include "ofh_tx_window_checker.h"
#include "ofh_uplink_request_handler_metrics_collector.h"
#include "ocudu/ofh/ethernet/ethernet_frame_pool.h"
#include "ocudu/ofh/serdes/ofh_cplane_message_properties.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_timing_parameters.h"
#include "ocudu/ofh/transmitter/ofh_uplink_request_handler.h"
#include "ocudu/ran/tdd/tdd_ul_dl_config.h"


namespace ocudu {
namespace ofh {

/// Uplink request handler implementation configuration.

/// Uplink request handler implementation configuration.
struct uplink_request_handler_impl_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// PRACH Contol-Plane enabled flag.
  /// PRACH Contol-Plane enabled flag.
  bool is_prach_cp_enabled;
  /// PRACH eAxC.
  /// PRACH eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> prach_eaxc;
  /// Uplink data eAxC.
  /// Uplink data eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_data_eaxc;
  /// Optional TDD configuration.
  /// Optional TDD configuration.
  std::optional<tdd_ul_dl_config_common> tdd_config;
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Subcarrier spacing.
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Uplink request processing time in microseconds.
  /// Uplink request processing time in microseconds.
  std::chrono::microseconds ul_processing_time;
  /// Transmission window timing parameters for delay management.
  /// Transmission window timing parameters for delay management.
  tx_window_timing_parameters tx_timing_params;
  /// If set to true, logs late events as warnings, otherwise as info.
  /// If set to true, logs late events as warnings, otherwise as info.
  bool enable_log_warnings_for_lates;
};

/// Uplink request handler implmentation dependencies.

/// Uplink request handler implmentation dependencies.
struct uplink_request_handler_impl_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// Error notifier.
  /// Error notifier.
  error_notifier& err_notifier;
  /// Uplink slot context repository.
  /// Uplink slot context repository.
  std::shared_ptr<uplink_context_repository> ul_slot_repo;
  /// Uplink PRACH context repository.
  /// Uplink PRACH context repository.
  std::shared_ptr<prach_context_repository> ul_prach_repo;
  /// Notified uplink grid symbol repository.
  /// Notified uplink grid symbol repository.
  std::shared_ptr<uplink_notified_grid_symbol_repository> notifier_symbol_repo;
  /// Data flow for Control-Plane scheduling commands.
  /// Data flow for Control-Plane scheduling commands.
  std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow;
  /// Ethernet frame pool.
  /// Ethernet frame pool.
  std::shared_ptr<ether::eth_frame_pool> frame_pool;
};

/// Open Fronthaul uplink request handler.

/// Open Fronthaul uplink request handler.
class uplink_request_handler_impl : public uplink_request_handler
{
public:
  uplink_request_handler_impl(const uplink_request_handler_impl_config&  config,
                              uplink_request_handler_impl_dependencies&& dependencies);

  // See interface for documentation.

  // See interface for documentation.
  void handle_prach_occasion(const prach_buffer_context& context, shared_prach_buffer buffer) override;

  // See interface for documentation.

  // See interface for documentation.
  void handle_new_uplink_slot(const resource_grid_context& context, const shared_resource_grid& grid) override;

  /// Returns the OTA symbol boundary notifier of this uplink request handler implementation.

  /// Returns the OTA symbol boundary notifier of this uplink request handler implementation.
  ota_symbol_boundary_notifier& get_ota_symbol_boundary_notifier() { return window_checker; }

  /// Returns the metrics collector of this uplink request handler implementation.

  /// Returns the metrics collector of this uplink request handler implementation.
  uplink_request_handler_metrics_collector& get_metrics_collector() { return metrics_collector; }


private:
  ocudulog::basic_logger&                                 logger;
  const bool                                              is_prach_cp_enabled;
  const cyclic_prefix                                     cp;
  const std::optional<tdd_ul_dl_config_common>            tdd_config;
  const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC>   prach_eaxc;
  const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC>   ul_eaxc;
  tx_window_checker                                       window_checker;
  std::shared_ptr<uplink_context_repository>              ul_slot_repo;
  std::shared_ptr<prach_context_repository>               ul_prach_repo;
  std::shared_ptr<uplink_notified_grid_symbol_repository> notifier_symbol_repo;
  std::unique_ptr<data_flow_cplane_scheduling_commands>   data_flow;
  std::shared_ptr<ether::eth_frame_pool>                  frame_pool;
  error_notifier&                                         err_notifier;
  uplink_request_handler_metrics_collector                metrics_collector;
  bool                                                    enable_log_warnings_for_lates;
};


} // namespace ofh
} // namespace ocudu
