// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/ptrs/ptrs_pdsch_generator_factory.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/support_factories.h"
#include "ocudu/phy/upper/sequence_generators/sequence_generator_factories.h"
#include "ocudu/phy/upper/signal_processors/ptrs/ptrs_pdsch_generator.h"
#include <memory>


namespace ocudu {

/// Phase Tracking Reference Signals (PT-RS) for PDSCH generator factory interface.

/// Phase Tracking Reference Signals (PT-RS) for PDSCH generator factory interface.
class ptrs_pdsch_generator_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ptrs_pdsch_generator_factory() = default;

  /// Creates a PT-RS for PDSCH generator.

  /// Creates a PT-RS for PDSCH generator.
  virtual std::unique_ptr<ptrs_pdsch_generator> create() = 0;
};

/// \brief Creates a generic PT-RS for PDSCH generator factory.
/// \param[in] pseudo_random_gen_factory Pseudo-random sequence generator factory.
/// \return A PT-RS for PDSCH generator factory instance.

/// \brief Creates a generic PT-RS for PDSCH generator factory.
/// \param[in] pseudo_random_gen_factory Pseudo-random sequence generator factory.
/// \return A PT-RS for PDSCH generator factory instance.
std::shared_ptr<ptrs_pdsch_generator_factory>
create_ptrs_pdsch_generator_generic_factory(std::shared_ptr<pseudo_random_generator_factory> pseudo_random_gen_factory,
                                            std::shared_ptr<resource_grid_mapper_factory>    rg_mapper_factory);


} // namespace ocudu
