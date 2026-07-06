// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_high/du_high_clock_controller.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/mac_clock_controller.h"
#include <memory>


namespace ocudu {


class task_executor;
class io_broker;
class timer_manager;


namespace odu {

/// Creates a clock controller for the DU-high that allows switching between automatic and manual ticking modes.

/// Creates a clock controller for the DU-high that allows switching between automatic and manual ticking modes.
std::unique_ptr<mac_clock_controller>
create_du_high_clock_controller(timer_manager& timers, io_broker& broker, task_executor& tick_exec);


} // namespace odu
} // namespace ocudu
