// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_receiver_impl.h  (62 lines)
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


#include "ethernet_rx_buffer_pool.h"
#include "ethernet_rx_metrics_collector_impl.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ethernet/ethernet_controller.h"
#include "ocudu/ofh/ethernet/ethernet_receiver.h"
#include "ocudu/ofh/ethernet/ethernet_receiver_config.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {


class task_executor;


namespace ether {

/// Implementation for the Ethernet receiver.

/// Implementation for the Ethernet receiver.
class receiver_impl : public receiver, private receiver_operation_controller
{
  static constexpr unsigned BUFFER_SIZE = 9600;


public:
  receiver_impl(const receiver_config& config, task_executor& executor_, ocudulog::basic_logger& logger_);


  ~receiver_impl() override;

  // See interface for documentation.

  // See interface for documentation.
  receiver_operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  // See interface for documentation.
  receiver_metrics_collector* get_metrics_collector() override;


private:
  // See interface for documentation.
  // See interface for documentation.
  void start(frame_notifier& notifier_) override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;

  /// Main receiving loop.

  /// Main receiving loop.
  void receive_loop();

  /// Receives new Ethernet frames from the socket.
  ///
  /// \note This function will block until new frames become available.

  /// Receives new Ethernet frames from the socket.
  ///
  /// \note This function will block until new frames become available.
  void receive();


private:
  ocudulog::basic_logger&         logger;
  task_executor&                  executor;
  frame_notifier*                 notifier;
  int                             socket_fd = -1;
  rt_stop_event_source            stop_manager;
  ethernet_rx_buffer_pool         buffer_pool;
  receiver_metrics_collector_impl metrics_collector;
};


} // namespace ether
} // namespace ocudu
