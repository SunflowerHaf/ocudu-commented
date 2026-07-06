// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ngap/mobility_management_metrics.h  (20 lines)
//
// INTERFACE HEADER — include/ocudu/ngap
// NGAP interface headers: n2_connection_client (manages the SCTP connection to the AMF), ngap_message_handler interfaces for all NGAP procedures, and the NGAP-to-RRC message passing interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

// Mobility Management metrics, see TS 28.552 section 5.1.1.6.

// Mobility Management metrics, see TS 28.552 section 5.1.1.6.
struct mobility_management_metrics {
  // Section 5.1.1.6.1: Inter-gNB handovers.
  // Section 5.1.1.6.1: Inter-gNB handovers.
  unsigned nof_handover_preparations_requested  = 0;
  unsigned nof_successful_handover_preparations = 0;

  // Section 5.1.1.6.2: Intra-gNB handovers.

  // Section 5.1.1.6.2: Intra-gNB handovers.
  unsigned nof_handover_executions_requested  = 0;
  unsigned nof_successful_handover_executions = 0;
};


} // namespace ocudu
