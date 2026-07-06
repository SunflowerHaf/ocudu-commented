// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/phys_cell_id.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace phys_cell_id {

/// Number of NR N_id_1 Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.

/// Number of NR N_id_1 Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.
constexpr unsigned NOF_NID_1 = 336;

/// Number of NR N_id_2 Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.

/// Number of NR N_id_2 Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.
constexpr unsigned NOF_NID_2 = 3;

/// Number of NR N_id Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.

/// Number of NR N_id Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.
constexpr unsigned NOF_NID = NOF_NID_1 * NOF_NID_2;

/// Compute N_id_1 from the Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.

/// Compute N_id_1 from the Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.
constexpr unsigned NID_1(unsigned NID)
{
  return NID / NOF_NID_2;
}

/// Compute N_id_2 from the Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.

/// Compute N_id_2 from the Physical Cell Identifier (PCI) as described in TS38.211 Section 7.4.2.1 Physical-layer cell
/// identities.
constexpr unsigned NID_2(unsigned NID)
{
  return NID % NOF_NID_2;
}


} // namespace phys_cell_id
} // namespace ocudu
