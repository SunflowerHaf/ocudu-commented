// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/srs/srs_resource_formatter.h  (56 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/srs/srs_resource_configuration.h"
#include "ocudu/support/format/delimited_formatter.h"


namespace fmt {

/// \brief Custom formatter for \c ocudu::srs_resource_configuration.

/// \brief Custom formatter for \c ocudu::srs_resource_configuration.
template <>
struct formatter<ocudu::srs_resource_configuration> {
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
  auto format(const ocudu::srs_resource_configuration& resource, FormatContext& ctx) const
  {
    helper.format_if_verbose(ctx, "nof_antenna_ports={}", fmt::underlying(resource.nof_antenna_ports));
    helper.format_always(ctx,
                         "symb=[{}, {})",
                         resource.start_symbol,
                         resource.start_symbol.value() + static_cast<unsigned>(resource.nof_symbols));
    helper.format_if_verbose(ctx, "configuration_index={}", resource.configuration_index);
    helper.format_always(ctx, "sequence_id={}", resource.sequence_id);
    helper.format_if_verbose(ctx, "bandwidth_index={}", resource.bandwidth_index);
    helper.format_if_verbose(ctx, "comb_size={}", fmt::underlying(resource.comb_size));
    helper.format_if_verbose(ctx, "comb_offset={}", resource.comb_offset);
    helper.format_if_verbose(ctx, "cyclic_shift={}", resource.cyclic_shift);
    helper.format_if_verbose(ctx, "freq_position={}", resource.freq_position);
    helper.format_if_verbose(ctx, "freq_shift={}", resource.freq_shift);
    helper.format_if_verbose(ctx, "freq_hopping={}", resource.freq_hopping);
    helper.format_if_verbose(ctx, "hopping={}", fmt::underlying(resource.hopping));
    if (resource.periodicity.has_value()) {
      helper.format_if_verbose(
          ctx, "periodicity={}/{}", resource.periodicity->periodicity, resource.periodicity->offset);
    } else {
      helper.format_if_verbose(ctx, "periodicity=na");
    }


    return ctx.out();
  }
};


} // namespace fmt
