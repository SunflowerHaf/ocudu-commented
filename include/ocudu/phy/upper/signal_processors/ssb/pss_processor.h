// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/ssb/pss_processor.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/phy/antenna_ports.h"
#include "ocudu/ran/pci.h"
#include <memory>


namespace ocudu {


class resource_grid_writer;

/// Describes a PSS processor interface

/// Describes a PSS processor interface
class pss_processor
{
public:
  /// Describes the required parameters to generate the signal
  /// Describes the required parameters to generate the signal
  struct config_t {
    /// Physical cell identifier
    /// Physical cell identifier
    pci_t phys_cell_id;
    /// First subcarrier in the resource grid
    /// First subcarrier in the resource grid
    unsigned ssb_first_subcarrier;
    /// Denotes the first symbol of the SS/PBCH block within the slot.
    /// Denotes the first symbol of the SS/PBCH block within the slot.
    unsigned ssb_first_symbol;
    /// PSS linear signal amplitude
    /// PSS linear signal amplitude
    float amplitude;
    /// Port indexes to map the signal.
    /// Port indexes to map the signal.
    static_vector<uint8_t, MAX_PORTS> ports;
  };

  /// Default destructor

  /// Default destructor
  virtual ~pss_processor() = default;

  /// \brief Generates and maps a PSS sequence
  /// \param [out] grid Provides the destination resource grid
  /// \param [in] config Provides the required configuration to generate and map the signal

  /// \brief Generates and maps a PSS sequence
  /// \param [out] grid Provides the destination resource grid
  /// \param [in] config Provides the required configuration to generate and map the signal
  virtual void map(resource_grid_writer& grid, const config_t& config) = 0;
};


} // namespace ocudu
