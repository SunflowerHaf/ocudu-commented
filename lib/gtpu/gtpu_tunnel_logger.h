// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gtpu/gtpu_tunnel_logger.h  (55 lines)
//
// LIBRARY: lib/gtpu
// GTP-U (GPRS Tunnelling Protocol for User Plane, TS 29.281) implementation. Creates and demultiplexes GTP-U tunnels on F1-U (DU↔CU-UP) and N3 (CU-UP↔UPF). Manages TEID (Tunnel Endpoint Identifier) allocation and per-tunnel routing tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/gtpu/gtpu_teid.h"
#include "ocudu/support/format/fmt_to_c_str.h"
#include "ocudu/support/format/prefixed_logger.h"
#include "fmt/format.h"
#include "fmt/std.h"


namespace ocudu {


class gtpu_tunnel_log_prefix
{
public:
  gtpu_tunnel_log_prefix(std::optional<uint32_t> ue_index, gtpu_teid_t teid, const char* dir)
  {
    fmt::memory_buffer buffer;
    if (ue_index.has_value()) {
      fmt::format_to(std::back_inserter(buffer), "ue={} {} teid={}: ", *ue_index, dir, teid);
    } else {
      fmt::format_to(std::back_inserter(buffer), "{} teid={}: ", dir, teid);
    }
    prefix = ocudu::to_c_str(buffer);
  }
  const char* to_c_str() const { return prefix.c_str(); }


private:
  std::string prefix;
};


using gtpu_tunnel_logger = prefixed_logger<gtpu_tunnel_log_prefix>;


} // namespace ocudu


namespace fmt {

// associated formatter

// associated formatter
template <>
struct formatter<ocudu::gtpu_tunnel_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::gtpu_tunnel_log_prefix o, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", o.to_c_str());
  }
};
} // namespace fmt
