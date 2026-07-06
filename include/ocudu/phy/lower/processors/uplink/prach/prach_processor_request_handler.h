// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/prach/prach_processor_request_handler.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/shared_prach_buffer.h"


namespace ocudu {


struct prach_buffer_context;

/// \brief Lower physical layer PRACH processor - Request handler interface.
///
/// This class provides an interface for requesting the capture and demodulation of PRACH occasions.

/// \brief Lower physical layer PRACH processor - Request handler interface.
///
/// This class provides an interface for requesting the capture and demodulation of PRACH occasions.
class prach_processor_request_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~prach_processor_request_handler() = default;

  /// \brief Handles a new PRACH request.
  ///
  /// The PRACH buffer and context provided to this method are forwarded to a dedicated block that takes care of the
  /// request asynchronously. A notification through the \ref prach_processor_notifier interface will inform the client
  /// that the request has been processed and that the PRACH demodulated sequence is available in \c buffer.
  ///
  /// \param[in] buffer Destination PRACH buffer.
  /// \param[in] context PRACH context.

  /// \brief Handles a new PRACH request.
  ///
  /// The PRACH buffer and context provided to this method are forwarded to a dedicated block that takes care of the
  /// request asynchronously. A notification through the \ref prach_processor_notifier interface will inform the client
  /// that the request has been processed and that the PRACH demodulated sequence is available in \c buffer.
  ///
  /// \param[in] buffer Destination PRACH buffer.
  /// \param[in] context PRACH context.
  virtual void handle_request(shared_prach_buffer buffer, const prach_buffer_context& context) = 0;
};


} // namespace ocudu
