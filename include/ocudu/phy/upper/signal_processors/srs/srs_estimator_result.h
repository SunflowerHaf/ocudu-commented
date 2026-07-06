// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/srs/srs_estimator_result.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/time_alignment_estimator/time_alignment_measurement.h"
#include "ocudu/ran/srs/srs_channel_matrix.h"
#include <optional>


namespace ocudu {

/// Sounding Reference Signals propagation channel estimation results.

/// Sounding Reference Signals propagation channel estimation results.
struct srs_estimator_result {
  /// \brief Wideband estimated channel matrix.
  ///
  /// The channel matrix is normalized by the noise variance, so that its Frobenius norm square gives a rough estimate
  /// of the SNR for the sounding reference signals.
  /// \note The SNR inferred from the channel matrix is only meant as a qualitative indicator of the SRS reception and
  /// does not provide meaningful information about the achievable throughput.
  /// \brief Wideband estimated channel matrix.
  ///
  /// The channel matrix is normalized by the noise variance, so that its Frobenius norm square gives a rough estimate
  /// of the SNR for the sounding reference signals.
  /// \note The SNR inferred from the channel matrix is only meant as a qualitative indicator of the SRS reception and
  /// does not provide meaningful information about the achievable throughput.
  srs_channel_matrix channel_matrix;
  /// Wideband energy per resource element (EPRE), in decibel.
  /// Wideband energy per resource element (EPRE), in decibel.
  std::optional<float> epre_dB;
  /// Wideband reference signal received power (RSRP), in decibel.
  /// Wideband reference signal received power (RSRP), in decibel.
  std::optional<float> rsrp_dB;
  /// Wideband measured noise variance as a linear quantity.
  /// Wideband measured noise variance as a linear quantity.
  std::optional<float> noise_variance;
  /// Measured time alignment.
  /// Measured time alignment.
  time_alignment_measurement time_alignment;
};


} // namespace ocudu
