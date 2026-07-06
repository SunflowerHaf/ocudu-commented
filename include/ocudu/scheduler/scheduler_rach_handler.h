// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/scheduler_rach_handler.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/rnti.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// RACH indication Message. It contains all the RACHs detected in a given slot and cell.

/// RACH indication Message. It contains all the RACHs detected in a given slot and cell.
struct rach_indication_message {
  du_cell_index_t cell_index;
  slot_point      slot_rx;


  struct preamble {
    unsigned preamble_id;
    /// Allocated TC-RNTI, for Contention-based RACH, or C-RNTI, for Contention-free RACH.
    /// Allocated TC-RNTI, for Contention-based RACH, or C-RNTI, for Contention-free RACH.
    rnti_t        tc_rnti;
    phy_time_unit time_advance;
  };


  struct occasion {
    /// Index of the first OFDM Symbol where RACH was detected.
    /// Index of the first OFDM Symbol where RACH was detected.
    unsigned                                                  start_symbol;
    unsigned                                                  frequency_index;
    static_vector<preamble, MAX_PREAMBLES_PER_PRACH_OCCASION> preambles;
  };


  static_vector<occasion, MAX_PRACH_OCCASIONS_PER_SLOT> occasions;
};


class scheduler_rach_handler
{
public:
  virtual ~scheduler_rach_handler() = default;

  /// \brief Handle RACH indication message.

  /// \brief Handle RACH indication message.
  virtual void handle_rach_indication(const rach_indication_message& msg) = 0;
};


} // namespace ocudu
