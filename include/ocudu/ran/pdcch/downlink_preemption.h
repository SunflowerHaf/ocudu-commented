// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/downlink_preemption.h  (59 lines)
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
#include "ocudu/ran/du_types.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/support/units.h"
#include <cstdint>


namespace ocudu {

/// \brief UE configuration to monitor PDCCH for INT_RNTI (interruption).
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e DownlinkPreemption).

/// \brief UE configuration to monitor PDCCH for INT_RNTI (interruption).
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e DownlinkPreemption).
struct downlink_preemption {
  /// \brief Set selection for DL-preemption indication.
  /// \remark See TS 38.213, clause 11.2.
  /// \brief Set selection for DL-preemption indication.
  /// \remark See TS 38.213, clause 11.2.
  enum class time_frequency_set { set0, set1 };

  /// \brief Indication of 14 bit INT values inside DCI payload.
  /// \remark See TS 38.213, clause 11.2.

  /// \brief Indication of 14 bit INT values inside DCI payload.
  /// \remark See TS 38.213, clause 11.2.
  struct int_configuration_per_serving_cell {
    du_cell_index_t serving_cell_id;
    /// Starting position (in bits) of the 14 bit INT value applicable for this serving cell within the DCI payload.
    /// Must be multiples of 14 (bit). See TS 38.213, clause 11.2.
    /// Values {0..maxINT-DCI-PayloadSize-1}, where maxINT-DCI-PayloadSize = 126.
    /// Starting position (in bits) of the 14 bit INT value applicable for this serving cell within the DCI payload.
    /// Must be multiples of 14 (bit). See TS 38.213, clause 11.2.
    /// Values {0..maxINT-DCI-PayloadSize-1}, where maxINT-DCI-PayloadSize = 126.
    unsigned position_in_dci;


    bool operator==(const int_configuration_per_serving_cell& rhs) const
    {
      return std::tie(serving_cell_id, position_in_dci) == std::tie(rhs.serving_cell_id, rhs.position_in_dci);
    }


    bool operator!=(const int_configuration_per_serving_cell& rhs) const { return !(rhs == *this); }
  };

  /// RNTI used for indication pre-emption in DL.

  /// RNTI used for indication pre-emption in DL.
  rnti_t int_rnti;
  /// Determines how the UE interprets the DL preemption DCI payload.
  /// Determines how the UE interprets the DL preemption DCI payload.
  time_frequency_set time_freq_set;
  /// Total length of the DCI payload scrambled with INT-RNTI. Values {0..maxINT-DCI-PayloadSize}, where
  /// maxINT-DCI-PayloadSize = 126.
  /// Total length of the DCI payload scrambled with INT-RNTI. Values {0..maxINT-DCI-PayloadSize}, where
  /// maxINT-DCI-PayloadSize = 126.
  units::bits dci_payload_size;
  /// Indicates (per serving cell) the position of the 14 bit INT values inside the DCI payload.
  /// Indicates (per serving cell) the position of the 14 bit INT values inside the DCI payload.
  static_vector<int_configuration_per_serving_cell, MAX_NOF_DU_CELLS> int_cfg;


  bool operator==(const downlink_preemption& rhs) const
  {
    return std::tie(int_rnti, time_freq_set, dci_payload_size, int_cfg) ==
           std::tie(rhs.int_rnti, rhs.time_freq_set, rhs.dci_payload_size, rhs.int_cfg);
  }


  bool operator!=(const downlink_preemption& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
