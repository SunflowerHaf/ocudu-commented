// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/upper_phy_error_handler.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// Upper physical layer error handler.

/// Upper physical layer error handler.
class upper_phy_error_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~upper_phy_error_handler() = default;

  /// \brief Handles a late downlink message.
  ///
  /// \param[in] slot Slot of the downlink message.

  /// \brief Handles a late downlink message.
  ///
  /// \param[in] slot Slot of the downlink message.
  virtual void handle_late_downlink_message(slot_point slot) = 0;

  /// \brief Handles a late uplink message.
  ///
  /// \param[in] slot Slot of the uplink message.

  /// \brief Handles a late uplink message.
  ///
  /// \param[in] slot Slot of the uplink message.
  virtual void handle_late_uplink_message(slot_point slot) = 0;

  /// \brief Handles a late PRACH request message.
  ///
  /// \param[in] slot Slot of the PRACH request message.

  /// \brief Handles a late PRACH request message.
  ///
  /// \param[in] slot Slot of the PRACH request message.
  virtual void handle_late_prach_message(slot_point slot) = 0;
};


} // namespace ocudu
