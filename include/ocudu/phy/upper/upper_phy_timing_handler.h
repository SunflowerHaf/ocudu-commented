// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/upper_phy_timing_handler.h  (34 lines)
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


struct upper_phy_timing_context;

/// Upper physical layer handler to align timing boundaries.

/// Upper physical layer handler to align timing boundaries.
class upper_phy_timing_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~upper_phy_timing_handler() = default;

  /// \brief Handles a new TTI boundary event.
  ///
  /// \param[in] context Notification context.

  /// \brief Handles a new TTI boundary event.
  ///
  /// \param[in] context Notification context.
  virtual void handle_tti_boundary(const upper_phy_timing_context& context) = 0;

  /// \brief Handles a half slot (7th OFDM symbol) packet arrival.
  ///
  /// \param[in] context Notification context.

  /// \brief Handles a half slot (7th OFDM symbol) packet arrival.
  ///
  /// \param[in] context Notification context.
  virtual void handle_ul_half_slot_boundary(const upper_phy_timing_context& context) = 0;

  /// \brief Handles a full slot (14th OFDM symbol) packet arrival.
  ///
  /// \param[in] context Notification context.

  /// \brief Handles a full slot (14th OFDM symbol) packet arrival.
  ///
  /// \param[in] context Notification context.
  virtual void handle_ul_full_slot_boundary(const upper_phy_timing_context& context) = 0;
};


} // namespace ocudu
