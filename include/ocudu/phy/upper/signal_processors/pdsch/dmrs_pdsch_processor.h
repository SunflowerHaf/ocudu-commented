// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/pdsch/dmrs_pdsch_processor.h  (52 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/mask_types.h"
#include "ocudu/phy/support/precoding_configuration.h"
#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/resource_allocation/rb_bitmap.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {


class resource_grid_writer;

/// Describes a DMRS for PDSCH processor interface.

/// Describes a DMRS for PDSCH processor interface.
class dmrs_pdsch_processor
{
public:
  /// Describes the required parameters to generate the signal as described in 3GPP TS38.211 Section 7.4.1.1.
  /// Describes the required parameters to generate the signal as described in 3GPP TS38.211 Section 7.4.1.1.
  struct config_t {
    /// Slot context for sequence initialization.
    /// Slot context for sequence initialization.
    slot_point slot;
    /// Reference point for PDSCH DM-RS \e k in RBs.
    /// Reference point for PDSCH DM-RS \e k in RBs.
    unsigned reference_point_k_rb;
    /// DM-RS config type (\e dmrsConfigType).
    /// DM-RS config type (\e dmrsConfigType).
    dmrs_config_type type;
    /// PDSCH DMRS-Scrambling-ID (\e pdschDmrsScramblingId).
    /// PDSCH DMRS-Scrambling-ID (\e pdschDmrsScramblingId).
    unsigned scrambling_id;
    /// DM-RS sequence initialization (\f$n_{SCID}\f$).
    /// DM-RS sequence initialization (\f$n_{SCID}\f$).
    bool n_scid;
    /// Generated signal linear amplitude.
    /// Generated signal linear amplitude.
    float amplitude;
    /// DM-RS position mask. Indicates the OFDM symbols carrying DM-RS within the slot.
    /// DM-RS position mask. Indicates the OFDM symbols carrying DM-RS within the slot.
    symbol_slot_mask symbols_mask;
    /// Allocation RB list, the entries set to true are used for transmission.
    /// Allocation RB list, the entries set to true are used for transmission.
    crb_bitmap rb_mask;
    /// Precoding configuration.
    /// Precoding configuration.
    precoding_configuration precoding;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~dmrs_pdsch_processor() = default;

  /// \brief Generates and maps DMRS for PDSCH.
  /// \param [out] grid  Resource grid writer interface.
  /// \param [in] config PT-RS configuration.

  /// \brief Generates and maps DMRS for PDSCH.
  /// \param [out] grid  Resource grid writer interface.
  /// \param [in] config PT-RS configuration.
  virtual void map(resource_grid_writer& grid, const config_t& config) = 0;
};


} // namespace ocudu
