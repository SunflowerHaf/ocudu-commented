// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rlc/rlc_factory.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/rlc
// RLC interface headers: rlc_rx_pdu_handler and rlc_tx_sdu_handler (data path interfaces), rlc_rx_am_status_notifier (ARQ status report callback), rlc_metrics_notifier, and the RLC entity configuration types for AM, UM, and TM modes.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/pcap/rlc_pcap.h"
#include "ocudu/ran/gnb_du_id.h"
#include "ocudu/rlc/rlc_config.h"
#include "ocudu/rlc/rlc_entity.h"
#include "ocudu/rlc/rlc_rx.h"
#include "ocudu/rlc/rlc_tx.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/timers.h"
#include <memory>


namespace ocudu {


struct rlc_entity_creation_message {
  gnb_du_id_t                          gnb_du_id;
  du_ue_index_t                        ue_index;
  rb_id_t                              rb_id;
  rlc_config                           config;
  rlc_rx_upper_layer_data_notifier*    rx_upper_dn;
  rlc_tx_upper_layer_data_notifier*    tx_upper_dn;
  rlc_tx_upper_layer_control_notifier* tx_upper_cn;
  rlc_tx_lower_layer_notifier*         tx_lower_dn;
  timer_manager*                       timers;
  task_executor*                       pcell_executor;
  task_executor*                       ue_executor;
  rlc_metrics_notifier*                rlc_metrics_notif;
  rlc_pcap*                            pcap_writer;
};

/// Creates an instance of a RLC bearer

/// Creates an instance of a RLC bearer
std::unique_ptr<rlc_entity> create_rlc_entity(const rlc_entity_creation_message& msg);


} // namespace ocudu
