// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/lower_phy_downlink_handler.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/resource_grid_context.h"


namespace ocudu {


class shared_resource_grid;

/// \brief Lower physical layer downlink handler interface.
///
/// The downlink handler modulates and transmits the given downlink resource grid through the underlying radio device.

/// \brief Lower physical layer downlink handler interface.
///
/// The downlink handler modulates and transmits the given downlink resource grid through the underlying radio device.
class lower_phy_downlink_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_downlink_handler() = default;

  /// \brief Handles the given resource grid to be transmitted.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid Resource grid to transmit.

  /// \brief Handles the given resource grid to be transmitted.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid Resource grid to transmit.
  virtual void handle_resource_grid(const resource_grid_context& context, const shared_resource_grid& grid) = 0;
};


} // namespace ocudu
