// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/metrics/du_metrics_aggregator_impl.h  (52 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "du_procedure_metrics_collector.h"
#include "ocudu/du/du_high/du_manager/du_manager.h"
#include "ocudu/du/du_high/du_manager/du_manager_params.h"
#include "ocudu/du/du_high/du_metrics_notifier.h"


namespace ocudu {


class mac_metrics_notifier;
class scheduler_metrics_notifier;
struct scheduler_metrics_report;


namespace odu {


class du_manager_metrics_aggregator_impl final : public du_manager_mac_metric_aggregator
{
public:
  du_manager_metrics_aggregator_impl(const du_manager_params::metrics_config_params& params_,
                                     task_executor&                                  du_mng_exec_,
                                     timer_manager&                                  timers_,
                                     f1ap_metrics_collector&                         f1ap_collector_);
  ~du_manager_metrics_aggregator_impl() override;

  // DU metrics collector interface

  // DU metrics collector interface
  void aggregate_mac_metrics_report(const mac_metric_report& report) override;

  /// Get collector of DU control-plane procedure metrics.

  /// Get collector of DU control-plane procedure metrics.
  du_procedure_metrics_collector& get_proc_collector() { return du_mng_collector; }


  void handle_cell_start(du_cell_index_t cell_index);
  void handle_cell_stop(du_cell_index_t cell_index);


private:
  void trigger_report();


  const du_manager_params::metrics_config_params params;
  task_executor&                                 du_mng_exec;
  timer_manager&                                 timers;
  f1ap_metrics_collector&                        f1ap_collector;
  du_procedure_metrics_collector                 du_mng_collector;


  unsigned          next_version = 0;
  du_metrics_report next_report{};
};


} // namespace odu
} // namespace ocudu
