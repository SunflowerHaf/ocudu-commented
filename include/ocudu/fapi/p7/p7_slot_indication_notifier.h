// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/p7_slot_indication_notifier.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {
namespace fapi {


struct slot_indication;

/// \brief P7 slot indication message notifier interface.
///
/// This interface notifies the reception of slot indications from the underlying PHY.

/// \brief P7 slot indication message notifier interface.
///
/// This interface notifies the reception of slot indications from the underlying PHY.
class p7_slot_indication_notifier
{
public:
  virtual ~p7_slot_indication_notifier() = default;

  /// \brief Notifies the reception of a slot indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a slot indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_slot_indication(const slot_indication& msg) = 0;
};


} // namespace fapi
} // namespace ocudu
