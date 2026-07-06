// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_message_receiver_task_dispatcher.h  (78 lines)
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


#include "ofh_message_receiver.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/ofh/ethernet/ethernet_controller.h"
#include "ocudu/support/executors/task_executor.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul message receiver interface implementation that dispatches tasks to the actual receiver.

/// Open Fronthaul message receiver interface implementation that dispatches tasks to the actual receiver.
class ofh_message_receiver_task_dispatcher : public message_receiver, public operation_controller
{
public:
  ofh_message_receiver_task_dispatcher(ocudulog::basic_logger&          logger_,
                                       message_receiver&                msg_receiver_,
                                       task_executor&                   executor_,
                                       unsigned                         sector_,
                                       std::unique_ptr<ether::receiver> eth_receiver_) :
    logger(logger_),
    msg_receiver(msg_receiver_),
    executor(executor_),
    sector(sector_),
    eth_receiver(std::move(eth_receiver_))
  {
    ocudu_assert(eth_receiver, "Invalid Ethernet receiver");
  }

  // See interface for documentation.

  // See interface for documentation.
  void start() override
  {
    stop_manager.reset();
    eth_receiver->get_operation_controller().start(*this);
  }

  // See interface for documentation.

  // See interface for documentation.
  void stop() override
  {
    // Ethernet blocks until stop is completed.
    // Ethernet blocks until stop is completed.
    eth_receiver->get_operation_controller().stop();
    stop_manager.stop();
  }

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  // See interface for documentation.
  void on_new_frame(ether::unique_rx_buffer buffer) override
  {
    auto token = stop_manager.get_token();
    if (OCUDU_UNLIKELY(token.is_stop_requested())) {
      return;
    }


    if (!executor.defer([this, buff = std::move(buffer), tk = std::move(token)]() mutable {
          msg_receiver.on_new_frame(std::move(buff));
        })) {
      logger.warning("Failed to dispatch receiver task for sector#{}", sector);
    }
  }

  // See interface for the documentation.

  // See interface for the documentation.
  message_receiver_metrics_collector* get_metrics_collector() override { return msg_receiver.get_metrics_collector(); }


private:
  ocudulog::basic_logger&          logger;
  message_receiver&                msg_receiver;
  task_executor&                   executor;
  const unsigned                   sector;
  std::unique_ptr<ether::receiver> eth_receiver;
  rt_stop_event_source             stop_manager;
};


} // namespace ofh
} // namespace ocudu
