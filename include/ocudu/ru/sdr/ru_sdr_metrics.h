// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/sdr/ru_sdr_metrics.h  (39 lines)
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
#include <limits>


namespace ocudu {

/// SDR Radio Unit sector metrics.

/// SDR Radio Unit sector metrics.
struct ru_sdr_sector_metrics {
  unsigned sector_id;
  float    tx_avg_power_dB;
  float    tx_peak_power_dB;
  float    tx_papr_dB;
  float    tx_clipping_prob = std::numeric_limits<double>::quiet_NaN();
  float    rx_avg_power_dB;
  float    rx_peak_power_dB;
  float    rx_papr_dB;
  double   rx_clipping_prob = std::numeric_limits<double>::quiet_NaN();
};

/// Radio metrics.

/// Radio metrics.
struct radio_metrics {
  unsigned late_count      = 0;
  unsigned underflow_count = 0;
  unsigned overflow_count  = 0;
};

/// SDR Radio Unit metrics.

/// SDR Radio Unit metrics.
struct ru_sdr_metrics {
  static_vector<ru_sdr_sector_metrics, MAX_CELLS_PER_DU> cells;
  radio_metrics                                          radio;
};


} // namespace ocudu
