// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/e2/e2_metric_connector_manager.h
//
// Purpose (plain English):
//   A thin generic container that holds one E2 metric connector object per
//   cell. Templated so the same manager class works for DU, CU-CP, and CU-UP
//   metrics (each unit uses a different concrete ConnectorType / NotifierType /
//   InterfaceType triple).
//
//   The E2 metric connector sits between the RAN layer that produces metrics
//   (the scheduler, RLC, PDCP, etc.) and the E2 agent that sends them to the
//   RIC in E2SM-KPM Indication messages. It exposes two views:
//     get_e2_metric_notifier(i)   — the "push" side: the RAN layer calls this
//                                   to report a new metric sample.
//     get_e2_metrics_interface(i) — the "pull" side: the E2 agent reads from
//                                   this to build its KPM reports.
// =============================================================================
#pragma once


#include "ocudu/support/ocudu_assert.h"
#include <cassert>
#include <memory>
#include <vector>


namespace ocudu {

/// Manages the E2 metric connectors of the app.

template <typename ConnectorType, typename NotifierType, typename InterfaceType>
class e2_metric_connector_manager
{
public:
  e2_metric_connector_manager(unsigned nof_cells = 1)
  {
    for (unsigned i = 0, e = nof_cells; i != e; ++i) {
      e2_metric_connectors.push_back(std::make_shared<ConnectorType>());
    }
  }


  ~e2_metric_connector_manager() = default;


  e2_metric_connector_manager(e2_metric_connector_manager&& other) noexcept :
    e2_metric_connectors(std::move(other.e2_metric_connectors))
  {
  }


  /// Returns the notifier interface for the given cell index.
  NotifierType& get_e2_metric_notifier(unsigned index)
  {
    ocudu_assert(index < e2_metric_connectors.size(), "Invalid index");
    return *(e2_metric_connectors[index]);
  }

  /// Returns the metrics-read interface for the given cell index.
  InterfaceType& get_e2_metrics_interface(unsigned index)
  {
    ocudu_assert(index < e2_metric_connectors.size(), "Invalid index");
    return *(e2_metric_connectors[index]);
  }


private:
  std::vector<std::shared_ptr<ConnectorType>> e2_metric_connectors;
};


} // namespace ocudu
