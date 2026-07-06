// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/generator_helpers.h
//
// Purpose (plain English):
//   Two small facilities shared by every JSON metrics generator:
//
//   DEFAULT_JSON_INDENT — the indentation level (2 spaces) used when
//     serialising nlohmann::json objects to strings. All HTTP metric
//     responses use this to keep output human-readable.
//
//   to_json(nlohmann::json&, slot_point) — a nlohmann ADL hook that lets
//     slot_point values be embedded directly in JSON objects. It converts
//     the slot_point to its standard "SFN.slot" string representation.
// =============================================================================
#pragma once

#include "external/nlohmann/json.hpp"
#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// [Implementation defined] Default indentation size for the JSON metrics.
constexpr unsigned DEFAULT_JSON_INDENT = 2U;


inline void to_json(nlohmann::json& json, slot_point slot)
{
  json = fmt::format("{}", slot);
}

} // namespace ocudu
