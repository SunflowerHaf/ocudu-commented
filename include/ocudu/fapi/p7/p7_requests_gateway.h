// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/p7_requests_gateway.h  (42 lines)
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


struct dl_tti_request;
struct tx_data_request;
struct ul_dci_request;
struct ul_tti_request;

/// This interface represents the gateway for sending P7 requests to the underlying PHY.

/// This interface represents the gateway for sending P7 requests to the underlying PHY.
class p7_requests_gateway
{
public:
  virtual ~p7_requests_gateway() = default;

  /// \brief Sends a downlink TTI request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends a downlink TTI request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_dl_tti_request(const dl_tti_request& msg) = 0;

  /// \brief Sends an uplink TTI request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends an uplink TTI request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_ul_tti_request(const ul_tti_request& msg) = 0;

  /// \brief Sends an uplink DCI request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends an uplink DCI request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_ul_dci_request(const ul_dci_request& msg) = 0;

  /// \brief Sends a TX data request message.
  ///
  /// \param[in]  msg   Message contents.

  /// \brief Sends a TX data request message.
  ///
  /// \param[in]  msg   Message contents.
  virtual void send_tx_data_request(const tx_data_request& msg) = 0;
};


} // namespace fapi
} // namespace ocudu
