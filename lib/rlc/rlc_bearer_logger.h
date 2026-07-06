// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/rlc/rlc_bearer_logger.h  (51 lines)
//
// LIBRARY: lib/rlc
// Radio Link Control (RLC, TS 38.322): provides ARQ (Automatic Repeat reQuest) in Acknowledged Mode (AM) and segmentation in Unacknowledged Mode (UM). Sits between MAC and PDCP. In the DU, one RLC entity per Radio Bearer per UE.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/gnb_du_id.h"
#include "ocudu/ran/rb_id.h"
#include "ocudu/support/format/fmt_to_c_str.h"
#include "ocudu/support/format/prefixed_logger.h"
#include "fmt/format.h"


namespace ocudu {


class rlc_bearer_log_prefix
{
public:
  rlc_bearer_log_prefix(gnb_du_id_t gnb_du_id, uint32_t ue_index, rb_id_t rb_id, const char* dir)
  {
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "du={} ue={} {} {}: ", fmt::underlying(gnb_du_id), ue_index, rb_id, dir);
    prefix = ocudu::to_c_str(buffer);
  }
  const char* to_c_str() const { return prefix.c_str(); }


private:
  std::string prefix;
};


using rlc_bearer_logger = prefixed_logger<rlc_bearer_log_prefix>;


} // namespace ocudu


namespace fmt {

// associated formatter

// associated formatter
template <>
struct formatter<ocudu::rlc_bearer_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::rlc_bearer_log_prefix& o, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", o.to_c_str());
  }
};
} // namespace fmt
