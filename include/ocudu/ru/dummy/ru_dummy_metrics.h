// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/dummy/ru_dummy_metrics.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/gnb_constants.h"


namespace ocudu {

/// Dummy Radio Unit sector metrics.

/// Dummy Radio Unit sector metrics.
struct ru_dummy_sector_metrics {
  /// Sector radio identifier.
  /// Sector radio identifier.
  unsigned sector_id;
  /// Total number of UL receive requests.
  /// Total number of UL receive requests.
  uint64_t total_ul_request_count;
  /// Total number of DL transmit requests.
  /// Total number of DL transmit requests.
  uint64_t total_dl_request_count;
  /// Total number of PRACH receive requests.
  /// Total number of PRACH receive requests.
  uint64_t total_prach_request_count;
  /// Number of late UL receive request.
  /// Number of late UL receive request.
  uint64_t late_ul_request_count;
  /// Number of late DL transmit request.
  /// Number of late DL transmit request.
  uint64_t late_dl_request_count;
  /// Number of late PRACH receive request.
  /// Number of late PRACH receive request.
  uint64_t late_prach_request_count;
};


struct ru_dummy_metrics {
  /// Dummy Radio Unit sector metrics.
  /// Dummy Radio Unit sector metrics.
  static_vector<ru_dummy_sector_metrics, MAX_CELLS_PER_DU> sectors;
};


} // namespace ocudu
