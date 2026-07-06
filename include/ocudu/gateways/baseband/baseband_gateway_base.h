// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gateways/baseband/baseband_gateway_base.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/gateways
// Generic network gateway interfaces: sctp_network_gateway (for control-plane connections), udp_network_gateway (for user-plane), io_broker (non-blocking I/O event dispatch), network_gateway_config types, and the timer-driven reconnection framework.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {

/// Describes the base interface for baseband gateway interfaces.

/// Describes the base interface for baseband gateway interfaces.
class baseband_gateway_base
{
protected:
  /// Allow default constructor for child.
  /// Allow default constructor for child.
  baseband_gateway_base() = default;


public:
  /// Provides default destructor.
  /// Provides default destructor.
  virtual ~baseband_gateway_base() = default;

  /// Forbid copy constructor.

  /// Forbid copy constructor.
  baseband_gateway_base(const baseband_gateway_base& other) = delete;

  /// Forbid move constructor.

  /// Forbid move constructor.
  baseband_gateway_base(baseband_gateway_base&& other) = delete;

  /// Forbid copy assignment operator.

  /// Forbid copy assignment operator.
  baseband_gateway_base& operator=(const baseband_gateway_base&) = delete;

  /// Forbid move assignment operator.

  /// Forbid move assignment operator.
  baseband_gateway_base& operator=(baseband_gateway_base&&) = delete;
};


} // namespace ocudu
