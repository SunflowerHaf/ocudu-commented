// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Precoding factories.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/generic_functions/precoding/precoding_factories.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Precoding factories.

#pragma once


#include "ocudu/phy/generic_functions/precoding/channel_precoder.h"


namespace ocudu {

/// Factory that builds channel precoder objects.

/// Factory that builds channel precoder objects.
class channel_precoder_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~channel_precoder_factory() = default;

  /// Creates and returns a channel precoder object.

  /// Creates and returns a channel precoder object.
  virtual std::unique_ptr<channel_precoder> create() = 0;
};

/// \brief Creates and returns a channel precoder factory.
///
/// \param[in] precoder_type A string indicating the precoder implementation to create. Values: generic, auto, avx2.
/// \return A channel precoder factory for the chosen precoder implementation.

/// \brief Creates and returns a channel precoder factory.
///
/// \param[in] precoder_type A string indicating the precoder implementation to create. Values: generic, auto, avx2.
/// \return A channel precoder factory for the chosen precoder implementation.
std::shared_ptr<channel_precoder_factory> create_channel_precoder_factory(const std::string& precoder_type);


} // namespace ocudu
