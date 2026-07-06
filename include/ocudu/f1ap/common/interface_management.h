// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/common/interface_management.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cause/f1ap_cause.h"
#include "ocudu/ran/nr_cgi.h"
#include "ocudu/ran/pci.h"


namespace ocudu {

/// Cell commanded by the CU to be activated via the F1AP interface.

/// Cell commanded by the CU to be activated via the F1AP interface.
struct f1ap_cell_to_activate {
  nr_cell_global_id_t        cgi;
  std::optional<pci_t>       pci;
  std::vector<plmn_identity> available_plmn_list;
};

/// Cell failed to be activated via the F1AP interface.

/// Cell failed to be activated via the F1AP interface.
struct f1ap_cell_failed_to_activate {
  nr_cell_global_id_t cgi;
  f1ap_cause_t        cause;
};

/// Cell commanded by the CU to be deactivated via the F1AP interface.

/// Cell commanded by the CU to be deactivated via the F1AP interface.
struct f1ap_cell_to_deactivate {
  nr_cell_global_id_t cgi;
};


} // namespace ocudu
