// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_metrics_notifier.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct mac_metric_report;

/// Notifier used by MAC to report new metrics.

/// Notifier used by MAC to report new metrics.
class mac_metrics_notifier
{
public:
  virtual ~mac_metrics_notifier() = default;

  /// \brief Called on every new MAC metrics report.
  /// \param report Metric report.

  /// \brief Called on every new MAC metrics report.
  /// \param report Metric report.
  virtual void on_new_metrics_report(const mac_metric_report& report) = 0;
};


} // namespace ocudu
