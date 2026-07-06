// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p5/p5_requests_gateway.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {
namespace fapi {


struct config_request;
struct param_request;
struct start_request;
struct stop_request;

/// This interface represents the gateway for sending FAPI request messages to the underlying PHY.

/// This interface represents the gateway for sending FAPI request messages to the underlying PHY.
class p5_requests_gateway
{
public:
  virtual ~p5_requests_gateway() = default;

  /// \brief Sends a param request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends a param request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_param_request(const param_request& msg) = 0;

  /// \brief Sends a configuration request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends a configuration request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_config_request(const config_request& msg) = 0;

  /// \brief Sends a start request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends a start request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_start_request(const start_request& msg) = 0;

  /// \brief Sends a stop request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends a stop request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_stop_request(const stop_request& msg) = 0;
};


} // namespace fapi
} // namespace ocudu
