// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/config/scheduler_expert_config_validator.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/scheduler/config/scheduler_expert_config.h"
#include <string>


namespace ocudu {

/// \brief Checks whether the provided scheduler expert configuration is valid.
///
/// \param config Scheduler expert configuration.
/// \return In case an invalid parameter is detected, returns a string containing an error message.

/// \brief Checks whether the provided scheduler expert configuration is valid.
///
/// \param config Scheduler expert configuration.
/// \return In case an invalid parameter is detected, returns a string containing an error message.
inline error_type<std::string> is_scheduler_expert_config_valid(const scheduler_expert_config& config)
{
  // :TODO: Implement me!
  // :TODO: Implement me!
  return {};
}


} // namespace ocudu
