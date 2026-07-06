// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2_cu_metrics_connector.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/e2/e2_cu.h"
#include "ocudu/f1u/cu_up/f1u_metrics.h"
#include "ocudu/pdcp/pdcp_metrics.h"
#include <deque>


namespace ocudu {


constexpr unsigned MAX_UE_METRICS = 10;

/// \brief Class used to receive metrics reports from scheduler and sends them to the e2 interface.

/// \brief Class used to receive metrics reports from scheduler and sends them to the e2 interface.
class e2_cu_metrics_connector : public e2_cu_metrics_notifier, public e2_cu_metrics_interface
{
public:
  e2_cu_metrics_connector();


  ~e2_cu_metrics_connector() = default;


  void report_metrics(const pdcp_metrics_container& metrics) override;


  void report_metrics(const ocuup::f1u_metrics_container& metrics) override;


  void report_metrics(const cu_cp_metrics_report& metrics) override;


  void connect_e2_cu_meas_provider(std::unique_ptr<e2_cu_metrics_notifier> meas_provider) override;


private:
  std::unique_ptr<e2_cu_metrics_notifier> e2_meas_provider;
};
} // namespace ocudu
