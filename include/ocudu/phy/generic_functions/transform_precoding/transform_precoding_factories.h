// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Transform precoding factories.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/generic_functions/transform_precoding/transform_precoding_factories.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Transform precoding factories.

#pragma once


#include "ocudu/phy/generic_functions/generic_functions_factories.h"
#include "ocudu/phy/generic_functions/transform_precoding/transform_precoder.h"
#include <memory>


namespace ocudu {

/// Factory that builds transform precoder objects.

/// Factory that builds transform precoder objects.
class transform_precoder_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~transform_precoder_factory() = default;

  /// Creates and returns a transform precoder object.

  /// Creates and returns a transform precoder object.
  virtual std::unique_ptr<transform_precoder> create() = 0;
};

/// \brief Creates and returns a transform precoder factory based on the DFT algorithm.
///
/// \return A transform precoder factory.

/// \brief Creates and returns a transform precoder factory based on the DFT algorithm.
///
/// \return A transform precoder factory.
std::shared_ptr<transform_precoder_factory>
create_dft_transform_precoder_factory(std::shared_ptr<dft_processor_factory>, unsigned max_nof_prb);


} // namespace ocudu
