// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cell_meas_manager/measurement_context.h  (98 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/nrppa/nrppa.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/ran/gnb_id.h"
#include "ocudu/ran/nr_cgi.h"
#include "ocudu/ran/pci.h"
#include "ocudu/rrc/meas_types.h"
#include <map>
#include <unordered_map>


namespace ocudu {
namespace ocucp {


struct meas_context_t {
  meas_obj_id_t    meas_obj_id   = meas_obj_id_t::invalid;
  report_cfg_id_t  report_cfg_id = report_cfg_id_t::invalid;
  unsigned         gnb_id_bit_length;
  nr_cell_identity nci;
  pci_t            pci;
};


class cell_meas_manager_ue_context
{
public:
  /// \brief Get the next available meas id.
  /// \brief Get the next available meas id.
  meas_id_t allocate_meas_id()
  {
    // return invalid when no meas id is available
    // return invalid when no meas id is available
    if (meas_ids.size() == MAX_NOF_MEAS) {
      return meas_id_t::invalid;
    }


    auto new_meas_id = (meas_id_t)meas_ids.find_first_empty();
    if (new_meas_id == meas_id_t::max) {
      return meas_id_t::invalid;
    }
    meas_ids.emplace(meas_id_to_uint(new_meas_id));
    return new_meas_id;
  }

  /// Remove all meas ids from the context, including lookups.

  /// Remove all meas ids from the context, including lookups.
  void clear_meas_ids()
  {
    meas_id_to_meas_context.clear();
    meas_ids.clear();

    // Mark zero index as occupied as the first valid meas ID is 1.

    // Mark zero index as occupied as the first valid meas ID is 1.
    meas_ids.emplace(0);
  }

  /// \brief Get the next available meas obj id.

  /// \brief Get the next available meas obj id.
  meas_obj_id_t allocate_meas_obj_id()
  {
    // return invalid when no meas obj id is available
    // return invalid when no meas obj id is available
    if (meas_obj_ids.size() == MAX_NOF_MEAS_OBJ) {
      return meas_obj_id_t::invalid;
    }


    auto new_meas_obj_id = (meas_obj_id_t)meas_obj_ids.find_first_empty();
    if (new_meas_obj_id == meas_obj_id_t::max) {
      return meas_obj_id_t::invalid;
    }
    meas_obj_ids.emplace(meas_obj_id_to_uint(new_meas_obj_id));
    return new_meas_obj_id;
  }

  /// Remove all meas obj ids from the context, including lookups.

  /// Remove all meas obj ids from the context, including lookups.
  void clear_meas_obj_ids()
  {
    nci_to_meas_obj_id.clear();
    meas_obj_ids.clear();

    // Mark zero index as occupied as the first valid meas obj ID is 1.

    // Mark zero index as occupied as the first valid meas obj ID is 1.
    meas_obj_ids.emplace(0);
  }


  slotted_array<meas_id_t, MAX_NOF_MEAS>         meas_ids;     // 0 is reserved for invalid meas_id
  slotted_array<meas_obj_id_t, MAX_NOF_MEAS_OBJ> meas_obj_ids; // 0 is reserved for invalid meas_obj_id


  std::map<meas_id_t, meas_context_t>              meas_id_to_meas_context;
  std::map<nr_cell_identity, meas_obj_id_t>        nci_to_meas_obj_id;
  std::optional<cell_measurement_positioning_info> meas_results;


  cell_meas_manager_ue_context()
  {
    // Mark zero index as occupied as the first valid meas(-obj) ID is 1.
    // Mark zero index as occupied as the first valid meas(-obj) ID is 1.
    meas_ids.emplace(0);
    meas_obj_ids.emplace(0);
  }
};


} // namespace ocucp
} // namespace ocudu
