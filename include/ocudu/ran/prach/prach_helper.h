// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_helper.h  (52 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/adt/interval.h"
#include "ocudu/ran/duplex_mode.h"
#include "ocudu/ran/prach/prach_configuration.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include <optional>


namespace ocudu {


struct tdd_ul_dl_config_common;


namespace prach_helper {

/// \brief Checks whether a given PRACH configuration index is valid for a given frequency range and duplex mode.
/// \return \c default_success_t if the given parameters are supported, otherwise an error message is provided.

/// \brief Checks whether a given PRACH configuration index is valid for a given frequency range and duplex mode.
/// \return \c default_success_t if the given parameters are supported, otherwise an error message is provided.
error_type<std::string> prach_config_index_is_valid(uint16_t prach_cfg_idx, frequency_range fr, duplex_mode dplx_mode);

/// \brief Checks whether a given PRACH Zero Correlation Zone (ZCZ) is valid for a given PRACH config index, frequency
/// range, and duplex mode.
/// \return \c default_success_t if the given parameters are supported, otherwise an error message is provided.

/// \brief Checks whether a given PRACH Zero Correlation Zone (ZCZ) is valid for a given PRACH config index, frequency
/// range, and duplex mode.
/// \return \c default_success_t if the given parameters are supported, otherwise an error message is provided.
error_type<std::string> zero_correlation_zone_is_valid(uint8_t         zero_correlation_zone,
                                                       uint16_t        prach_cfg_idx,
                                                       frequency_range freq_range,
                                                       duplex_mode     dplx_mode);

/// \brief Finds whether a PRACH config index fits in the provided TDD pattern.
/// \return In case of failure, returns the range of PRACH slots that did not fit in the TDD pattern. If the PRACH
/// configuration is invalid, an empty interval of slots is returned.

/// \brief Finds whether a PRACH config index fits in the provided TDD pattern.
/// \return In case of failure, returns the range of PRACH slots that did not fit in the TDD pattern. If the PRACH
/// configuration is invalid, an empty interval of slots is returned.
error_type<interval<uint8_t>>
prach_fits_in_tdd_pattern(subcarrier_spacing pusch_scs, uint16_t prach_cfg_idx, const tdd_ul_dl_config_common& tdd_cfg);

/// \brief Finds a PRACH configuration index that ensures that PRACH falls in an TDD UL slot.

/// \brief Finds a PRACH configuration index that ensures that PRACH falls in an TDD UL slot.
std::optional<uint8_t> find_valid_prach_config_index(subcarrier_spacing             pusch_scs,
                                                     uint8_t                        zero_correlation_zone,
                                                     const tdd_ul_dl_config_common& tdd_cfg);

/// \brief Checks whether the nof. SSB per RACH occasion and nof. contention based preambles per SSB is valid.
/// \return In case config is not supported, a string with an error message is returned.

/// \brief Checks whether the nof. SSB per RACH occasion and nof. contention based preambles per SSB is valid.
/// \return In case config is not supported, a string with an error message is returned.
error_type<std::string> nof_ssb_per_ro_and_nof_cb_preambles_per_ssb_is_valid(ssb_per_rach_occasions nof_ssb_per_ro,
                                                                             uint8_t nof_cb_preambles_per_ssb);

/// \brief Checks whether a given PRACH Root Sequence Index is valid for a given PRACH format.
/// \return \c default_success_t if the given parameters are supported, otherwise an error message is provided.

/// \brief Checks whether a given PRACH Root Sequence Index is valid for a given PRACH format.
/// \return \c default_success_t if the given parameters are supported, otherwise an error message is provided.
error_type<std::string> prach_root_sequence_index_is_valid(unsigned prach_root_seq_idx, prach_format_type format);
} // namespace prach_helper
} // namespace ocudu
