// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_paging_information_handler.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/paging_information.h"


namespace ocudu {

/// \brief Interface to handle paging information from the CU-CP.

/// \brief Interface to handle paging information from the CU-CP.
class mac_paging_information_handler
{
public:
  virtual ~mac_paging_information_handler() = default;

  /// \brief Handles Paging information.
  ///
  /// \param msg Information of the paging message to schedule.

  /// \brief Handles Paging information.
  ///
  /// \param msg Information of the paging message to schedule.
  virtual void handle_paging_information(const paging_information& msg) = 0;
};


} // namespace ocudu
