// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: metrics/du_high_rlc_metrics_producer.cpp
//
// Purpose (plain English):
//   One-liner implementation: wraps the raw rlc_metrics into an
//   rlc_metrics_impl and notifies the framework. The framework then calls
//   the rlc_metrics_callback (defined in du_high_rlc_metrics.h) which
//   dispatches handle_metric() on all registered consumers.
// =============================================================================

#include "du_high_rlc_metrics_producer.h"
#include "du_high_rlc_metrics.h"


using namespace ocudu;


void rlc_metrics_producer_impl::report_metrics(const rlc_metrics& report)
{
  // Wrap the raw data and push it into the metrics fan-out pipeline.
  notifier.on_new_metric(rlc_metrics_impl(report));
}
