// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/cu_cp/f1ap_du_context.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/gnb_du_id.h"
#include <string>


namespace ocudu {
namespace ocucp {

/// Context of the DU that has setup an F1 connection to the CU-CP.

/// Context of the DU that has setup an F1 connection to the CU-CP.
struct f1ap_du_context {
  gnb_du_id_t gnb_du_id = gnb_du_id_t::invalid;
  std::string gnb_du_name;
  uint8_t     gnb_du_rrc_version;
};


} // namespace ocucp
} // namespace ocudu
