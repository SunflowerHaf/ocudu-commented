// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/downlink/downlink_processor_factories.h  (50 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/lower/processors/downlink/downlink_processor.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_factories.h"
#include "ocudu/phy/lower/sampling_rate.h"
#include <memory>


namespace ocudu {

/// Describes a sector configuration.

/// Describes a sector configuration.
struct downlink_processor_configuration {
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
  /// Number of transmit ports.
  /// Number of transmit ports.
  unsigned nof_tx_ports;
  /// Number of slots notified in advance in the TTI boundary event.
  /// Number of slots notified in advance in the TTI boundary event.
  unsigned nof_slot_tti_in_advance;
};

/// Lower physical layer downlink processor - Factory interface.

/// Lower physical layer downlink processor - Factory interface.
class lower_phy_downlink_processor_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_downlink_processor_factory() = default;

  /// Creates a lower PHY downlink processor.

  /// Creates a lower PHY downlink processor.
  virtual std::unique_ptr<lower_phy_downlink_processor> create(const downlink_processor_configuration& config,
                                                               task_executor& modulation_executor) = 0;
};

/// Creates a software based downlink processor factory.

/// Creates a software based downlink processor factory.
std::shared_ptr<lower_phy_downlink_processor_factory>
create_downlink_processor_factory_sw(std::shared_ptr<pdxch_processor_factory> pdxch_proc_factory);


} // namespace ocudu
