// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pucch/pucch_tpc.h  (36 lines)
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

/// \brief UE Transmit Power Control (TPC) command configuration for PUCCH.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e PUCCH-TPC-CommandConfig).

/// \brief UE Transmit Power Control (TPC) command configuration for PUCCH.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e PUCCH-TPC-CommandConfig).
struct pucch_tpc_command_config {
  /// An index determining the position of the first bit of TPC command (applicable to the SpCell) inside the DCI format
  /// 2-2 payload. Values {1..15}.
  /// The field is mandatory present if the PUCCH-TPC-CommandConfig is provided in the PDCCH-Config for the SpCell.
  /// Otherwise, the field is absent.
  /// An index determining the position of the first bit of TPC command (applicable to the SpCell) inside the DCI format
  /// 2-2 payload. Values {1..15}.
  /// The field is mandatory present if the PUCCH-TPC-CommandConfig is provided in the PDCCH-Config for the SpCell.
  /// Otherwise, the field is absent.
  std::optional<uint8_t> tpc_index_pcell;
  /// An index determining the position of the first bit of TPC command (applicable to the PUCCH SCell) inside the DCI
  /// format 2-2 payload. Values {1..15}.
  /// The field is mandatory present if the PUCCH-TPC-CommandConfig is provided in the PDCCH-Config for the PUCCH-SCell.
  /// The field is optionally present, need R, if the UE is configured with a PUCCH SCell in this cell group and if the
  /// PUCCH-TPC-CommandConfig is provided in the PDCCH-Config for the SpCell.
  /// An index determining the position of the first bit of TPC command (applicable to the PUCCH SCell) inside the DCI
  /// format 2-2 payload. Values {1..15}.
  /// The field is mandatory present if the PUCCH-TPC-CommandConfig is provided in the PDCCH-Config for the PUCCH-SCell.
  /// The field is optionally present, need R, if the UE is configured with a PUCCH SCell in this cell group and if the
  /// PUCCH-TPC-CommandConfig is provided in the PDCCH-Config for the SpCell.
  std::optional<uint8_t> tpc_index_pucch_scell;


  bool operator==(const pucch_tpc_command_config& rhs) const
  {
    return std::tie(tpc_index_pcell, tpc_index_pucch_scell) == std::tie(rhs.tpc_index_pcell, rhs.tpc_index_pucch_scell);
  }


  bool operator!=(const pucch_tpc_command_config& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
