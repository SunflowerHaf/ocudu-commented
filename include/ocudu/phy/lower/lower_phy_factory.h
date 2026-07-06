// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/lower_phy_factory.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/lower/lower_phy.h"
#include "ocudu/phy/lower/lower_phy_configuration.h"
#include "ocudu/phy/lower/processors/downlink/downlink_processor_factories.h"
#include "ocudu/phy/lower/processors/uplink/uplink_processor_factories.h"
#include <memory>


namespace ocudu {

/// Lower physical layer factory.

/// Lower physical layer factory.
class lower_phy_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_factory() = default;

  /// Creates a lower physical layer.

  /// Creates a lower physical layer.
  virtual std::unique_ptr<lower_phy> create(const lower_phy_configuration& config,
                                            const lower_phy_dependencies&  dependencies) = 0;
};

/// Creates a software based lower physical layer factory.

/// Creates a software based lower physical layer factory.
std::shared_ptr<lower_phy_factory>
create_lower_phy_factory_sw(std::shared_ptr<lower_phy_downlink_processor_factory> downlink_proc_factory,
                            std::shared_ptr<lower_phy_uplink_processor_factory>   uplink_proc_factory);


} // namespace ocudu
