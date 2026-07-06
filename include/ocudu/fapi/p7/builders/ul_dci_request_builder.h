// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/builders/ul_dci_request_builder.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/builders/dl_pdcch_pdu_builder.h"
#include "ocudu/fapi/p7/messages/ul_dci_request.h"


namespace ocudu {
namespace fapi {

/// UL_DCI.request message builder that helps to fill in the parameters specified in SCF-222 v4.0 section 3.4.4.

/// UL_DCI.request message builder that helps to fill in the parameters specified in SCF-222 v4.0 section 3.4.4.
class ul_dci_request_builder
{
  ul_dci_request& msg;


public:
  explicit ul_dci_request_builder(ul_dci_request& msg_) : msg(msg_) {}

  /// \brief Sets the UL_DCI.request slot point and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.4 in table UL_DCI.request message body.

  /// \brief Sets the UL_DCI.request slot point and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.4 in table UL_DCI.request message body.
  ul_dci_request_builder& set_slot(slot_point slot)
  {
    msg.slot = slot;


    return *this;
  }

  /// \brief Adds a PDCCH PDU to the UL_DCI.request basic parameters and returns a reference to the PDCCH PDU builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.4 in table UL_DCI.request message body.

  /// \brief Adds a PDCCH PDU to the UL_DCI.request basic parameters and returns a reference to the PDCCH PDU builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.4 in table UL_DCI.request message body.
  dl_pdcch_pdu_builder add_pdcch_pdu()
  {
    auto& pdu = msg.pdus.emplace_back();


    dl_pdcch_pdu_builder builder(pdu.pdu);


    return builder;
  }
};


} // namespace fapi
} // namespace ocudu
