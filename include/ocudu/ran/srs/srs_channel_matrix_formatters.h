// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/srs/srs_channel_matrix_formatters.h  (47 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/srs/srs_channel_matrix.h"


namespace fmt {

/// \brief Custom formatter for \c srs_channel_matrix.

/// \brief Custom formatter for \c srs_channel_matrix.
template <>
struct formatter<ocudu::srs_channel_matrix> {
  /// Default constructor.
  /// Default constructor.
  formatter() = default;


  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::srs_channel_matrix& matrix, FormatContext& ctx) const
  {
    unsigned nof_rx_ports = matrix.get_nof_rx_ports();
    unsigned nof_tx_ports = matrix.get_nof_tx_ports();


    format_to(ctx.out(), "[");
    for (unsigned i_rx_port = 0; i_rx_port != nof_rx_ports; ++i_rx_port) {
      if (i_rx_port != 0) {
        format_to(ctx.out(), ";");
      }
      for (unsigned i_tx_port = 0; i_tx_port != nof_tx_ports; ++i_tx_port) {
        if (i_tx_port != 0) {
          format_to(ctx.out(), ",");
        }
        format_to(ctx.out(), "{:+.3f}", matrix.get_coefficient(i_rx_port, i_tx_port));
      }
    }
    format_to(ctx.out(), "]");


    return ctx.out();
  }
};


} // namespace fmt
