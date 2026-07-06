// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1u/cu_up/f1u_bearer_factory.cpp  (39 lines)
//
// LIBRARY: lib/f1u
// F1-U user-plane interface: the GTP-U-based data path between the DU and the CU-UP. Implements the DU-side and CU-UP-side endpoints, TEID management, flow mapping, and the connector that links F1-U sockets to the PDCP and RLC layers.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/f1u/cu_up/f1u_bearer_factory.h"
#include "f1u_bearer_impl.h"


using namespace ocudu;
using namespace ocuup;


std::unique_ptr<f1u_bearer> ocudu::ocuup::create_f1u_bearer(uint32_t                       ue_index,
                                                            drb_id_t                       drb_id,
                                                            const up_transport_layer_info& ul_up_tnl_info,
                                                            const f1u_config&              config,
                                                            f1u_tx_pdu_notifier&           tx_pdu_notifier,
                                                            f1u_rx_delivery_notifier&      rx_delivery_notifier,
                                                            f1u_rx_sdu_notifier&           rx_sdu_notifier,
                                                            timer_factory                  ue_dl_timer_factory,
                                                            timer_factory                  ue_ctrl_timer_factory,
                                                            unique_timer&                  ue_inactivity_timer,
                                                            task_executor&                 dl_exec,
                                                            task_executor&                 ul_exec,
                                                            task_executor&                 ctrl_exec)
{
  auto bearer = std::make_unique<f1u_bearer_impl>(ue_index,
                                                  drb_id,
                                                  ul_up_tnl_info,
                                                  config,
                                                  tx_pdu_notifier,
                                                  rx_delivery_notifier,
                                                  rx_sdu_notifier,
                                                  ue_dl_timer_factory,
                                                  ue_ctrl_timer_factory,
                                                  ue_inactivity_timer,
                                                  dl_exec,
                                                  ul_exec,
                                                  ctrl_exec);
  return bearer;
}
