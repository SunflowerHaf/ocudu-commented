// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: fapi/fapi_logger_registrator.h
//
// Purpose (plain English):
//   Registers the "FAPI" log channel with the central logger service at
//   startup. The FAPI channel traces the MAC↔PHY message exchange: P5
//   messages during cell bring-up (PARAM.req/rsp, CONFIG.req/rsp,
//   START.req, STOP.req) and P7 messages every slot (DL_TTI.req,
//   UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind).
//
//   Setting fapi_level to "debug" in the YAML will log every single FAPI
//   message, which is extremely verbose but invaluable when diagnosing why
//   the physical layer is not behaving as the MAC expects.
// =============================================================================

#pragma once


#include "fapi_config.h"


namespace ocudu {

/// Registers the fapi loggers in the logger service.

/// Registers and configures the "FAPI" logger channel.
inline void register_fapi_loggers(const fapi_unit_config& log_cfg)
{
  // "true" = create the channel if it doesn't already exist (safe to call
  // multiple times; subsequent calls just adjust the level).
  auto& fapi_logger = ocudulog::fetch_basic_logger("FAPI", true);
  fapi_logger.set_level(log_cfg.fapi_level);
}


} // namespace ocudu
