// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_up/adapters/pdcp_adapters.h  (168 lines)
//
// LIBRARY: lib/cu_up
// O-RAN Central Unit User Plane core: the PDCP layer (ciphering, integrity, header compression), SDAP (QoS flow to DRB mapping), F1-U endpoint management, N3 GTP-U endpoint, and the O-CU-UP factory. One CU-UP instance handles all UEs' user-plane data.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_up/cu_up_manager.h"
#include "ocudu/e1ap/cu_up/e1ap_cu_up.h"
#include "ocudu/f1u/cu_up/f1u_tx_sdu_handler.h"
#include "ocudu/pdcp/pdcp_rx.h"
#include "ocudu/pdcp/pdcp_tx.h"
#include "ocudu/sdap/sdap.h"


namespace ocudu {
namespace ocuup {

/// Adapter between PDCP and SDAP

/// Adapter between PDCP and SDAP
class pdcp_sdap_adapter : public pdcp_rx_upper_data_notifier
{
public:
  pdcp_sdap_adapter()           = default;
  ~pdcp_sdap_adapter() override = default;


  void connect_sdap(sdap_rx_pdu_handler& sdap_handler_) { sdap_handler = &sdap_handler_; }


  void on_new_sdu(byte_buffer sdu, bool integrity_verified) override
  {
    // The value of integrity_verified is unused for DRBs.
    // The value of integrity_verified is unused for DRBs.
    ocudu_assert(sdap_handler != nullptr, "SDAP handler must not be nullptr");
    sdap_handler->handle_pdu(std::move(sdu));
  }


private:
  sdap_rx_pdu_handler* sdap_handler = nullptr;
};

/// Adapter between PDCP Rx and E1AP (to be forwarded to RRC in the DU)

/// Adapter between PDCP Rx and E1AP (to be forwarded to RRC in the DU)
class pdcp_rx_cu_up_mngr_adapter : public pdcp_rx_upper_control_notifier
{
public:
  pdcp_rx_cu_up_mngr_adapter()           = default;
  ~pdcp_rx_cu_up_mngr_adapter() override = default;


  void connect_cu_up_mngr(cu_up_ue_index_t ue_index_, cu_up_manager_pdcp_interface* cu_up_mngr_)
  {
    cu_up_mngr = cu_up_mngr_;
    ue_index   = ue_index_;
  }


  void on_protocol_failure() override
  {
    if (cu_up_mngr == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").debug("Ignoring on_protocol_failure() from PDCP Rx: No E1AP handler.");
      return;
    }
    cu_up_mngr->handle_pdcp_protocol_failure(ue_index);
  }


  void on_integrity_failure() override
  {
    if (cu_up_mngr == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").debug("Ignoring on_integrity_failure() from PDCP Rx: No E1AP handler.");
      return;
    }
    cu_up_mngr->handle_pdcp_integrity_failure(ue_index);
  }


  void on_max_count_reached() override
  {
    if (cu_up_mngr == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").debug(
          "Max COUNT reached from PDCP Rx, but no E1AP handler present. Ignoring.");
      return;
    }
    cu_up_mngr->handle_pdcp_max_count_reached(ue_index);
  }


  void on_resume_required() override
  {
    if (cu_up_mngr == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").debug(
          "Resume requested from PDCP Rx, but no E1AP handler present. Ignoring");
      return;
    }
    cu_up_mngr->handle_pdcp_resume_required(ue_index);
  }


  cu_up_manager_pdcp_interface* cu_up_mngr = nullptr;
  cu_up_ue_index_t              ue_index   = INVALID_CU_UP_UE_INDEX;
};

/// Adapter between PDCP and F1-U

/// Adapter between PDCP and F1-U
class pdcp_f1u_adapter : public pdcp_tx_lower_notifier
{
public:
  pdcp_f1u_adapter()           = default;
  ~pdcp_f1u_adapter() override = default;


  void connect_f1u(f1u_tx_sdu_handler& f1u_handler_) { f1u_handler = &f1u_handler_; }
  void disconnect_f1u() { f1u_handler = nullptr; }


  void on_new_pdu(byte_buffer pdu, bool is_retx) override
  {
    if (f1u_handler == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").info("Dropped DL PDU. F1-U handler is not connected");
    } else {
      f1u_handler->handle_sdu(std::move(pdu), is_retx);
    }
  }


  void on_discard_pdu(uint32_t pdcp_sn) override
  {
    if (f1u_handler == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").info("Dropped discard command. F1-U handler is not connected");
    } else {
      f1u_handler->discard_sdu(pdcp_sn);
    }
  }


private:
  f1u_tx_sdu_handler* f1u_handler = nullptr;
};

/// Adapter between PDCP Tx and E1AP (to be forwarded to RRC in the DU)

/// Adapter between PDCP Tx and E1AP (to be forwarded to RRC in the DU)
class pdcp_tx_cu_up_mngr_adapter : public pdcp_tx_upper_control_notifier
{
public:
  pdcp_tx_cu_up_mngr_adapter()           = default;
  ~pdcp_tx_cu_up_mngr_adapter() override = default;


  void connect_cu_up_mngr(cu_up_ue_index_t ue_index_, cu_up_manager_pdcp_interface* cu_up_mngr_)
  {
    cu_up_mngr = cu_up_mngr_;
    ue_index   = ue_index_;
  }


  void on_protocol_failure() override
  {
    ocudulog::fetch_basic_logger("PDCP").warning("Ignoring on_protocol_failure() from PDCP Tx: No E1AP handler");
  }


  void on_max_count_reached() override
  {
    if (cu_up_mngr == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").warning(
          "No CU-UP manager handler for PDCP Tx control events. All events will be ignored");
      return;
    }
    cu_up_mngr->handle_pdcp_max_count_reached(ue_index);
  }


  void on_resume_required() override
  {
    if (cu_up_mngr == nullptr) {
      ocudulog::fetch_basic_logger("PDCP").debug(
          "Resume requested from PDCP Tx, but no E1AP handler present. Ignoring");
      return;
    }
    cu_up_mngr->handle_pdcp_resume_required(ue_index);
  }


private:
  cu_up_manager_pdcp_interface* cu_up_mngr = nullptr;
  cu_up_ue_index_t              ue_index   = INVALID_CU_UP_UE_INDEX;
};


} // namespace ocuup
} // namespace ocudu
