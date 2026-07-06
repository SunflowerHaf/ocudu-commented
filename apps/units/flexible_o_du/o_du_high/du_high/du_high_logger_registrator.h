// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_high_logger_registrator.h
//
// Purpose (plain English):
//   Registers every log channel used by the DU High with the central logger
//   service and applies the user's requested log levels. Called once during
//   startup, before the DU High is constructed.
//
//   Channels registered:
//     DU, DU-MNG, UE-MNG — DU-layer control and UE management (one level).
//     MAC, SCHED          — Medium Access Control + scheduler (one level).
//     RLC                 — Radio Link Control layer.
//     DU-F1               — F1AP signalling between the DU and the CU-CP.
//     DU-F1-U             — F1-U user-plane tunnels.
//     GTPU                — GTP-U protocol layer.
// =============================================================================

#pragma once


#include "du_high_config.h"


namespace ocudu {

/// Registers the DU high loggers in the logger service.

/// \brief Registers and configures all DU High logger channels.
///
/// Must be called before any DU High component tries to log — the logger
/// service does not create channels on demand, so logging before registration
/// would silently drop messages.
inline void register_du_high_loggers(const du_high_unit_logger_config& log_cfg)
{
  // DU, DU-MNG (DU manager), and UE-MNG (UE manager) share one log level.
  for (const auto& id : {"DU", "DU-MNG", "UE-MNG"}) {
    auto& du_logger = ocudulog::fetch_basic_logger(id, false);
    du_logger.set_level(log_cfg.du_level);
    du_logger.set_hex_dump_max_size(log_cfg.hex_max_size);
  }


  // MAC and SCHED are created with "true" (create-if-missing). They tend
  // to be fetched earlier than other channels during init.
  for (const auto& id : {"MAC", "SCHED"}) {
    auto& mac_logger = ocudulog::fetch_basic_logger(id, true);
    mac_logger.set_level(log_cfg.mac_level);
    mac_logger.set_hex_dump_max_size(log_cfg.hex_max_size);
  }


  // RLC — Radio Link Control (segmentation, ARQ, header compression).
  auto& rlc_logger = ocudulog::fetch_basic_logger("RLC", false);
  rlc_logger.set_level(log_cfg.rlc_level);
  rlc_logger.set_hex_dump_max_size(log_cfg.hex_max_size);


  // DU-F1 — F1AP control-plane messages (cell setup, UE context, handover).
  auto& du_f1ap_logger = ocudulog::fetch_basic_logger("DU-F1", false);
  du_f1ap_logger.set_level(log_cfg.f1ap_level);
  du_f1ap_logger.set_hex_dump_max_size(log_cfg.hex_max_size);


  // DU-F1-U — GTP-U user-plane tunnels over F1.
  auto& f1u_logger = ocudulog::fetch_basic_logger("DU-F1-U", false);
  f1u_logger.set_level(log_cfg.f1u_level);
  f1u_logger.set_hex_dump_max_size(log_cfg.hex_max_size);


  // GTPU — the GTP-U protocol layer itself (tunnel management, TEID handling).
  auto& gtpu_logger = ocudulog::fetch_basic_logger("GTPU", false);
  gtpu_logger.set_level(log_cfg.gtpu_level);
  gtpu_logger.set_hex_dump_max_size(log_cfg.hex_max_size);
}


} // namespace ocudu
