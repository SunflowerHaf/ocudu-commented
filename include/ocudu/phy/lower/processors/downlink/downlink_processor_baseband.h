// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/downlink/downlink_processor_baseband.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gateways/baseband/baseband_gateway_timestamp.h"
#include "ocudu/gateways/baseband/baseband_gateway_transmitter_metadata.h"
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_pool.h"


namespace ocudu {

/// \brief Lower physical layer downlink processor - Baseband interface.
///
/// Processes baseband samples, it derives the symbol and slot timing from the provided timestamp.

/// \brief Lower physical layer downlink processor - Baseband interface.
///
/// Processes baseband samples, it derives the symbol and slot timing from the provided timestamp.
class downlink_processor_baseband
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~downlink_processor_baseband() = default;

  /// Baseband processing result.

  /// Baseband processing result.
  struct processing_result {
    /// Baseband generation metadata.
    /// Baseband generation metadata.
    baseband_gateway_transmitter_metadata metadata;
    /// Smart pointer to a baseband buffer.
    /// Smart pointer to a baseband buffer.
    baseband_gateway_buffer_ptr buffer;
  };

  /// \brief Processes baseband at the given timestamp.
  ///
  /// If the given timestamp does not match with a slot boundary or there is no transmit request, it returns a valid
  /// buffer filled with zeros. Otherwise, it returns a valid buffer with the modulated baseband signal for the given
  /// slot.
  ///
  /// \param timestamp Given timestamp as a number of samples passed since an known epoch in time.
  /// \return The processing results with a valid buffer and the metadata indicating the contents on the buffer.

  /// \brief Processes baseband at the given timestamp.
  ///
  /// If the given timestamp does not match with a slot boundary or there is no transmit request, it returns a valid
  /// buffer filled with zeros. Otherwise, it returns a valid buffer with the modulated baseband signal for the given
  /// slot.
  ///
  /// \param timestamp Given timestamp as a number of samples passed since an known epoch in time.
  /// \return The processing results with a valid buffer and the metadata indicating the contents on the buffer.
  virtual processing_result process(baseband_gateway_timestamp timestamp) = 0;
};


} // namespace ocudu
