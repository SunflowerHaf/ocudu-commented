// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_receiver_impl.h  (106 lines)
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


#include "../support/uplink_context_repository.h"
#include "ofh_closed_rx_window_handler.h"
#include "ofh_message_receiver_impl.h"
#include "ofh_message_receiver_task_dispatcher.h"
#include "ofh_receiver_controller.h"
#include "ofh_receiver_metrics_collector_impl.h"
#include "ofh_rx_symbol_reorderer.h"
#include "ofh_rx_window_checker.h"
#include "ocudu/ofh/receiver/ofh_receiver.h"
#include "ocudu/ofh/receiver/ofh_receiver_configuration.h"


namespace ocudu {


class task_executor;


namespace ofh {

/// Open Fronthaul receiver implementation dependencies.

/// Open Fronthaul receiver implementation dependencies.
struct receiver_impl_dependencies {
  /// Message receiver dependencies.
  /// Message receiver dependencies.
  struct message_rx_dependencies {
    /// Logger.
    /// Logger.
    ocudulog::basic_logger* logger = nullptr;
    /// eCPRI packet decoder.
    /// eCPRI packet decoder.
    std::unique_ptr<ecpri::packet_decoder> ecpri_decoder;
    /// Ethernet frame decoder.
    /// Ethernet frame decoder.
    std::unique_ptr<ether::vlan_frame_decoder> eth_frame_decoder;
    /// User-Plane uplink data flow.
    /// User-Plane uplink data flow.
    std::unique_ptr<data_flow_uplane_uplink_data> data_flow_uplink;
    /// User-Plane uplink PRACH data flow.
    /// User-Plane uplink PRACH data flow.
    std::unique_ptr<data_flow_uplane_uplink_prach> data_flow_prach;
    /// Sequence id checker.
    /// Sequence id checker.
    std::unique_ptr<sequence_id_checker> seq_id_checker;
  };


  struct close_rx_window_dependencies {
    std::shared_ptr<prach_context_repository>  prach_repo;
    std::shared_ptr<uplink_context_repository> uplink_repo;
    std::shared_ptr<uplane_rx_symbol_notifier> notifier;
  };

  /// Logger.

  /// Logger.
  ocudulog::basic_logger* logger = nullptr;
  /// Task executor.
  /// Task executor.
  task_executor* executor = nullptr;
  /// Message receiver dependencies.
  /// Message receiver dependencies.
  message_rx_dependencies msg_rx_dependencies;
  /// Closed reception window handler dependencies.
  /// Closed reception window handler dependencies.
  close_rx_window_dependencies window_handler_dependencies;
  /// Received symbol reorderer.
  /// Received symbol reorderer.
  std::shared_ptr<rx_symbol_reorderer> symbol_reorderer;
  /// Ethernet receiver.
  /// Ethernet receiver.
  std::unique_ptr<ether::receiver> eth_receiver;
};

/// OTA symbol boundary dispatcher for the receiver.

/// OTA symbol boundary dispatcher for the receiver.
class ota_symbol_boundary_dispatcher : public ota_symbol_boundary_notifier
{
  std::vector<ota_symbol_boundary_notifier*> handlers;


public:
  ota_symbol_boundary_dispatcher(std::vector<ota_symbol_boundary_notifier*> handlers_) : handlers(std::move(handlers_))
  {
  }

  // See interface for documentation

  // See interface for documentation
  void on_new_symbol(const slot_symbol_point_context& symbol_point_context) override;
};

/// \brief Open Fronthaul receiver.
///
/// The Open Fronthaul receiver that groups and owns all the uplink related classes.

/// \brief Open Fronthaul receiver.
///
/// The Open Fronthaul receiver that groups and owns all the uplink related classes.
class receiver_impl : public receiver
{
public:
  receiver_impl(const receiver_config& config, receiver_impl_dependencies&& dependencies);


  ~receiver_impl() override { get_operation_controller().stop(); }

  // See interface for documentation.

  // See interface for documentation.
  ota_symbol_boundary_notifier* get_ota_symbol_boundary_notifier() override;

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override;

  // See interface for documentation.

  // See interface for documentation.
  receiver_metrics_collector* get_metrics_collector() override;


private:
  std::shared_ptr<rx_symbol_reorderer> symbol_reorderer;
  closed_rx_window_handler             closed_window_handler;
  rx_window_checker                    window_checker;
  ota_symbol_boundary_dispatcher       symbol_boundary_dispatcher;
  message_receiver_impl                msg_receiver;
  receiver_metrics_collector_impl      metrics_collector;
  ofh_message_receiver_task_dispatcher rcv_task_dispatcher;
  receiver_controller                  ctrl;
};


} // namespace ofh
} // namespace ocudu
