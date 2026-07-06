// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/ssb/pbch_mib_pack.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/ssb/pbch_mib_message.h"
#include <cstdint>


namespace ocudu {

/// \brief Packs the PBCH timing parameters in 8 bits.
///
/// The PBCH payload generation is described in TS38.212 Section 7.1.1.
///
/// \param[in] sfn               System Frame Number (0..1023).
/// \param[in] hrf               \c true if the SS/PBCH block transmission is in an odd half frame, \c false otherwise.
/// \param[in] ssb_block_index   SS/PBCH block opportunity index in a 5ms burst.
/// \param[in] subcarrier_offset Parameter \e ssb-SubcarrierOffset.
/// \param[in] Lmax              Maximum number of SS/PBCH block candidates in a 5ms burst, described in TS38.213
///                              Section 4.1.
/// \return The packed PBCH parameters.

/// \brief Packs the PBCH timing parameters in 8 bits.
///
/// The PBCH payload generation is described in TS38.212 Section 7.1.1.
///
/// \param[in] sfn               System Frame Number (0..1023).
/// \param[in] hrf               \c true if the SS/PBCH block transmission is in an odd half frame, \c false otherwise.
/// \param[in] ssb_block_index   SS/PBCH block opportunity index in a 5ms burst.
/// \param[in] subcarrier_offset Parameter \e ssb-SubcarrierOffset.
/// \param[in] Lmax              Maximum number of SS/PBCH block candidates in a 5ms burst, described in TS38.213
///                              Section 4.1.
/// \return The packed PBCH parameters.
uint8_t pbch_timing_pack(uint32_t              sfn,
                         bool                  hrf,
                         uint8_t               ssb_block_idx,
                         ssb_subcarrier_offset subcarrier_offset,
                         unsigned              L_max);

/// \brief Packs the Master Information Block (MIB).
///
/// The MIB contents are described by the Information Element \e MIB in TS38.331 Section 6.2.2.
///
/// \param[in] msg   PBCH Message containing an MIB for packing.
/// \return Packed MIB payload.

/// \brief Packs the Master Information Block (MIB).
///
/// The MIB contents are described by the Information Element \e MIB in TS38.331 Section 6.2.2.
///
/// \param[in] msg   PBCH Message containing an MIB for packing.
/// \return Packed MIB payload.
uint32_t pbch_mib_pack(const pbch_mib_message& msg);

/// \brief Packs the PBCH payload including the Master Information Block (MIB) and the timing bits.
///
/// The PBCH payload generation is described in TS38.212 Section 7.1.1. The MIB contents are described by the
/// Information Element \e MIB in TS38.331 Section 6.2.2.
///
/// \param[in] msg   PBCH Message containing an MIB for packing.
/// \param[in] Lmax  Maximum number of SS/PBCH block candidates in a 5ms burst, described in TS38.213
///                  Section 4.1.
/// \return Packed PBCH payload.

/// \brief Packs the PBCH payload including the Master Information Block (MIB) and the timing bits.
///
/// The PBCH payload generation is described in TS38.212 Section 7.1.1. The MIB contents are described by the
/// Information Element \e MIB in TS38.331 Section 6.2.2.
///
/// \param[in] msg   PBCH Message containing an MIB for packing.
/// \param[in] Lmax  Maximum number of SS/PBCH block candidates in a 5ms burst, described in TS38.213
///                  Section 4.1.
/// \return Packed PBCH payload.
uint32_t pbch_mib_and_timing_pack(const pbch_mib_message& msg, unsigned L_max);


} // namespace ocudu
