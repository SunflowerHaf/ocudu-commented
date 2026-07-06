// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_config_validator.h
//
// Purpose (plain English):
//   Sanity-checks the parsed O-DU High config *before* the O-DU High is
//   constructed. Catches user configuration errors up front (e.g. a PRACH
//   frequency that doesn't fit the band, an invalid PDCCH aggregation level)
//   and prints friendly errors instead of crashing deep inside the RAN code
//   later.
//
//   Currently only the DU High branch has validators; FAPI and E2 rely on
//   their own CLI11-time type checks (which run automatically during parsing).
// =============================================================================

#pragma once


#include "du_high/du_high_config_validator.h"
#include "o_du_high_unit_config.h"


namespace ocudu {

/// Validates the given O-DU high configuration. Returns true on success, false otherwise.

/// \brief Runs all validators against the O-DU High config.
/// \return true if every check passes; false (with error printed) on failure.
inline bool validate_o_du_high_config(const o_du_high_unit_config& config)
{
  return validate_du_high_config(config.du_high_cfg.config);
}


} // namespace ocudu
