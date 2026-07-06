// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/ru_error_notifier.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// Radio Unit error context.

/// Radio Unit error context.
struct ru_error_context {
  /// Slot context.
  /// Slot context.
  slot_point slot;
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
};

/// Radio Unit interface error notifier.

/// Radio Unit interface error notifier.
class ru_error_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ru_error_notifier() = default;

  /// \brief Notifies a late downlink message.
  ///
  /// \param[in] context Context of the error.

  /// \brief Notifies a late downlink message.
  ///
  /// \param[in] context Context of the error.
  virtual void on_late_downlink_message(const ru_error_context& context) = 0;

  /// \brief Notifies a late uplink request message.
  ///
  /// \param[in] context Context of the error.

  /// \brief Notifies a late uplink request message.
  ///
  /// \param[in] context Context of the error.
  virtual void on_late_uplink_message(const ru_error_context& context) = 0;

  /// \brief Notifies a late PRACH request message.
  ///
  /// \param[in] context Context of the error.

  /// \brief Notifies a late PRACH request message.
  ///
  /// \param[in] context Context of the error.
  virtual void on_late_prach_message(const ru_error_context& context) = 0;
};


} // namespace ocudu
