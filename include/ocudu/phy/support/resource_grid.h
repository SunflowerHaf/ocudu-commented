// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/resource_grid.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"


namespace ocudu {


class resource_grid_reader;
class resource_grid_writer;

/// Describes a resource grid class with writer and reader interfaces.

/// Describes a resource grid class with writer and reader interfaces.
class resource_grid
{
public:
  virtual ~resource_grid() = default;

  /// Sets all resource elements in the grid to zero.

  /// Sets all resource elements in the grid to zero.
  virtual void set_all_zero() = 0;

  /// Gets the resource grid writer.

  /// Gets the resource grid writer.
  virtual resource_grid_writer& get_writer() = 0;

  /// Gets the resource grid reader.

  /// Gets the resource grid reader.
  virtual const resource_grid_reader& get_reader() const = 0;
};


} // namespace ocudu
