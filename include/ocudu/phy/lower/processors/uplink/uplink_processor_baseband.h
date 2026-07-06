// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/uplink_processor_baseband.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"
#include "ocudu/gateways/baseband/baseband_gateway_timestamp.h"


namespace ocudu {


class baseband_gateway_buffer_reader;

/// \brief Lower physical layer uplink processor - Baseband interface.
///
/// Processes baseband samples. It derives the symbol and slot timing from the number of processed samples.

/// \brief Lower physical layer uplink processor - Baseband interface.
///
/// Processes baseband samples. It derives the symbol and slot timing from the number of processed samples.
class uplink_processor_baseband
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplink_processor_baseband() = default;

  /// \brief Processes any number of baseband samples.
  ///
  /// \param[in] buffer    Baseband samples to process.
  /// \param[in] timestamp Time instant in which the first sample was captured.
  /// \remark The number of channels in \c buffer must be equal to the number of receive ports for the sector.

  /// \brief Processes any number of baseband samples.
  ///
  /// \param[in] buffer    Baseband samples to process.
  /// \param[in] timestamp Time instant in which the first sample was captured.
  /// \remark The number of channels in \c buffer must be equal to the number of receive ports for the sector.
  virtual void process(const baseband_gateway_buffer_reader& buffer, baseband_gateway_timestamp timestamp) = 0;
};


} // namespace ocudu
