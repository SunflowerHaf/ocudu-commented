// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/consumers/du_procedure_metrics_consumers.h
//
// Purpose (plain English):
//   Logger consumer for DU management procedure metrics — specifically how
//   long UE-creation procedures take. Written to the log once per metrics
//   period as "DU manager metrics: nof_ue_creations=N avg=Xusec max=Yusec".
// =============================================================================

#pragma once


#include "ocudu/du/du_high/du_manager/du_procedure_metrics_report.h"
#include "ocudu/ocudulog/log_channel.h"
#include <optional>


namespace ocudu {

/// Logger consumer for the DU procedure metrics.

/// Logs DU procedure statistics (UE creation latency).
class du_procedure_metrics_consumer_log
{
public:
  explicit du_procedure_metrics_consumer_log(ocudulog::log_channel& log_chan_) : log_chan(log_chan_) {}

  /// Handle the given DU procedure metrics.

  /// Handle a (possibly absent) procedure metrics report.
  void handle_metric(const std::optional<odu::du_procedure_metrics_report>& report);


private:
  ocudulog::log_channel& log_chan;
};


} // namespace ocudu
