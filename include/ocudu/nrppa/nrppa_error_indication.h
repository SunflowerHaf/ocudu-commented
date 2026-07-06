// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/nrppa/nrppa_error_indication.h  (20 lines)
//
// INTERFACE HEADER — include/ocudu/nrppa
// NRPPa interface headers: nrppa_message_handler and the positioning measurement request/response types used by the positioning sub-system.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cause/nrppa_cause.h"
#include "ocudu/ran/crit_diagnostics.h"
#include <optional>


namespace ocudu {
namespace ocucp {


struct nrppa_error_indication {
  nrppa_cause_t                     cause;
  std::optional<crit_diagnostics_t> crit_diagnostics;
};


} // namespace ocucp
} // namespace ocudu
