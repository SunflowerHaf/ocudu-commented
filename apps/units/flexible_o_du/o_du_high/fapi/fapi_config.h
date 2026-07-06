// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: fapi/fapi_config.h
//
// Purpose (plain English):
//   Configuration struct for the FAPI (Functional API) layer. FAPI is the
//   interface between the MAC layer (in the DU High) and the upper physical
//   layer (in the DU Low). It defines the message types and timing contracts
//   for passing downlink scheduling decisions and uplink indication callbacks
//   between the two halves.
//
//   In a split-8 setup the DU High and DU Low run in the same process, so
//   FAPI messages never leave the machine — they flow through in-process
//   adaptors. The only user-tunable parameter at the application layer is the
//   log level for FAPI messages, which controls how verbosely the FAPI adaptor
//   traces P5 (cell configuration) and P7 (per-slot data) exchanges.
//
//   If you see "FAPI" in the gNB logs, that is the adaptor layer converting
//   MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into
//   the FAPI message formats and vice versa.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/logger.h"


namespace ocudu {

/// FAPI configuration.

/// FAPI adaptor log-level configuration.
struct fapi_unit_config {
  /// FAPI log level.
  /// Log level for FAPI P5 (configuration) and P7 (per-slot) message tracing.
  /// Default: warning — avoids flooding the log at normal operation.
  ocudulog::basic_levels fapi_level = ocudulog::basic_levels::warning;
};


} // namespace ocudu
