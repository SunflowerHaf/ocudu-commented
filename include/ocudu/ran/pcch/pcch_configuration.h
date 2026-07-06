// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pcch/pcch_configuration.h  (61 lines)
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
#include "ocudu/adt/tiny_optional.h"


namespace ocudu {

/// \brief Default paging cycle, used to derive 'T' in TS 38.304. Value rf32 corresponds to 32 radio frames and so on.
/// \remark See TS 38.331, PagingCycle.

/// \brief Default paging cycle, used to derive 'T' in TS 38.304. Value rf32 corresponds to 32 radio frames and so on.
/// \remark See TS 38.331, PagingCycle.
enum class paging_cycle { rf32 = 32, rf64 = 64, rf128 = 128, rf256 = 256 };

/// \brief Used to paging related configuration.
/// \remark See TS 38.331, PCCH-Config.

/// \brief Used to paging related configuration.
/// \remark See TS 38.331, PCCH-Config.
struct pcch_config {
  /// \brief Maximum number of paging occasion per paging frame.
  /// \remark See TS 38.331, maxPO-perPF.
  /// \brief Maximum number of paging occasion per paging frame.
  /// \remark See TS 38.331, maxPO-perPF.
  static constexpr unsigned MAX_PO_PER_PF = 4;

  /// \brief The number of PDCCH monitoring occasions corresponding to an SSB within a Paging Occasion.
  /// \remark See TS 38.331, nrofPDCCH-MonitoringOccasionPerSSB-InPO. This field is part of PCCH_Config IE and is
  /// present only if cell operates with shared spectrum channel access.
  /// \remark See TS 38.304, clause 7.1, if nrofPDCCH-MonitoringOccasionPerSSB-InPO is not configured its value is equal
  /// to 1.

  /// \brief The number of PDCCH monitoring occasions corresponding to an SSB within a Paging Occasion.
  /// \remark See TS 38.331, nrofPDCCH-MonitoringOccasionPerSSB-InPO. This field is part of PCCH_Config IE and is
  /// present only if cell operates with shared spectrum channel access.
  /// \remark See TS 38.304, clause 7.1, if nrofPDCCH-MonitoringOccasionPerSSB-InPO is not configured its value is equal
  /// to 1.
  static constexpr unsigned NR_OF_PDCCH_MONITORING_OCCASION_PER_SSB_IN_PO = 1;

  /// \brief Number of paging occasions per paging frame.

  /// \brief Number of paging occasions per paging frame.
  enum class nof_po_per_pf { four = 4, two = 2, one = 1 };
  /// Number of paging frames per DRX cycle. nAndPagingFrameOffset in TS 38.331 in divided into \c nof_pf and \c
  /// paging_frame_offset. e.g. for value oneEighthT and DRX value of 32 RF gives nof. paging frames per DRX cycle is 4.
  /// Number of paging frames per DRX cycle. nAndPagingFrameOffset in TS 38.331 in divided into \c nof_pf and \c
  /// paging_frame_offset. e.g. for value oneEighthT and DRX value of 32 RF gives nof. paging frames per DRX cycle is 4.
  enum class nof_pf_per_drx_cycle { oneT = 1, halfT = 2, quarterT = 4, oneEighthT = 8, oneSixteethT = 16 };

  /// \brief Points out the type of first PDCCH monitoring occasion for paging of each PO of the PF.

  /// \brief Points out the type of first PDCCH monitoring occasion for paging of each PO of the PF.
  enum class first_pdcch_monitoring_occasion_of_po_type {
    scs15khzOneT,
    scs30khzOneT_scs15khzHalfT,
    scs60khzOneT_scs30khzHalfT_scs15khzQuarterT,
    scs120khzOneT_scs60khzHalfT_scs30khzQuarterT_scs15khzOneEighthT,
    scs120khzHalfT_scs60khzQuarterT_scs30khzOneEighthT_scs15khzOneSixteenthT,
    scs480khzOneT_scs120khzQuarterT_scs60khzOneEighthT_scs30khzOneSixteenthT,
    scs480khzHalfT_scs120khzOneEighthT_scs60khzOneSixteenthT,
    scs480khzQuarterT_scs120khzOneSixteenthT,
  };


  paging_cycle default_paging_cycle;


  nof_pf_per_drx_cycle nof_pf;
  /// Values {0,...,(T/n) - 1}. e.g. if n = quarterT, then values range from 0 to 3.
  /// Values {0,...,(T/n) - 1}. e.g. if n = quarterT, then values range from 0 to 3.
  unsigned paging_frame_offset{0};


  nof_po_per_pf ns;

  /// See TS 38.331, firstPDCCH-MonitoringOccasionOfPO.

  /// See TS 38.331, firstPDCCH-MonitoringOccasionOfPO.
  std::optional<first_pdcch_monitoring_occasion_of_po_type> first_pdcch_mo_of_po_type;
  static_vector<unsigned, MAX_PO_PER_PF>                    first_pdcch_monitoring_occasion_of_po_value;
};


} // namespace ocudu
