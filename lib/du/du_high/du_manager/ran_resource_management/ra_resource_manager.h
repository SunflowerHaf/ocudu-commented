// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/ran_resource_management/ra_resource_manager.h  (33 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "du_ue_resource_config.h"
#include "ocudu/du/du_cell_config.h"


namespace ocudu::odu {

/// Handler of allocation of RA preambles for Contention-free Random Access (CFRA).

/// Handler of allocation of RA preambles for Contention-free Random Access (CFRA).
class ra_resource_manager
{
public:
  ra_resource_manager(span<const du_cell_config> cell_cfg_list);

  /// Allocate RA resources to a given UE.

  /// Allocate RA resources to a given UE.
  void allocate_cfra_resources(du_ue_resource_config& ue_res_cfg);

  /// Deallocate RA resources of a given UE.

  /// Deallocate RA resources of a given UE.
  void deallocate_cfra_resources(du_ue_resource_config& ue_res_cfg);


private:
  struct cell_ra_context {
    const du_cell_config* cell_cfg;
    std::vector<unsigned> free_preamble_idx_list;
  };


  std::vector<cell_ra_context> cells;
};


} // namespace ocudu::odu
