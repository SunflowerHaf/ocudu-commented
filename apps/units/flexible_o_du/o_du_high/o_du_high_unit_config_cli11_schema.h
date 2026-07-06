// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_config_cli11_schema.h
//
// Purpose (plain English):
//   Aggregator that plugs the three O-DU High sub-configs (DU High, FAPI, E2)
//   into the CLI11 command-line/YAML parser used by the gNB. It provides two
//   inline helpers so that the top-level split_8 factory does not need to know
//   which sub-schemas exist:
//
//     * configure_cli11_with_o_du_high_config_schema — called once during
//       startup, registers every DU-High/FAPI/E2 field (their command-line
//       flag names, YAML keys, default values, type checkers) with the CLI11
//       App object. After this the parser knows the full schema.
//
//     * autoderive_o_du_high_parameters_after_parsing — called immediately
//       *after* the YAML has been parsed. Some fields are not set directly by
//       the user but derived from others (e.g. SSB position from the ARFCN,
//       or E2 endpoints from higher-level toggles). This runs those
//       derivations for the DU High and E2 pieces (FAPI has no derived
//       params, so it isn't called).
// =============================================================================

#pragma once


#include "du_high/du_high_config_cli11_schema.h"
#include "e2/o_du_high_e2_config_cli11_schema.h"
#include "fapi/fapi_config_cli11_schema.h"
#include "o_du_high_unit_config.h"
#include "CLI/CLI11.hpp"


namespace ocudu {

/// Configures the given CLI11 application with the O-DU high configuration schema.

/// \brief Registers every DU High + FAPI + E2 config field with the CLI11 parser.
///
/// After this call returns, the parser can read a YAML file (or a set of
/// command-line arguments) and write the values straight into \p unit_cfg.
/// Order does not matter functionally, but is kept consistent with the rest
/// of the codebase (DU High first, then FAPI, then E2).
///
/// \param app       The CLI11 application object to which we add options.
/// \param unit_cfg  The unit config struct that will receive the parsed values.
inline void configure_cli11_with_o_du_high_config_schema(CLI::App& app, o_du_high_unit_config& unit_cfg)
{
  configure_cli11_with_du_high_config_schema(app, unit_cfg.du_high_cfg);
  configure_cli11_with_fapi_config_schema(app, unit_cfg.fapi_cfg);
  configure_cli11_with_o_du_high_e2_config_schema(app, unit_cfg.e2_cfg);
}

/// Auto derive O-DU high parameters after the parsing.

/// \brief Fills in derived parameters after CLI11 has parsed the YAML/CLI.
///
/// Some config values are not entered directly by the user, but computed from
/// others once parsing is complete. For example, the DU High derives the SSB
/// numerology from the cell's ARFCN band; the E2 config derives connection
/// endpoints from the enable-toggles. FAPI has no such derivations, hence its
/// absence here.
inline void autoderive_o_du_high_parameters_after_parsing(CLI::App& app, o_du_high_unit_config& unit_cfg)
{
  autoderive_du_high_parameters_after_parsing(app, unit_cfg.du_high_cfg.config);
  autoderive_o_du_high_e2_parameters_after_parsing(unit_cfg.e2_cfg);
}


} // namespace ocudu
