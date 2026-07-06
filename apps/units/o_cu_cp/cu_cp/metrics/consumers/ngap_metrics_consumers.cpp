// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_cp/cu_cp/metrics/consumers/ngap_metrics_consumers.cpp  (21 lines)
//
// Purpose (plain English):
//   Part of the O-RAN CU-CP/CU-UP application unit infrastructure layer.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ngap_metrics_consumers.h"


using namespace ocudu;


void ngap_metrics_consumer_log::handle_metric(const std::vector<ngap_info>&      report,
                                              const mobility_management_metrics& mobility_metrics)
{
  if (report.empty()) {
    return;
  }


  fmt::memory_buffer buffer;
  fmt::format_to(std::back_inserter(buffer), "CU-CP NGAP metrics: {}", format_ngap_metrics(report, mobility_metrics));


  log_chan("{}", to_c_str(buffer));
  buffer.clear();
}
