// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/support/network/io_broker_factory.cpp  (18 lines)
//
// LIBRARY: lib/support
// General-purpose C++ utilities: async task executors, thread pools, timer manager, memory pools, span/expected/bounded_integer types, signal dispatcher, config parsers, format helpers, synchronisation primitives (stop_event, sync_event), and versioning. Not 5G-specific — these could be a standalone C++ utility library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/support/io/io_broker_factory.h"
#include "io_broker_epoll.h"


using namespace ocudu;


std::unique_ptr<io_broker> ocudu::create_io_broker(io_broker_type type, const io_broker_config& config)
{
  switch (type) {
    case io_broker_type::epoll:
      return std::make_unique<io_broker_epoll>(config);
    default:
      ocudu_terminate("IO broker type not supported");
  }
  return nullptr;
}
