// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/flexible_o_du_ntn_configuration_manager_factory.h  (39 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ntn/ntn_configuration_manager.h"
#include "ocudu/ntn/ntn_configuration_manager_config.h"
#include <memory>


namespace ocudu {


class task_executor;
class timer_manager;
class ru_controller;
struct application_unit_commands;
class mac_subframe_time_mapper;


namespace odu {
class du_configurator;
} // namespace odu

/// NTN Configuration Manager factory interface.
/// \param ntn_cfg  NTN Configuration Manager config.
/// \param du_cfgtr DU configurator interface.
/// \param du_time_mapper_accessor entity to access MAC slot-time mapper.
/// \param ru_ctrl  RU controller interface.
/// \param timers   Timers for the update task.
/// \param timer_exec Task executor for the periodic SIB19 update task.
/// \return True on success.

/// NTN Configuration Manager factory interface.
/// \param ntn_cfg  NTN Configuration Manager config.
/// \param du_cfgtr DU configurator interface.
/// \param du_time_mapper_accessor entity to access MAC slot-time mapper.
/// \param ru_ctrl  RU controller interface.
/// \param timers   Timers for the update task.
/// \param timer_exec Task executor for the periodic SIB19 update task.
/// \return True on success.
std::unique_ptr<ocudu_ntn::ntn_configuration_manager>
create_ntn_configuration_manager(const ocudu_ntn::ntn_configuration_manager_config& ntn_cfg,
                                 odu::du_configurator&                              du_cfgtr,
                                 mac_subframe_time_mapper&                          du_time_mapper_accessor,
                                 ru_controller&                                     ru_ctrl,
                                 timer_manager&                                     timers,
                                 task_executor&                                     timer_exec);


} // namespace ocudu
