// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/ofh/ru_ofh_configuration.h  (49 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ofh_sector_config.h"


namespace ocudu {


class ru_error_notifier;
class ru_timing_notifier;
class ru_uplink_plane_rx_symbol_notifier;
class task_executor;

/// Radio Unit configuration for the Open Fronthaul implementation.

/// Radio Unit configuration for the Open Fronthaul implementation.
struct ru_ofh_configuration {
  /// Individual Open Fronthaul sector configurations.
  /// Individual Open Fronthaul sector configurations.
  std::vector<ofh::sector_configuration> sector_configs;
  /// GPS Alpha - Valid value range: [0, 1.2288e7].
  /// GPS Alpha - Valid value range: [0, 1.2288e7].
  unsigned gps_Alpha;
  /// GPS Beta - Valid value range: [-32768, 32767].
  /// GPS Beta - Valid value range: [-32768, 32767].
  int gps_Beta;
  /// Busy waiting enabled flag.
  /// Busy waiting enabled flag.
  bool enable_busy_waiting = false;
};

/// Radio Unit dependencies for the Open Fronthaul implementation.

/// Radio Unit dependencies for the Open Fronthaul implementation.
struct ru_ofh_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger* logger = nullptr;
  /// Radio Unit timing notifier.
  /// Radio Unit timing notifier.
  ru_timing_notifier* timing_notifier = nullptr;
  /// Radio Unit error notifier.
  /// Radio Unit error notifier.
  ru_error_notifier* error_notifier = nullptr;
  /// Radio Unit received symbol notifier.
  /// Radio Unit received symbol notifier.
  ru_uplink_plane_rx_symbol_notifier* rx_symbol_notifier = nullptr;
  /// Realtime timing task executor.
  /// Realtime timing task executor.
  task_executor* rt_timing_executor = nullptr;

  /// Individual Open Fronthaul sector dependencies.

  /// Individual Open Fronthaul sector dependencies.
  std::vector<ofh::sector_dependencies> sector_dependencies;
};

/// Returns true if the given Open Fronthaul configuration is valid, otherwise false.

/// Returns true if the given Open Fronthaul configuration is valid, otherwise false.
bool is_valid_ru_ofh_config(const ru_ofh_configuration& config);


} // namespace ocudu
