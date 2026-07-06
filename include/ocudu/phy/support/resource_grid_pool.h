// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/resource_grid_pool.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/resource_grid.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/phy/support/shared_resource_grid.h"
#include <vector>


namespace ocudu {

/// Resource grid pool interface.

/// Resource grid pool interface.
class resource_grid_pool
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~resource_grid_pool() = default;

  /// \brief Allocates a resource grid for the given context.
  ///
  /// Attempts to allocate a resource grid based on the provided allocation context. If the system is under high load,
  /// the allocation might fail. When allocation fails, the reason for the failure is logged to the \e PHY logger
  /// channel.
  ///
  /// \param [in] slot The slot for resource grid allocation.
  /// \return A valid shared resource grid if the allocation is successful; otherwise, an invalid shared resource grid.

  /// \brief Allocates a resource grid for the given context.
  ///
  /// Attempts to allocate a resource grid based on the provided allocation context. If the system is under high load,
  /// the allocation might fail. When allocation fails, the reason for the failure is logged to the \e PHY logger
  /// channel.
  ///
  /// \param [in] slot The slot for resource grid allocation.
  /// \return A valid shared resource grid if the allocation is successful; otherwise, an invalid shared resource grid.
  virtual shared_resource_grid allocate_resource_grid(slot_point slot) = 0;
};


} // namespace ocudu
