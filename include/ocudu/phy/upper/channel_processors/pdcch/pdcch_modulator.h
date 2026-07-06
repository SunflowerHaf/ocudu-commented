// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pdcch/pdcch_modulator.h  (52 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/phy/support/precoding_configuration.h"
#include "ocudu/ran/resource_allocation/rb_bitmap.h"


namespace ocudu {


class resource_grid_writer;

/// \brief Describes a PDCCH modulator interface.
///
/// \remark Defined in TS38.211 Section 7.3.2 Physical downlink control channel (PDCCH).
/// \note The configuration assumes the CCE-to-REG and REG-to-PRB mapping is included in \c rb_mask.

/// \brief Describes a PDCCH modulator interface.
///
/// \remark Defined in TS38.211 Section 7.3.2 Physical downlink control channel (PDCCH).
/// \note The configuration assumes the CCE-to-REG and REG-to-PRB mapping is included in \c rb_mask.
class pdcch_modulator
{
public:
  /// Describes the necessary parameters to modulate a PDCCH transmission.
  /// Describes the necessary parameters to modulate a PDCCH transmission.
  struct config_t {
    /// Indicates the RBs used for the PDCCH transmission.
    /// Indicates the RBs used for the PDCCH transmission.
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
    /// Parameter \f$n_{RNTI}\f$ used for PDCCH data scrambling according to TS38.211 Section 7.3.2.3.
    /// Parameter \f$n_{RNTI}\f$ used for PDCCH data scrambling according to TS38.211 Section 7.3.2.3.
    unsigned n_rnti;
    /// Scaling factor to apply to the resource elements according to PDCCH power allocation in TS38.213.
    /// Scaling factor to apply to the resource elements according to PDCCH power allocation in TS38.213.
    float scaling;
    /// Precoding information for the PDCCH transmission.
    /// Precoding information for the PDCCH transmission.
    precoding_configuration precoding;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~pdcch_modulator() = default;

  /// \brief Modulates a PDCCH codeword according to TS38.211 Section 7.3.2.
  /// \param[out] grid   Resource grid writer interface.
  /// \param[in] data    PDCCH codeword to modulate.
  /// \param[in] config  Necessary parameters for modulating PDCCH.
  /// \remark The codeword length shall be consistent with the resource mapping.
  /// \remark An assertion is triggered if the number of precoding layers is not one.

  /// \brief Modulates a PDCCH codeword according to TS38.211 Section 7.3.2.
  /// \param[out] grid   Resource grid writer interface.
  /// \param[in] data    PDCCH codeword to modulate.
  /// \param[in] config  Necessary parameters for modulating PDCCH.
  /// \remark The codeword length shall be consistent with the resource mapping.
  /// \remark An assertion is triggered if the number of precoding layers is not one.
  virtual void modulate(resource_grid_writer& grid, span<const uint8_t> data, const config_t& config) = 0;
};


} // namespace ocudu
