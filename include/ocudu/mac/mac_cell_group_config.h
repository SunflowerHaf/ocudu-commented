// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_cell_group_config.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/mac/bsr_config.h"
#include "ocudu/mac/phr_config.h"
#include "ocudu/ran/drx_config.h"
#include "ocudu/ran/sr_configuration.h"
#include "ocudu/ran/time_alignment_config.h"


namespace ocudu {

/// \c MAC-CellGroupConfig, TS 38.331.

/// \c MAC-CellGroupConfig, TS 38.331.
struct mac_cell_group_config {
  /// \c drx-Config.
  /// \c drx-Config.
  std::optional<drx_config> drx_cfg;
  /// \c schedulingRequestConfig.
  /// \c schedulingRequestConfig.
  std::vector<scheduling_request_to_addmod> scheduling_request_config;
  /// \c bsr-Config.
  /// \c bsr-Config.
  std::optional<bsr_config> bsr_cfg;
  /// \c tag-Config.
  /// \c tag-Config.
  static_vector<time_alignment_group, MAX_NOF_TIME_ALIGNMENT_GROUPS> tag_config;
  /// \c phr-Config.
  /// \c phr-Config.
  std::optional<phr_config> phr_cfg;
  /// \c skipUplinkTxDynamic.
  /// \c skipUplinkTxDynamic.
  bool skip_uplink_tx_dynamic = false;
  // TODO: add remaining fields.
  // TODO: add remaining fields.
};


} // namespace ocudu
