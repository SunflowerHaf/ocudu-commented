// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/common/e1ap_logger.h  (50 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e1ap/common/e1ap_types.h"
#include "ocudu/support/format/fmt_to_c_str.h"
#include "ocudu/support/format/prefixed_logger.h"
#include "fmt/format.h"


namespace ocudu {


class e1ap_log_prefix
{
public:
  e1ap_log_prefix(cu_up_e1_index_t e1_index)
  {
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "e1={}: ", fmt::underlying(e1_index));
    prefix = ocudu::to_c_str(buffer);
  }
  const char* to_c_str() const { return prefix.c_str(); }


private:
  std::string prefix;
};


using e1ap_logger = prefixed_logger<e1ap_log_prefix>;


} // namespace ocudu


namespace fmt {

// associated formatter

// associated formatter
template <>
struct formatter<ocudu::e1ap_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::e1ap_log_prefix& o, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", o.to_c_str());
  }
};
} // namespace fmt
