// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/o_cu_cp_impl.h  (59 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_cp.h"
#include "ocudu/cu_cp/cu_cp_ng_setup_notifier.h"
#include "ocudu/cu_cp/cu_cp_operation_controller.h"
#include "ocudu/cu_cp/o_cu_cp.h"
#include "ocudu/e2/e2.h"
#include <memory>


namespace ocudu {
namespace ocucp {

/// O-RAN CU-CP implementation.

/// O-RAN CU-CP implementation.
class o_cu_cp_impl : public o_cu_cp, public cu_cp_operation_controller
{
public:
  explicit o_cu_cp_impl(std::unique_ptr<cu_cp> cu_cp_);

  // See interface for documentation.

  // See interface for documentation.
  cu_cp& get_cu_cp() override { return *cu_impl; }

  // See interface for documentation.

  // See interface for documentation.
  cu_cp_operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  // See interface for documentation.
  void start() override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;


private:
  std::unique_ptr<cu_cp> cu_impl;
};

/// O-RAN CU-CP with E2 implementation.

/// O-RAN CU-CP with E2 implementation.
class o_cu_cp_with_e2_impl : public o_cu_cp_impl
{
public:
  o_cu_cp_with_e2_impl(std::unique_ptr<e2_agent>                         e2agent_,
                       std::unique_ptr<cu_cp>                            cu_cp_,
                       std::unique_ptr<cu_cp_ng_setup_complete_notifier> ng_setup_adapter_);

  // See interface for documentation.

  // See interface for documentation.
  void start() override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;


private:
  std::unique_ptr<cu_cp_ng_setup_complete_notifier> ng_setup_e2_adapter;
  std::unique_ptr<e2_agent>                         e2agent;
};


} // namespace ocucp
} // namespace ocudu
