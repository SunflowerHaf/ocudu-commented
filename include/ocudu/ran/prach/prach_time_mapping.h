// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_time_mapping.h  (60 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/ran/nr_band.h"
#include "ocudu/ran/prach/prach_constants.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu::prach_helper {

/// Time-domain information related with the PRACH preamble positioning in slots, in a system frame.

/// Time-domain information related with the PRACH preamble positioning in slots, in a system frame.
class preamble_slot_mapping
{
  /// Maximum number of slots that are contained in a system frame.
  /// \note Computed considering a maximum number of slots per subframe of 16 (SCS = 240kHz). The maximum subcarrier
  /// spacing is limited by the maximum SS/PBCH block subcarrier spacing for FR2 given in the TS 38.104 Table 5.4.3.3-2.
  /// Maximum number of slots that are contained in a system frame.
  /// \note Computed considering a maximum number of slots per subframe of 16 (SCS = 240kHz). The maximum subcarrier
  /// spacing is limited by the maximum SS/PBCH block subcarrier spacing for FR2 given in the TS 38.104 Table 5.4.3.3-2.
  static constexpr unsigned MAX_NOF_PRACH_SLOTS_PER_FRAME = radio_frame_constants::NOF_SUBFRAMES_PER_FRAME * 16;


public:
  preamble_slot_mapping(nr_band band, subcarrier_spacing ul_scs, uint16_t prach_config_index);

  /// Set to true if the selected preamble is long.

  /// Set to true if the selected preamble is long.
  bool has_long_preamble() const { return use_long_preamble; }

  /// For long PRACH preamble formats, this is the duration of the PRACH preamble in slots, which can be more than 1.
  /// For short PRACH preamble formats, this is the duration of the burst of PRACH opportunities, which can be 1 or 2
  /// slots, as per Section 5.3.2, and Tables 6.3.3.2-2 and 6.3.3.2-3, TS 38.211.

  /// For long PRACH preamble formats, this is the duration of the PRACH preamble in slots, which can be more than 1.
  /// For short PRACH preamble formats, this is the duration of the burst of PRACH opportunities, which can be 1 or 2
  /// slots, as per Section 5.3.2, and Tables 6.3.3.2-2 and 6.3.3.2-3, TS 38.211.
  unsigned prach_burst_length_slots() const { return prach_length_slots; }

  /// Whether a PRACH preamble start falls in the given SFN.

  /// Whether a PRACH preamble start falls in the given SFN.
  bool is_sfn_prach_occasion(unsigned sfn) const { return sfn_occasions.test(sfn % sfn_occasions.size()); }

  /// PRACH system frame (SFN) period. Parameter \f$x\f$ in TS 38.211 Section 6.3.3.2.

  /// PRACH system frame (SFN) period. Parameter \f$x\f$ in TS 38.211 Section 6.3.3.2.
  unsigned sfn_period() const { return sfn_occasions.size(); }

  /// Whether a PRACH preamble start falls in the given slot index.
  /// \note In the case of long preamble, this will skip non-starting slots. For the short preamble, this will skip any
  /// slot which does not contain any PRACH occasions.

  /// Whether a PRACH preamble start falls in the given slot index.
  /// \note In the case of long preamble, this will skip non-starting slots. For the short preamble, this will skip any
  /// slot which does not contain any PRACH occasions.
  bool has_slot_index_prach_occasion(unsigned slot_index) const { return slot_occasions.test(slot_index); }

  /// Whether the provided slot falls in a PRACH preamble occasion (both SFN and slot index).

  /// Whether the provided slot falls in a PRACH preamble occasion (both SFN and slot index).
  bool has_prach_occasion(slot_point sl) const
  {
    return is_sfn_prach_occasion(sl.sfn()) and has_slot_index_prach_occasion(sl.slot_index());
  }


private:
  bool     use_long_preamble  = false;
  unsigned prach_length_slots = 0;
  /// Set of system frame numbers (SFN) that satisfy the condition \f$n_{SFN} \bmod x = y\f$. The size of the bitset
  /// is the PRACH system frame (SFN) period. Parameter \f$x\f$ in TS 38.211 Section 6.3.3.2.
  /// Set of system frame numbers (SFN) that satisfy the condition \f$n_{SFN} \bmod x = y\f$. The size of the bitset
  /// is the PRACH system frame (SFN) period. Parameter \f$x\f$ in TS 38.211 Section 6.3.3.2.
  bounded_bitset<prach_constants::MAX_PRACH_SFN_PERIOD> sfn_occasions;
  /// Set of the slots that contain PRACH occasions within a system frame.
  /// Set of the slots that contain PRACH occasions within a system frame.
  bounded_bitset<MAX_NOF_PRACH_SLOTS_PER_FRAME> slot_occasions;
};


} // namespace ocudu::prach_helper
