// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/gateways/e1_connection_server.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>
#include <optional>


namespace ocudu {
namespace ocucp {


class cu_cp_e1_handler;

/// Connection server responsible for handling new connection requests/drops coming from CU-UPs via the E1 interface
/// and converting them into CU-CP commands.

/// Connection server responsible for handling new connection requests/drops coming from CU-UPs via the E1 interface
/// and converting them into CU-CP commands.
class e1_connection_server
{
public:
  virtual ~e1_connection_server() = default;

  /// Attach a CU-CP handler to the E1 connection server.

  /// Attach a CU-CP handler to the E1 connection server.
  virtual void attach_cu_cp(cu_cp_e1_handler& cu_e1_handler_) = 0;

  /// Stop the E1 connection server.

  /// Stop the E1 connection server.
  virtual void stop() = 0;

  /// \brief Get port on which the E1 Server is listening for new connections.
  /// \return The port number on which the E1 Server is listening for new connections.

  /// \brief Get port on which the E1 Server is listening for new connections.
  /// \return The port number on which the E1 Server is listening for new connections.
  virtual std::optional<uint16_t> get_listen_port() const = 0;
};


} // namespace ocucp
} // namespace ocudu
