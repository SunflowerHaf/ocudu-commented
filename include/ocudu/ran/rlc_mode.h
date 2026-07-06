// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/rlc_mode.h  (60 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "fmt/format.h"
#include <string>


namespace ocudu {

/// RLC NR modes

/// RLC NR modes
enum class rlc_mode { tm, um_bidir, um_unidir_ul, um_unidir_dl, am };


inline bool from_string(rlc_mode& mode, const std::string& str)
{
  if (str == "am") {
    mode = rlc_mode::am;
    return true;
  }
  if (str == "um-bidir") {
    mode = rlc_mode::um_bidir;
    return true;
  }
  if (str == "um-unidir-ul") {
    mode = rlc_mode::um_unidir_ul;
    return true;
  }
  if (str == "um-unidir-dl") {
    mode = rlc_mode::um_unidir_dl;
    return true;
  }
  if (str == "tm") {
    mode = rlc_mode::tm;
    return true;
  }
  return false;
}


} // namespace ocudu


namespace fmt {


template <>
struct formatter<ocudu::rlc_mode> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::rlc_mode mode, FormatContext& ctx) const
  {
    static constexpr const char* options[] = {"TM", "UM Bi-dir", "UM Uni-dir-UL", "UM Uni-dir-DL", "AM"};
    return format_to(ctx.out(), "{}", options[static_cast<unsigned>(mode)]);
  }
};


} // namespace fmt
