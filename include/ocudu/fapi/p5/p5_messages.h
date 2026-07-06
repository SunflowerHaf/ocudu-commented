// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p5/p5_messages.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/cell_config.h"
#include "ocudu/fapi/common/error_code.h"


namespace ocudu {
namespace fapi {

/// Param request message.

/// Param request message.
struct param_request {};

/// Param response message.

/// Param response message.
struct param_response {
  error_code_id error_code;
};

/// Config request message.

/// Config request message.
struct config_request {
  cell_configuration cell_cfg;
};

/// Config response message.

/// Config response message.
struct config_response {
  error_code_id error_code;
};

/// Start request message.

/// Start request message.
struct start_request {};

/// Start response message.

/// Start response message.
struct start_response {};

/// Stop request message.

/// Stop request message.
struct stop_request {};

/// Stop indication message.

/// Stop indication message.
struct stop_indication {};


} // namespace fapi
} // namespace ocudu
