// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/band_helper_constants.h  (52 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


namespace band_helper {


constexpr unsigned KHZ_TO_HZ = 1000U;
constexpr double   HZ_TO_KHZ = 1e-3;

/// Offset \f$F_{REF-Offs}\f$ expressed in Hz, for 3GHz-24.25GHz freq. range, as per Table 5.4.2.1-1, TS 38.104.

/// Offset \f$F_{REF-Offs}\f$ expressed in Hz, for 3GHz-24.25GHz freq. range, as per Table 5.4.2.1-1, TS 38.104.
constexpr double N_REF_OFFSET_3_GHZ_24_5_GHZ = 3e9;
/// Offset \f$F_{REF-Offs}\f$ expressed in Hz, for 24.25GHz-100GHz freq. range, as per Table 5.4.2.1-1, TS 38.104.
/// Offset \f$F_{REF-Offs}\f$ expressed in Hz, for 24.25GHz-100GHz freq. range, as per Table 5.4.2.1-1, TS 38.104.
constexpr double N_REF_OFFSET_24_5_GHZ_100_GHZ = 24.25e9;
/// Offset \f$F_{REF-Offs}\f$ expressed in Hz, for 24.25GHz-100GHz freq. range, as per Table 5.4.2.1-1, TS 38.104.
/// Offset \f$F_{REF-Offs}\f$ expressed in Hz, for 24.25GHz-100GHz freq. range, as per Table 5.4.2.1-1, TS 38.104.
constexpr double BASE_FREQ_GSCN_RASTER_24_5_GHZ_100_GHZ = 24250.08e6;
/// Maximum frequency that can be converted to ARFCN, as per Table 5.4.2.1-1, TS 38.104.
/// Maximum frequency that can be converted to ARFCN, as per Table 5.4.2.1-1, TS 38.104.
constexpr double MAX_RASTER_FREQ = 100e9;
/// Freq. step in Hz, corresponding to \f$N\f$ for 0GHz-3GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
/// Freq. step in Hz, corresponding to \f$N\f$ for 0GHz-3GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
constexpr double N_SIZE_SYNC_RASTER_1_HZ = 1200e3;
/// Freq. step in Hz, corresponding to \f$M\f$ for 0GHz-3GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
/// Freq. step in Hz, corresponding to \f$M\f$ for 0GHz-3GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
constexpr double M_SIZE_SYNC_RASTER_1_HZ = 50e3;
/// Freq. step in Hz, corresponding to \f$M\f$ for 3GHz-24.25GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
/// Freq. step in Hz, corresponding to \f$M\f$ for 3GHz-24.25GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
constexpr double N_SIZE_SYNC_RASTER_2_HZ = 1440e3;
/// Freq. step in Hz, corresponding to \f$M\f$ for 24.25GHz-100GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
/// Freq. step in Hz, corresponding to \f$M\f$ for 24.25GHz-100GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
constexpr double N_SIZE_SYNC_RASTER_3_HZ = 17280e3;
/// Upper-bound for \f$N\f$ within the 0GHz-3GHz frequency range, as per Table 5.4.3.1-1, TS 38.104.
/// Upper-bound for \f$N\f$ within the 0GHz-3GHz frequency range, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned N_UB_SYNC_RASTER_1 = 2500;
/// Upper-bound for \f$N\f$ within the 3GHz-24.25GHz frequency range, as per Table 5.4.3.1-1, TS 38.104.
/// Upper-bound for \f$N\f$ within the 3GHz-24.25GHz frequency range, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned N_UB_SYNC_RASTER_2 = 14757;
/// Upper-bound for \f$N\f$ within the 24.25GHz-100GHz frequency range, as per Table 5.4.3.1-1, TS 38.104.
/// Upper-bound for \f$N\f$ within the 24.25GHz-100GHz frequency range, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned N_UB_SYNC_RASTER_3 = 4383;
/// Minimum GSCN value for the freq range 0GHz - 3GHz, as per Table 5.4.3.1-1, TS 38.104.
/// Minimum GSCN value for the freq range 0GHz - 3GHz, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned MIN_GSCN_FREQ_0_3GHZ = 2;
/// Minimum GSCN value for the freq range 3GHz - 24.5GHz, as per Table 5.4.3.1-1, TS 38.104.
/// Minimum GSCN value for the freq range 3GHz - 24.5GHz, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned MIN_GSCN_FREQ_3GHZ_24_5GHZ = 7499;
/// Minimum GSCN value for the freq range 24.5GHz - 100GHz, as per Table 5.4.3.1-1, TS 38.104.
/// Minimum GSCN value for the freq range 24.5GHz - 100GHz, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned MIN_GSCN_FREQ_24_5_GHZ_100_GHZ = 22256;
/// Maximum GSCN value for the freq range 24.5GHz - 100GHz, as per Table 5.4.3.1-1, TS 38.104.
/// Maximum GSCN value for the freq range 24.5GHz - 100GHz, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned MAX_GSCN_FREQ_24_5_GHZ_100_GHZ = 26639;
/// Lower-bound for GSCN within 3GHz-24.25GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
/// Lower-bound for GSCN within 3GHz-24.25GHz freq. range, as per Table 5.4.3.1-1, TS 38.104.
constexpr unsigned GSCN_LB_SYNC_RASTER_2 = 7499U;
/// Lower-bound for GSCN for band n79 and bandwidth equal to or greater than 40MHz, as per Table 5.4.3.3-1, TS 38.104.
/// Lower-bound for GSCN for band n79 and bandwidth equal to or greater than 40MHz, as per Table 5.4.3.3-1, TS 38.104.
constexpr unsigned GSCN_LB_N_79_BW_40_MHZ = 8480U;
/// Lower-bound for GSCN for band n104, as per Table 5.4.3.3-1, TS 38.104.
/// Lower-bound for GSCN for band n104, as per Table 5.4.3.3-1, TS 38.104.
constexpr unsigned GSCN_LB_N_104 = 9882U;


} // namespace band_helper
} // namespace ocudu
