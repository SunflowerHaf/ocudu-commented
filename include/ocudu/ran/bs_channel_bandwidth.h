// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/bs_channel_bandwidth.h  (69 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/error_handling.h"


namespace ocudu {

/// Labels for the BS Channel Bandwidth, described in TS38.104, Table 5.3.2-1 for FR1 and Table 5.3.2-2 for FR2.

/// Labels for the BS Channel Bandwidth, described in TS38.104, Table 5.3.2-1 for FR1 and Table 5.3.2-2 for FR2.
enum class bs_channel_bandwidth {
  invalid = 0,
  MHz5    = 5,
  MHz10   = 10,
  MHz15   = 15,
  MHz20   = 20,
  MHz25   = 25,
  MHz30   = 30,
  MHz35   = 35,
  MHz40   = 40,
  MHz45   = 45,
  MHz50   = 50,
  MHz60   = 60,
  MHz70   = 70,
  MHz80   = 80,
  MHz90   = 90,
  MHz100  = 100,
  MHz200  = 200,
  MHz400  = 400,
};

/// Converts the BS channel bandwidth label into the actual BW value in MHz.

/// Converts the BS channel bandwidth label into the actual BW value in MHz.
constexpr unsigned bs_channel_bandwidth_to_MHz(bs_channel_bandwidth bw)
{
  return static_cast<unsigned>(bw);
}

/// Converts the actual BW value in MHz to the BS channel bandwidth label.

/// Converts the actual BW value in MHz to the BS channel bandwidth label.
constexpr bs_channel_bandwidth MHz_to_bs_channel_bandwidth(unsigned bw)
{
  return static_cast<bs_channel_bandwidth>(bw);
}

/// Labels for the <em>Minimum Channel Bandwidth for FR1<\em>. This is not explicitly defined in the TS, but it is used
/// by TS 38.213, Section 13 for the Coreset 0 configuration. As per TS 38.104, Table 5.3.5-1 for FR1 and Table 5.3.5-2
/// for FR2, there are three possible minimum BW: 5MHz, 10MHz, 20MHz, 40MHz and 50MHz.

/// Labels for the <em>Minimum Channel Bandwidth for FR1<\em>. This is not explicitly defined in the TS, but it is used
/// by TS 38.213, Section 13 for the Coreset 0 configuration. As per TS 38.104, Table 5.3.5-1 for FR1 and Table 5.3.5-2
/// for FR2, there are three possible minimum BW: 5MHz, 10MHz, 20MHz, 40MHz and 50MHz.
enum class min_channel_bandwidth { MHz5 = 0, MHz10, MHz20, MHz40, MHz50, invalid };

/// Converts the Minimum Channel Bandwidth for FR1 into the actual BW value in MHz.

/// Converts the Minimum Channel Bandwidth for FR1 into the actual BW value in MHz.
constexpr unsigned min_channel_bandwidth_to_MHz(min_channel_bandwidth bw)
{
  switch (bw) {
    case min_channel_bandwidth::MHz5:
      return 5;
    case min_channel_bandwidth::MHz10:
      return 10;
    case min_channel_bandwidth::MHz20:
      return 20;
    case min_channel_bandwidth::MHz40:
      return 40;
    case min_channel_bandwidth::MHz50:
      return 50;
    default:
      report_fatal_error("Un-supported minimum channel bw.");
  }
}


} // namespace ocudu
