// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2ap_configuration.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/gnb_cu_up_id.h"
#include "ocudu/ran/gnb_du_id.h"
#include "ocudu/ran/gnb_id.h"
#include <chrono>
#include <optional>
#include <string>


namespace ocudu {

/// \brief E2AP configuration

/// \brief E2AP configuration
struct e2ap_configuration {
  gnb_id_t                      gnb_id = {0, 22};
  std::string                   plmn; /// Full PLMN as string (without possible filler digit) e.g. "00101"
  std::optional<gnb_du_id_t>    gnb_du_id;
  std::optional<gnb_cu_up_id_t> gnb_cu_up_id;
  unsigned                      max_setup_retries           = 5;
  std::chrono::milliseconds     ric_reconnection_retry_time = std::chrono::milliseconds{1000};
  bool                          e2sm_kpm_enabled            = false;
  bool                          e2sm_rc_enabled             = false;
  bool                          e2sm_ccc_enabled            = false;
};


} // namespace ocudu
