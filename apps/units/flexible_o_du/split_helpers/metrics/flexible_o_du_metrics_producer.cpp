// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/metrics/flexible_o_du_metrics_producer.cpp  (15 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "flexible_o_du_metrics_producer.h"
#include "flexible_o_du_app_service_metrics.h"


using namespace ocudu;


void o_du_metrics_producer_impl::on_new_metrics(const flexible_o_du_metrics& metrics)
{
  flexible_o_du_app_service_metrics_impl metric_set(metrics);


  notifier.on_new_metric(metric_set);
}
