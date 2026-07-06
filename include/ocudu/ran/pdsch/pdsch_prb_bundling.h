// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdsch/pdsch_prb_bundling.h  (40 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <variant>


namespace ocudu {

/// \brief Indicates the PRB bundle type and bundle size(s).
/// \remark See TS 38.214, clause 5.1.2.3.

/// \brief Indicates the PRB bundle type and bundle size(s).
/// \remark See TS 38.214, clause 5.1.2.3.
struct prb_bundling {
  struct static_bundling {
    enum class bundling_size { n4, wideband };


    std::optional<bundling_size> sz;


    bool operator==(const static_bundling& rhs) const { return sz == rhs.sz; }
    bool operator!=(const static_bundling& rhs) const { return !(rhs == *this); }
  };


  struct dynamic_bundling {
    enum class bundling_size_set1 { n4, wideband, n2_wideband, n4_wideband };
    enum class bundling_size_set2 { n4, wideband };


    std::optional<bundling_size_set1> sz_set1;
    std::optional<bundling_size_set2> sz_set2;


    bool operator==(const dynamic_bundling& rhs) const { return sz_set1 == rhs.sz_set1 && sz_set2 == rhs.sz_set2; }
    bool operator!=(const dynamic_bundling& rhs) const { return !(rhs == *this); }
  };


  std::variant<static_bundling, dynamic_bundling> bundling;


  bool operator==(const prb_bundling& rhs) const { return bundling == rhs.bundling; }
  bool operator!=(const prb_bundling& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
