// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p5/p5_responses_notifier.h  (38 lines)
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


struct config_response;
struct param_response;
struct stop_indication;

/// \brief Configuration message notifier interface.
///
/// This interface notifies the reception of FAPI configuration P5 response messages from the underlying PHY.

/// \brief Configuration message notifier interface.
///
/// This interface notifies the reception of FAPI configuration P5 response messages from the underlying PHY.
class p5_responses_notifier
{
public:
  virtual ~p5_responses_notifier() = default;

  /// \brief Notifies the reception of a parameter response message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a parameter response message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_param_response(const param_response& msg) = 0;

  /// \brief Notifies the reception of a configuration response message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a configuration response message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_config_response(const config_response& msg) = 0;

  /// \brief Notifies the reception of a stop response message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a stop response message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_stop_indication(const stop_indication& msg) = 0;
};


} // namespace fapi
} // namespace ocudu
