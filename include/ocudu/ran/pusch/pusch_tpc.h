// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/pusch_tpc.h  (36 lines)
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

/// \brief UE Transmit Power Control (TPC) command configuration for PUSCH.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e PUSCH-TPC-CommandConfig).

/// \brief UE Transmit Power Control (TPC) command configuration for PUSCH.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e PUSCH-TPC-CommandConfig).
struct pusch_tpc_command_config {
  /// An index determining the position of the first bit of TPC command inside the DCI format 2-2 payload.
  /// Values {1..15}. Field is optionally present if this serving cell is configured with a supplementary uplink (SUL).
  /// It is mandatory present otherwise.
  /// An index determining the position of the first bit of TPC command inside the DCI format 2-2 payload.
  /// Values {1..15}. Field is optionally present if this serving cell is configured with a supplementary uplink (SUL).
  /// It is mandatory present otherwise.
  std::optional<uint8_t> tpc_index;
  /// An index determining the position of the first bit of TPC command inside the DCI format 2-2 payload.
  /// Values {1..15}. Present only if serving cell is configured with a supplementary uplink (SUL).
  /// An index determining the position of the first bit of TPC command inside the DCI format 2-2 payload.
  /// Values {1..15}. Present only if serving cell is configured with a supplementary uplink (SUL).
  std::optional<uint8_t> tpc_index_sul;
  /// The serving cell to which the acquired power control commands are applicable. If the value is absent, the UE
  /// applies the TPC commands to the serving cell on which the command has been received.
  /// The serving cell to which the acquired power control commands are applicable. If the value is absent, the UE
  /// applies the TPC commands to the serving cell on which the command has been received.
  std::optional<du_cell_index_t> target_cell;


  bool operator==(const pusch_tpc_command_config& rhs) const
  {
    return std::tie(tpc_index, tpc_index_sul, target_cell) ==
           std::tie(rhs.tpc_index, rhs.tpc_index_sul, rhs.target_cell);
  }


  bool operator!=(const pusch_tpc_command_config& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
