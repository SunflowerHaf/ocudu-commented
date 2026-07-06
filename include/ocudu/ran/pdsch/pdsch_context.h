// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdsch/pdsch_context.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/harq_id.h"
#include "ocudu/ran/rnti.h"


namespace ocudu {

/// PDSCH transmission context.

/// PDSCH transmission context.
class pdsch_context
{
public:
  /// Default constructor.
  /// Default constructor.
  pdsch_context() = default;

  /// Constructs from values.

  /// Constructs from values.
  explicit pdsch_context(harq_id_t h_id_, unsigned k1_, unsigned nof_retxs_) :
    h_id(h_id_), k1(k1_), nof_retxs(nof_retxs_)
  {
  }

  /// Comparison operators.

  /// Comparison operators.
  bool operator==(const pdsch_context& other) const
  {
    return h_id == other.h_id && k1 == other.k1 && nof_retxs == other.nof_retxs;
  }
  bool operator!=(const pdsch_context& other) const { return !(*this == other); }

  /// Gets the HARQ process identifier.

  /// Gets the HARQ process identifier.
  harq_id_t get_h_id() const { return h_id; }

  /// Gets if the PDSCH transmission is new.

  /// Gets if the PDSCH transmission is new.
  bool is_new_data() const { return nof_retxs == 0; }


private:
  friend struct fmt::formatter<pdsch_context>;
  harq_id_t h_id      = INVALID_HARQ_ID;
  unsigned  k1        = 0;
  unsigned  nof_retxs = 0;
};


} // namespace ocudu
