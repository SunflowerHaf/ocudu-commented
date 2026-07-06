// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/mac/mac_sched/positioning_handler.h  (41 lines)
//
// LIBRARY: lib/mac
// Medium Access Control (MAC, TS 38.321): scheduler interface adaptor, HARQ process management, multiplexing/demultiplexing of logical channels into transport blocks, random-access (RACH) handling, and timing-advance control. Interfaces: MAC SDU to/from RLC, MAC PDU to/from the lower PHY via FAPI.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/mac_cell_control_information_handler.h"
#include "ocudu/mac/mac_cell_manager.h"
#include "ocudu/mac/mac_positioning_measurement_handler.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/timers.h"


namespace ocudu {


class scheduler_positioning_handler;
class task_executor;


class cell_positioning_handler
{
public:
  virtual ~cell_positioning_handler() = default;

  /// Handle SRS indication from lower layers.

  /// Handle SRS indication from lower layers.
  virtual void handle_srs_indication(const mac_srs_indication_message& msg) = 0;
};


class positioning_handler : public mac_positioning_measurement_handler
{
public:
  virtual ~positioning_handler() = default;

  /// Create a cell handler.

  /// Create a cell handler.
  virtual std::unique_ptr<cell_positioning_handler> add_cell(du_cell_index_t cell_index) = 0;
};


std::unique_ptr<positioning_handler> create_positioning_handler(scheduler_positioning_handler& sched,
                                                                task_executor&                 ctrl_exec,
                                                                timer_manager&                 timers,
                                                                ocudulog::basic_logger&        logger);


} // namespace ocudu
