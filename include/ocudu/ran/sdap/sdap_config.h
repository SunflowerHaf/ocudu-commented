// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/sdap/sdap_config.h  (84 lines)
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


namespace ocudu {

/// SDAP header options for UL

/// SDAP header options for UL
enum class sdap_hdr_ul_cfg { present = 0, absent };

/// SDAP header options for DL

/// SDAP header options for DL
enum class sdap_hdr_dl_cfg { present = 0, absent };

/// Configurable parameters for SDAP mapping.
/// Based on SDAP-Config defined in E1AP specification (TS 38.463 clause 9.3.1.39),
/// as that is the simplest configuration defined in the standard.
///
/// Other layers (such as RRC and SDAP) can define their own configs, re-using
/// this existing config and adding their own extra configuration as required.

/// Configurable parameters for SDAP mapping.
/// Based on SDAP-Config defined in E1AP specification (TS 38.463 clause 9.3.1.39),
/// as that is the simplest configuration defined in the standard.
///
/// Other layers (such as RRC and SDAP) can define their own configs, re-using
/// this existing config and adding their own extra configuration as required.
struct sdap_ran_config {
  bool            default_drb = false;
  sdap_hdr_ul_cfg header_ul   = sdap_hdr_ul_cfg::absent;
  sdap_hdr_dl_cfg header_dl   = sdap_hdr_dl_cfg::absent;
};


} // namespace ocudu

// Formatters

// Formatters
namespace fmt {

// Header config

// Header config
template <>
struct formatter<ocudu::sdap_hdr_ul_cfg> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::sdap_hdr_ul_cfg hdr_cfg, FormatContext& ctx) const
  {
    static constexpr const char* options[] = {"present", "absent"};
    return format_to(ctx.out(), "{}", options[static_cast<unsigned>(hdr_cfg)]);
  }
};

// Header config

// Header config
template <>
struct formatter<ocudu::sdap_hdr_dl_cfg> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::sdap_hdr_dl_cfg hdr_cfg, FormatContext& ctx) const
  {
    static constexpr const char* options[] = {"present", "absent"};
    return format_to(ctx.out(), "{}", options[static_cast<unsigned>(hdr_cfg)]);
  }
};

// SDAP config

// SDAP config
template <>
struct formatter<ocudu::sdap_ran_config> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::sdap_ran_config cfg, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "default_drb={} hdr_ul={} hdr_dl={}", cfg.default_drb, cfg.header_ul, cfg.header_dl);
  }
};


} // namespace fmt
