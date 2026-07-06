// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_data_flow_cplane_scheduling_commands_task_dispatcher.h  (87 lines)
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
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/rtsan.h"
#include "ocudu/support/synchronization/stop_event.h"
#include <memory>


namespace ocudu {
namespace ofh {

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow task dispatcher implementation.

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow task dispatcher implementation.
class data_flow_cplane_downlink_task_dispatcher : public data_flow_cplane_scheduling_commands,
                                                  public operation_controller
{
public:
  data_flow_cplane_downlink_task_dispatcher(ocudulog::basic_logger&                               logger_,
                                            std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow_cplane_,
                                            task_executor&                                        executor_,
                                            unsigned                                              sector_id_) :
    logger(logger_), data_flow_cplane(std::move(data_flow_cplane_)), executor(executor_), sector_id(sector_id_)
  {
    ocudu_assert(data_flow_cplane, "Invalid data flow");
  }

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  // See interface for documentation.
  void start() override { stop_manager.reset(); }

  // See interface for documentation.

  // See interface for documentation.
  void stop() override { stop_manager.stop(); }

  // See interface for documentation.

  // See interface for documentation.
  void enqueue_section_type_1_message(const data_flow_cplane_type_1_context& context) override
  {
    // Do not process Control Plane if the stop was requested.
    // Do not process Control Plane if the stop was requested.
    auto token = stop_manager.get_token();
    if (OCUDU_UNLIKELY(token.is_stop_requested())) {
      return;
    }


    if (!executor.defer([this, context, tk = std::move(token)]() noexcept OCUDU_RTSAN_NONBLOCKING {
          data_flow_cplane->enqueue_section_type_1_message(context);
        })) {
      logger.warning(
          "Sector#{}: failed to dispatch Control-Plane type 1 message for slot '{}'", sector_id, context.slot);
    }
  }

  // See interface for documentation.

  // See interface for documentation.
  void enqueue_section_type_3_prach_message(const data_flow_cplane_scheduling_prach_context& context) override
  {
    // Do not process Control Plane if the stop was requested.
    // Do not process Control Plane if the stop was requested.
    auto token = stop_manager.get_token();
    if (OCUDU_UNLIKELY(token.is_stop_requested())) {
      return;
    }


    if (!executor.defer([this, context, tk = std::move(token)]() noexcept OCUDU_RTSAN_NONBLOCKING {
          data_flow_cplane->enqueue_section_type_3_prach_message(context);
        })) {
      logger.warning(
          "Sector#{}: failed to dispatch Control-Plane type 3 message for slot '{}'", sector_id, context.slot);
    }
  }

  // See interface for documentation.

  // See interface for documentation.
  data_flow_message_encoding_metrics_collector* get_metrics_collector() override
  {
    return data_flow_cplane->get_metrics_collector();
  }


private:
  ocudulog::basic_logger&                               logger;
  std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow_cplane;
  task_executor&                                        executor;
  const unsigned                                        sector_id;
  rt_stop_event_source                                  stop_manager;
};


} // namespace ofh
} // namespace ocudu
