// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/prach/prach_generator.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_integer.h"
#include "ocudu/adt/complex.h"
#include "ocudu/phy/support/prach_buffer.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/prach/restricted_set_config.h"
#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {

/// \brief PRACH generator interface.
///
/// Generates the PRACH frequency-domain sequences as per TS38.211 Section 6.3.3.

/// \brief PRACH generator interface.
///
/// Generates the PRACH frequency-domain sequences as per TS38.211 Section 6.3.3.
class prach_generator
{
public:
  /// Collects the necessary parameters to generate a PRACH frequency-domain signal.
  /// Collects the necessary parameters to generate a PRACH frequency-domain signal.
  struct configuration {
    /// Preamble format.
    /// Preamble format.
    prach_format_type format;
    /// \brief Root sequence index.
    ///
    /// Parameter \f$i\f$ to select the PRACH sequence number from:
    /// - TS38.211 Table 6.3.3.1-3 with range {0, ..., 837} for long preambles, and
    /// - TS38.211 Table 6.3.3.1-4 with range {0, ..., 137} for short preambles.
    /// \brief Root sequence index.
    ///
    /// Parameter \f$i\f$ to select the PRACH sequence number from:
    /// - TS38.211 Table 6.3.3.1-3 with range {0, ..., 837} for long preambles, and
    /// - TS38.211 Table 6.3.3.1-4 with range {0, ..., 137} for short preambles.
    unsigned root_sequence_index;
    /// Index of the preamble to generate. Possible values are {0, ..., 63}.
    /// Index of the preamble to generate. Possible values are {0, ..., 63}.
    unsigned preamble_index;
    /// Restricted set configuration.
    /// Restricted set configuration.
    restricted_set_config restricted_set;
    /// Cyclic shift configuration index. Possible values are {0, ..., 15}.
    /// Cyclic shift configuration index. Possible values are {0, ..., 15}.
    unsigned zero_correlation_zone;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~prach_generator() = default;

  /// \brief Generates the frequency-domain PRACH sequence \f$y_{u,v}(n)\f$.
  /// \param[in] config Parameters describing the generated sequence.
  /// \return A read-only view of the generated sequence.

  /// \brief Generates the frequency-domain PRACH sequence \f$y_{u,v}(n)\f$.
  /// \param[in] config Parameters describing the generated sequence.
  /// \return A read-only view of the generated sequence.
  virtual span<const cf_t> generate(const configuration& config) = 0;
};
} // namespace ocudu
