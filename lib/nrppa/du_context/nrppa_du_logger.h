// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/nrppa/du_context/nrppa_du_logger.h  (50 lines)
//
// LIBRARY: lib/nrppa
// NR Positioning Protocol A (NRPPa, TS 38.455): the interface between the gNB and the 5GC Location Management Function (LMF). Used for UE positioning (OTDOA, ECID measurements). Implements ASN.1 encode/decode + procedure state machines.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/support/format/fmt_to_c_str.h"
#include "ocudu/support/format/prefixed_logger.h"
#include "fmt/format.h"


namespace ocudu::ocucp {


class nrppa_du_log_prefix
{
public:
  nrppa_du_log_prefix(cu_cp_du_index_t du_index)
  {
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "du={}: ", fmt::underlying(du_index));
    prefix = ocudu::to_c_str(buffer);
  }
  const char* to_c_str() const { return prefix.c_str(); }


private:
  std::string prefix;
};


using nrppa_du_logger = prefixed_logger<nrppa_du_log_prefix>;


} // namespace ocudu::ocucp


namespace fmt {

// associated formatter

// associated formatter
template <>
struct formatter<ocudu::ocucp::nrppa_du_log_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::ocucp::nrppa_du_log_prefix& o, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", o.to_c_str());
  }
};
} // namespace fmt
