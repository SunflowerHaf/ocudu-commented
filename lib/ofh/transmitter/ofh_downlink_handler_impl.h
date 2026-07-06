// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_downlink_handler_impl.h  (99 lines)
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


#include "ofh_data_flow_cplane_scheduling_commands.h"
#include "ofh_data_flow_uplane_downlink_data.h"
#include "ofh_downlink_handler_metrics_collector.h"
#include "ofh_tx_window_checker.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/ofh/ethernet/ethernet_frame_pool.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/transmitter/ofh_downlink_handler.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_configuration.h"
#include "ocudu/ran/tdd/tdd_ul_dl_config.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {
namespace ofh {

/// Downlink handler implementation configuration.

/// Downlink handler implementation configuration.
struct downlink_handler_impl_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// Downlink eAxCs.
  /// Downlink eAxCs.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> dl_eaxc;
  /// Optional TDD configuration.
  /// Optional TDD configuration.
  std::optional<tdd_ul_dl_config_common> tdd_config;
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Subcarrier spacing.
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Downlink processing time in microseconds.
  /// Downlink processing time in microseconds.
  std::chrono::microseconds dl_processing_time;
  /// Transmission window timing parameters for delay management.
  /// Transmission window timing parameters for delay management.
  tx_window_timing_parameters tx_timing_params;
  /// If set to true, logs late events as warnings, otherwise as info.
  /// If set to true, logs late events as warnings, otherwise as info.
  bool enable_log_warnings_for_lates;
};

/// Downlink handler implementation dependencies.

/// Downlink handler implementation dependencies.
struct downlink_handler_impl_dependencies {
  /// Logger
  /// Logger
  ocudulog::basic_logger& logger;
  /// Error notifier.
  /// Error notifier.
  error_notifier& err_notifier;
  /// Data flow for Control-Plane.
  /// Data flow for Control-Plane.
  std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow_cplane;
  /// Data flow for User-Plane.
  /// Data flow for User-Plane.
  std::unique_ptr<data_flow_uplane_downlink_data> data_flow_uplane;
  /// Ethernet frame pool downlink Control-Plane.
  /// Ethernet frame pool downlink Control-Plane.
  std::shared_ptr<ether::eth_frame_pool> frame_pool_dl_cp;
  /// Ethernet frame pool downlink User-Plane.
  /// Ethernet frame pool downlink User-Plane.
  std::shared_ptr<ether::eth_frame_pool> frame_pool_dl_up;
};

/// Open Fronthaul downlink handler implementation.

/// Open Fronthaul downlink handler implementation.
class downlink_handler_impl : public downlink_handler, public operation_controller
{
public:
  downlink_handler_impl(const downlink_handler_impl_config& config, downlink_handler_impl_dependencies&& dependencies);


  ~downlink_handler_impl() override { stop(); }

  // See interface for documentation.

  // See interface for documentation.
  void start() override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;

  // See interface for documentation.

  // See interface for documentation.
  void handle_dl_data(const resource_grid_context& context, const shared_resource_grid& grid) override;

  /// Returns the OTA symbol boundary notifier of this downlink handler implementation.

  /// Returns the OTA symbol boundary notifier of this downlink handler implementation.
  ota_symbol_boundary_notifier& get_ota_symbol_boundary_notifier() { return window_checker; }

  /// Returns the metrics collector of this downlink handler implementation.

  /// Returns the metrics collector of this downlink handler implementation.
  downlink_handler_metrics_collector& get_metrics_collector() { return metrics_collector; }


private:
  const unsigned                                        sector_id;
  ocudulog::basic_logger&                               logger;
  const cyclic_prefix                                   cp;
  const std::optional<tdd_ul_dl_config_common>          tdd_config;
  const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> dl_eaxc;
  tx_window_checker                                     window_checker;
  std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow_cplane;
  std::unique_ptr<data_flow_uplane_downlink_data>       data_flow_uplane;
  std::shared_ptr<ether::eth_frame_pool>                frame_pool_dl_cp;
  std::shared_ptr<ether::eth_frame_pool>                frame_pool_dl_up;
  error_notifier&                                       err_notifier;
  downlink_handler_metrics_collector                    metrics_collector;
  bool                                                  enable_log_warnings_for_lates;
  rt_stop_event_source                                  stop_control;
};


} // namespace ofh
} // namespace ocudu
