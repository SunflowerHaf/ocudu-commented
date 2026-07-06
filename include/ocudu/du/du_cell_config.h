// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_cell_config.h  (56 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/config/mac_cell_group_params.h"
#include "ocudu/ran/nr_cgi.h"
#include "ocudu/ran/sib/system_info_config.h"
#include "ocudu/ran/tac.h"
#include "ocudu/scheduler/config/ran_cell_config.h"
#include "ocudu/scheduler/config/slice_rrm_policy_config.h"


namespace ocudu {
namespace odu {

/// Parameters that are used to initialize or build the \c PhysicalCellGroupConfig, TS 38.331.

/// Parameters that are used to initialize or build the \c PhysicalCellGroupConfig, TS 38.331.
struct phy_cell_group_params {
  /// \brief \c p-NR-FR1, part \c PhysicalCellGroupConfig, TS 38.331.
  /// The maximum total TX power to be used by the UE in this NR cell group across all serving cells in FR1.
  /// \brief \c p-NR-FR1, part \c PhysicalCellGroupConfig, TS 38.331.
  /// The maximum total TX power to be used by the UE in this NR cell group across all serving cells in FR1.
  std::optional<bounded_integer<int, -30, 33>> p_nr_fr1;
};

/// Cell Configuration, including common and UE-dedicated configs, that the DU will use to generate other configs for
/// other layers (e.g. scheduler).

/// Cell Configuration, including common and UE-dedicated configs, that the DU will use to generate other configs for
/// other layers (e.g. scheduler).
struct du_cell_config {
  tac_t               tac;
  nr_cell_global_id_t nr_cgi;

  /// Whether the DU automatically attempts to activate the cell or waits for a command from the SMO.
  /// Note: If set to false, the DU won't add this cell to the list of served cells in the F1 Setup Request.

  /// Whether the DU automatically attempts to activate the cell or waits for a command from the SMO.
  /// Note: If set to false, the DU won't add this cell to the list of served cells in the F1 Setup Request.
  bool enabled = true;

  /// MIB cellBarred field (TS 38.331): true=barred, false=notBarred.

  /// MIB cellBarred field (TS 38.331): true=barred, false=notBarred.
  bool cell_barred = false;
  /// MIB intraFreqReselection field (TS 38.331): true=allowed, false=notAllowed.
  /// MIB intraFreqReselection field (TS 38.331): true=allowed, false=notAllowed.
  bool intra_freq_reselection = true;

  /// Information for UE cell access and SI scheduling.

  /// Information for UE cell access and SI scheduling.
  si_acquisition_info si;

  /// RAN-specific parameters of the cell.

  /// RAN-specific parameters of the cell.
  ran_cell_config ran;

  /// Parameters to initialize/build the \c phy_cell_group.

  /// Parameters to initialize/build the \c phy_cell_group.
  phy_cell_group_params pcg_params;

  /// Parameters to initialize/build the \c mac_cell_group_config.

  /// Parameters to initialize/build the \c mac_cell_group_config.
  mac_cell_group_params mcg_params;

  /// List of RAN slices to support in the scheduler.

  /// List of RAN slices to support in the scheduler.
  std::vector<slice_rrm_policy_config> rrm_policy_members;
};


} // namespace odu
} // namespace ocudu
