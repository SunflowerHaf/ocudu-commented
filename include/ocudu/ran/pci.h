// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pci.h  (49 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>


namespace ocudu {

/// 3GPP TS 38.331, PhysCellId ::= INTEGER (0..1007).

/// 3GPP TS 38.331, PhysCellId ::= INTEGER (0..1007).
using pci_t                 = uint16_t;
constexpr pci_t MIN_PCI     = 0;
constexpr pci_t MAX_PCI     = 1007;
constexpr pci_t INVALID_PCI = MAX_PCI + 1;

/// Returns true if the given struct is valid, otherwise false.

/// Returns true if the given struct is valid, otherwise false.
constexpr bool is_valid(pci_t pci)
{
  // PCI must be in [0..1007].
  // PCI must be in [0..1007].
  return pci < INVALID_PCI;
}

/// \brief IE "PCI-Range" in TS 38.331. Specifies a range of Physical Cell Identifiers.

/// \brief IE "PCI-Range" in TS 38.331. Specifies a range of Physical Cell Identifiers.
struct pci_range_t {
  pci_t start;
  enum class range_t {
    n1        = 1,
    n4        = 4,
    n8        = 8,
    n12       = 12,
    n16       = 16,
    n24       = 24,
    n32       = 32,
    n48       = 48,
    n64       = 64,
    n84       = 84,
    n96       = 96,
    n128      = 128,
    n168      = 168,
    n252      = 252,
    n504      = 504,
    n1008     = 1008,
    max_range = n1008
  };
  range_t size;
};


} // namespace ocudu
