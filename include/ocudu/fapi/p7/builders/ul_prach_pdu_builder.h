// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/builders/ul_prach_pdu_builder.h  (64 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/ul_prach_pdu.h"


namespace ocudu {
namespace fapi {

/// PRACH PDU builder that helps to fill in the parameters specified in SCF-222 v4.0 section 3.4.3.1.

/// PRACH PDU builder that helps to fill in the parameters specified in SCF-222 v4.0 section 3.4.3.1.
class ul_prach_pdu_builder
{
  ul_prach_pdu& pdu;


public:
  explicit ul_prach_pdu_builder(ul_prach_pdu& pdu_) : pdu(pdu_) {}

  /// \brief Sets the PRACH PDU preamble parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.

  /// \brief Sets the PRACH PDU preamble parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.
  ul_prach_pdu_builder& set_preamble_parameters(ul_prach_pdu::preambles_interval preambles)
  {
    pdu.preambles = preambles;


    return *this;
  }

  /// \brief Sets the PRACH PDU PRACH parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.

  /// \brief Sets the PRACH PDU PRACH parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.
  ul_prach_pdu_builder& set_prach_parameters(uint8_t num_prach_ocas, uint16_t num_cs, prach_format_type prach_format)
  {
    pdu.num_prach_ocas = num_prach_ocas;
    pdu.num_cs         = num_cs;
    pdu.prach_format   = prach_format;


    return *this;
  }

  /// \brief Sets the PRACH PDU frequency domain related parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.

  /// \brief Sets the PRACH PDU frequency domain related parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.
  ul_prach_pdu_builder& set_frequency_domain_parameters(uint8_t index_fd_ra, uint8_t num_fd_ra)
  {
    pdu.index_fd_ra = index_fd_ra;
    pdu.num_fd_ra   = num_fd_ra;


    return *this;
  }

  /// \brief Sets the PRACH PDU time domain related parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.

  /// \brief Sets the PRACH PDU time domain related parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.3.1 in table PRACH PDU.
  ul_prach_pdu_builder& set_time_domain_parameters(uint8_t prach_start_symbol)
  {
    pdu.prach_start_symbol = prach_start_symbol;


    return *this;
  }
};


} // namespace fapi
} // namespace ocudu
