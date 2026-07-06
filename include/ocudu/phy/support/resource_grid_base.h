// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/resource_grid_base.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

/// \brief Resource grid base interface.
///
/// Provides getters.

/// \brief Resource grid base interface.
///
/// Provides getters.
class resource_grid_base
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~resource_grid_base() = default;

  /// Gets the resource grid number of ports.

  /// Gets the resource grid number of ports.
  virtual unsigned get_nof_ports() const = 0;

  /// Gets the resource grid number of subcarriers.

  /// Gets the resource grid number of subcarriers.
  virtual unsigned get_nof_subc() const = 0;

  /// Gets the resource grid number of symbols.

  /// Gets the resource grid number of symbols.
  virtual unsigned get_nof_symbols() const = 0;
};


} // namespace ocudu
