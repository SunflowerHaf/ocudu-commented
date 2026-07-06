// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/lower_phy_baseband_metrics.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>
#include <optional>
#include <utility>


namespace ocudu {

/// \brief Clipping event counters.
///
/// It comprises of the number of clipped samples and the total number of processed samples.

/// \brief Clipping event counters.
///
/// It comprises of the number of clipped samples and the total number of processed samples.
struct clipping_counters {
  uint64_t nof_clipped_samples;
  uint64_t nof_processed_samples;


  bool operator==(const clipping_counters& other) const
  {
    return (nof_clipped_samples == other.nof_clipped_samples) && (nof_processed_samples == other.nof_processed_samples);
  }
  bool operator!=(const clipping_counters& other) const { return !operator==(other); }
};

/// Collects transmit or receive signal statistics.

/// Collects transmit or receive signal statistics.
struct lower_phy_baseband_metrics {
  /// Average power.
  /// Average power.
  float avg_power;
  /// Peak power.
  /// Peak power.
  float peak_power;
  /// Clipping counters.
  /// Clipping counters.
  std::optional<clipping_counters> clipping;
};


} // namespace ocudu
