// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p5/p5_operational_change_request_notifier.h  (33 lines)
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


struct cell_configuration;

/// \brief P5 FAPI operational change request notifier.
///
/// Notifies that P5 FAPI START/STOP request messages have been processed and requests a change in the operational state
/// of the cell.

/// \brief P5 FAPI operational change request notifier.
///
/// Notifies that P5 FAPI START/STOP request messages have been processed and requests a change in the operational state
/// of the cell.
class p5_operational_change_request_notifier
{
public:
  virtual ~p5_operational_change_request_notifier() = default;

  /// \brief Notifies a start request from FAPI.
  ///
  /// This method is synchronous, as such, when this callback returns the start procedure will be completed. Returns
  /// true on start success, otherwise false.

  /// \brief Notifies a start request from FAPI.
  ///
  /// This method is synchronous, as such, when this callback returns the start procedure will be completed. Returns
  /// true on start success, otherwise false.
  virtual bool on_start_request(const cell_configuration& config) = 0;

  /// \brief Notifies a stop request from FAPI.
  ///
  /// This method is synchronous, so when this function returns the stop process is already finished.

  /// \brief Notifies a stop request from FAPI.
  ///
  /// This method is synchronous, so when this function returns the stop process is already finished.
  virtual void on_stop_request() = 0;
};


} // namespace fapi
} // namespace ocudu
