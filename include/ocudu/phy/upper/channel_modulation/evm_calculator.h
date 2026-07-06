// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_modulation/evm_calculator.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/phy/upper/log_likelihood_ratio.h"
#include "ocudu/ran/sch/modulation_scheme.h"


namespace ocudu {

/// Error Vector Magnitude calculator.

/// Error Vector Magnitude calculator.
class evm_calculator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~evm_calculator() = default;

  /// \brief Calculates the EVM for a transmission.
  ///
  /// \param[in] soft_bits  The soft bits from the modulation demapper.
  /// \param[in] symbols    The complex-valued channel symbols, prior to the modulation demapper.
  /// \param[in] modulation The modulation scheme.
  /// \return The calculated EVM.
  /// \remark The size of \c soft_bits must be equal to the size of \c symbols times the number of bits per symbol
  /// corresponding to \c modulation.

  /// \brief Calculates the EVM for a transmission.
  ///
  /// \param[in] soft_bits  The soft bits from the modulation demapper.
  /// \param[in] symbols    The complex-valued channel symbols, prior to the modulation demapper.
  /// \param[in] modulation The modulation scheme.
  /// \return The calculated EVM.
  /// \remark The size of \c soft_bits must be equal to the size of \c symbols times the number of bits per symbol
  /// corresponding to \c modulation.
  virtual float
  calculate(span<const log_likelihood_ratio> soft_bits, span<const cf_t> symbols, modulation_scheme modulation) = 0;
};


} // namespace ocudu
