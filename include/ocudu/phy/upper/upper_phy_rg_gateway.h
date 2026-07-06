// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/upper_phy_rg_gateway.h  (27 lines)
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

/// Interface of the upper physical layer resource grid gateway.

/// Interface of the upper physical layer resource grid gateway.
class upper_phy_rg_gateway
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~upper_phy_rg_gateway() = default;

  /// \brief Sends the given resource grid through the gateway.
  ///
  /// \param[in] context Context the resource grid belongs to.
  /// \param[in] grid    Resource grid.

  /// \brief Sends the given resource grid through the gateway.
  ///
  /// \param[in] context Context the resource grid belongs to.
  /// \param[in] grid    Resource grid.
  virtual void send(const resource_grid_context& context, shared_resource_grid grid) = 0;
};


} // namespace ocudu
