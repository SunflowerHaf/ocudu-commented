// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/radio_link_monitoring.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/csi_rs/csi_rs_id.h"
#include "ocudu/ran/ssb/ssb_configuration.h"
#include <variant>


namespace ocudu {

/// Defines which resource types to be used for the Radio Link Monitoring Configuration.

/// Defines which resource types to be used for the Radio Link Monitoring Configuration.
enum class rlm_resource_type : uint8_t { default_type = 0, ssb, csi_rs, ssb_and_csi_rs };


enum class rlm_res_id_t : uint8_t { MIN_RLM_RES_ID = 0, MAX_RLM_RES_ID = 9, MAX_NOF_RLF_RESOURCES = 10 };


constexpr rlm_res_id_t to_rlm_res_id(std::underlying_type_t<rlm_res_id_t> idx)
{
  return static_cast<rlm_res_id_t>(idx);
}

/// "RadioLinkMonitoringConfig" as per TS 38.331.

/// "RadioLinkMonitoringConfig" as per TS 38.331.
struct radio_link_monitoring_config {
  struct radio_link_monitoring_rs {
    enum class purpose { beam_failure = 0, rlf, both };


    rlm_res_id_t                                res_id;
    purpose                                     resource_purpose;
    std::variant<ssb_id_t, nzp_csi_rs_res_id_t> detection_resource;


    bool operator==(const radio_link_monitoring_rs& rhs) const
    {
      return resource_purpose == rhs.resource_purpose and detection_resource == rhs.detection_resource;
    }
  };


  static_vector<radio_link_monitoring_rs, static_cast<size_t>(rlm_res_id_t::MAX_NOF_RLF_RESOURCES)> rlm_resources;

  // TODO: to be expanded with Beam Failure Resources, when supported.


  // TODO: to be expanded with Beam Failure Resources, when supported.

  bool operator==(const radio_link_monitoring_config& rhs) const { return rlm_resources == rhs.rlm_resources; }


  bool operator!=(const radio_link_monitoring_config& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
