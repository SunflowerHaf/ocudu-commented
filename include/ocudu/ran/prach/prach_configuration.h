// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_configuration.h  (82 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/duplex_mode.h"
#include "ocudu/ran/frequency_range.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/slot_point.h"
#include <cstdint>


namespace ocudu {

/// Indicates the number of SSBs per RACH occasion (L1 parameter 'SSB-per-rach-occasion'). See TS 38.331, \c
/// ssb-perRACH-OccasionAndCB-PreamblesPerSSB. Values {1/8, 1/4, 1/2, 1, 2, 4, 8, 16}.
/// Value 1/8 corresponds to one SSB associated with 8 RACH occasions and so on so forth.

/// Indicates the number of SSBs per RACH occasion (L1 parameter 'SSB-per-rach-occasion'). See TS 38.331, \c
/// ssb-perRACH-OccasionAndCB-PreamblesPerSSB. Values {1/8, 1/4, 1/2, 1, 2, 4, 8, 16}.
/// Value 1/8 corresponds to one SSB associated with 8 RACH occasions and so on so forth.
enum class ssb_per_rach_occasions : uint8_t { one_eighth = 0, one_forth, one_half, one, two, four, eight, sixteen };


inline float ssb_per_rach_occ_to_float(ssb_per_rach_occasions value)
{
  return static_cast<float>(1U << (static_cast<unsigned>(value))) / 8.0f;
}

/// \brief Contains the PRACH configuration parameters.
///
/// The parameters are used in TS38.211 Section 6.3.3.2 and they are derived from TS38.211 Tables 6.3.3.2-2, 6.3.3.2-3
/// and 6.3.3.2-4.
///
/// The PRACH transmission occasions are in the system frames \f$n_{SFN}\f$ that satisfy \f$n_{SFN} \bmod x = y\f$.

/// \brief Contains the PRACH configuration parameters.
///
/// The parameters are used in TS38.211 Section 6.3.3.2 and they are derived from TS38.211 Tables 6.3.3.2-2, 6.3.3.2-3
/// and 6.3.3.2-4.
///
/// The PRACH transmission occasions are in the system frames \f$n_{SFN}\f$ that satisfy \f$n_{SFN} \bmod x = y\f$.
struct prach_configuration {
  /// Maximum number of system frame offsets.
  /// Maximum number of system frame offsets.
  static constexpr unsigned max_nof_sfn_offsets = 2;
  /// Maximum number of PRACH slots per radio frame assuming a subcarrier spacing of 60kHz.
  /// Maximum number of PRACH slots per radio frame assuming a subcarrier spacing of 60kHz.
  static constexpr unsigned max_nof_slots_60kHz_frame =
      NOF_SUBFRAMES_PER_FRAME * (1U << to_numerology_value(subcarrier_spacing::kHz60));

  /// Preamble format (see [here](\ref preamble_format) for more information).

  /// Preamble format (see [here](\ref preamble_format) for more information).
  prach_format_type format;
  /// SFN period, \f$x\f$.
  /// SFN period, \f$x\f$.
  unsigned x;
  /// SFN offset \f$y\f$.
  /// SFN offset \f$y\f$.
  static_vector<uint8_t, max_nof_sfn_offsets> y;
  /// \brief Slots within a radio frame that contain PRACH occasions.
  ///
  /// The slot numbering assumes the subcarrier spacing:
  /// - 15kHz for FR1; and
  /// - 60kHz for FR2.
  /// \brief Slots within a radio frame that contain PRACH occasions.
  ///
  /// The slot numbering assumes the subcarrier spacing:
  /// - 15kHz for FR1; and
  /// - 60kHz for FR2.
  static_vector<uint8_t, max_nof_slots_60kHz_frame> slots;
  /// Starting OFDM symbol index.
  /// Starting OFDM symbol index.
  uint8_t starting_symbol;
  /// \brief Number of PRACH slots. Set zero for reserved.
  ///
  /// Depending on the frequency range:
  /// - FR1: within a subframe (15 kHz slot); or
  /// - FR2: within a 60 kHz slot.
  /// \brief Number of PRACH slots. Set zero for reserved.
  ///
  /// Depending on the frequency range:
  /// - FR1: within a subframe (15 kHz slot); or
  /// - FR2: within a 60 kHz slot.
  uint8_t nof_prach_slots_within_subframe;
  /// Number of time-domain PRACH occasions within a PRACH slot. Set zero for reserved.
  /// Number of time-domain PRACH occasions within a PRACH slot. Set zero for reserved.
  uint8_t nof_occasions_within_slot;
  /// PRACH duration in symbols. Only valid for short preamble formats.
  /// PRACH duration in symbols. Only valid for short preamble formats.
  uint8_t duration;
};

/// Reserved PRACH configuration. Indicates the configuration parameters are invalid.

/// Reserved PRACH configuration. Indicates the configuration parameters are invalid.
const prach_configuration PRACH_CONFIG_RESERVED = {prach_format_type::invalid, UINT32_MAX, {}, {}, 0, 0, 0, 0};

/// \brief Gets a PRACH configuration.
///
/// Arguments are considered valid if:
/// - They are consistent with the TS38.211 Tables 6.3.3.2-2, 6.3.3.2-3 and 6.3.3.2-4, and
/// - the combination is implemented.
///
/// Currently, not all configurations are supported.
///
/// \param[in] fr                 Frequency range (see [here](\ref frequency_range) for more information).
/// \param[in] dm                 Duplex mode (see [here](\ref duplex_mode) for more information).
/// \param[in] prach_config_index PRACH configuration index with range {0, ..., 262}.
/// \return A valid PRACH configuration if the provided arguments are valid. Otherwise, \ref PRACH_CONFIG_RESERVED.

/// \brief Gets a PRACH configuration.
///
/// Arguments are considered valid if:
/// - They are consistent with the TS38.211 Tables 6.3.3.2-2, 6.3.3.2-3 and 6.3.3.2-4, and
/// - the combination is implemented.
///
/// Currently, not all configurations are supported.
///
/// \param[in] fr                 Frequency range (see [here](\ref frequency_range) for more information).
/// \param[in] dm                 Duplex mode (see [here](\ref duplex_mode) for more information).
/// \param[in] prach_config_index PRACH configuration index with range {0, ..., 262}.
/// \return A valid PRACH configuration if the provided arguments are valid. Otherwise, \ref PRACH_CONFIG_RESERVED.
prach_configuration prach_configuration_get(frequency_range fr, duplex_mode dm, uint16_t prach_config_index);


} // namespace ocudu
