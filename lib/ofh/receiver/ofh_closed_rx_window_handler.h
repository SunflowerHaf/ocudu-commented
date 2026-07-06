// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_closed_rx_window_handler.h  (106 lines)
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
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/ofh_uplane_rx_symbol_notifier.h"
#include "ocudu/ofh/receiver/ofh_receiver_metrics.h"
#include "ocudu/ofh/receiver/ofh_receiver_timing_parameters.h"
#include "ocudu/ofh/receiver/ofh_receiver_warn_unreceived_frames_parameters.h"
#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include "ocudu/ofh/timing/slot_symbol_point.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {


class task_executor;


namespace ofh {

/// Closed reception window handler configuration.

/// Closed reception window handler configuration.
struct closed_rx_window_handler_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// Time in number of symbols that the decoder needs to process an Open Fronthaul message. It delays closing the
  /// reception window.
  /// Time in number of symbols that the decoder needs to process an Open Fronthaul message. It delays closing the
  /// reception window.
  unsigned nof_symbols_to_process_uplink = 0;
  /// Open Fronthaul receive window parameters.
  /// Open Fronthaul receive window parameters.
  rx_window_timing_parameters rx_timing_params;
  /// Warn unreceived Open Fronthaul messages.
  /// Warn unreceived Open Fronthaul messages.
  warn_unreceived_ru_frames warn_unreceived_frames = warn_unreceived_ru_frames::after_traffic_detection;
};

/// Closed reception window handler dependencies.

/// Closed reception window handler dependencies.
struct closed_rx_window_handler_dependencies {
  ocudulog::basic_logger*                    logger   = nullptr;
  task_executor*                             executor = nullptr;
  std::shared_ptr<prach_context_repository>  prach_repo;
  std::shared_ptr<uplink_context_repository> uplink_repo;
  std::shared_ptr<uplane_rx_symbol_notifier> notifier;
};

/// Open Fronthaul closed reception window handler.

/// Open Fronthaul closed reception window handler.
class closed_rx_window_handler : public ota_symbol_boundary_notifier, public operation_controller
{
public:
  closed_rx_window_handler(const closed_rx_window_handler_config&  config,
                           closed_rx_window_handler_dependencies&& dependencies);


  void start() override { stop_manager.reset(); }


  void stop() override { stop_manager.stop(); }

  // See interface for documentation.

  // See interface for documentation.
  void on_new_symbol(const slot_symbol_point_context& symbol_point_context) override;

  /// Starts logging unreceived OFH messages.

  /// Starts logging unreceived OFH messages.
  void start_logging_unreceived_messages()
  {
    if (warn_unreceived_frames == warn_unreceived_ru_frames::after_traffic_detection && !log_unreceived_messages) {
      log_unreceived_messages = true;
    }
  }

  /// Collects the metrics of the closed reception window metrics.

  /// Collects the metrics of the closed reception window metrics.
  void collect_metrics(closed_rx_window_metrics& metrics);


private:
  /// \brief Handles the uplink context for the closed reception window given by symbol point.
  ///
  /// Pops an uplink context from the uplink repository and when the context is valid, notifies it using the User-Plane
  /// received symbol notifier.
  /// \brief Handles the uplink context for the closed reception window given by symbol point.
  ///
  /// Pops an uplink context from the uplink repository and when the context is valid, notifies it using the User-Plane
  /// received symbol notifier.
  void handle_uplink_context(slot_symbol_point symbol_point);

  /// \brief Handles the PRACH context for the closed reception window given by symbol point.
  ///
  /// Pops a PRACH context from the PRACH repository and when the context is valid, notifies it using the User-Plane
  /// received symbol notifier.

  /// \brief Handles the PRACH context for the closed reception window given by symbol point.
  ///
  /// Pops a PRACH context from the PRACH repository and when the context is valid, notifies it using the User-Plane
  /// received symbol notifier.
  void handle_prach_context(slot_symbol_point symbol_point);


private:
  /// \brief Notification delay of the resource grid or PRACH buffer in symbol units.
  ///
  /// This delay is calculated with the T4a_max parameter plus the number of symbols that takes to decode a received
  /// Open Fronthaul message.
  /// \brief Notification delay of the resource grid or PRACH buffer in symbol units.
  ///
  /// This delay is calculated with the T4a_max parameter plus the number of symbols that takes to decode a received
  /// Open Fronthaul message.
  const unsigned                             notification_delay_in_symbols;
  const unsigned                             sector_id;
  const warn_unreceived_ru_frames            warn_unreceived_frames;
  bool                                       log_unreceived_messages;
  ocudulog::basic_logger&                    logger;
  task_executor&                             executor;
  std::shared_ptr<prach_context_repository>  prach_repo;
  std::shared_ptr<uplink_context_repository> uplink_repo;
  std::shared_ptr<uplane_rx_symbol_notifier> notifier;
  /// Counts every symbol not received when reception window closes.
  /// Counts every symbol not received when reception window closes.
  std::atomic<unsigned> nof_missed_uplink_symbols;
  /// Counts every PRACH not received when the reception window closes.
  /// Counts every PRACH not received when the reception window closes.
  std::atomic<unsigned> nof_missed_prach_contexts;
  rt_stop_event_source  stop_manager;
};


} // namespace ofh
} // namespace ocudu
