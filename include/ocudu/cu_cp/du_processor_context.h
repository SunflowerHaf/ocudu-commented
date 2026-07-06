// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_cp/du_processor_context.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/cu_cp
// CU-CP public interfaces: the abstract classes that the CU-CP exposes to the rest of the system. Key interfaces: cu_cp (the top-level factory and lifecycle), cu_cp_operation_controller (start/stop), n2_connection_client (NGAP socket management), cu_configurator (SSB/RRM/SIB remote changes), and the UE management interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/ran/du_cell_index.h"
#include "ocudu/ran/nr_band.h"
#include "ocudu/ran/nr_cgi.h"
#include "ocudu/ran/pci.h"
#include "ocudu/ran/tac.h"


namespace ocudu::ocucp {

/// Basic cell system information provided by DU

/// Basic cell system information provided by DU
struct du_sys_info {
  byte_buffer packed_mib;
  byte_buffer packed_sib1;
};


struct du_cell_configuration {
  /// CU-CP specific DU cell identifier.
  /// CU-CP specific DU cell identifier.
  du_cell_index_t cell_index = INVALID_DU_CELL_INDEX;
  /// Global cell ID.
  /// Global cell ID.
  nr_cell_global_id_t cgi;
  /// Tracking Area Code
  /// Tracking Area Code
  tac_t tac;
  /// Physical cell ID
  /// Physical cell ID
  pci_t pci;
  /// PLMN identitys served by the cell.
  /// PLMN identitys served by the cell.
  std::vector<plmn_identity> served_plmns;
  /// NR bands provided/supported by the cell.
  /// NR bands provided/supported by the cell.
  std::vector<nr_band> bands;
  /// System Information provided by the DU for this cell.
  /// System Information provided by the DU for this cell.
  du_sys_info sys_info;
  /// Deactivated PLMN identitys initially served by the cell.
  /// Deactivated PLMN identitys initially served by the cell.
  std::vector<plmn_identity> deactivated_plmns;
};


} // namespace ocudu::ocucp
