// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/du_high/rlc.h
//
// Purpose (plain English):
//   Generates JSON from RLC per-RB metrics: TX/RX bytes, AM retransmissions, UM discards.
//
//   Two entry points (consistent across all generators):
//     generate()        — returns a nlohmann::json object.
//     generate_string() — dumps that object to a UTF-8 string with optional indentation.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "external/nlohmann/json.hpp"
#include <string>


namespace ocudu {


struct rlc_metrics;


namespace app_helpers {
namespace json_generators {

/// Generates a nlohmann JSON object that codifies the given RLC metrics.

/// Generates a nlohmann JSON object that codifies the given RLC metrics.
nlohmann::json generate(const rlc_metrics& metrics);

/// Generates a string in JSON format that codifies the given RLC metrics.

/// Generates a string in JSON format that codifies the given RLC metrics.
std::string generate_string(const rlc_metrics& metrics, int indent = -1);


} // namespace json_generators
} // namespace app_helpers
} // namespace ocudu
