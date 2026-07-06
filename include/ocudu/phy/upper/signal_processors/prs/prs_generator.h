// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/prs/prs_generator.h  (25 lines)
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


class resource_grid_writer;
struct prs_generator_configuration;

/// Positioning Reference Signals (PRS) generator interface.

/// Positioning Reference Signals (PRS) generator interface.
class prs_generator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~prs_generator() = default;

  /// \brief Generates Positioning Reference Signals (PRS) according to TS38.211 Section 7.4.1.7.
  /// \param[out] grid   Resource grid.
  /// \param[in]  config PRS transmission configuration.

  /// \brief Generates Positioning Reference Signals (PRS) according to TS38.211 Section 7.4.1.7.
  /// \param[out] grid   Resource grid.
  /// \param[in]  config PRS transmission configuration.
  virtual void generate(resource_grid_writer& grid, const prs_generator_configuration& config) = 0;
};


} // namespace ocudu
