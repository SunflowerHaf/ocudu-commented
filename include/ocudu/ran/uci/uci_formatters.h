// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/uci/uci_formatters.h  (82 lines)
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
#include "ocudu/support/format/delimited_formatter.h"

/// Custom formatter for \c ocudu::uci_part2_size_description::parameter.

/// Custom formatter for \c ocudu::uci_part2_size_description::parameter.
template <>
struct fmt::formatter<ocudu::uci_part2_size_description::parameter> {
  /// Helper used to parse formatting options and format fields.
  /// Helper used to parse formatting options and format fields.
  ocudu::delimited_formatter helper;

  /// Default constructor.

  /// Default constructor.
  formatter() = default;


  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return helper.parse(ctx);
  }


  template <typename FormatContext>
  auto format(const ocudu::uci_part2_size_description::parameter& value, FormatContext& ctx) const
  {
    helper.format_always(ctx, "offset={}", value.offset);
    helper.format_always(ctx, "width={}", value.width);
    return ctx.out();
  }
};

/// Custom formatter for \c ocudu::uci_part2_size_description::entry.

/// Custom formatter for \c ocudu::uci_part2_size_description::entry.
template <>
struct fmt::formatter<ocudu::uci_part2_size_description::entry> {
  /// Helper used to parse formatting options and format fields.
  /// Helper used to parse formatting options and format fields.
  ocudu::delimited_formatter helper;

  /// Default constructor.

  /// Default constructor.
  formatter() = default;


  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return helper.parse(ctx);
  }


  template <typename FormatContext>
  auto format(const ocudu::uci_part2_size_description::entry& value, FormatContext& ctx) const
  {
    helper.format_always(
        ctx, "params=[{:,}]", ocudu::span<const ocudu::uci_part2_size_description::parameter>(value.parameters));
    helper.format_always(ctx, "map=[{:,}]", ocudu::span<const uint16_t>(value.map));
    return ctx.out();
  }
};

/// Custom formatter for \c ocudu::uci_part2_size_description.

/// Custom formatter for \c ocudu::uci_part2_size_description.
template <>
struct fmt::formatter<ocudu::uci_part2_size_description> {
  /// Helper used to parse formatting options and format fields.
  /// Helper used to parse formatting options and format fields.
  ocudu::delimited_formatter helper;

  /// Default constructor.

  /// Default constructor.
  formatter() = default;


  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return helper.parse(ctx);
  }


  template <typename FormatContext>
  auto format(const ocudu::uci_part2_size_description& description, FormatContext& ctx) const
  {
    helper.format_always(
        ctx, "entries=[{:,}]", ocudu::span<const ocudu::uci_part2_size_description::entry>(description.entries));


    return ctx.out();
  }
};
