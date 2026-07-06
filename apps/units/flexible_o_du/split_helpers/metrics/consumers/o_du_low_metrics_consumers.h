// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/metrics/consumers/o_du_low_metrics_consumers.h  (50 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"


namespace ocudu {


namespace app_services {
class remote_server_metrics_gateway;
} // namespace app_services


namespace odu {
struct o_du_low_metrics;
} // namespace odu

/// JSON handler for the O-DU low metrics.

/// JSON handler for the O-DU low metrics.
class o_du_low_metrics_consumer_json
{
public:
  explicit o_du_low_metrics_consumer_json(app_services::remote_server_metrics_gateway& gateway_) : gateway(gateway_) {}

  // Handles the O-RU metrics.

  // Handles the O-RU metrics.
  void handle_metric(const odu::o_du_low_metrics& metric);


private:
  app_services::remote_server_metrics_gateway& gateway;
};

/// Logger consumer for the O-DU low metrics.

/// Logger consumer for the O-DU low metrics.
class o_du_low_metrics_consumer_log
{
public:
  o_du_low_metrics_consumer_log(ocudulog::log_channel& log_chan_, bool verbose_) :
    log_chan(log_chan_), verbose(verbose_)
  {
    ocudu_assert(log_chan.enabled(), "JSON log channel is not enabled");
  }

  // Handles the O-RU metrics.

  // Handles the O-RU metrics.
  void handle_metric(const odu::o_du_low_metrics& metric);


private:
  ocudulog::log_channel& log_chan;
  const bool             verbose;
};


} // namespace ocudu
