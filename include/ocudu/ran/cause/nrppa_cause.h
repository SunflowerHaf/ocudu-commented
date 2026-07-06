// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/cause/nrppa_cause.h  (63 lines)
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
#include <variant>


namespace ocudu {

/// The NRPPa radio network cause, see TS 38.455 section 9.2.1.

/// The NRPPa radio network cause, see TS 38.455 section 9.2.1.
enum class nrppa_cause_radio_network_t : uint8_t {
  unspecified = 0,
  requested_item_not_supported,
  requested_item_temporarily_not_available
};

/// The NRPPa protocol cause, see TS 38.455 section 9.2.1.

/// The NRPPa protocol cause, see TS 38.455 section 9.2.1.
enum class nrppa_cause_protocol_t : uint8_t {
  transfer_syntax_error = 0,
  abstract_syntax_error_reject,
  abstract_syntax_error_ignore_and_notify,
  msg_not_compatible_with_receiver_state,
  semantic_error,
  unspecified,
  abstract_syntax_error_falsely_constructed_msg
};

/// The NRPPa misc cause, see TS 38.455 section 9.2.1.

/// The NRPPa misc cause, see TS 38.455 section 9.2.1.
enum class nrppa_cause_misc_t : uint8_t { unspecified = 0 };

/// The NRPPa cause to indicate the reason for a particular event, see TS 38.455 section 9.2.1.
/// The NRPPa cause is a union of the radio network cause, protocol cause and misc cause.

/// The NRPPa cause to indicate the reason for a particular event, see TS 38.455 section 9.2.1.
/// The NRPPa cause is a union of the radio network cause, protocol cause and misc cause.
using nrppa_cause_t = std::variant<nrppa_cause_radio_network_t, nrppa_cause_protocol_t, nrppa_cause_misc_t>;


} // namespace ocudu


namespace fmt {

// nrppa_cause_t formatter

// nrppa_cause_t formatter
template <>
struct formatter<ocudu::nrppa_cause_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::nrppa_cause_t o, FormatContext& ctx)
  {
    if (const auto* result = std::get_if<ocudu::nrppa_cause_radio_network_t>(&o)) {
      return format_to(ctx.out(), "radio_network-id{}", *result);
    }
    if (const auto* result = std::get_if<ocudu::nrppa_cause_protocol_t>(&o)) {
      return format_to(ctx.out(), "protocol-id{}", *result);
    }
    return format_to(ctx.out(), "misc-id{}", std::get<ocudu::nrppa_cause_misc_t>(o));
  }
};


} // namespace fmt
