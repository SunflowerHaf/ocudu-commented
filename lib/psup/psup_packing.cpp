// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/psup/psup_packing.cpp  (133 lines)
//
// LIBRARY: lib/psup
// PDU Session User Plane (PSUP): packs and unpacks the 3GPP TS 38.415 NR user-plane protocol headers used on the N3 (gNB → UPF) and F1-U (DU → CU-UP) GTP-U tunnels. The header carries QFI (QoS Flow Identifier) and other per-PDU metadata.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/psup/psup_packing.h"
#include "ocudu/support/bit_encoding.h"


using namespace ocudu;


bool psup_packing::unpack(psup_dl_pdu_session_information& dl_pdu_session_information, byte_buffer_view container) const
{
  bit_decoder decoder{container};

  // PDU Type

  // PDU Type
  uint8_t pdu_type = 0;
  decoder.unpack(pdu_type, 4);
  if (uint_to_psup_pdu_type(pdu_type) != dl_pdu_session_information.pdu_type) {
    logger.error(
        "Invalid PDU type. unpacked={} expected={}", pdu_type, fmt::underlying(dl_pdu_session_information.pdu_type));
    return false;
  }

  // QMP

  // QMP
  bool qmp = false;
  decoder.unpack(qmp, 1);

  // SNP

  // SNP
  bool snp = false;
  decoder.unpack(snp, 1);

  // Spare

  // Spare
  uint8_t spare = 0;
  decoder.unpack(spare, 2);
  if (spare != 0) {
    logger.warning("Spare bits set in first octet. value={:#x}", spare);
    // TS 38.415 Sec. 5.5.1
    // 'Spare bits should be set to "0" by the sender and should not be checked by the receiver.'
    // TS 38.415 Sec. 5.5.1
    // 'Spare bits should be set to "0" by the sender and should not be checked by the receiver.'
  }

  // PPP

  // PPP
  bool ppp = false;
  decoder.unpack(ppp, 1);

  // RQI

  // RQI
  decoder.unpack(dl_pdu_session_information.rqi, 1);

  // QoS Flow Identifier

  // QoS Flow Identifier
  uint8_t qos_flow_id = 0;
  decoder.unpack(qos_flow_id, 6);
  dl_pdu_session_information.qos_flow_id = uint_to_qos_flow_id(qos_flow_id);


  if (ppp) {
    // PPI
    // PPI
    uint8_t ppi = 0;
    decoder.unpack(ppi, 3);
    dl_pdu_session_information.ppi = uint_to_psup_ppi(ppi);

    // Spare

    // Spare
    spare = 0;
    decoder.unpack(spare, 5);
    if (spare != 0) {
      logger.warning("Spare bits set in third octet. value={:#x}", spare);
      // TS 38.415 Sec. 5.5.1
      // 'Spare bits should be set to "0" by the sender and should not be checked by the receiver.'
      // TS 38.415 Sec. 5.5.1
      // 'Spare bits should be set to "0" by the sender and should not be checked by the receiver.'
    }
  }


  if (qmp) {
    // DL Sending Time Stamp
    // DL Sending Time Stamp
    dl_pdu_session_information.dl_sending_time_stamp = 0;
    decoder.unpack(dl_pdu_session_information.dl_sending_time_stamp.value(), 64);
  }


  if (snp) {
    // DL QFI Sequence Number
    // DL QFI Sequence Number
    dl_pdu_session_information.dl_qfi_sn = 0;
    decoder.unpack(dl_pdu_session_information.dl_qfi_sn.value(), 24);
  }


  return true;
}


bool psup_packing::pack(byte_buffer& out_buf, const psup_dl_pdu_session_information& dl_pdu_session_information) const
{
  size_t      start_len = out_buf.length();
  bit_encoder encoder{out_buf};

  // PDU Type

  // PDU Type
  encoder.pack(psup_pdu_type_to_uint(dl_pdu_session_information.pdu_type), 4);

  // QMP

  // QMP
  encoder.pack(dl_pdu_session_information.dl_sending_time_stamp.has_value(), 1);

  // SNP

  // SNP
  encoder.pack(dl_pdu_session_information.dl_qfi_sn.has_value(), 1);

  // Spare

  // Spare
  encoder.pack(0, 2);

  // PPP

  // PPP
  encoder.pack(dl_pdu_session_information.ppi.has_value(), 1);

  // RQI

  // RQI
  encoder.pack(dl_pdu_session_information.rqi, 1);

  // QoS Flow Identifier

  // QoS Flow Identifier
  encoder.pack(qos_flow_id_to_uint(dl_pdu_session_information.qos_flow_id), 6);


  if (dl_pdu_session_information.ppi.has_value()) {
    // PPI
    // PPI
    encoder.pack(psup_ppi_to_uint(dl_pdu_session_information.ppi.value()), 3);
    // Spare
    // Spare
    encoder.pack(0, 5);
  }


  if (dl_pdu_session_information.dl_sending_time_stamp.has_value()) {
    // DL Sending Time Stamp
    // DL Sending Time Stamp
    encoder.pack(dl_pdu_session_information.dl_sending_time_stamp.value(), 64);
  }


  if (dl_pdu_session_information.dl_qfi_sn.has_value()) {
    // DL QFI Sequence Number
    // DL QFI Sequence Number
    encoder.pack(dl_pdu_session_information.dl_qfi_sn.value(), 24);
  }

  // Add padding such that length is (n*4-2) octets, where n is a positive integer.

  // Add padding such that length is (n*4-2) octets, where n is a positive integer.
  while (((out_buf.length() - start_len) + 2) % 4) {
    if (not out_buf.append(0x0)) {
      return false;
    }
  }
  return true;
}
