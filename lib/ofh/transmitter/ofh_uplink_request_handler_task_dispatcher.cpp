// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_uplink_request_handler_task_dispatcher.cpp  (57 lines)
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

#include "ofh_uplink_request_handler_task_dispatcher.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/phy/support/shared_resource_grid.h"
#include "ocudu/support/rtsan.h"


using namespace ocudu;
using namespace ofh;


void uplink_request_handler_task_dispatcher::start()
{
  stop_manager.reset();
}


void uplink_request_handler_task_dispatcher::stop()
{
  stop_manager.stop();
}


void uplink_request_handler_task_dispatcher::handle_prach_occasion(const prach_buffer_context& context,
                                                                   shared_prach_buffer         buffer)
{
  // Do not process if stop was requested.
  // Do not process if stop was requested.
  auto token = stop_manager.get_token();
  if (OCUDU_UNLIKELY(token.is_stop_requested())) {
    return;
  }


  if (!executor.defer([context,
                       prach_buff = std::move(buffer),
                       this,
                       tk = std::move(token)]() mutable noexcept OCUDU_RTSAN_NONBLOCKING {
        uplink_handler.handle_prach_occasion(context, std::move(prach_buff));
      })) {
    logger.warning(
        "Sector#{}: failed to handle PRACH in the uplink request handler for slot '{}'", sector_id, context.slot);
  }
}


void uplink_request_handler_task_dispatcher::handle_new_uplink_slot(const resource_grid_context& context,
                                                                    const shared_resource_grid&  grid)
{
  // Do not process if stop was requested.
  // Do not process if stop was requested.
  auto token = stop_manager.get_token();
  if (OCUDU_UNLIKELY(token.is_stop_requested())) {
    return;
  }


  if (!executor.defer([context, rg = grid.copy(), this, tk = std::move(token)]() noexcept OCUDU_RTSAN_NONBLOCKING {
        uplink_handler.handle_new_uplink_slot(context, rg);
      })) {
    logger.warning(
        "Sector#{}: failed to handle uplink slot in the uplink request handler for slot '{}'", sector_id, context.slot);
  }
}
