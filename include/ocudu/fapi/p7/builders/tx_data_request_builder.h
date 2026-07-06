// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/builders/tx_data_request_builder.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/tx_data_request.h"


namespace ocudu {
namespace fapi {

/// Tx_Data.request message builder that helps to fill in the parameters specified in SCF-222 v4.0 section 3.4.6.

/// Tx_Data.request message builder that helps to fill in the parameters specified in SCF-222 v4.0 section 3.4.6.
class tx_data_request_builder
{
public:
  explicit tx_data_request_builder(tx_data_request& msg_) : msg(msg_) {}

  /// \brief Sets the Tx_Data.request slot point and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.6 in table Tx_Data.request message body.

  /// \brief Sets the Tx_Data.request slot point and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.6 in table Tx_Data.request message body.
  tx_data_request_builder& set_slot(slot_point slot)
  {
    msg.slot = slot;


    return *this;
  }

  /// \brief Adds a new PDU to the Tx_Data.request message and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.6 in table Tx_Data.request message body.

  /// \brief Adds a new PDU to the Tx_Data.request message and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.6 in table Tx_Data.request message body.
  tx_data_request_builder& add_pdu(uint16_t pdu_index, uint8_t cw_index, const shared_transport_block& payload)
  {
    msg.pdus.emplace_back(pdu_index, cw_index, payload);
    return *this;
  }


private:
  tx_data_request& msg;
};


} // namespace fapi
} // namespace ocudu
