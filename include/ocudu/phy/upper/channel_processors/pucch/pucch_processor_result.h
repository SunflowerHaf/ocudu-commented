// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pucch/pucch_processor_result.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/upper/channel_processors/pucch/pucch_uci_message.h"
#include "ocudu/phy/upper/channel_state_information.h"


namespace ocudu {

/// Collects PUCCH processor results.

/// Collects PUCCH processor results.
struct pucch_processor_result {
  /// Channel state information.
  /// Channel state information.
  channel_state_information csi;
  /// UCI message.
  /// UCI message.
  pucch_uci_message message;
  /// Detection metric normalized with respect to the detection threshold (if applicable).
  /// Detection metric normalized with respect to the detection threshold (if applicable).
  std::optional<float> detection_metric;
};


} // namespace ocudu
