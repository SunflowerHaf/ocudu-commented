// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/sequence_generators/sequence_generator_factories.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/upper/sequence_generators/low_papr_sequence_collection.h"
#include "ocudu/phy/upper/sequence_generators/low_papr_sequence_generator.h"
#include "ocudu/phy/upper/sequence_generators/pseudo_random_generator.h"
#include <memory>


namespace ocudu {


class low_papr_sequence_generator_factory;


class low_papr_sequence_collection_factory
{
public:
  virtual ~low_papr_sequence_collection_factory() = default;
  virtual std::unique_ptr<low_papr_sequence_collection>
  create(unsigned m, unsigned delta, span<const float> alphas) = 0;
};


std::shared_ptr<low_papr_sequence_collection_factory>
create_low_papr_sequence_collection_sw_factory(std::shared_ptr<low_papr_sequence_generator_factory> lpg_factory);


class low_papr_sequence_generator_factory
{
public:
  virtual ~low_papr_sequence_generator_factory()                = default;
  virtual std::unique_ptr<low_papr_sequence_generator> create() = 0;
};


std::shared_ptr<low_papr_sequence_generator_factory> create_low_papr_sequence_generator_sw_factory();


class pseudo_random_generator_factory
{
public:
  virtual ~pseudo_random_generator_factory()                = default;
  virtual std::unique_ptr<pseudo_random_generator> create() = 0;
};


std::shared_ptr<pseudo_random_generator_factory> create_pseudo_random_generator_sw_factory();


} // namespace ocudu
