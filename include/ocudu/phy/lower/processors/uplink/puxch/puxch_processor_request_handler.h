// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/puxch/puxch_processor_request_handler.h  (32 lines)
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
class shared_resource_grid;

/// \brief Lower physical layer PUxCH processor - Request handler interface.
///
/// Provides an interface for requesting the capture and demodulation of PUxCH occasions.

/// \brief Lower physical layer PUxCH processor - Request handler interface.
///
/// Provides an interface for requesting the capture and demodulation of PUxCH occasions.
class puxch_processor_request_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~puxch_processor_request_handler() = default;

  /// \brief Handles a new PUxCH request.
  ///
  /// The resource grid and context provided to this method are forwarded to a dedicated block that takes care of the
  /// request asynchronously. A notification through the \ref puxch_processor_notifier interface will inform the client
  /// that the request has been processed and that the PUxCH demodulated sequence is available in \c grid.
  ///
  /// \param[in] grid Destination uplink resource grid.
  /// \param[in] context Resource grid context.

  /// \brief Handles a new PUxCH request.
  ///
  /// The resource grid and context provided to this method are forwarded to a dedicated block that takes care of the
  /// request asynchronously. A notification through the \ref puxch_processor_notifier interface will inform the client
  /// that the request has been processed and that the PUxCH demodulated sequence is available in \c grid.
  ///
  /// \param[in] grid Destination uplink resource grid.
  /// \param[in] context Resource grid context.
  virtual void handle_request(const shared_resource_grid& grid, const resource_grid_context& context) = 0;
};


} // namespace ocudu
