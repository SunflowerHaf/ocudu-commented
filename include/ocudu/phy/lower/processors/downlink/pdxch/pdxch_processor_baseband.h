// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_baseband.h  (46 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_pool.h"
#include "ocudu/phy/lower/lower_phy_baseband_metrics.h"
#include "ocudu/ran/slot_point.h"
#include <optional>


namespace ocudu {

/// \brief Lower physical layer PDxCH processor - Baseband interface.
///
/// Processes baseband samples with slot granularity.

/// \brief Lower physical layer PDxCH processor - Baseband interface.
///
/// Processes baseband samples with slot granularity.
class pdxch_processor_baseband
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~pdxch_processor_baseband() = default;

  /// Describes the context of a newly generated slot.

  /// Describes the context of a newly generated slot.
  struct slot_context {
    /// Slot context.
    /// Slot context.
    slot_point slot;
    /// Radio sector identifier.
    /// Radio sector identifier.
    unsigned sector;
  };

  /// Groups baseband metrics and buffer for a slot.

  /// Groups baseband metrics and buffer for a slot.
  struct slot_result {
    /// Collected baseband buffer metrics.
    /// Collected baseband buffer metrics.
    lower_phy_baseband_metrics metrics = {};
    /// Actual baseband buffer. Set to nullptr if there was no transmit request in the given slot.
    /// Actual baseband buffer. Set to nullptr if there was no transmit request in the given slot.
    baseband_gateway_buffer_ptr buffer = nullptr;
  };

  /// \brief Processes a baseband OFDM slot.
  ///
  /// \param[in] context OFDM Symbol context.
  /// \return Slot downlink baseband results.

  /// \brief Processes a baseband OFDM slot.
  ///
  /// \param[in] context OFDM Symbol context.
  /// \return Slot downlink baseband results.
  virtual slot_result process_slot(slot_context context) = 0;
};


} // namespace ocudu
