// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rlc/rlc_entity.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/rlc
// RLC interface headers: rlc_rx_pdu_handler and rlc_tx_sdu_handler (data path interfaces), rlc_rx_am_status_notifier (ARQ status report callback), rlc_metrics_notifier, and the RLC entity configuration types for AM, UM, and TM modes.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/rlc/rlc_metrics.h"
#include "ocudu/rlc/rlc_rx.h"
#include "ocudu/rlc/rlc_tx.h"


namespace ocudu {

/// Class used to interface with an RLC entity.
/// It will contain getters for the TX and RX entities interfaces.

/// Class used to interface with an RLC entity.
/// It will contain getters for the TX and RX entities interfaces.
class rlc_entity
{
public:
  rlc_entity()                             = default;
  virtual ~rlc_entity()                    = default;
  rlc_entity(const rlc_entity&)            = delete;
  rlc_entity& operator=(const rlc_entity&) = delete;
  rlc_entity(rlc_entity&&)                 = delete;
  rlc_entity& operator=(rlc_entity&&)      = delete;

  /// \brief Stops all internal timers.
  ///
  /// This function is inteded to be called upon removal of the bearer before destroying it.
  /// It stops all timers with handlers that may delegate tasks to another executor that could face a deleted object at
  /// a later execution time.
  /// Before this function is called, the adjacent layers should already be disconnected so that no timer is restarted.
  ///
  /// Note: This function shall only be called from ue_executor.

  /// \brief Stops all internal timers.
  ///
  /// This function is inteded to be called upon removal of the bearer before destroying it.
  /// It stops all timers with handlers that may delegate tasks to another executor that could face a deleted object at
  /// a later execution time.
  /// Before this function is called, the adjacent layers should already be disconnected so that no timer is restarted.
  ///
  /// Note: This function shall only be called from ue_executor.
  virtual void stop() = 0;


  virtual rlc_tx_upper_layer_data_interface* get_tx_upper_layer_data_interface() = 0;
  virtual rlc_tx_lower_layer_interface*      get_tx_lower_layer_interface()      = 0;
  virtual rlc_rx_lower_layer_interface*      get_rx_lower_layer_interface()      = 0;
  virtual rlc_metrics                        get_metrics()                       = 0;
};


} // namespace ocudu
