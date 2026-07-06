// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/nrppa/nrppa_otdoa.h  (76 lines)
//
// INTERFACE HEADER — include/ocudu/nrppa
// NRPPa interface headers: nrppa_message_handler and the positioning measurement request/response types used by the positioning sub-system.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cause/nrppa_cause.h"
#include "ocudu/ran/crit_diagnostics.h"
#include "ocudu/ran/nr_cgi.h"
#include "ocudu/ran/positioning/common.h"
#include "ocudu/ran/tac.h"
#include <optional>
#include <variant>
#include <vector>


namespace ocudu {
namespace ocucp {


enum class nrppa_otdoa_info_item {
  pci,
  cgi,
  tac,
  earfcn,
  prs_bw,
  prs_cfg_idx,
  cp_len,
  no_dl_frames,
  no_ant_ports,
  sfn_init_time,
  ng_ran_access_point_position,
  prsmutingcfg,
  prsid,
  tpid,
  tp_type,
  crs_cp_len,
  dl_bw,
  multipleprs_cfgsper_cell,
  prs_occasion_group,
  prs_freq_hop_cfg,
  tdd_cfg
};


struct nrppa_otdoa_info_type_item {
  nrppa_otdoa_info_item otdoa_info_item;
};


struct nrppa_otdoa_information_request {
  std::vector<nrppa_otdoa_info_type_item> otdoa_info_type;
};


using nrppa_sfn_initisation_time_nr = uint64_t;


using nrppa_otdoa_cell_info_item =
    std::variant<tac_t, ng_ran_access_point_position_t, nr_cell_global_id_t, nrppa_sfn_initisation_time_nr>;


struct nrppa_otdoa_cells_item {
  std::vector<nrppa_otdoa_cell_info_item> otdoa_cell_info;
};


struct nrppa_otdoa_information_response {
  std::vector<nrppa_otdoa_cells_item> otdoa_info_type;
  std::optional<crit_diagnostics_t>   crit_diagnostics;
};


struct nrppa_otdoa_information_failure {
  nrppa_cause_t                     cause;
  std::optional<crit_diagnostics_t> crit_diagnostics;
};


struct nrppa_error_indication {
  nrppa_cause_t                     cause;
  std::optional<crit_diagnostics_t> crit_diagnostics;
};


} // namespace ocucp
} // namespace ocudu
