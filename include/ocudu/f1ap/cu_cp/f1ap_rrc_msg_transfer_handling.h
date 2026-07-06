// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/cu_cp/f1ap_rrc_msg_transfer_handling.h  (50 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/ran/rb_id.h"
#include "ocudu/ran/rnti.h"


namespace ocudu::ocucp {


struct f1ap_dl_rrc_message {
  cu_cp_ue_index_t ue_index = cu_cp_ue_index_t::invalid;
  srb_id_t         srb_id   = srb_id_t::nulltype;
  byte_buffer      rrc_container;
};

/// Handles incoming DL RRC messages to be transmitted over the F1 interface.

/// Handles incoming DL RRC messages to be transmitted over the F1 interface.
class f1ap_rrc_message_handler
{
public:
  virtual ~f1ap_rrc_message_handler() = default;

  /// Handles the given DL RRC message.

  /// Handles the given DL RRC message.
  virtual void handle_dl_rrc_message_transfer(const f1ap_dl_rrc_message& msg) = 0;
};

/// Notifier interface used to notify outgoing UL CCCH PDUs that were received over the F1 interface.

/// Notifier interface used to notify outgoing UL CCCH PDUs that were received over the F1 interface.
class f1ap_ul_ccch_notifier
{
public:
  virtual ~f1ap_ul_ccch_notifier() = default;

  /// This callback is invoked on each outgoing UL CCCH PDU.

  /// This callback is invoked on each outgoing UL CCCH PDU.
  virtual void on_ul_ccch_pdu(byte_buffer pdu, rnti_t c_rnti) = 0;
};

/// Notifier interface used to notify outgoing UL DCCH PDUs that were received over the F1 interface.

/// Notifier interface used to notify outgoing UL DCCH PDUs that were received over the F1 interface.
class f1ap_ul_dcch_notifier
{
public:
  virtual ~f1ap_ul_dcch_notifier() = default;

  /// This callback is invoked on each outgoing UL DCCH PDU.

  /// This callback is invoked on each outgoing UL DCCH PDU.
  virtual void on_ul_dcch_pdu(byte_buffer pdu) = 0;
};


} // namespace ocudu::ocucp
