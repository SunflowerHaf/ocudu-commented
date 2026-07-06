// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/converters/rlc_config_helpers.h  (41 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../du_ue/du_bearer.h"
#include "ocudu/du/du_high/du_manager/du_manager_params.h"
#include "ocudu/f1ap/du/f1ap_du_ue_config.h"
#include "ocudu/mac/mac_lc_config.h"
#include "ocudu/ran/du_types.h"
#include "ocudu/ran/rb_id.h"
#include "ocudu/rlc/rlc_config.h"
#include "ocudu/rlc/rlc_factory.h"


namespace ocudu {
namespace odu {

/// \brief Create configuration for RLC SRB entity.

/// \brief Create configuration for RLC SRB entity.
rlc_entity_creation_message make_rlc_entity_creation_message(gnb_du_id_t                              du_id,
                                                             du_ue_index_t                            ue_index,
                                                             du_cell_index_t                          pcell_index,
                                                             du_ue_srb&                               bearer,
                                                             const rlc_config&                        rlc_cfg,
                                                             const du_manager_params::service_params& du_services,
                                                             rlc_tx_upper_layer_control_notifier&     rlc_rlf_notifier,
                                                             rlc_pcap&                                rlc_pcap);

/// \brief Create configuration for RLC DRB entity.

/// \brief Create configuration for RLC DRB entity.
rlc_entity_creation_message make_rlc_entity_creation_message(gnb_du_id_t                              du_id,
                                                             du_ue_index_t                            ue_index,
                                                             du_cell_index_t                          pcell_index,
                                                             du_ue_drb&                               bearer,
                                                             const rlc_config&                        rlc_cfg,
                                                             const du_manager_params::service_params& du_services,
                                                             rlc_tx_upper_layer_control_notifier&     rlc_rlf_notifier,
                                                             rlc_metrics_notifier*                    rlc_metrics_notif,
                                                             rlc_pcap&                                rlc_pcap);


} // namespace odu
} // namespace ocudu
