// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/uplink_pdu_validator.h  (55 lines)
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
#include "ocudu/phy/upper/channel_processors/prach/prach_detector.h"
#include "ocudu/phy/upper/channel_processors/pucch/pucch_processor.h"
#include "ocudu/phy/upper/channel_processors/pusch/pusch_processor.h"
#include "ocudu/phy/upper/signal_processors/srs/srs_estimator_configuration.h"


namespace ocudu {

/// Uplink processor validation interface.

/// Uplink processor validation interface.
class uplink_pdu_validator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplink_pdu_validator() = default;

  /// \brief Validates PRACH detector configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PRACH detector configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const prach_detector::configuration& config) const = 0;

  /// \brief Validates PUCCH Format 0 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PUCCH Format 0 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const pucch_processor::format0_configuration& config) const = 0;

  /// \brief Validates PUCCH Format 1 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PUCCH Format 1 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const pucch_processor::format1_configuration& config) const = 0;

  /// \brief Validates PUCCH Format 2 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PUCCH Format 2 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const pucch_processor::format2_configuration& config) const = 0;

  /// \brief Validates PUCCH Format 3 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PUCCH Format 3 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const pucch_processor::format3_configuration& config) const = 0;

  /// \brief Validates PUCCH Format 4 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PUCCH Format 4 configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const pucch_processor::format4_configuration& config) const = 0;

  /// \brief Validates PUSCH configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates PUSCH configuration parameters.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const pusch_processor::pdu_t& config) const = 0;

  /// \brief Validates Sounding Reference Signals channel estimator configuration.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.

  /// \brief Validates Sounding Reference Signals channel estimator configuration.
  /// \return A success if the parameters contained in \c config are supported, an error message otherwise.
  virtual error_type<std::string> is_valid(const srs_estimator_configuration& config) const = 0;
};


} // namespace ocudu
