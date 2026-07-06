// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/builders/tx_precoding_and_beamforming_pdu_builder.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/tx_precoding_and_beamforming_pdu.h"


namespace ocudu {
namespace fapi {

/// Helper class to fill the transmission precoding and beamforming parameters specified in SCF-222 v4.0
/// section 3.4.2.5.

/// Helper class to fill the transmission precoding and beamforming parameters specified in SCF-222 v4.0
/// section 3.4.2.5.
class tx_precoding_and_beamforming_pdu_builder
{
  tx_precoding_and_beamforming_pdu& pdu;


public:
  explicit tx_precoding_and_beamforming_pdu_builder(tx_precoding_and_beamforming_pdu& pdu_) : pdu(pdu_) {}

  /// Sets the PRG parameters for the fields of the tranmission precoding and beamforming PDU.
  /// \note These parameters are specified in SCF-222 v4.0 section 3.4.2.5, in table Tx precoding and beamforming PDU.

  /// Sets the PRG parameters for the fields of the tranmission precoding and beamforming PDU.
  /// \note These parameters are specified in SCF-222 v4.0 section 3.4.2.5, in table Tx precoding and beamforming PDU.
  tx_precoding_and_beamforming_pdu_builder& set_prg_parameters(unsigned prg_size)
  {
    pdu.prg_size = prg_size;


    return *this;
  }

  /// \brief Sets the precoding matrix index in the transmission precoding and beamforming PDU.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.2.5, in table Tx precoding and beamforming PDU.

  /// \brief Sets the precoding matrix index in the transmission precoding and beamforming PDU.
  ///
  /// These parameters are specified in SCF-222 v4.0 section 3.4.2.5, in table Tx precoding and beamforming PDU.
  tx_precoding_and_beamforming_pdu_builder& set_pmi(unsigned pm_index)
  {
    pdu.prg.pm_index = pm_index;


    return *this;
  }
};


} // namespace fapi
} // namespace ocudu
