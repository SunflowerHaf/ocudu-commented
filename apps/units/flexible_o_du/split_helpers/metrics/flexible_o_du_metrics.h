// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/metrics/flexible_o_du_metrics.h  (18 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/du/o_du_metrics.h"
#include "ocudu/ru/ru_metrics.h"


namespace ocudu {

/// Flexible O-RAN DU metrics.

/// Flexible O-RAN DU metrics.
struct flexible_o_du_metrics {
  odu::o_du_metrics du;
  ru_metrics        ru;
};


} // namespace ocudu
