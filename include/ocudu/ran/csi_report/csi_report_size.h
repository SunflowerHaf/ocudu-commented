// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/csi_report/csi_report_size.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/uci/uci_part2_size_description.h"
#include "ocudu/support/units.h"


namespace ocudu {

/// Collects the parameters that describe the CSI report size transmitted in PUCCH and PUSCH.

/// Collects the parameters that describe the CSI report size transmitted in PUCCH and PUSCH.
struct csi_report_size {
  /// \brief CSI Part 1 number of bits.
  ///
  /// It is the total number of CSI Part 1 reports described in TS38.212 Table 6.3.2.1.2-6.
  /// \brief CSI Part 1 number of bits.
  ///
  /// It is the total number of CSI Part 1 reports described in TS38.212 Table 6.3.2.1.2-6.
  units::bits part1_size;

  /// \brief CSI Part 1 correspondence to CSI Part 2 size.
  ///
  /// It provides the necessary information for calculating the CSI Part 2 reports payload size from the CSI Part 1
  /// decoded payload. The CSI Part 2 payload is described in TS38.212 Table 6.3.2.1.2-7.

  /// \brief CSI Part 1 correspondence to CSI Part 2 size.
  ///
  /// It provides the necessary information for calculating the CSI Part 2 reports payload size from the CSI Part 1
  /// decoded payload. The CSI Part 2 payload is described in TS38.212 Table 6.3.2.1.2-7.
  uci_part2_size_description part2_correspondence;

  /// \brief CSI Part 2 minimum payload size.
  ///
  /// Minimum number of CSI Part 2 payload bits given \c part2_correspondence. It is calculated by
  /// adding the minimum CSI Part 2 report sizes for all entries in \c part2_correpondence.

  /// \brief CSI Part 2 minimum payload size.
  ///
  /// Minimum number of CSI Part 2 payload bits given \c part2_correspondence. It is calculated by
  /// adding the minimum CSI Part 2 report sizes for all entries in \c part2_correpondence.
  units::bits part2_min_size;

  /// \brief CSI Part 2 maximum payload size.
  ///
  /// Maximum number of CSI Part 2 payload bits given \c part2_correspondence. It is calculated by
  /// adding the maximum CSI Part 2 report sizes for all entries in \c part2_correpondence.

  /// \brief CSI Part 2 maximum payload size.
  ///
  /// Maximum number of CSI Part 2 payload bits given \c part2_correspondence. It is calculated by
  /// adding the maximum CSI Part 2 report sizes for all entries in \c part2_correpondence.
  units::bits part2_max_size;
};


} // namespace ocudu
