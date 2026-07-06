// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_transmitter_ota_symbol_task_dispatcher.h  (73 lines)
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


#include "ocudu/adt/span.h"
#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/rtsan.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {
namespace ofh {

/// OTA symbol task dispatcher for the transmitter.

/// OTA symbol task dispatcher for the transmitter.
class transmitter_ota_symbol_task_dispatcher : public ota_symbol_boundary_notifier, public operation_controller
{
public:
  transmitter_ota_symbol_task_dispatcher(unsigned                      sector_id_,
                                         ocudulog::basic_logger&       logger_,
                                         task_executor&                executor_,
                                         ota_symbol_boundary_notifier& dl_window_checker_,
                                         ota_symbol_boundary_notifier& ul_window_checker_,
                                         ota_symbol_boundary_notifier& msg_symbol_handler_) :
    sector_id(sector_id_),
    logger(logger_),
    executor(executor_),
    dl_window_checker(dl_window_checker_),
    ul_window_checker(ul_window_checker_),
    msg_symbol_handler(msg_symbol_handler_)
  {
  }

  // See interface for documentation.

  // See interface for documentation.
  void start() override { stop_manager.reset(); }

  // See interface for documentation.

  // See interface for documentation.
  void stop() override { stop_manager.stop(); }

  // See interface for documentation.

  // See interface for documentation.
  void on_new_symbol(const slot_symbol_point_context& symbol_point_context) override
  {
    auto token = stop_manager.get_token();
    if (OCUDU_UNLIKELY(token.is_stop_requested())) {
      return;
    }


    dl_window_checker.on_new_symbol(symbol_point_context);
    ul_window_checker.on_new_symbol(symbol_point_context);


    if (!executor.defer([this, symbol_point_context, tk = std::move(token)]() noexcept OCUDU_RTSAN_NONBLOCKING {
          msg_symbol_handler.on_new_symbol(symbol_point_context);
        })) {
      logger.warning(
          "Sector #{}: Failed to dispatch new symbol task in the message transmitter for slot '{}' and symbol '{}'",
          sector_id,
          symbol_point_context.symbol_point.get_slot(),
          symbol_point_context.symbol_point.get_symbol_index());
    }
  }


private:
  const unsigned                sector_id;
  ocudulog::basic_logger&       logger;
  task_executor&                executor;
  ota_symbol_boundary_notifier& dl_window_checker;
  ota_symbol_boundary_notifier& ul_window_checker;
  ota_symbol_boundary_notifier& msg_symbol_handler;
  rt_stop_event_source          stop_manager;
};


} // namespace ofh
} // namespace ocudu
