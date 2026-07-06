// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/builders/srs_indication_builder.h  (90 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/srs_indication.h"


namespace ocudu {
namespace fapi {

/// SRS indication PDU builder that helps fill in the parameters specified in SCF-222 v4.0 section 3.4.10.

/// SRS indication PDU builder that helps fill in the parameters specified in SCF-222 v4.0 section 3.4.10.
class srs_indication_pdu_builder
{
  srs_indication_pdu& pdu;


public:
  explicit srs_indication_pdu_builder(srs_indication_pdu& pdu_) : pdu(pdu_) {}

  /// \brief Sets the SRS indication PDU UE specific parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10.

  /// \brief Sets the SRS indication PDU UE specific parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10.
  srs_indication_pdu_builder& set_ue_specific_parameters(rnti_t rnti)
  {
    pdu.rnti = rnti;


    return *this;
  }

  /// \brief Sets the SRS indication PDU metrics parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10.

  /// \brief Sets the SRS indication PDU metrics parameters and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10.
  srs_indication_pdu_builder& set_metrics_parameters(std::optional<phy_time_unit> timing_advance_offset)
  {
    pdu.timing_advance_offset = timing_advance_offset;


    return *this;
  }

  /// \brief Sets the SRS indication PDU normalized channel I/Q matrix and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10 Table 3-132.

  /// \brief Sets the SRS indication PDU normalized channel I/Q matrix and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10 Table 3-132.
  srs_indication_pdu_builder& set_codebook_report_matrix(const srs_channel_matrix& matrix)
  {
    pdu.matrix = matrix;


    return *this;
  }

  /// \brief Sets the SRS indication PDU positioning report and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v8.0 Section 3.4.10 Table 3-209.

  /// \brief Sets the SRS indication PDU positioning report and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v8.0 Section 3.4.10 Table 3-209.
  srs_indication_pdu_builder& set_positioning_report_parameters(std::optional<phy_time_unit> ul_relative_toa,
                                                                std::optional<float>         rsrp)
  {
    pdu.positioning = std::make_optional<srs_positioning_report>({.ul_relative_toa = ul_relative_toa, .rsrp = rsrp});


    return *this;
  }
};

/// SRS.indication message builder that helps to fill in the parameters specified in SCF-222 v4.0 Section 3.4.10.

/// SRS.indication message builder that helps to fill in the parameters specified in SCF-222 v4.0 Section 3.4.10.
class srs_indication_builder
{
  srs_indication& msg;


public:
  explicit srs_indication_builder(srs_indication& msg_) : msg(msg_) {}

  /// \brief Sets the \e SRS.indication slot and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10 in table SRS.indication message body.

  /// \brief Sets the \e SRS.indication slot and returns a reference to the builder.
  ///
  /// These parameters are specified in SCF-222 v4.0 Section 3.4.10 in table SRS.indication message body.
  srs_indication_builder& set_slot(slot_point slot)
  {
    msg.slot = slot;


    return *this;
  }

  /// Sets a SRS PDU to the \e SRS.indication message and returns a SRS PDU builder.

  /// Sets a SRS PDU to the \e SRS.indication message and returns a SRS PDU builder.
  srs_indication_pdu_builder set_pdu(rnti_t rnti)
  {
    srs_indication_pdu_builder builder(msg.pdu);
    builder.set_ue_specific_parameters(rnti);


    return builder;
  }
};


} // namespace fapi
} // namespace ocudu
