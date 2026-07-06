// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/srs/srs_estimator_configuration.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/slot_point.h"
#include "ocudu/ran/srs/srs_constants.h"
#include "ocudu/ran/srs/srs_context.h"
#include "ocudu/ran/srs/srs_resource_configuration.h"
#include <cstdint>


namespace ocudu {

/// Parameters required to receive the Sounding Reference Signals described in 3GPP TS38.211 Section 6.4.1.4.

/// Parameters required to receive the Sounding Reference Signals described in 3GPP TS38.211 Section 6.4.1.4.
struct srs_estimator_configuration {
  /// Context information.
  /// Context information.
  std::optional<srs_context> context;
  /// Numerology, SFN and slot index.
  /// Numerology, SFN and slot index.
  slot_point slot;
  /// SRS resource configuration.
  /// SRS resource configuration.
  srs_resource_configuration resource;
  /// Receive port list.
  /// Receive port list.
  static_vector<uint8_t, srs_constants::max_nof_rx_ports> ports;
};


} // namespace ocudu
