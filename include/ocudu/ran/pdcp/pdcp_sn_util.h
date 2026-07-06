// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcp/pdcp_sn_util.h  (93 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer_view.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/pdcp/pdcp_sn_size.h"
#include "ocudu/support/bit_encoding.h"
#include <cstdint>
#include <optional>


namespace ocudu {

/// \brief Extract PDCP SN from PDCP PDU (or RLC SDU) if applicable.
///
/// This function extracts the PDCP SN from a PDCP PDU (or RLC SDU) in case of a data PDU.
/// Control PDUs return no value as they do not contain a PDCP SN.
///
/// \param pdcp_pdu PDCP PDU (or RLC SDU) from which the PDCP SN shall be extracted.
/// \param pdcp_sn_len The length of the PDCP SN (12 bit or 18 bit) in the PDU.
/// \param is_srb Determines the bearer type: SRB (true) or DRB (false).
/// \return The PDCP SN of the PDU in case of a data PDU; or no value in case of control PDU.

/// \brief Extract PDCP SN from PDCP PDU (or RLC SDU) if applicable.
///
/// This function extracts the PDCP SN from a PDCP PDU (or RLC SDU) in case of a data PDU.
/// Control PDUs return no value as they do not contain a PDCP SN.
///
/// \param pdcp_pdu PDCP PDU (or RLC SDU) from which the PDCP SN shall be extracted.
/// \param pdcp_sn_len The length of the PDCP SN (12 bit or 18 bit) in the PDU.
/// \param is_srb Determines the bearer type: SRB (true) or DRB (false).
/// \return The PDCP SN of the PDU in case of a data PDU; or no value in case of control PDU.
inline std::optional<uint32_t>
get_pdcp_sn(byte_buffer_view pdcp_pdu, pdcp_sn_size pdcp_sn_len, bool is_srb, ocudulog::basic_logger& logger)
{
  if (pdcp_pdu.empty()) {
    logger.error("Cannot get PDCP SN from empty PDU");
    return {};
  }


  if (is_srb && pdcp_sn_len != pdcp_sn_size::size12bits) {
    logger.error(
        "Cannot get PDCP SN of SRB PDU: Invalid pdcp_sn_len={}. pdcp_pdu_len=", pdcp_sn_len, pdcp_pdu.length());
    return {};
  }


  bit_decoder decoder{pdcp_pdu};
  bool        read_ok;

  // D/C field (or R for SRBs)

  // D/C field (or R for SRBs)
  uint8_t dc_field = {};
  read_ok          = decoder.unpack(dc_field, 1);
  if (!read_ok) {
    logger.error("Failed to get PDCP SN: Cannot read D/C field. pdcp_pdu_len={}", pdcp_pdu.length());
    return {};
  }


  if (!is_srb && dc_field == 0) {
    logger.debug("Cannot get PDCP SN of DRB control PDU");
    return {};
  }


  if (is_srb && dc_field == 1) {
    logger.warning("Cannot get PDCP SN of SRB PDU: Reserved MSB set. pdcp_pdu_len={}", pdcp_pdu.length());
    return {};
  }


  uint8_t  reserved;
  uint32_t pdcp_sn;
  switch (pdcp_sn_len) {
    case pdcp_sn_size::size12bits:
      read_ok &= decoder.unpack(reserved, 3);
      read_ok &= decoder.unpack(pdcp_sn, 12);
      break;
    case ocudu::pdcp_sn_size::size18bits:
      read_ok &= decoder.unpack(reserved, 5);
      read_ok &= decoder.unpack(pdcp_sn, 18);
      break;
    default:
      logger.error("Cannot get PDCP SN: Unsupported pdcp_sn_len={}", pdcp_sn_len);
      return {};
  }


  if (!read_ok) {
    logger.error("Failed to get PDCP SN: Cannot read PDCP header. pdcp_pdu_len={}", pdcp_pdu.length());
    return {};
  }


  if (reserved != 0) {
    if (is_srb) {
      logger.warning("Cannot get PDCP SN for SRB PDU with reserved bits set. pdcp_pdu_len={}", pdcp_pdu.length());
    } else {
      logger.warning("Cannot get PDCP SN for DRB data PDU with reserved bits set. pdcp_pdu_len={}", pdcp_pdu.length());
    }
    return {};
  }


  return pdcp_sn;
}


} // namespace ocudu
