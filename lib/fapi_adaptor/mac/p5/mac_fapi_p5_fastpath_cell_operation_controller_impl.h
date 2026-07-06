// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/p5/mac_fapi_p5_fastpath_cell_operation_controller_impl.h  (68 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi/cell_config.h"
#include "ocudu/mac/phy_cell_operation_controller.h"
#include "ocudu/ocudulog/logger.h"


namespace ocudu {


class task_executor;
class timer_manager;


namespace fapi {
class p5_requests_gateway;
} // namespace fapi


namespace fapi_adaptor {


struct p5_transaction_outcome_manager;
class operation_controller;

/// MAC-FAPI P5 fastpath cell operation controller implementation configuration.

/// MAC-FAPI P5 fastpath cell operation controller implementation configuration.
struct mac_fapi_p5_fastpath_cell_operation_controller_impl_config {
  fapi::cell_configuration cell_cfg;
};

/// MAC-FAPI P5 fastpath cell operation controller implementation dependencies.

/// MAC-FAPI P5 fastpath cell operation controller implementation dependencies.
struct mac_fapi_p5_fastpath_cell_operation_controller_impl_dependencies {
  ocudulog::basic_logger&         logger;
  fapi::p5_requests_gateway&      p5_gateway;
  p5_transaction_outcome_manager& transaction_manager;
  timer_manager&                  timers;
  task_executor&                  fapi_ctrl_executor;
  task_executor&                  mac_ctrl_executor;
};

/// MAC-FAPI P5 cell operation controller implementation.

/// MAC-FAPI P5 cell operation controller implementation.
class mac_fapi_p5_fastpath_cell_operation_controller_impl : public phy_cell_operation_controller
{
  /// [[Implementation defined]] Timeout for the FAPI configuration messages.
  /// [[Implementation defined]] Timeout for the FAPI configuration messages.
  static constexpr std::chrono::milliseconds TIMEOUT_IN_MILLISECONDS{5000};


public:
  mac_fapi_p5_fastpath_cell_operation_controller_impl(
      const mac_fapi_p5_fastpath_cell_operation_controller_impl_config&       config,
      const mac_fapi_p5_fastpath_cell_operation_controller_impl_dependencies& dependencies);

  // See interface for documentation.

  // See interface for documentation.
  async_task<bool> start() override;

  // See interface for documentation.

  // See interface for documentation.
  async_task<bool> stop() override;


private:
  const fapi::cell_configuration  cell_cfg;
  ocudulog::basic_logger&         logger;
  fapi::p5_requests_gateway&      p5_gateway;
  p5_transaction_outcome_manager& transaction_manager;
  timer_manager&                  timers;
  task_executor&                  fapi_ctrl_executor;
  task_executor&                  mac_ctrl_executor;
};


} // namespace fapi_adaptor
} // namespace ocudu
