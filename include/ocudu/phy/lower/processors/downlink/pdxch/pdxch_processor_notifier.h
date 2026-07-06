// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_notifier.h  (35 lines)
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


struct resource_grid_context;

/// \brief Lower physical layer PDxCH processor - Notifier interface.
///
/// Notifies a variety of PDxCH-related events such as requests outside the occasion window or overflows of PDxCH
/// requests.

/// \brief Lower physical layer PDxCH processor - Notifier interface.
///
/// Notifies a variety of PDxCH-related events such as requests outside the occasion window or overflows of PDxCH
/// requests.
class pdxch_processor_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~pdxch_processor_notifier() = default;

  /// \brief Notifies the unavailability of a downlink resource grid.
  ///
  /// This error happens in a sector when the resource grid for the processing slot is not available at the time when a
  /// symbol is modulated.
  ///
  /// The time window the lower physical layer can receive a resource grid for a slot starts with
  /// lower_phy_timing_notifier::on_tti_boundary() and finishes with the beginning of the processing of the first symbol
  /// within the slot.
  ///
  /// \param[in] context Context in which the resource grid is not available.
  /// \sa lower_phy_rg_handler::handle_resource_grid.

  /// \brief Notifies the unavailability of a downlink resource grid.
  ///
  /// This error happens in a sector when the resource grid for the processing slot is not available at the time when a
  /// symbol is modulated.
  ///
  /// The time window the lower physical layer can receive a resource grid for a slot starts with
  /// lower_phy_timing_notifier::on_tti_boundary() and finishes with the beginning of the processing of the first symbol
  /// within the slot.
  ///
  /// \param[in] context Context in which the resource grid is not available.
  /// \sa lower_phy_rg_handler::handle_resource_grid.
  virtual void on_pdxch_request_late(const resource_grid_context& context) = 0;
};


} // namespace ocudu
