// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_cp/ue_configuration.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/cu_cp
// CU-CP public interfaces: the abstract classes that the CU-CP exposes to the rest of the system. Key interfaces: cu_cp (the top-level factory and lifecycle), cu_cp_operation_controller (start/stop), n2_connection_client (NGAP socket management), cu_configurator (SSB/RRM/SIB remote changes), and the UE management interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <chrono>


namespace ocudu::ocucp {

/// UE configuration passed to CU-CP

/// UE configuration passed to CU-CP
struct ue_configuration {
  std::chrono::seconds inactivity_timer{7200};
  /// Timeout for requesting a PDU session in seconds, before the UE is released.
  /// Timeout for requesting a PDU session in seconds, before the UE is released.
  std::chrono::seconds request_pdu_session_timeout = std::chrono::seconds{2};
  /// When set to false, UEs will not be set to RRC inactive.
  /// When set to false, UEs will not be set to RRC inactive.
  bool enable_rrc_inactive = false;
  /// RAN Paging cycle for RRC inactive UEs in number of radio frames.
  /// RAN Paging cycle for RRC inactive UEs in number of radio frames.
  uint8_t ran_paging_cycle = 32;
  /// T380 timer value in minutes.
  /// T380 timer value in minutes.
  std::chrono::minutes t380 = std::chrono::minutes{10};
  /// Number of bits used for UE ID in I-RNTI.
  /// Number of bits used for UE ID in I-RNTI.
  uint8_t nof_i_rnti_ue_bits = 13;
};


} // namespace ocudu::ocucp
