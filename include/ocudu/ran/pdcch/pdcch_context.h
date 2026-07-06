// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/pdcch_context.h  (40 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pdcch/search_space.h"
#include "ocudu/ran/rnti.h"


namespace ocudu {

/// PDCCH transmission context.

/// PDCCH transmission context.
class pdcch_context
{
public:
  /// Default constructor.
  /// Default constructor.
  pdcch_context() = default;


  explicit pdcch_context(search_space_id         ss_id_,
                         const char*             dci_format_,
                         std::optional<unsigned> harq_feedback_timing_) :
    ss_id(ss_id_), dci_format(dci_format_), harq_feedback_timing(harq_feedback_timing_)
  {
  }

  /// Comparison operators.

  /// Comparison operators.
  bool operator==(const pdcch_context& other) const
  {
    return ss_id == other.ss_id && dci_format == other.dci_format && harq_feedback_timing == other.harq_feedback_timing;
  }
  bool operator!=(const pdcch_context& other) const { return !(*this == other); }


private:
  friend struct fmt::formatter<pdcch_context>;
  search_space_id         ss_id      = MAX_NOF_SEARCH_SPACES;
  const char*             dci_format = nullptr;
  std::optional<unsigned> harq_feedback_timing;
};


} // namespace ocudu
