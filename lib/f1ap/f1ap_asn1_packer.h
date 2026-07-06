// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/f1ap_asn1_packer.h  (30 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/f1ap/du/f1ap_du.h"
#include "ocudu/gateways/sctp_network_gateway.h"
#include "ocudu/ocudulog/ocudulog.h"
#include <cstdio>


namespace ocudu {


class f1ap_asn1_packer : public f1ap_message_handler
{
public:
  explicit f1ap_asn1_packer(sctp_network_gateway_data_handler& gw, f1ap_message_handler& f1ap);


  void handle_packed_pdu(const byte_buffer& pdu);


  void handle_message(const f1ap_message& msg) override;


private:
  ocudulog::basic_logger&            logger;
  sctp_network_gateway_data_handler& gw;
  f1ap_message_handler&              f1ap;
};


} // namespace ocudu
