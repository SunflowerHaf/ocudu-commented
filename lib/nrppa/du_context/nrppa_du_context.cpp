// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/nrppa/du_context/nrppa_du_context.cpp  (66 lines)
//
// LIBRARY: lib/nrppa
// NR Positioning Protocol A (NRPPa, TS 38.455): the interface between the gNB and the 5GC Location Management Function (LMF). Used for UE positioning (OTDOA, ECID measurements). Implements ASN.1 encode/decode + procedure state machines.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "nrppa_du_context.h"


using namespace ocudu;
using namespace ocucp;


nrppa_du_context_list::nrppa_du_context_list(ocudulog::basic_logger& logger_) : logger(logger_) {}


bool nrppa_du_context_list::contains(cu_cp_du_index_t du_index) const
{
  return dus.find(du_index) != dus.end();
}


nrppa_du_context& nrppa_du_context_list::operator[](cu_cp_du_index_t du_index)
{
  ocudu_assert(dus.find(du_index) != dus.end(), "du={}: NRPPA DU context not found", du_index);


  return dus.at(du_index);
}


nrppa_du_context& nrppa_du_context_list::add_du(cu_cp_du_index_t du_index, nrppa_f1ap_notifier& f1ap_notifier)
{
  logger.debug("du={} : NRPPA DU context created", fmt::underlying(du_index));
  dus.emplace(
      std::piecewise_construct, std::forward_as_tuple(du_index), std::forward_as_tuple(du_index, f1ap_notifier));
  return dus.at(du_index);
}


void nrppa_du_context_list::update_du_index(cu_cp_du_index_t     new_du_index,
                                            cu_cp_du_index_t     old_du_index,
                                            nrppa_f1ap_notifier& new_f1ap_notifier)
{
  ocudu_assert(new_du_index != cu_cp_du_index_t::invalid, "Invalid new_du_index={}", new_du_index);
  ocudu_assert(old_du_index != cu_cp_du_index_t::invalid, "Invalid old_du_index={}", old_du_index);
  ocudu_assert(dus.find(old_du_index) != dus.end(), "du={}: NRPPA DU context not found", old_du_index);
  ocudu_assert(dus.find(new_du_index) == dus.end(), "du={}: NRPPA DU context already exists", new_du_index);

  // Create new DU context.

  // Create new DU context.
  dus.emplace(std::piecewise_construct,
              std::forward_as_tuple(new_du_index),
              std::forward_as_tuple(new_du_index, new_f1ap_notifier));

  // Remove old DU context.

  // Remove old DU context.
  dus.erase(old_du_index);


  dus.at(new_du_index).logger.log_debug("Updated DU index from du_index={}", old_du_index);
}


void nrppa_du_context_list::remove_du_context(cu_cp_du_index_t du_index)
{
  if (dus.find(du_index) == dus.end()) {
    logger.warning("du={}: NRPPA DU not found", du_index);
    return;
  }


  dus.at(du_index).logger.log_debug("Removing NRPPA DU context");
  dus.erase(du_index);
}


size_t nrppa_du_context_list::size() const
{
  return dus.size();
}
