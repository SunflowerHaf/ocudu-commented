// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_cp/cu_cp_metrics_handler.h  (54 lines)
//
// INTERFACE HEADER — include/ocudu/cu_cp
// CU-CP public interfaces: the abstract classes that the CU-CP exposes to the rest of the system. Key interfaces: cu_cp (the top-level factory and lifecycle), cu_cp_operation_controller (start/stop), n2_connection_client (NGAP socket management), cu_configurator (SSB/RRM/SIB remote changes), and the UE management interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_cp_metrics_notifier.h"
#include <chrono>
#include <memory>


namespace ocudu::ocucp {

/// Request for CU-CP metrics reporting.

/// Request for CU-CP metrics reporting.
struct periodic_metric_report_request {
  /// \brief The period at which the CU-CP metrics are reported. In case, the period is 0, the CU-CP metrics are only
  /// sent once.
  /// \brief The period at which the CU-CP metrics are reported. In case, the period is 0, the CU-CP metrics are only
  /// sent once.
  std::chrono::milliseconds period{0};
  /// \brief The notifier used by the CU-CP to report metrics.
  /// \brief The notifier used by the CU-CP to report metrics.
  cu_cp_metrics_report_notifier* report_notifier = nullptr;
};

/// Metric Report session instance.

/// Metric Report session instance.
class metrics_report_session
{
public:
  /// Closes the session and destroys it.
  /// Closes the session and destroys it.
  virtual ~metrics_report_session() = default;

  /// Configure the metrics report session.

  /// Configure the metrics report session.
  virtual void reconfigure_request(const periodic_metric_report_request& request) = 0;

  /// Close the session, explicitly stopping the reporting of new metrics.

  /// Close the session, explicitly stopping the reporting of new metrics.
  virtual void stop() = 0;
};

/// Interface for requesting CU-CP metrics

/// Interface for requesting CU-CP metrics
class metrics_handler
{
public:
  virtual ~metrics_handler() = default;

  /// \brief Create a new metrics periodic report session.
  /// \return Handle to the session. When the session object goes out of scope, the session is automatically closed.

  /// \brief Create a new metrics periodic report session.
  /// \return Handle to the session. When the session object goes out of scope, the session is automatically closed.
  virtual std::unique_ptr<metrics_report_session>
  create_periodic_report_session(const periodic_metric_report_request& request) = 0;

  /// \brief Synchronously request a new single metrics report. The call blocks until the report is ready.
  ///
  /// Note: Given its blocking nature, avoid calling this method in contexts other than unit tests.
  /// \return The metrics report.

  /// \brief Synchronously request a new single metrics report. The call blocks until the report is ready.
  ///
  /// Note: Given its blocking nature, avoid calling this method in contexts other than unit tests.
  /// \return The metrics report.
  virtual cu_cp_metrics_report request_metrics_report() const = 0;
};


} // namespace ocudu::ocucp
