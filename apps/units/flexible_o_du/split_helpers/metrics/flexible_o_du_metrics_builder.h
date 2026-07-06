// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/metrics/flexible_o_du_metrics_builder.h  (36 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "apps/helpers/metrics/metrics_config.h"
#include "apps/services/cmdline/stdout_metrics_command.h"
#include "apps/services/metrics/metrics_config.h"
#include "ocudu/ran/pci.h"


namespace ocudu {


class flexible_o_du_metrics_notifier;


namespace app_helpers {
struct metrics_config;
} // namespace app_helpers


namespace app_services {
class metrics_notifier;
class remote_server_metrics_gateway;
} // namespace app_services

/// Builds the flexible O-DU metrics configuration.

/// Builds the flexible O-DU metrics configuration.
flexible_o_du_metrics_notifier* build_flexible_o_du_metrics_config(
    std::vector<app_services::metrics_config>& metrics,
    std::vector<std::unique_ptr<app_services::toggle_stdout_metrics_app_command::metrics_subcommand>>&
                                                 metrics_subcommands,
    app_services::metrics_notifier&              notifier,
    app_services::remote_server_metrics_gateway* remote_metrics_gateway,
    const app_helpers::metrics_config&           metrics_cfg,
    const std::vector<pci_t>&                    pci_cell_map,
    std::chrono::nanoseconds                     symbol_duration);


} // namespace ocudu
