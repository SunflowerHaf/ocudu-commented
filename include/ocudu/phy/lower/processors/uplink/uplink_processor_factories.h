// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/uplink_processor_factories.h  (50 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/lower/modulation/modulation_factories.h"
#include "ocudu/phy/lower/processors/uplink/prach/prach_processor_factories.h"
#include "ocudu/phy/lower/processors/uplink/puxch/puxch_processor_factories.h"
#include "ocudu/phy/lower/processors/uplink/uplink_processor.h"
#include "ocudu/phy/lower/sampling_rate.h"
#include <memory>


namespace ocudu {

/// Describes a sector configuration.

/// Describes a sector configuration.
struct uplink_processor_configuration {
  /// Sector identifier.
  /// Sector identifier.
  unsigned sector_id;
  /// Subcarrier spacing.
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Cyclic prefix configuration.
  /// Cyclic prefix configuration.
  cyclic_prefix cp;
  /// Baseband sampling rate.
  /// Baseband sampling rate.
  sampling_rate rate;
  /// Bandwidth in PRB.
  /// Bandwidth in PRB.
  unsigned bandwidth_prb;
  /// Center frequency in Hz.
  /// Center frequency in Hz.
  double center_frequency_Hz;
  /// Number of receive ports.
  /// Number of receive ports.
  unsigned nof_rx_ports;
};

/// Lower physical layer uplink processor - Factory interface.

/// Lower physical layer uplink processor - Factory interface.
class lower_phy_uplink_processor_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_uplink_processor_factory() = default;

  /// Creates a lower PHY uplink processor.

  /// Creates a lower PHY uplink processor.
  virtual std::unique_ptr<lower_phy_uplink_processor> create(const uplink_processor_configuration& config) = 0;
};

/// Creates a software based uplink processor factory.

/// Creates a software based uplink processor factory.
std::shared_ptr<lower_phy_uplink_processor_factory>
create_uplink_processor_factory_sw(std::shared_ptr<prach_processor_factory> prach_proc_factory,
                                   std::shared_ptr<puxch_processor_factory> puxch_proc_factory);


} // namespace ocudu
