// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/ru_timing_notifier.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/slot_point_extended.h"


namespace ocudu {

/// TTI boundary context.

/// TTI boundary context.
struct tti_boundary_context {
  /// Slot point associated with the time point.
  /// Slot point associated with the time point.
  slot_point_extended slot;
  /// Time point associated to the slot point.
  /// Time point associated to the slot point.
  std::chrono::time_point<std::chrono::system_clock> time_point;
};

/// Radio Unit interface to notify timing related events.

/// Radio Unit interface to notify timing related events.
class ru_timing_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ru_timing_notifier() = default;

  /// \brief Notifies a new TTI boundary event.
  ///
  /// Notifies that the processing of a new slot has started.
  ///
  /// \param[in] slot_context Slot time point context.

  /// \brief Notifies a new TTI boundary event.
  ///
  /// Notifies that the processing of a new slot has started.
  ///
  /// \param[in] slot_context Slot time point context.
  virtual void on_tti_boundary(const tti_boundary_context& slot_context) = 0;

  /// \brief Notifies that an uplink half slot has been received and processed by the Radio Unit.
  ///
  /// \param[in] slot Current slot.

  /// \brief Notifies that an uplink half slot has been received and processed by the Radio Unit.
  ///
  /// \param[in] slot Current slot.
  virtual void on_ul_half_slot_boundary(slot_point slot) = 0;

  /// \brief Notifies that an uplink full slot has been received and processed by the Radio Unit.
  ///
  /// \param[in] slot Current slot.

  /// \brief Notifies that an uplink full slot has been received and processed by the Radio Unit.
  ///
  /// \param[in] slot Current slot.
  virtual void on_ul_full_slot_boundary(slot_point slot) = 0;
};


} // namespace ocudu
