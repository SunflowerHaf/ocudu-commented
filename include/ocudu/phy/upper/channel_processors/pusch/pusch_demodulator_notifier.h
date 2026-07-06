// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pusch/pusch_demodulator_notifier.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <optional>


namespace ocudu {

/// PUSCH demodulator interface to notify the demodulation statistics of a codeword.

/// PUSCH demodulator interface to notify the demodulation statistics of a codeword.
class pusch_demodulator_notifier
{
public:
  /// Collects PUSCH demodulation statistics.
  /// Collects PUSCH demodulation statistics.
  struct demodulation_stats {
    /// Estimated Signal-to-Interference-plus-Noise Ratio (SINR) at the output of the equalizer.
    /// Estimated Signal-to-Interference-plus-Noise Ratio (SINR) at the output of the equalizer.
    std::optional<float> sinr_dB;
    /// Measured EVM.
    /// Measured EVM.
    std::optional<float> evm;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~pusch_demodulator_notifier() = default;

  /// \brief Notifies intermediate PUSCH demodulator statistics.
  /// \param i_symbol OFDM symbol index within the slot.
  /// \param stats    OFDM symbol statistics.

  /// \brief Notifies intermediate PUSCH demodulator statistics.
  /// \param i_symbol OFDM symbol index within the slot.
  /// \param stats    OFDM symbol statistics.
  virtual void on_provisional_stats(unsigned i_symbol, const demodulation_stats& stats) = 0;

  /// Notifies the end of PUSCH processing and the final demodulator statistics.

  /// Notifies the end of PUSCH processing and the final demodulator statistics.
  virtual void on_end_stats(const demodulation_stats& stats) = 0;
};


} // namespace ocudu
