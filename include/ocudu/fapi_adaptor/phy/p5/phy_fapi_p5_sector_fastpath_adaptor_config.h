// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/phy/p5/phy_fapi_p5_sector_fastpath_adaptor_config.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once
#include "ocudu/ocudulog/logger.h"


namespace ocudu {


class upper_phy_operation_controller;
class task_executor;


namespace fapi_adaptor {

/// PHY-FAPI P5 sector fastpath adaptor configuration.

/// PHY-FAPI P5 sector fastpath adaptor configuration.
struct phy_fapi_p5_sector_fastpath_adaptor_config {
  /// Sector identifier.
  /// Sector identifier.
  unsigned sector_id;
};

/// PHY-FAPI P5 sector fastpath adaptor dependencies.

/// PHY-FAPI P5 sector fastpath adaptor dependencies.
struct phy_fapi_p5_sector_fastpath_adaptor_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// Executor.
  /// Executor.
  task_executor& executor;
  /// Upper PHY operation controller.
  /// Upper PHY operation controller.
  upper_phy_operation_controller& upper_phy_controller;
};


} // namespace fapi_adaptor
} // namespace ocudu
