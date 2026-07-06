// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/pdcp/pdcp_metrics.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/pdcp
// PDCP interface headers: pdcp_rx_pdu_handler and pdcp_tx_sdu_handler (the data flow interfaces), pdcp_rx_upper_data_notifier and pdcp_tx_lower_notifier (callbacks to layers above/below), pdcp_metrics_notifier, and the PDCP entity configuration types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/pdcp/pdcp_entity.h"
#include "ocudu/ran/cu_types.h"
#include "ocudu/ran/gnb_id.h"
#include "ocudu/ran/rb_id.h"


namespace ocudu {


struct pdcp_metrics_container;

/// \brief Notifier interface used to report PDCP metrics.

/// \brief Notifier interface used to report PDCP metrics.
class pdcp_metrics_notifier
{
public:
  virtual ~pdcp_metrics_notifier() = default;

  /// \brief This method will be called periodically to report the latest PDCP metrics statistics.

  /// \brief This method will be called periodically to report the latest PDCP metrics statistics.
  virtual void report_metrics(const pdcp_metrics_container& metrics) = 0;
};
} // namespace ocudu
