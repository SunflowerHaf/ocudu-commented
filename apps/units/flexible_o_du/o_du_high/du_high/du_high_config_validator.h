// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_high_config_validator.h
//
// Purpose (plain English):
//   Declares the single entry point for DU High configuration validation.
//   The implementation (in du_high_config_validator.cpp) runs ~1800 lines of
//   checks against the parsed config — cell bandwidth vs. PDCCH positions,
//   PRACH frequency vs. PUCCH boundary, PDSCH/PUSCH MCS limits, scheduler
//   parameters, NTN timing constraints, and many more. Any failure prints an
//   informative error and returns false so startup aborts cleanly.
// =============================================================================

#pragma once


#include "du_high_config.h"


namespace ocudu {

/// Validates the given DU high configuration. Returns true on success, false otherwise.

/// \brief Validates the complete DU High configuration.
/// \return true if all checks pass; false (with error printed to stdout) on failure.
bool validate_du_high_config(const du_high_unit_config& config);


} // namespace ocudu
