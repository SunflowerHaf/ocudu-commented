// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_modulation/channel_modulation_factories.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/upper/channel_modulation/demodulation_mapper.h"
#include "ocudu/phy/upper/channel_modulation/evm_calculator.h"
#include "ocudu/phy/upper/channel_modulation/modulation_mapper.h"
#include <memory>


namespace ocudu {


class modulation_mapper_factory
{
public:
  virtual ~modulation_mapper_factory()                = default;
  virtual std::unique_ptr<modulation_mapper> create() = 0;
};


std::shared_ptr<modulation_mapper_factory> create_modulation_mapper_factory();


class demodulation_mapper_factory
{
public:
  virtual ~demodulation_mapper_factory()                = default;
  virtual std::unique_ptr<demodulation_mapper> create() = 0;
};


std::shared_ptr<demodulation_mapper_factory> create_demodulation_mapper_factory();


class evm_calculator_factory
{
public:
  virtual ~evm_calculator_factory()                = default;
  virtual std::unique_ptr<evm_calculator> create() = 0;
};


std::shared_ptr<evm_calculator_factory> create_evm_calculator_factory();


} // namespace ocudu
