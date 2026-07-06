// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/du_ue/du_ue_cond_mobility_manager.h  (31 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace odu {

/// \brief Tracks conditional mobility state for a UE in the DU.

/// \brief Tracks conditional mobility state for a UE in the DU.
class du_ue_cond_mobility_manager
{
public:
  /// \brief Mark that an Access Success is expected for this UE upon C-RNTI CE reception.
  /// \brief Mark that an Access Success is expected for this UE upon C-RNTI CE reception.
  void set_success_access_required();

  /// \brief Indicates whether Access Success is currently expected for this UE.

  /// \brief Indicates whether Access Success is currently expected for this UE.
  bool is_success_access_required() const;

  /// \brief Handle a C-RNTI CE indication.
  ///
  /// Returns true and clears the flag if an Access Success was pending for this UE.
  /// Returns false without modifying state if no Access Success was expected.

  /// \brief Handle a C-RNTI CE indication.
  ///
  /// Returns true and clears the flag if an Access Success was pending for this UE.
  /// Returns false without modifying state if no Access Success was expected.
  bool handle_crnti_ce_indication();


private:
  bool success_access_required = false;
};


} // namespace odu
} // namespace ocudu
