// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/metrics/du_procedure_metrics_collector.h  (54 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/du/du_high/du_manager/du_procedure_metrics_report.h"
#include <algorithm>


namespace ocudu::odu {

/// Collector of metrics associated with procedures in the DU manager.

/// Collector of metrics associated with procedures in the DU manager.
class du_procedure_metrics_collector
{
public:
  du_procedure_metrics_collector(bool enabled_) : active_flag(enabled_) {}

  /// Called on the completion of a UE creation procedure.

  /// Called on the completion of a UE creation procedure.
  void on_ue_creation_completion(std::chrono::nanoseconds latency)
  {
    data.ue_create_count++;
    data.sum_ue_creation_latency += latency;
    data.max_ue_creation_latency = std::max(data.max_ue_creation_latency, latency);
  }


  void reset() { data = {}; }


  void collect_metric_report(du_procedure_metrics_report& report)
  {
    report.average_ue_creation_latency = data.ue_create_count > 0
                                             ? (data.sum_ue_creation_latency / data.ue_create_count)
                                             : std::chrono::nanoseconds::zero();
    report.max_ue_creation_latency     = data.max_ue_creation_latency;
    report.nof_ue_creations            = data.ue_create_count;

    // Reset non-persistent metrics.

    // Reset non-persistent metrics.
    reset();
  }


  bool enabled() const { return active_flag; }


private:
  struct non_persistent_metrics {
    unsigned                 ue_create_count = 0;
    std::chrono::nanoseconds sum_ue_creation_latency{0};
    std::chrono::nanoseconds max_ue_creation_latency{0};
  };


  bool active_flag = false;


  non_persistent_metrics data;
};


} // namespace ocudu::odu
