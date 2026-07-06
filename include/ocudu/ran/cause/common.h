// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/cause/common.h  (240 lines)
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
#include <cstdint>


namespace ocudu {

/// The protocol cause.
/// For E1AP see TS 38.463 section 9.3.1.2.
/// For F1AP see TS 38.473 section 9.3.1.2.
/// For NGAP see TS 38.413 section 9.3.1.2.

/// The protocol cause.
/// For E1AP see TS 38.463 section 9.3.1.2.
/// For F1AP see TS 38.473 section 9.3.1.2.
/// For NGAP see TS 38.413 section 9.3.1.2.
enum class cause_protocol_t : uint8_t {
  transfer_syntax_error = 0,
  abstract_syntax_error_reject,
  abstract_syntax_error_ignore_and_notify,
  msg_not_compatible_with_receiver_state,
  semantic_error,
  abstract_syntax_error_falsely_constructed_msg,
  unspecified
};

/// The misc cause.
/// For E1AP see TS 38.463 section 9.3.1.2.
/// For F1AP see TS 38.473 section 9.3.1.2.

/// The misc cause.
/// For E1AP see TS 38.463 section 9.3.1.2.
/// For F1AP see TS 38.473 section 9.3.1.2.
enum class cause_misc_t : uint8_t {
  ctrl_processing_overload = 0,
  not_enough_user_plane_processing_res,
  hardware_fail,
  om_intervention,
  unspecified
};

/// Provides the establishment cause for the RRCSetupRequest in accordance with the information
/// received from upper layers, see TS 38.331 section 6.2.2.

/// Provides the establishment cause for the RRCSetupRequest in accordance with the information
/// received from upper layers, see TS 38.331 section 6.2.2.
enum class establishment_cause_t : uint8_t {
  emergency = 0,
  high_prio_access,
  mt_access,
  mo_sig,
  mo_data,
  mo_voice_call,
  mo_video_call,
  mo_sms,
  mps_prio_access,
  mcs_prio_access,
  unknown
};

/// RRC connection establishment failure causes per TS 28.552, section 5.1.1.15.3.

/// RRC connection establishment failure causes per TS 28.552, section 5.1.1.15.3.
enum class establishment_fail_cause_t : uint8_t { network_reject = 0, no_reply, other };

/// Provides the resume cause for the RRCResumeRequest in accordance with the information
/// received from upper layers, see TS 38.331 section 6.2.2.

/// Provides the resume cause for the RRCResumeRequest in accordance with the information
/// received from upper layers, see TS 38.331 section 6.2.2.
enum class resume_cause_t : uint8_t {
  emergency = 0,
  high_prio_access,
  mt_access,
  mo_sig,
  mo_data,
  mo_voice_call,
  mo_video_call,
  mo_sms,
  rna_upd,
  mps_prio_access,
  mcs_prio_access,
  unknown
};


} // namespace ocudu


namespace fmt {


template <>
struct formatter<ocudu::cause_protocol_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::cause_protocol_t& cause, FormatContext& ctx) const
  {
    if (cause == ocudu::cause_protocol_t::transfer_syntax_error) {
      return format_to(ctx.out(), "transfer_syntax_error");
    }
    if (cause == ocudu::cause_protocol_t::abstract_syntax_error_reject) {
      return format_to(ctx.out(), "abstract_syntax_error_reject");
    }
    if (cause == ocudu::cause_protocol_t::abstract_syntax_error_ignore_and_notify) {
      return format_to(ctx.out(), "abstract_syntax_error_ignore_and_notify");
    }
    if (cause == ocudu::cause_protocol_t::msg_not_compatible_with_receiver_state) {
      return format_to(ctx.out(), "msg_not_compatible_with_receiver_state");
    }
    if (cause == ocudu::cause_protocol_t::semantic_error) {
      return format_to(ctx.out(), "semantic_error");
    }
    if (cause == ocudu::cause_protocol_t::abstract_syntax_error_falsely_constructed_msg) {
      return format_to(ctx.out(), "abstract_syntax_error_falsely_constructed_msg");
    }
    if (cause == ocudu::cause_protocol_t::unspecified) {
      return format_to(ctx.out(), "unspecified");
    }


    return format_to(ctx.out(), "unknown");
  }
};


