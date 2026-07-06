// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/common/e1ap_asn1_packer.h  (30 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/e1ap/common/e1ap_common.h"
#include "ocudu/gateways/sctp_network_gateway.h"
#include "ocudu/ocudulog/ocudulog.h"
#include <cstdio>


namespace ocudu {


class e1ap_asn1_packer : public e1ap_message_handler
{
public:
  explicit e1ap_asn1_packer(sctp_network_gateway_data_handler& gw, e1ap_message_handler& e1ap);


  void handle_packed_pdu(const byte_buffer& pdu);


  void handle_message(const e1ap_message& msg) override;


private:
  ocudulog::basic_logger&            logger;
  sctp_network_gateway_data_handler& gw;
  e1ap_message_handler&              e1ap;
};


} // namespace ocudu
