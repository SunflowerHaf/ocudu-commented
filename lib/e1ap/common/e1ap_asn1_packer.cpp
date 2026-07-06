// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/common/e1ap_asn1_packer.cpp  (43 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "e1ap_asn1_packer.h"
#include "ocudu/e1ap/common/e1ap_message.h"


using namespace ocudu;


e1ap_asn1_packer::e1ap_asn1_packer(sctp_network_gateway_data_handler& gw_, e1ap_message_handler& e1ap_handler) :
  logger(ocudulog::fetch_basic_logger("E1AP-ASN1-PCK")), gw(gw_), e1ap(e1ap_handler)
{
}

// Received packed E1AP PDU that needs to be unpacked and forwarded.

// Received packed E1AP PDU that needs to be unpacked and forwarded.
void e1ap_asn1_packer::handle_packed_pdu(const byte_buffer& bytes)
{
  logger.debug("Received PDU of {} bytes", bytes.length());


  asn1::cbit_ref bref(bytes);
  e1ap_message   msg = {};
  if (msg.pdu.unpack(bref) != asn1::OCUDUASN_SUCCESS) {
    logger.error("Couldn't unpack PDU");
    return;
  }

  // call packet handler

  // call packet handler
  e1ap.handle_message(msg);
}

// Receive populated ASN1 struct that needs to be packed and forwarded.

// Receive populated ASN1 struct that needs to be packed and forwarded.
void e1ap_asn1_packer::handle_message(const e1ap_message& msg)
{
  // pack PDU into temporary buffer
  // pack PDU into temporary buffer
  byte_buffer   tx_pdu;
  asn1::bit_ref bref(tx_pdu);
  if (msg.pdu.pack(bref) != asn1::OCUDUASN_SUCCESS) {
    logger.error("Failed to pack PDU");
    return;
  }


  gw.handle_pdu(tx_pdu);
}
