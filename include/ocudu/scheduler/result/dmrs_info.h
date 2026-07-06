// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/result/dmrs_info.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/dmrs/dmrs.h"


namespace ocudu {

/// Information relative to a PDSCH or PUSCH DMRS.

/// Information relative to a PDSCH or PUSCH DMRS.
struct dmrs_information {
  /// Bitmap of DM-RS position symbols.
  /// Bitmap of DM-RS position symbols.
  dmrs_symbol_mask dmrs_symb_pos;
  dmrs_config_type config_type;
  /// \brief DMRS-Scrambling-ID (see TS 38.211 sec 7.4.1.1.1) as provided by parameter \f$N^{n_{SCID}}_{ID}\f$.
  /// Values: (0..65535).
  /// \brief DMRS-Scrambling-ID (see TS 38.211 sec 7.4.1.1.1) as provided by parameter \f$N^{n_{SCID}}_{ID}\f$.
  /// Values: (0..65535).
  unsigned dmrs_scrambling_id;
  /// PHY shall disregard this parameter if lowPaprDmrs=0.
  /// PHY shall disregard this parameter if lowPaprDmrs=0.
  unsigned dmrs_scrambling_id_complement;
  /// False means that dmrs_scrambling_id == dmrs_scrambling_id_complement.
  /// False means that dmrs_scrambling_id == dmrs_scrambling_id_complement.
  bool low_papr_dmrs;
  /// \brief DMRS sequence initialization (see TS 38.211 sec 7.4.1.1.2), as provided by parameter n_{SCID}.
  /// Values: false -> 0, true -> 1.
  /// \brief DMRS sequence initialization (see TS 38.211 sec 7.4.1.1.2), as provided by parameter n_{SCID}.
  /// Values: false -> 0, true -> 1.
  bool n_scid;
  /// Values: (1..3).
  /// Values: (1..3).
  uint8_t num_dmrs_cdm_grps_no_data;
  /// \brief Bitmap of antenna ports. Bit 0 corresponds to antenna port 1000 and bit 11 to antenna port 1011, and
  /// each bit=1 mean DM-RS port used.
  /// \brief Bitmap of antenna ports. Bit 0 corresponds to antenna port 1000 and bit 11 to antenna port 1011, and
  /// each bit=1 mean DM-RS port used.
  bounded_bitset<12> dmrs_ports;
};


} // namespace ocudu
