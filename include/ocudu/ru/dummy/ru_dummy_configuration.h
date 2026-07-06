// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/dummy/ru_dummy_configuration.h  (48 lines)
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
#include "ocudu/ran/subcarrier_spacing.h"
#include "ocudu/ru/ru_error_notifier.h"
#include "ocudu/ru/ru_timing_notifier.h"
#include "ocudu/ru/ru_uplink_plane.h"
#include "ocudu/support/executors/task_executor.h"


namespace ocudu {

/// Collects the necessary parameters for the dummy radio unit.

/// Collects the necessary parameters for the dummy radio unit.
struct ru_dummy_configuration {
  /// Flag that enables (or not) metrics.
  /// Flag that enables (or not) metrics.
  bool are_metrics_enabled;
  /// Subcarrier spacing - Determines the slot timing.
  /// Subcarrier spacing - Determines the slot timing.
  subcarrier_spacing scs;
  /// Number of sectors.
  /// Number of sectors.
  unsigned nof_sectors;
  /// \brief Number of slots is notified in advance of the transmission time.
  ///
  /// Sets the maximum allowed processing delay in slots.
  /// \brief Number of slots is notified in advance of the transmission time.
  ///
  /// Sets the maximum allowed processing delay in slots.
  unsigned max_processing_delay_slots;
  /// DL processing processing delay in slots. See \ref ru_dummy_appconfig::dl_processing_delay for more information.
  /// DL processing processing delay in slots. See \ref ru_dummy_appconfig::dl_processing_delay for more information.
  unsigned dl_processing_delay;
  /// Time scaling, \ref ru_dummy_unit_config::time_scaling for more details.
  /// Time scaling, \ref ru_dummy_unit_config::time_scaling for more details.
  float time_scaling;
};

/// Collects the necessary dependencies for the dummy radio unit.

/// Collects the necessary dependencies for the dummy radio unit.
struct ru_dummy_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// Asynchronous task executor.
  /// Asynchronous task executor.
  task_executor* executor = nullptr;
  /// Radio Unit uplink plane received symbol notifier.
  /// Radio Unit uplink plane received symbol notifier.
  ru_uplink_plane_rx_symbol_notifier& symbol_notifier;
  /// Radio Unit timing notifier.
  /// Radio Unit timing notifier.
  ru_timing_notifier& timing_notifier;
  /// Radio Unit error notifier.
  /// Radio Unit error notifier.
  ru_error_notifier& error_notifier;
};


} // namespace ocudu
