// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/cu_cp/cu_cp_json_helper.h
//
// Purpose (plain English):
//   Generates JSON from CU-CP metrics (UE counts, handover stats, connection metrics). Called by rlc_metrics_consumer_json and similar sinks when CU-CP metrics are enabled.
//
//   Two entry points (consistent across all generators):
//     generate()        — returns a nlohmann::json object.
//     generate_string() — dumps that object to a UTF-8 string with optional indentation.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "external/nlohmann/json.hpp"
#include "ocudu/cu_cp/cu_cp_metrics_notifier.h"
#include "ocudu/support/timers.h"
#include <string>


namespace ocudu {


struct cu_cp_metrics_report;


namespace app_helpers {
namespace json_generators {

/// Generates a nlohmann JSON object that codifies the given CU-CP metrics.

/// Generates a nlohmann JSON object that codifies the given CU-CP metrics.
nlohmann::json generate(const cu_cp_metrics_report& report);

/// Generates a string in JSON format that codifies the given CU-CP metrics.

/// Generates a string in JSON format that codifies the given CU-CP metrics.
std::string generate_string(const cu_cp_metrics_report& report, int indent = -1);


} // namespace json_generators
} // namespace app_helpers
} // namespace ocudu
