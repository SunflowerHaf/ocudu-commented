// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: metrics/du_high_rlc_metrics_consumers.h
//
// Purpose (plain English):
//   Declares the three "sink" objects for RLC metrics — one per output channel:
//
//     rlc_metrics_consumer_json — serialises each RLC sample to JSON and sends
//       it to the HTTP remote-server gateway. Used when json_metrics is enabled.
//
//     rlc_metrics_consumer_log — formats each RLC sample as a human-readable
//       log line (per RB: DU index, UE index, RB ID, TX and RX counters).
//
//     rlc_metrics_consumer_e2 — forwards each sample to the E2 RIC agent via
//       rlc_metrics_notifier, so the RIC can make RRM decisions.
//
//   All three implement app_services::metrics_consumer and receive samples
//   via handle_metric() when the dispatch callback fires.
// =============================================================================

#pragma once


#include "du_high_rlc_metrics.h"
#include "ocudu/ocudulog/log_channel.h"
#include "ocudu/ocudulog/logger.h"


namespace ocudu {


namespace app_services {
class remote_server_metrics_gateway;
} // namespace app_services

/// Consumer for the json RLC metrics.

/// Sends each RLC sample to the HTTP JSON metrics endpoint.
class rlc_metrics_consumer_json : public app_services::metrics_consumer
{
public:
  explicit rlc_metrics_consumer_json(app_services::remote_server_metrics_gateway& gateway_) : gateway(gateway_) {}

  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;


private:
  app_services::remote_server_metrics_gateway& gateway;
};

/// Consumer for the log RLC metrics.

/// Writes each RLC sample as a formatted log line.
class rlc_metrics_consumer_log : public app_services::metrics_consumer
{
public:
  explicit rlc_metrics_consumer_log(ocudulog::log_channel& log_chan_) : log_chan(log_chan_)
  {
    ocudu_assert(log_chan.enabled(), "Logger log channel is not enabled");
  }

  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;


private:
  ocudulog::log_channel& log_chan;
};

/// Consumer for the E2 RLC metrics.

/// Forwards each RLC sample to the E2 RIC agent.
class rlc_metrics_consumer_e2 : public app_services::metrics_consumer
{
public:
  explicit rlc_metrics_consumer_e2(rlc_metrics_notifier& notifier_) : notifier(notifier_) {}

  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;


private:
  rlc_metrics_notifier& notifier;
};


} // namespace ocudu
