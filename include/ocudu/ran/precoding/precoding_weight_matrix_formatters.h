// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/precoding/precoding_weight_matrix_formatters.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/precoding/precoding_weight_matrix.h"
#include "ocudu/support/format/delimited_formatter.h"


namespace fmt {

/// \brief Custom formatter for \c precoding_configuration

/// \brief Custom formatter for \c precoding_configuration
template <>
struct formatter<ocudu::precoding_weight_matrix> {
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
  auto format(const ocudu::precoding_weight_matrix& matrix, FormatContext& ctx) const
  {
    unsigned nof_layers = matrix.get_nof_layers();
    unsigned nof_ports  = matrix.get_nof_ports();


    format_to(ctx.out(), "[");
    for (unsigned i_layer = 0; i_layer != nof_layers; ++i_layer) {
      if (i_layer != 0) {
        format_to(ctx.out(), ";");
      }
      for (unsigned i_port = 0; i_port != nof_ports; ++i_port) {
        if (i_port != 0) {
          format_to(ctx.out(), ",");
        }
        format_to(ctx.out(), "{:+.2f}", matrix.get_coefficient(i_layer, i_port));
      }
    }
    format_to(ctx.out(), "]");


    return ctx.out();
  }
};


} // namespace fmt
