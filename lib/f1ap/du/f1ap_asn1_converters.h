// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/f1ap_asn1_converters.h  (24 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/f1ap/du/f1ap_du_connection_manager.h"


namespace asn1 {
namespace f1ap {


struct served_cell_info_s;


}
} // namespace asn1


namespace ocudu {
namespace odu {


asn1::f1ap::served_cell_info_s make_asn1_served_cell_info(const du_served_cell_info& served_cell,
                                                          span<const s_nssai_t>      slices);


}
} // namespace ocudu
