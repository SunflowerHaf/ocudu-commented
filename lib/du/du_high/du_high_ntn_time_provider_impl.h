// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_high_ntn_time_provider_impl.h  (31 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/mac_subframe_time_mapper.h"
#include "ocudu/ntn/ntn_time_provider.h"


namespace ocudu {
namespace odu {

/// Implementation of the NTN time provider.

/// Implementation of the NTN time provider.
class du_high_ntn_time_provider_impl : public ocudu_ntn::ntn_time_provider
{
public:
  explicit du_high_ntn_time_provider_impl(mac_subframe_time_mapper& time_mapper_);

  /// \brief Get the last time slot mapping.
  ///
  /// This function provides access to the most recent time slot mapping for time synchronization operations in NTN
  /// context.
  /// \return Optional containing the time slot mapping if available.

  /// \brief Get the last time slot mapping.
  ///
  /// This function provides access to the most recent time slot mapping for time synchronization operations in NTN
  /// context.
  /// \return Optional containing the time slot mapping if available.
  std::optional<ocudu_ntn::ntn_time_slot_mapping> get_last_mapping(subcarrier_spacing scs) override;


private:
  mac_subframe_time_mapper& subframe_time_mapper;
};


} // namespace odu
} // namespace ocudu
