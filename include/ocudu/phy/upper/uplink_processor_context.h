// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/uplink_processor_context.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pucch/pucch_mapping.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// PUCCH context for Format 0 or Format 1.

/// PUCCH context for Format 0 or Format 1.
struct ul_pucch_f0_f1_context {
  /// Scheduling request opportunity indicator.
  /// Scheduling request opportunity indicator.
  bool is_sr_opportunity;
};

/// PUCCH context.

/// PUCCH context.
struct ul_pucch_context {
  /// Slot description (also specifies the numerology).
  /// Slot description (also specifies the numerology).
  slot_point slot;
  /// Radio Network Temporary Identifier (RNTI).
  /// Radio Network Temporary Identifier (RNTI).
  rnti_t rnti;
  /// PUCCH format type.
  /// PUCCH format type.
  pucch_format format;
  /// Format 0 or Format 1 context.
  /// Format 0 or Format 1 context.
  std::optional<ul_pucch_f0_f1_context> context_f0_f1;
};

/// Sounding Reference Signals context.

/// Sounding Reference Signals context.
struct ul_srs_context {
  /// Slot description (also specifies the numerology).
  /// Slot description (also specifies the numerology).
  slot_point slot;
  /// Radio Network Temporary Identifier (RNTI).
  /// Radio Network Temporary Identifier (RNTI).
  rnti_t rnti;
  /// Normalized channel IQ matrix report requested.
  /// Normalized channel IQ matrix report requested.
  bool is_normalized_channel_iq_matrix_report_requested;
  /// Positioning report requested.
  /// Positioning report requested.
  bool is_positioning_report_requested;
};


} // namespace ocudu
