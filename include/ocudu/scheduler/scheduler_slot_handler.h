// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/scheduler_slot_handler.h  (35 lines)
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
#include "ocudu/ran/slot_point_extended.h"


namespace ocudu {


struct sched_result;

/// Interface to forward slot indications and error indications to the MAC scheduler.

/// Interface to forward slot indications and error indications to the MAC scheduler.
class scheduler_slot_handler
{
public:
  /// \brief Effect that the errors in the lower layers had on the results provided by the scheduler for a given
  /// slot and cell.
  /// \brief Effect that the errors in the lower layers had on the results provided by the scheduler for a given
  /// slot and cell.
  struct error_outcome {
    bool pdcch_discarded : 1;
    bool pdsch_discarded : 1;
    bool pusch_and_pucch_discarded : 1;
  };


  virtual ~scheduler_slot_handler() = default;

  /// \brief Handle slot indications that arrive to the scheduler for a given cell.

  /// \brief Handle slot indications that arrive to the scheduler for a given cell.
  virtual const sched_result& slot_indication(slot_point_extended sl_tx, du_cell_index_t cell_index) = 0;

  /// \brief Handle error indications caused by lates or invalid scheduling results.

  /// \brief Handle error indications caused by lates or invalid scheduling results.
  virtual void handle_error_indication(slot_point sl_tx, du_cell_index_t cell_index, error_outcome event) = 0;
};


} // namespace ocudu
