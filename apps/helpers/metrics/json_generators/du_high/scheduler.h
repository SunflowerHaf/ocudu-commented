// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/du_high/scheduler.h
//
// Purpose (plain English):
//   Generates JSON from the per-UE scheduler report: DL/UL MCS, bitrate, HARQ ok/nok, CQI, RI, BSR, TA.
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


struct scheduler_metrics_report;


namespace app_helpers {
namespace json_generators {

/// Generates a nlohmann JSON object that codifies the given scheduler metrics.

/// Generates a nlohmann JSON object that codifies the given scheduler metrics.
nlohmann::json generate(const scheduler_metrics_report& metrics);

/// Generates a string in JSON format that codifies the given scheduler metrics.

/// Generates a string in JSON format that codifies the given scheduler metrics.
std::string generate_string(const scheduler_metrics_report& metrics, int indent = -1);


} // namespace json_generators
} // namespace app_helpers
} // namespace ocudu
