// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_sdu_handler.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/adt/byte_buffer_chain.h"
#include "ocudu/rlc/rlc_buffer_state.h"


namespace ocudu {

/// This interface notifies to upper layers the reception of new SDUs over a logical channel.

/// This interface notifies to upper layers the reception of new SDUs over a logical channel.
class mac_sdu_rx_notifier
{
public:
  virtual ~mac_sdu_rx_notifier() = default;

  /// This callback is invoked on each received SDU.

  /// This callback is invoked on each received SDU.
  virtual void on_new_sdu(byte_buffer_slice sdu) = 0;
};

/// This interface represents the entry point of a logical channel in the MAC layer.

/// This interface represents the entry point of a logical channel in the MAC layer.
class mac_sdu_tx_builder
{
public:
  virtual ~mac_sdu_tx_builder() = default;

  /// Called by MAC to generate an MAC Tx SDU for the respective logical channel.
  /// \param mac_sdu_space The buffer of bytes where the MAC SDU payload will be written.
  /// \return Generated MAC SDU size.

  /// Called by MAC to generate an MAC Tx SDU for the respective logical channel.
  /// \param mac_sdu_space The buffer of bytes where the MAC SDU payload will be written.
  /// \return Generated MAC SDU size.
  virtual size_t on_new_tx_sdu(span<uint8_t> mac_sdu_space) = 0;

  /// Called by MAC to obtain the DL BSR for the respective logical channel.

  /// Called by MAC to obtain the DL BSR for the respective logical channel.
  virtual rlc_buffer_state on_buffer_state_update() = 0;
};


} // namespace ocudu
