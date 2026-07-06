// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/result/prach_info.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pci.h"
#include "ocudu/ran/prach/prach_format_type.h"


namespace ocudu {

/// Information relative to a PRACH opportunity.

/// Information relative to a PRACH opportunity.
struct prach_occasion_info {
  /// Physical Cell identifier.
  /// Physical Cell identifier.
  pci_t pci;
  /// Number of time-domain PRACH occasions (\f$N^{RAslot}_t\f$), as per TS38.211 Tables 6.3.3.2-[2-4].
  /// Number of time-domain PRACH occasions (\f$N^{RAslot}_t\f$), as per TS38.211 Tables 6.3.3.2-[2-4].
  uint8_t nof_prach_occasions;
  /// RACH format information for the PRACH occasions.
  /// RACH format information for the PRACH occasions.
  prach_format_type format;
  /// Frequency domain occasion index \f$n \in \{0,...,M-1\}\f$, where \f$M\f$ is the higher-layer parameter msg1-FDM,
  /// which can take the values \f$\{1,2,4,8\}\f$. See TS38.211, sec 6.3.3.2. Possible values {0,...,7}.
  /// Frequency domain occasion index \f$n \in \{0,...,M-1\}\f$, where \f$M\f$ is the higher-layer parameter msg1-FDM,
  /// which can take the values \f$\{1,2,4,8\}\f$. See TS38.211, sec 6.3.3.2. Possible values {0,...,7}.
  uint8_t index_fd_ra;
  /// Starting symbol for the first PRACH TD occasion.
  /// \remark See TS38.211, sec 6.3.3.2 and Tables 6.3.3.2-2 and 6.3.3.2-4. Possible values: {0,...,13}.
  /// Starting symbol for the first PRACH TD occasion.
  /// \remark See TS38.211, sec 6.3.3.2 and Tables 6.3.3.2-2 and 6.3.3.2-4. Possible values: {0,...,13}.
  uint8_t start_symbol;
  /// N-CS configuration as per TS38.211, Table 6.3.3.1-5. Possible values: {0,...,419}.
  /// N-CS configuration as per TS38.211, Table 6.3.3.1-5. Possible values: {0,...,419}.
  uint16_t nof_cs;
  /// Number of frequency domain occasions starting with index_fd_ra. Possible values: {1,...,8}.
  /// Number of frequency domain occasions starting with index_fd_ra. Possible values: {1,...,8}.
  uint8_t nof_fd_ra;
  /// Start of preamble logical index to monitor the PRACH occasions in this slot. Values: {0,...63}.
  /// Start of preamble logical index to monitor the PRACH occasions in this slot. Values: {0,...63}.
  uint8_t start_preamble_index;
  /// Number of preamble logical indices. Values: {1,...,64}.
  /// Number of preamble logical indices. Values: {1,...,64}.
  uint8_t nof_preamble_indexes;
};


} // namespace ocudu
