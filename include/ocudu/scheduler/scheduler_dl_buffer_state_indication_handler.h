// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/scheduler_dl_buffer_state_indication_handler.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/du_types.h"
#include "ocudu/ran/logical_channel/lcid.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// DL buffer state for a given RLC bearer.

/// DL buffer state for a given RLC bearer.
struct dl_buffer_state_indication_message {
  du_ue_index_t ue_index;
  lcid_t        lcid;
  unsigned      bs;
  /// Time-of-arrival, in slots, of the oldest PDU in the RLC entity Tx buffer.
  /// Time-of-arrival, in slots, of the oldest PDU in the RLC entity Tx buffer.
  slot_point hol_toa;
};

/// Scheduler interface to push DL buffer state updates for a given RLC bearer.

/// Scheduler interface to push DL buffer state updates for a given RLC bearer.
class scheduler_dl_buffer_state_indication_handler
{
public:
  virtual ~scheduler_dl_buffer_state_indication_handler() = default;

  /// Forward DL buffer state update to scheduler.

  /// Forward DL buffer state update to scheduler.
  virtual void handle_dl_buffer_state_indication(const dl_buffer_state_indication_message& bs) = 0;
};


} // namespace ocudu
