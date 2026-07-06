// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/ptrs/ptrs_pdsch_generator.h  (67 lines)
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
#include "ocudu/phy/support/re_pattern.h"
#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/ptrs/ptrs.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {


class resource_grid_writer;

/// Interface for the Phase Tracking Reference Signals (PT-RS) for PDSCH generator.

/// Interface for the Phase Tracking Reference Signals (PT-RS) for PDSCH generator.
class ptrs_pdsch_generator
{
public:
  /// Required parameters to generate the signal as described in 3GPP TS38.211 Section 7.4.1.2.
  /// Required parameters to generate the signal as described in 3GPP TS38.211 Section 7.4.1.2.
  struct configuration {
    /// Slot context for sequence initialization.
    /// Slot context for sequence initialization.
    slot_point slot;
    /// RNTI associated with the DCI scheduling the transmission, parameter \f$n_{RNTI}\f$.
    /// RNTI associated with the DCI scheduling the transmission, parameter \f$n_{RNTI}\f$.
    rnti_t rnti;
    /// DM-RS config type (\e dmrsConfigType).
    /// DM-RS config type (\e dmrsConfigType).
    dmrs_config_type dmrs_type;
    /// DM-RS for PDSCH reference point \e k in RBs, relative to Point A.
    /// DM-RS for PDSCH reference point \e k in RBs, relative to Point A.
    unsigned reference_point_k_rb;
    /// PDSCH DMRS-Scrambling-ID (\e pdschDmrsScramblingId).
    /// PDSCH DMRS-Scrambling-ID (\e pdschDmrsScramblingId).
    unsigned scrambling_id;
    /// DM-RS for PDSCH sequence initialization (\f$n_{SCID}\f$).
    /// DM-RS for PDSCH sequence initialization (\f$n_{SCID}\f$).
    bool n_scid;
    /// Generated signal linear amplitude.
    /// Generated signal linear amplitude.
    float amplitude;
    /// DM-RS position mask. Indicates the OFDM symbols carrying DM-RS within the slot.
    /// DM-RS position mask. Indicates the OFDM symbols carrying DM-RS within the slot.
    symbol_slot_mask dmrs_symbols_mask;
    /// PDSCH frequency domain allocation as a CRB mask. The entries set to true are used for transmission.
    /// PDSCH frequency domain allocation as a CRB mask. The entries set to true are used for transmission.
    crb_bitmap rb_mask;
    /// PDSCH time domain allocation.
    /// PDSCH time domain allocation.
    interval<uint8_t> time_allocation;
    /// Frequency domain density.
    /// Frequency domain density.
    ptrs_frequency_density freq_density;
    /// Time domain density.
    /// Time domain density.
    ptrs_time_density time_density;
    /// Resource element offset.
    /// Resource element offset.
    ptrs_re_offset re_offset;
    /// \brief Reserved RE pattern.
    ///
    /// Indicates the elements that cannot contain PT-RS as described in TS38.211 Section 7.4.1.2.2.
    /// \brief Reserved RE pattern.
    ///
    /// Indicates the elements that cannot contain PT-RS as described in TS38.211 Section 7.4.1.2.2.
    re_pattern_list reserved;
    /// PDSCH precoding configuration.
    /// PDSCH precoding configuration.
    precoding_configuration precoding;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~ptrs_pdsch_generator() = default;

  /// \brief Generates and maps PT-RS for PDSCH.
  /// \param [out] grid Destination resource grid.
  /// \param [in]  config Required configuration to generate and map the signal.

  /// \brief Generates and maps PT-RS for PDSCH.
  /// \param [out] grid Destination resource grid.
  /// \param [in]  config Required configuration to generate and map the signal.
  virtual void generate(resource_grid_writer& grid, const configuration& config) = 0;
};


} // namespace ocudu
