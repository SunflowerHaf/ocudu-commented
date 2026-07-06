// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1u/cu_up/f1u_bearer_logger.h  (54 lines)
//
// INTERFACE HEADER — include/ocudu/f1u
// F1-U interface headers: the DU-side and CU-UP-side F1-U gateway abstractions, the f1u_du_gateway and f1u_cu_up_gateway interfaces, and the TEID (tunnel endpoint) pool interface used to allocate unique tunnel identifiers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/rb_id.h"
#include "ocudu/ran/up_transport_layer_info.h"
#include "ocudu/support/format/fmt_to_c_str.h"
#include "ocudu/support/format/prefixed_logger.h"
#include "fmt/format.h"
#include <string.h>


namespace ocudu {
namespace ocuup {


class f1u_bearer_log_prefix
{
public:
  f1u_bearer_log_prefix(uint32_t ue_index, drb_id_t drb_id, const up_transport_layer_info& ul_tnl_info)
  {
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "ue={} {} ul-teid={}: ", ue_index, drb_id, ul_tnl_info.gtp_teid);
    prefix = ocudu::to_c_str(buffer);
  }
  const char* to_c_str() const { return prefix.c_str(); }


private:
  std::string prefix;
};


using f1u_bearer_logger = prefixed_logger<f1u_bearer_log_prefix>;


} // namespace ocuup
} // namespace ocudu


namespace fmt {

// associated formatter

// associated formatter
template <>
struct formatter<ocudu::ocuup::f1u_bearer_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::ocuup::f1u_bearer_log_prefix o, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", o.to_c_str());
  }
};
} // namespace fmt
