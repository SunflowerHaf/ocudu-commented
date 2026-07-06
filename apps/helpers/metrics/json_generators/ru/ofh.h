// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/ru/ofh.h
//
// Purpose (plain English):
//   Generates JSON from Open Fronthaul metrics per sector: DL/UL timing early/late/on-time counts. Only relevant when OFH is the RU path (not split-8).
//
//   Two entry points (consistent across all generators):
//     generate()        — returns a nlohmann::json object.
//     generate_string() — dumps that object to a UTF-8 string with optional indentation.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "external/nlohmann/json.hpp"
#include "ocudu/adt/span.h"
#include "ocudu/ran/pci.h"
#include <string>


namespace ocudu {


namespace ofh {
struct metrics;
}


namespace app_helpers {
namespace json_generators {

/// Generates a nlohmann JSON object that codifies the given Open Fronthaul low metrics.

/// Generates a nlohmann JSON object that codifies the given Open Fronthaul low metrics.
nlohmann::json
generate(const ofh::metrics& metrics, span<const pci_t> pci_sector_map, std::chrono::nanoseconds symbol_duration);

/// Generates a string in JSON format that codifies the given Open Fronthaul low metrics.

/// Generates a string in JSON format that codifies the given Open Fronthaul low metrics.
std::string generate_string(const ofh::metrics&      metrics,
                            span<const pci_t>        pci_sector_map,
                            std::chrono::nanoseconds symbol_duration,
                            int                      indent = -1);


} // namespace json_generators
} // namespace app_helpers
} // namespace ocudu
