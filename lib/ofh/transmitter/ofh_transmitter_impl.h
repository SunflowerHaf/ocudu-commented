// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_transmitter_impl.h  (88 lines)
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


#include "ofh_downlink_handler_impl.h"
#include "ofh_message_transmitter_impl.h"
#include "ofh_transmitter_metrics_collector_impl.h"
#include "ofh_transmitter_ota_symbol_task_dispatcher.h"
#include "ofh_uplink_request_handler_impl.h"
#include "ofh_uplink_request_handler_task_dispatcher.h"
#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/transmitter/ofh_transmitter.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_configuration.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul transmitter implementation dependencies.

/// Open Fronthaul transmitter implementation dependencies.
struct transmitter_impl_dependencies {
  /// Log.
  /// Log.
  ocudulog::basic_logger* logger = nullptr;
  /// Error notifier.
  /// Error notifier.
  error_notifier* err_notifier = nullptr;
  /// Transmitter task executor.
  /// Transmitter task executor.
  task_executor* executor = nullptr;
  /// Downlink task executor.
  /// Downlink task executor.
  task_executor* dl_executor = nullptr;
  /// Data flow for downlink Control-Plane.
  /// Data flow for downlink Control-Plane.
  std::unique_ptr<data_flow_cplane_scheduling_commands> dl_df_cplane;
  /// Data flow for downlink User-Plane.
  /// Data flow for downlink User-Plane.
  std::unique_ptr<data_flow_uplane_downlink_data> dl_df_uplane;
  /// Data flow for uplink Control-Plane scheduling commands.
  /// Data flow for uplink Control-Plane scheduling commands.
  std::unique_ptr<data_flow_cplane_scheduling_commands> ul_df_cplane;
  /// Uplink slot context repository.
  /// Uplink slot context repository.
  std::shared_ptr<uplink_context_repository> ul_slot_repo;
  /// Uplink PRACH context repository.
  /// Uplink PRACH context repository.
  std::shared_ptr<prach_context_repository> ul_prach_repo;
  /// Notified uplink grid symbol repository.
  /// Notified uplink grid symbol repository.
  std::shared_ptr<uplink_notified_grid_symbol_repository> notifier_symbol_repo;
  /// Ethernet transmitter.
  /// Ethernet transmitter.
  std::unique_ptr<ether::transmitter> eth_transmitter;
  /// Ethernet frame pool downlink Control-Plane.
  /// Ethernet frame pool downlink Control-Plane.
  std::shared_ptr<ether::eth_frame_pool> frame_pool_dl_cp;
  /// Ethernet frame pool uplink Control-Plane.
  /// Ethernet frame pool uplink Control-Plane.
  std::shared_ptr<ether::eth_frame_pool> frame_pool_ul_cp;
  /// Ethernet frame pool downlink User-Plane.
  /// Ethernet frame pool downlink User-Plane.
  std::shared_ptr<ether::eth_frame_pool> frame_pool_dl_up;
};


class transmitter_impl : public transmitter, public operation_controller
{
public:
  transmitter_impl(const transmitter_config& config, transmitter_impl_dependencies&& dependencies);


  ~transmitter_impl() override { stop(); }

  // See interface for documentation.

  // See interface for documentation.
  void start() override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  // See interface for documentation.
  uplink_request_handler& get_uplink_request_handler() override;

  // See interface for documentation.

  // See interface for documentation.
  downlink_handler& get_downlink_handler() override;

  // See interface for documentation.

  // See interface for documentation.
  ota_symbol_boundary_notifier& get_ota_symbol_boundary_notifier() override;


  transmitter_metrics_collector* get_metrics_collector() override;


private:
  downlink_handler_impl                  dl_handler;
  uplink_request_handler_impl            ul_request_handler;
  uplink_request_handler_task_dispatcher ul_task_dispatcher;
  message_transmitter_impl               msg_transmitter;
  transmitter_ota_symbol_task_dispatcher ota_dispatcher;
  transmitter_metrics_collector_impl     metrics_collector;
};


} // namespace ofh
} // namespace ocudu
