// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/mac/p5/mac_fapi_p5_sector_fastpath_adaptor_config.h  (39 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi/cell_config.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/timers.h"


namespace ocudu {


namespace fapi {
class p5_requests_gateway;
} // namespace fapi


namespace fapi_adaptor {

/// MAC-FAPI P5 sector fastpath adaptor configuration.

/// MAC-FAPI P5 sector fastpath adaptor configuration.
struct mac_fapi_p5_sector_fastpath_adaptor_config {
  fapi::cell_configuration cell_cfg;
};

/// MAC-FAPI P5 sector fastpath adaptor dependencies.

/// MAC-FAPI P5 sector fastpath adaptor dependencies.
struct mac_fapi_p5_sector_fastpath_adaptor_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// FAPI P5 requests gateway.
  /// FAPI P5 requests gateway.
  fapi::p5_requests_gateway& p5_gateway;
  /// Timer manager.
  /// Timer manager.
  timer_manager& timers;
  /// FAPI control task executor.
  /// FAPI control task executor.
  task_executor& fapi_ctrl_executor;
  /// MAC control task executor.
  /// MAC control task executor.
  task_executor& mac_ctrl_executor;
};


} // namespace fapi_adaptor
} // namespace ocudu
