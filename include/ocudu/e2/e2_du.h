// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2_du.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/e2.h"
#include "ocudu/rlc/rlc_metrics.h"
#include "ocudu/scheduler/scheduler_metrics.h"


namespace ocudu {


class e2_du_metrics_notifier : public scheduler_metrics_notifier, public rlc_metrics_notifier
{
public:
  virtual ~e2_du_metrics_notifier() = default;


  using rlc_metrics_notifier::report_metrics;
  using scheduler_metrics_notifier::report_metrics;
};


class e2_du_metrics_interface
{
public:
  virtual ~e2_du_metrics_interface() = default;

  /// \brief connects e2_du_metric_provider
  /// \param[in] meas_provider pointer to the e2_du_metric_provider

  /// \brief connects e2_du_metric_provider
  /// \param[in] meas_provider pointer to the e2_du_metric_provider
  virtual void connect_e2_du_meas_provider(std::unique_ptr<e2_du_metrics_notifier> meas_provider) = 0;
};
} // namespace ocudu
