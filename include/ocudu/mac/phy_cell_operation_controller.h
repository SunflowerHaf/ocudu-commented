// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/phy_cell_operation_controller.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/async/async_task.h"


namespace ocudu {

/// PHY cell operation controller that handles cell activation/deactivation.

/// PHY cell operation controller that handles cell activation/deactivation.
class phy_cell_operation_controller
{
public:
  virtual ~phy_cell_operation_controller() = default;

  /// Starts the cell.

  /// Starts the cell.
  virtual async_task<bool> start() = 0;

  /// Stops the cell.

  /// Stops the cell.
  virtual async_task<bool> stop() = 0;
};


} // namespace ocudu
