// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/resource_usage.h
//
// Purpose (plain English):
//   Generates JSON from process resource-usage metrics: CPU time (user/sys), memory (RSS, VMS), context switches.
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


struct resource_usage_metrics;


namespace app_helpers {
namespace json_generators {

/// Generates a nlohmann JSON object that codifies the given resource usage metrics.

/// Generates a nlohmann JSON object that codifies the given resource usage metrics.
nlohmann::json generate(const resource_usage_metrics& metrics);

/// Generates a string in JSON format that codifies the given resource usage metrics.

/// Generates a string in JSON format that codifies the given resource usage metrics.
std::string generate_string(const resource_usage_metrics& metrics, int indent = -1);


} // namespace json_generators
} // namespace app_helpers
} // namespace ocudu
