// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pucch/srs_tpc.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/du_types.h"
#include <cstdint>


namespace ocudu {

/// \brief UE Transmit Power Control (TPC) command configuration for SRS.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e SRS-TPC-CommandConfig).

/// \brief UE Transmit Power Control (TPC) command configuration for SRS.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e SRS-TPC-CommandConfig).
struct srs_tpc_command_config {
  /// The starting bit position of a block within the group DCI with SRS request fields (optional) and TPC commands. The
  /// value 1 of the field corresponds to the first/left most bit of format2-3. See TS 38.212, clause 7.3.1 and
  /// TS 38.213, clause 11.3. Values {1..31}.
  /// The starting bit position of a block within the group DCI with SRS request fields (optional) and TPC commands. The
  /// value 1 of the field corresponds to the first/left most bit of format2-3. See TS 38.212, clause 7.3.1 and
  /// TS 38.213, clause 11.3. Values {1..31}.
  std::optional<uint8_t> starting_bit_of_format_2_3;
  /// Indicate whether or not an SRS Request will be included i.e. 0 means SRS request bits in the field is 0 bits
  /// and 1 means SRS request bits in the field is 2 bits. Values {0..1}.
  /// Indicate whether or not an SRS Request will be included i.e. 0 means SRS request bits in the field is 0 bits
  /// and 1 means SRS request bits in the field is 2 bits. Values {0..1}.
  std::optional<uint8_t> field_type_format_2_3;
  /// The starting bit position of a block within the group DCI with SRS request fields (optional) and TPC commands for
  /// SUL. The value 1 of the field corresponds to the first/left most bit of format2-3. See TS 38.212, clause 7.3.1 and
  /// TS 38.213, clause 11.3. Values {1..31}.
  /// The starting bit position of a block within the group DCI with SRS request fields (optional) and TPC commands for
  /// SUL. The value 1 of the field corresponds to the first/left most bit of format2-3. See TS 38.212, clause 7.3.1 and
  /// TS 38.213, clause 11.3. Values {1..31}.
  std::optional<uint8_t> starting_bit_of_format_2_3_sul;


  bool operator==(const srs_tpc_command_config& rhs) const
  {
    return std::tie(starting_bit_of_format_2_3, field_type_format_2_3, starting_bit_of_format_2_3_sul) ==
           std::tie(rhs.starting_bit_of_format_2_3, rhs.field_type_format_2_3, rhs.starting_bit_of_format_2_3_sul);
  }


  bool operator!=(const srs_tpc_command_config& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
