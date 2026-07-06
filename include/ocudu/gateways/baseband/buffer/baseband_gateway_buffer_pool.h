// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Baseband gateway buffer pool definition.
///
/// The baseband gateway buffer pool wraps dynamic buffers in a buffer pool. The pool and its contents are created
/// during the initialization of the application.
///
/// The pool provides a baseband buffer smart pointer type that can be forwarded among different interfaces. When the
/// smart pointer is destroyed, the buffer returns to the pool.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gateways/baseband/buffer/baseband_gateway_buffer_pool.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/gateways
// Generic network gateway interfaces: sctp_network_gateway (for control-plane connections), udp_network_gateway (for user-plane), io_broker (non-blocking I/O event dispatch), network_gateway_config types, and the timer-driven reconnection framework.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Baseband gateway buffer pool definition.
///
/// The baseband gateway buffer pool wraps dynamic buffers in a buffer pool. The pool and its contents are created
/// during the initialization of the application.
///
/// The pool provides a baseband buffer smart pointer type that can be forwarded among different interfaces. When the
/// smart pointer is destroyed, the buffer returns to the pool.

#pragma once


#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_dynamic.h"
#include "ocudu/support/memory_pool/bounded_object_pool.h"


namespace ocudu {

/// Thread safe baseband buffer pool.

/// Thread safe baseband buffer pool.
using baseband_gateway_buffer_pool = bounded_unique_object_pool<baseband_gateway_buffer_dynamic>;

/// Smart pointer for managing baseband buffers.

/// Smart pointer for managing baseband buffers.
using baseband_gateway_buffer_ptr = baseband_gateway_buffer_pool::ptr;


} // namespace ocudu
