// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/p7_last_request_notifier.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace fapi {

/// \brief Slot-based, last message notifier interface.
///
/// This interface notifies, for each slot, the transmission of the last FAPI request that has been sent through the
/// FAPI message gateway.

/// \brief Slot-based, last message notifier interface.
///
/// This interface notifies, for each slot, the transmission of the last FAPI request that has been sent through the
/// FAPI message gateway.
class p7_last_request_notifier
{
public:
  virtual ~p7_last_request_notifier() = default;

  /// \brief Notifies the transmission of the last message corresponding to the given slot.
  ///
  /// \param[in] slot Current slot.

  /// \brief Notifies the transmission of the last message corresponding to the given slot.
  ///
  /// \param[in] slot Current slot.
  virtual void on_last_message(slot_point slot) = 0;
};


} // namespace fapi
} // namespace ocudu
