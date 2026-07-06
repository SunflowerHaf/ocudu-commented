// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/ue_context/f1ap_du_ue_config_update.h  (28 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../f1ap_du_context.h"
#include "f1ap_du_ue_manager.h"
#include "ocudu/f1ap/du/f1ap_du_ue_config.h"


namespace ocudu {
namespace odu {


class f1ap_metrics_collector_impl;

/// \brief Creates a new UE in the F1AP, on request by DU management plane.
/// \return Result of the F1 UE creation that contains the outcome (success/failure) and list of created F1c bearers.

/// \brief Creates a new UE in the F1AP, on request by DU management plane.
/// \return Result of the F1 UE creation that contains the outcome (success/failure) and list of created F1c bearers.
f1ap_ue_creation_response create_f1ap_ue(const f1ap_ue_creation_request& req,
                                         f1ap_du_ue_manager&             ues,
                                         const f1ap_du_context&          du_ctx,
                                         f1ap_event_manager&             ev_mng,
                                         f1ap_metrics_collector_impl&    metrics);

/// \brief Update existing UE configuration on request by DU management plane.

/// \brief Update existing UE configuration on request by DU management plane.
f1ap_ue_configuration_response update_f1ap_ue_config(const f1ap_ue_configuration_request& req, f1ap_du_ue_manager& ues);


} // namespace odu
} // namespace ocudu
