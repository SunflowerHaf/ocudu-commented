// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Interface of the upper-PHY notifier in charge of requesting symbol captures.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/upper_phy_rx_symbol_request_notifier.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Interface of the upper-PHY notifier in charge of requesting symbol captures.

#pragma once


#include "ocudu/phy/support/shared_prach_buffer.h"


namespace ocudu {


struct prach_buffer_context;
class resource_grid;
class shared_resource_grid;
struct resource_grid_context;

/// \brief Interface of the upper-PHY notifier in charge of requesting symbol captures.

/// \brief Interface of the upper-PHY notifier in charge of requesting symbol captures.
class upper_phy_rx_symbol_request_notifier
{
public:
  virtual ~upper_phy_rx_symbol_request_notifier() = default;

  /// \brief Notifies the event of a PRACH capture request.
  ///
  /// \param[in] context PRACH window context.
  /// \param[in] buffer  Buffer to be used by the request handler to write the PRACH window.

  /// \brief Notifies the event of a PRACH capture request.
  ///
  /// \param[in] context PRACH window context.
  /// \param[in] buffer  Buffer to be used by the request handler to write the PRACH window.
  virtual void on_prach_capture_request(const prach_buffer_context& context, shared_prach_buffer buffer) = 0;

  /// \brief Notifies the event of an uplink slot request.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid    Grid in which to store the captured data.

  /// \brief Notifies the event of an uplink slot request.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid    Grid in which to store the captured data.
  virtual void on_uplink_slot_request(const resource_grid_context& context, const shared_resource_grid& grid) = 0;
};


} // namespace ocudu
