// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/config/mac_cell_group_params.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/bsr_config.h"
#include "ocudu/mac/phr_config.h"
#include "ocudu/ran/sr_configuration.h"
#include <chrono>
#include <optional>


namespace ocudu {

/// Parameters that are used to generate UE DRX-Config.

/// Parameters that are used to generate UE DRX-Config.
struct drx_params {
  std::chrono::milliseconds on_duration;
  std::chrono::milliseconds long_cycle;
  std::chrono::milliseconds inactivity_timer;
  unsigned                  retx_timer_dl;
  unsigned                  retx_timer_ul;
};

/// Parameters that are used to initialize or build the \c MAC-CellGroupConfig, TS 38.331.

/// Parameters that are used to initialize or build the \c MAC-CellGroupConfig, TS 38.331.
struct mac_cell_group_params {
  periodic_bsr_timer                            periodic_timer = periodic_bsr_timer::sf10;
  retx_bsr_timer                                retx_timer     = retx_bsr_timer::sf80;
  std::optional<logical_channel_sr_delay_timer> lc_sr_delay_timer;
  std::optional<sr_prohib_timer>                sr_prohibit_timer;
  sr_max_tx                                     max_tx           = sr_max_tx::n64;
  phr_prohibit_timer                            phr_prohib_timer = phr_prohibit_timer::sf10;
  std::optional<drx_params>                     drx;
};


} // namespace ocudu
