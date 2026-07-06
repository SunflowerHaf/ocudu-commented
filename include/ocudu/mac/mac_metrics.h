// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_metrics.h  (68 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pci.h"
#include "ocudu/scheduler/scheduler_metrics.h"
#include <chrono>
#include <vector>


namespace ocudu {

/// Metrics relative to a specific MAC cell.

/// Metrics relative to a specific MAC cell.
struct mac_dl_cell_metric_report {
  struct latency_report {
    std::chrono::nanoseconds min;
    std::chrono::nanoseconds max;
    std::chrono::nanoseconds average;
    slot_point               max_slot;
  };

  /// Physical cell id.

  /// Physical cell id.
  pci_t pci;
  /// First SFN and SLOT of the report.
  /// First SFN and SLOT of the report.
  slot_point start_slot;
  /// Number of slots considered in this report.
  /// Number of slots considered in this report.
  unsigned nof_slots;
  /// Slot duration.
  /// Slot duration.
  std::chrono::nanoseconds slot_duration;
  /// Description of the wall clock latency of the MAC at handling slot indications.
  /// Description of the wall clock latency of the MAC at handling slot indications.
  latency_report wall_clock_latency;
  /// \brief Description of the wall clock latency between the lower layers signalling a slot indication and the MAC
  /// starting to handle it.
  /// \brief Description of the wall clock latency between the lower layers signalling a slot indication and the MAC
  /// starting to handle it.
  latency_report slot_ind_dequeue_latency;
  /// \brief Description of the delay in the MAC scheduler between receiving a slot indication and completing the
  /// scheduling
  /// \brief Description of the delay in the MAC scheduler between receiving a slot indication and completing the
  /// scheduling
  latency_report sched_latency;
  /// \brief Description of the delays between the MAC starting the processing of a slot indication and generating a DL
  /// TTI request.
  /// \brief Description of the delays between the MAC starting the processing of a slot indication and generating a DL
  /// TTI request.
  latency_report dl_tti_req_latency;
  /// \brief Description of the delays between the MAC completing a DL TTI request and completing a TX Data request.
  /// \brief Description of the delays between the MAC completing a DL TTI request and completing a TX Data request.
  latency_report tx_data_req_latency;
  /// \brief Description of the delays of the MAC at completing a UL TTI request.
  /// \brief Description of the delays of the MAC at completing a UL TTI request.
  latency_report ul_tti_req_latency;
  /// \brief Description of the time difference between two consecutive FAPI slot indication messages.
  /// \brief Description of the time difference between two consecutive FAPI slot indication messages.
  latency_report slot_ind_msg_time_diff;
  /// Number of voluntary context switches.
  /// Number of voluntary context switches.
  unsigned count_voluntary_context_switches;
  /// Number of involuntary context switches.
  /// Number of involuntary context switches.
  unsigned count_involuntary_context_switches;
  /// Whether the cell was marked for deactivation.
  /// Whether the cell was marked for deactivation.
  bool cell_deactivated;
};


struct mac_dl_metric_report {
  std::vector<mac_dl_cell_metric_report> cells;
};

/// \brief Structure holding the metrics of a MAC layer.

/// \brief Structure holding the metrics of a MAC layer.
struct mac_metric_report {
  /// Metrics of the MAC DL.
  /// Metrics of the MAC DL.
  mac_dl_metric_report dl;
  /// Metrics of the MAC scheduler.
  /// Metrics of the MAC scheduler.
  scheduler_metrics_report sched;
};


} // namespace ocudu
