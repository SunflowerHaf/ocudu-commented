// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/prach/prach_detector.h  (75 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/phy/support/prach_buffer.h"
#include "ocudu/phy/upper/channel_processors/prach/prach_detection_result.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/prach/prach_subcarrier_spacing.h"
#include "ocudu/ran/prach/restricted_set_config.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// \brief Describes a PRACH detector interface.
///
/// The PRACH sequence generation to detect is described in TS38.211 Section 6.3.3.

/// \brief Describes a PRACH detector interface.
///
/// The PRACH sequence generation to detect is described in TS38.211 Section 6.3.3.
class prach_detector
{
public:
  /// Configuration for PRACH detection.
  /// Configuration for PRACH detection.
  struct configuration {
    /// Root sequence index. Possibles values are {0, ..., 837} for long preambles and {0, ..., 137} for short
    /// preambles.
    /// Root sequence index. Possibles values are {0, ..., 837} for long preambles and {0, ..., 137} for short
    /// preambles.
    unsigned root_sequence_index;
    /// Preamble format.
    /// Preamble format.
    prach_format_type format;
    /// Restricted set configuration.
    /// Restricted set configuration.
    restricted_set_config restricted_set;
    /// Zero-correlation zone configuration index to calculate \f$N_{CS}\f$ as per TS38.211 Section 6.3.3.1.
    /// Zero-correlation zone configuration index to calculate \f$N_{CS}\f$ as per TS38.211 Section 6.3.3.1.
    unsigned zero_correlation_zone;
    /// Start preamble index to monitor. Possible values are {0, ..., 63}.
    /// Start preamble index to monitor. Possible values are {0, ..., 63}.
    unsigned start_preamble_index;
    /// \brief Number of preamble indices to monitor. Possible values are {1, ..., 64}.
    /// \note The sum <tt>start_preamble_index + nof_preamble_indices</tt> should be not larger than 64.
    /// \brief Number of preamble indices to monitor. Possible values are {1, ..., 64}.
    /// \note The sum <tt>start_preamble_index + nof_preamble_indices</tt> should be not larger than 64.
    unsigned nof_preamble_indices;
    /// Random access subcarrier spacing.
    /// Random access subcarrier spacing.
    prach_subcarrier_spacing ra_scs;
    /// Number of receive ports.
    /// Number of receive ports.
    unsigned nof_rx_ports;
    /// Slot and numerology, for logging.
    /// Slot and numerology, for logging.
    slot_point slot;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~prach_detector() = default;

  /// \brief Detects PRACH transmissions according to the given configuration.
  ///
  /// The PRACH detector assumes that \c signal is captured at the start of the PRACH reception window and it is at
  /// least as long as the PRACH preamble sequence.
  ///
  /// An assertion is triggered if the sum of start preamble index and number of preambles exceeds 64.
  ///
  /// \param[in] input  Baseband signal buffer.
  /// \param[in] config PRACH configuration for the slot.
  /// \return The detection result.

  /// \brief Detects PRACH transmissions according to the given configuration.
  ///
  /// The PRACH detector assumes that \c signal is captured at the start of the PRACH reception window and it is at
  /// least as long as the PRACH preamble sequence.
  ///
  /// An assertion is triggered if the sum of start preamble index and number of preambles exceeds 64.
  ///
  /// \param[in] input  Baseband signal buffer.
  /// \param[in] config PRACH configuration for the slot.
  /// \return The detection result.
  virtual prach_detection_result detect(const prach_buffer& input, const configuration& config) = 0;
};

/// \brief Describes the PRACH detector validator interface.

/// \brief Describes the PRACH detector validator interface.
class prach_detector_validator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~prach_detector_validator() = default;

  /// \brief Validates PRACH detector configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PRACH detector configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const prach_detector::configuration& config) const = 0;
};


} // namespace ocudu
