// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/upper_phy_error_notifier.h  (34 lines)
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

/// Upper physical layer error notifier.

/// Upper physical layer error notifier.
class upper_phy_error_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~upper_phy_error_notifier() = default;

  /// \brief Notifies a late downlink message.
  ///
  /// \param[in] dl_msg_slot Slot of the downlink message.

  /// \brief Notifies a late downlink message.
  ///
  /// \param[in] dl_msg_slot Slot of the downlink message.
  virtual void on_late_downlink_message(slot_point dl_msg_slot) = 0;

  /// \brief Notifies a late uplink request message.
  ///
  /// \param[in] ul_msg_slot Slot of the uplink message.

  /// \brief Notifies a late uplink request message.
  ///
  /// \param[in] ul_msg_slot Slot of the uplink message.
  virtual void on_late_uplink_message(slot_point ul_msg_slot) = 0;

  /// \brief Notifies a late PRACH request message.
  ///
  /// \param[in] prach_msg_slot Slot of the uplink message.

  /// \brief Notifies a late PRACH request message.
  ///
  /// \param[in] prach_msg_slot Slot of the uplink message.
  virtual void on_late_prach_message(slot_point prach_msg_slot) = 0;
};


} // namespace ocudu
