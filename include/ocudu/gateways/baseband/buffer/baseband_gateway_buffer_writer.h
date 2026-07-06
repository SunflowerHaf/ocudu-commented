// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gateways/baseband/buffer/baseband_gateway_buffer_writer.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/gateways
// Generic network gateway interfaces: sctp_network_gateway (for control-plane connections), udp_network_gateway (for user-plane), io_broker (non-blocking I/O event dispatch), network_gateway_config types, and the timer-driven reconnection framework.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"


namespace ocudu {

/// \brief Read-write baseband buffer interface.
///
/// It comprises get_nof_channels() channels of get_nof_samples() samples each.

/// \brief Read-write baseband buffer interface.
///
/// It comprises get_nof_channels() channels of get_nof_samples() samples each.
class baseband_gateway_buffer_writer
{
public:
  virtual ~baseband_gateway_buffer_writer() = default;

  /// Gets the number of channels.

  /// Gets the number of channels.
  virtual unsigned get_nof_channels() const = 0;

  /// Gets the number of samples.

  /// Gets the number of samples.
  virtual unsigned get_nof_samples() const = 0;

  /// \brief Gets a channel buffer.
  /// \param[in] channel_idx Indicates the channel index.
  /// \return A view to a baseband buffer.
  /// \note An invalid channel index causes undefined behaviour.

  /// \brief Gets a channel buffer.
  /// \param[in] channel_idx Indicates the channel index.
  /// \return A view to a baseband buffer.
  /// \note An invalid channel index causes undefined behaviour.
  virtual span<ci16_t> get_channel_buffer(unsigned channel_idx) = 0;

  /// See get_channel_buffer() documentation.

  /// See get_channel_buffer() documentation.
  span<ci16_t> operator[](unsigned channel_index) { return get_channel_buffer(channel_index); }
};


} // namespace ocudu
