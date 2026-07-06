// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_paging_procedure.h  (23 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/f1ap/f1ap.h"
#include "ocudu/ocudulog/logger.h"


namespace ocudu {
namespace odu {


class f1ap_du_paging_notifier;
struct f1ap_du_context;

/// Handles a Paging Request message as per TS38.473, Section 8.7.

/// Handles a Paging Request message as per TS38.473, Section 8.7.
bool handle_paging_request(const asn1::f1ap::paging_s& msg,
                           f1ap_du_paging_notifier&    paging_notifier,
                           f1ap_du_context&            ctxt,
                           ocudulog::basic_logger&     logger);


} // namespace odu
} // namespace ocudu
