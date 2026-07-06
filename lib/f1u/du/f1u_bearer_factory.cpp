// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1u/du/f1u_bearer_factory.cpp  (26 lines)
//
// LIBRARY: lib/f1u
// F1-U user-plane interface: the GTP-U-based data path between the DU and the CU-UP. Implements the DU-side and CU-UP-side endpoints, TEID management, flow mapping, and the connector that links F1-U sockets to the PDCP and RLC layers.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/f1u/du/f1u_bearer_factory.h"
#include "f1u_bearer_impl.h"


using namespace ocudu;
using namespace odu;


std::unique_ptr<f1u_bearer> ocudu::odu::create_f1u_bearer(const f1u_bearer_creation_message& msg)
{
  ocudu_assert(msg.rx_sdu_notifier != nullptr, "Cannot create F1-U bearer: RX SDU notifier is not configured.");
  ocudu_assert(msg.tx_pdu_notifier != nullptr, "Cannot create F1-U bearer: TX PDU notifier is not configured.");
  ocudu_assert(msg.ue_executor != nullptr, "Cannot create F1-U bearer: UE executor is not configured.");
  ocudu_assert(msg.disconnector != nullptr, "Cannot create F1-U bearer: disconnector is not configured.");
  auto bearer = std::make_unique<f1u_bearer_impl>(msg.ue_index,
                                                  msg.drb_id,
                                                  msg.dl_tnl_info,
                                                  msg.config,
                                                  *msg.rx_sdu_notifier,
                                                  *msg.tx_pdu_notifier,
                                                  msg.timers,
                                                  *msg.ue_executor);
  return bearer;
}
