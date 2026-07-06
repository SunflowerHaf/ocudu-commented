// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_ue_control_information_handler.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/du_types.h"
#include "ocudu/ran/logical_channel/lcid.h"
#include <chrono>
#include <optional>


namespace ocudu {

/// DL Buffer state for a given RLC bearer.

/// DL Buffer state for a given RLC bearer.
struct mac_dl_buffer_state_indication_message {
  du_ue_index_t ue_index;
  lcid_t        lcid;
  /// Buffer Occupancy value in bytes.
  /// Buffer Occupancy value in bytes.
  unsigned bs;
  /// \brief Time-of-arrival of the oldest PDU in the RLC entity Tx buffer. This metric is relevant for delay
  /// prioritization in the scheduler.
  /// \brief Time-of-arrival of the oldest PDU in the RLC entity Tx buffer. This metric is relevant for delay
  /// prioritization in the scheduler.
  std::optional<std::chrono::system_clock::time_point> hol_toa;
};


class mac_ue_control_information_handler
{
public:
  virtual ~mac_ue_control_information_handler() = default;

  /// Forwards a new DL buffer state for a given UE and logical channel to the MAC.
  /// \param dl_bs Updated DL buffer state information for a logical channel.

  /// Forwards a new DL buffer state for a given UE and logical channel to the MAC.
  /// \param dl_bs Updated DL buffer state information for a logical channel.
  virtual void handle_dl_buffer_state_update(const mac_dl_buffer_state_indication_message& dl_bs) = 0;
};


} // namespace ocudu
