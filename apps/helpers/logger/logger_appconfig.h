// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/logger/logger_appconfig.h
//
// Purpose (plain English):
//   Top-level application logging configuration, shared by all unit types.
//   Sets where logs go (stdout or a file), the catch-all log level for any
//   channel that doesn't have its own override, and the hex-dump size limit.
//
//   In practice, this is the YAML [log] block at the root of the config file.
//   Individual layers (MAC, RLC, PHY, etc.) can override the level in their
//   own sub-blocks; any layer that doesn't have its own entry uses all_level.
//
//   config_level is special — it controls logging of the config-parsing
//   machinery itself. Set to "none" normally; "debug" prints every YAML key
//   being parsed, which is useful when tracking down why a config isn't
//   taking effect.
// =============================================================================
#pragma once

#include "ocudu/ocudulog/logger.h"
#include <string>


namespace ocudu {

/// Configuration of logging functionalities.
struct logger_appconfig {
  /// Path to log file or "stdout" to print to console.
  std::string filename = "stdout"; ///< "stdout" or an absolute file path.
  /// Default log level for all layers.
  ocudulog::basic_levels all_level = ocudulog::basic_levels::warning; ///< Default for all layers.
  /// Generic log level assigned to library components without layer-specific level.
  ocudulog::basic_levels lib_level    = ocudulog::basic_levels::warning; ///< Library components without own level.
  ocudulog::basic_levels e2ap_level   = ocudulog::basic_levels::warning; ///< E2AP protocol.
  ocudulog::basic_levels config_level = ocudulog::basic_levels::none; ///< Config-parsing machinery; normally off.

  /// Maximum number of bytes to write when dumping hex arrays.
  int hex_max_size = 0; ///< Max bytes per hex dump (0 = none, -1 = unlimited).
};

} // namespace ocudu