template <>
struct formatter<ocudu::cause_misc_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::cause_misc_t& cause, FormatContext& ctx) const
  {
    if (cause == ocudu::cause_misc_t::ctrl_processing_overload) {
      return format_to(ctx.out(), "ctrl_processing_overload");
    }
    if (cause == ocudu::cause_misc_t::not_enough_user_plane_processing_res) {
      return format_to(ctx.out(), "not_enough_user_plane_processing_res");
    }
    if (cause == ocudu::cause_misc_t::hardware_fail) {
      return format_to(ctx.out(), "hardware_fail");
    }
    if (cause == ocudu::cause_misc_t::om_intervention) {
      return format_to(ctx.out(), "om_intervention");
    }
    if (cause == ocudu::cause_misc_t::unspecified) {
      return format_to(ctx.out(), "unspecified");
    }


    return format_to(ctx.out(), "unknown");
  }
};


template <>
struct formatter<ocudu::establishment_cause_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::establishment_cause_t o, FormatContext& ctx) const
  {
    if (o == ocudu::establishment_cause_t::emergency) {
      return format_to(ctx.out(), "emergency");
    }
    if (o == ocudu::establishment_cause_t::high_prio_access) {
      return format_to(ctx.out(), "high_prio_access");
    }
    if (o == ocudu::establishment_cause_t::mt_access) {
      return format_to(ctx.out(), "mt_access");
    }
    if (o == ocudu::establishment_cause_t::mo_sig) {
      return format_to(ctx.out(), "mo_sig");
    }
    if (o == ocudu::establishment_cause_t::mo_data) {
      return format_to(ctx.out(), "mo_data");
    }
    if (o == ocudu::establishment_cause_t::mo_voice_call) {
      return format_to(ctx.out(), "mo_voice_call");
    }
    if (o == ocudu::establishment_cause_t::mo_video_call) {
      return format_to(ctx.out(), "mo_video_call");
    }
    if (o == ocudu::establishment_cause_t::mo_sms) {
      return format_to(ctx.out(), "mo_sms");
    }
    if (o == ocudu::establishment_cause_t::mps_prio_access) {
      return format_to(ctx.out(), "mps_prio_access");
    }
    if (o == ocudu::establishment_cause_t::mcs_prio_access) {
      return format_to(ctx.out(), "mcs_prio_access");
    }


    return format_to(ctx.out(), "unknown");
  }
};


template <>
struct formatter<ocudu::resume_cause_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::resume_cause_t o, FormatContext& ctx) const
  {
    if (o == ocudu::resume_cause_t::emergency) {
      return format_to(ctx.out(), "emergency");
    }
    if (o == ocudu::resume_cause_t::high_prio_access) {
      return format_to(ctx.out(), "high_prio_access");
    }
    if (o == ocudu::resume_cause_t::mt_access) {
      return format_to(ctx.out(), "mt_access");
    }
    if (o == ocudu::resume_cause_t::mo_sig) {
      return format_to(ctx.out(), "mo_sig");
    }
    if (o == ocudu::resume_cause_t::mo_data) {
      return format_to(ctx.out(), "mo_data");
    }
    if (o == ocudu::resume_cause_t::mo_voice_call) {
      return format_to(ctx.out(), "mo_voice_call");
    }
    if (o == ocudu::resume_cause_t::mo_video_call) {
      return format_to(ctx.out(), "mo_video_call");
    }
    if (o == ocudu::resume_cause_t::mo_sms) {
      return format_to(ctx.out(), "mo_sms");
    }
    if (o == ocudu::resume_cause_t::rna_upd) {
      return format_to(ctx.out(), "rna_upd");
    }
    if (o == ocudu::resume_cause_t::mps_prio_access) {
      return format_to(ctx.out(), "mps_prio_access");
    }
    if (o == ocudu::resume_cause_t::mcs_prio_access) {
      return format_to(ctx.out(), "mcs_prio_access");
    }


    return format_to(ctx.out(), "unknown");
  }
};


} // namespace fmt
