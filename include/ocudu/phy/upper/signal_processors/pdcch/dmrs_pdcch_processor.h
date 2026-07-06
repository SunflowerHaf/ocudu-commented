// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/pdcch/dmrs_pdcch_processor.h  (53 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/precoding_configuration.h"
#include "ocudu/phy/support/resource_grid_writer.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/resource_allocation/rb_bitmap.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {


class resource_grid_mapper;

/// Describes a DMRS for PDCCH processor interface.

/// Describes a DMRS for PDCCH processor interface.
class dmrs_pdcch_processor
{
public:
  /// Describes the necessary parameters to generate DMRS for a PDCCH transmission.
  /// Describes the necessary parameters to generate DMRS for a PDCCH transmission.
  struct config_t {
    /// Provides the slot timing and numerology.
    /// Provides the slot timing and numerology.
    slot_point slot;
    /// Cyclic prefix.
    /// Cyclic prefix.
    cyclic_prefix cp;
    /// Reference point for PDCCH DMRS \e k in RBs.
    /// Reference point for PDCCH DMRS \e k in RBs.
    unsigned reference_point_k_rb;
    /// Indicates the PRB used for the PDCCH transmission. The bit at position zero corresponds to CRB0.
    /// Indicates the PRB used for the PDCCH transmission. The bit at position zero corresponds to CRB0.
    crb_bitmap rb_mask;
    /// CORESET start symbol index.
    /// CORESET start symbol index.
    unsigned start_symbol_index;
    /// CORESET duration in symbols.
    /// CORESET duration in symbols.
    unsigned duration;
    /// Higher layer parameter PDCCH-DMRS-ScramblingID if it is given, otherwise the physical cell identifier.
    /// Higher layer parameter PDCCH-DMRS-ScramblingID if it is given, otherwise the physical cell identifier.
    unsigned n_id;
    /// Provides the linear signal amplitude to conform with the transmission power.
    /// Provides the linear signal amplitude to conform with the transmission power.
    float amplitude;
    /// Precoding configuration.
    /// Precoding configuration.
    precoding_configuration precoding;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~dmrs_pdcch_processor() = default;

  /// \brief Generates and maps DMRS for PDCCH according to TS38.211 Section 7.4.1.3.
  ///
  /// \param[out] grid   Resource grid writer interface.
  /// \param[in] config  Required configuration to generate and map the signal.

  /// \brief Generates and maps DMRS for PDCCH according to TS38.211 Section 7.4.1.3.
  ///
  /// \param[out] grid   Resource grid writer interface.
  /// \param[in] config  Required configuration to generate and map the signal.
  virtual void map(resource_grid_writer& grid, const config_t& config) = 0;
};


} // namespace ocudu
