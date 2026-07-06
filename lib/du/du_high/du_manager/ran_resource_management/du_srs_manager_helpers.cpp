// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/ran_resource_management/du_srs_manager_helpers.cpp  (61 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "du_srs_manager_helpers.h"
#include "ocudu/ran/srs/srs_bandwidth_configuration.h"
#include <ocudu/support/ocudu_assert.h>
#include <utility>


using namespace ocudu;
using namespace odu;
using namespace du_srs_mng_details;


std::optional<unsigned> ocudu::odu::du_srs_mng_details::compute_c_srs(unsigned nof_ul_bwp_rbs)
{
  // Iterate over Table 6.4.1.4.3-1, TS 38.211, and find the minimum \f$C_{SRS}\f$ value that maximizes \f$m_{SRS,0}\f$
  // under the constraint \f$m_{SRS,0}\f$ <= UL RBs.

  // As per Table 6.4.1.4.3-1, TS 38.211, the maximum value of \f$C_{SRS}\f$ is 63.
  // Iterate over Table 6.4.1.4.3-1, TS 38.211, and find the minimum \f$C_{SRS}\f$ value that maximizes \f$m_{SRS,0}\f$
  // under the constraint \f$m_{SRS,0}\f$ <= UL RBs.

  // As per Table 6.4.1.4.3-1, TS 38.211, the maximum value of \f$C_{SRS}\f$ is 63.
  constexpr unsigned max_non_valid_c_srs = 64;
  // Defines the pair of C_SRS and m_SRS values.
  // Defines the pair of C_SRS and m_SRS values.
  using pair_c_srs_m_srs                          = std::pair<unsigned, unsigned>;
  std::optional<pair_c_srs_m_srs> candidate_c_srs = std::nullopt;
  for (uint8_t c_srs = 0; c_srs != max_non_valid_c_srs; ++c_srs) {
    // As per Table 6.4.1.4.3-1, TS 38.211, we do not consider frequency hopping.
    // As per Table 6.4.1.4.3-1, TS 38.211, we do not consider frequency hopping.
    constexpr uint8_t b_srs_0    = 0;
    auto              srs_params = srs_configuration_get(c_srs, b_srs_0);


    if (not srs_params.has_value()) {
      ocudu_assertion_failure("C_SRS is not compatible with the current BW configuration");
      return std::nullopt;
    }

    // If there is no candidate C_SRS value, we set the first valid C_SRS value as the candidate.

    // If there is no candidate C_SRS value, we set the first valid C_SRS value as the candidate.
    if (not candidate_c_srs.has_value()) {
      candidate_c_srs = pair_c_srs_m_srs{c_srs, srs_params.value().m_srs};
    }
    // NOTE: the condition srs_params.value().m_srs > candidate_c_srs->second is used to find the minimum C_SRS value
    // that maximizes m_SRS.
    // NOTE: the condition srs_params.value().m_srs > candidate_c_srs->second is used to find the minimum C_SRS value
    // that maximizes m_SRS.
    else if (srs_params.value().m_srs <= nof_ul_bwp_rbs and srs_params.value().m_srs > candidate_c_srs->second) {
      candidate_c_srs = pair_c_srs_m_srs{c_srs, srs_params.value().m_srs};
    }
    // If we reach this point, no need to keep looking for a valid C_SRS value.
    // If we reach this point, no need to keep looking for a valid C_SRS value.
    if (srs_params.value().m_srs > nof_ul_bwp_rbs) {
      break;
    }
  }
  return candidate_c_srs.value().first;
}


unsigned ocudu::odu::du_srs_mng_details::compute_srs_rb_start(unsigned c_srs, unsigned nof_ul_bwp_rbs)
{
  // As per Section 6.4.1.4.3, the parameter \f$m_{SRS}\f$ = 0 is an index that, along with \f$C_{SRS}\f$, maps to the
  // bandwidth of the SRS resources.
  // As per Section 6.4.1.4.3, the parameter \f$m_{SRS}\f$ = 0 is an index that, along with \f$C_{SRS}\f$, maps to the
  // bandwidth of the SRS resources.
  constexpr uint8_t                      b_srs_0    = 0;
  const std::optional<srs_configuration> srs_params = srs_configuration_get(c_srs, b_srs_0);
  ocudu_sanity_check(srs_params.has_value() and nof_ul_bwp_rbs >= srs_params.value().m_srs,
                     "The SRS configuration is not valid");


  return (nof_ul_bwp_rbs - srs_params.value().m_srs) / 2;
}
