// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/flexible_o_du_factory.h  (33 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "apps/units/flexible_o_du/o_du_unit.h"
#include "apps/units/flexible_o_du/split_helpers/flexible_o_du_configs.h"
#include "ocudu/ru/ru.h"


namespace ocudu {


class flexible_o_du_metrics_notifier;

/// Flexible O-RAN DU factory interface.

/// Flexible O-RAN DU factory interface.
class flexible_o_du_factory
{
  const flexible_o_du_unit_config config;


public:
  explicit flexible_o_du_factory(const flexible_o_du_unit_config& config_) : config(config_) {}
  virtual ~flexible_o_du_factory() = default;

  /// Creates a flexible O-RAN DU using the given dependencies and configuration.

  /// Creates a flexible O-RAN DU using the given dependencies and configuration.
  o_du_unit create_flexible_o_du(const o_du_unit_dependencies& dependencies);


private:
  /// Creates a Radio Unit using the given config and dependencies.
  /// Creates a Radio Unit using the given config and dependencies.
  virtual std::unique_ptr<radio_unit> create_radio_unit(const flexible_o_du_ru_config&       ru_config,
                                                        const flexible_o_du_ru_dependencies& ru_dependencies) = 0;
};


} // namespace ocudu
