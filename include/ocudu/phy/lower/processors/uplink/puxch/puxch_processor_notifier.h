// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/puxch/puxch_processor_notifier.h  (40 lines)
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


struct lower_phy_rx_symbol_context;
struct resource_grid_context;
class shared_resource_grid;

/// \brief Lower physical layer PUxCH processor - Notifier interface.
///
/// Notifies a variety of PUxCH-related events such as requests outside the occasion window or overflows of PUxCH
/// requests.

/// \brief Lower physical layer PUxCH processor - Notifier interface.
///
/// Notifies a variety of PUxCH-related events such as requests outside the occasion window or overflows of PUxCH
/// requests.
class puxch_processor_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~puxch_processor_notifier() = default;

  /// \brief Notifies a PUxCH request outside the slot window.
  ///
  /// See \ref lower_phy_error_notifier::on_puxch_request_late for more information.
  /// \param[in] context PUxCH context.

  /// \brief Notifies a PUxCH request outside the slot window.
  ///
  /// See \ref lower_phy_error_notifier::on_puxch_request_late for more information.
  /// \param[in] context PUxCH context.
  virtual void on_puxch_request_late(const resource_grid_context& context) = 0;

  /// \brief Notifies the completion of the PUxCH request processing.
  ///
  /// See \ref lower_phy_error_notifier::on_puxch_request_late for more information.
  /// \param[in] grid     Received resource grid.
  /// \param[in] context  Received symbol context.
  /// \param[in] is_valid Set it to true if the resource grid data contains valid information. Otherwise, set it to
  /// false.

  /// \brief Notifies the completion of the PUxCH request processing.
  ///
  /// See \ref lower_phy_error_notifier::on_puxch_request_late for more information.
  /// \param[in] grid     Received resource grid.
  /// \param[in] context  Received symbol context.
  /// \param[in] is_valid Set it to true if the resource grid data contains valid information. Otherwise, set it to
  /// false.
  virtual void
  on_rx_symbol(const shared_resource_grid& grid, const lower_phy_rx_symbol_context& context, bool is_valid) = 0;
};


} // namespace ocudu
