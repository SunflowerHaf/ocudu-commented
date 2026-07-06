// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/phy/phy_fapi_fastpath_adaptor_config.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/phy/p5/phy_fapi_p5_sector_fastpath_adaptor_config.h"
#include "ocudu/fapi_adaptor/phy/p7/phy_fapi_p7_sector_fastpath_adaptor_config.h"


namespace ocudu {
namespace fapi_adaptor {

/// PHY-FAPI sector fastpath adaptor configuration.

/// PHY-FAPI sector fastpath adaptor configuration.
struct phy_fapi_sector_fastpath_adaptor_config {
  phy_fapi_p5_sector_fastpath_adaptor_config p5_config;
  phy_fapi_p7_sector_fastpath_adaptor_config p7_config;
};

/// PHY-FAPI sector fastpath adaptor dependencies.

/// PHY-FAPI sector fastpath adaptor dependencies.
struct phy_fapi_sector_fastpath_adaptor_dependencies {
  phy_fapi_p5_sector_fastpath_adaptor_dependencies p5_dependencies;
  phy_fapi_p7_sector_fastpath_adaptor_dependencies p7_dependencies;
};

/// PHY-FAPI fastpath adaptor configuration.

/// PHY-FAPI fastpath adaptor configuration.
struct phy_fapi_fastpath_adaptor_config {
  std::vector<phy_fapi_sector_fastpath_adaptor_config> sectors;
};

/// PHY-FAPI fastpath adaptor dependencies.

/// PHY-FAPI fastpath adaptor dependencies.
struct phy_fapi_fastpath_adaptor_dependencies {
  std::vector<phy_fapi_sector_fastpath_adaptor_dependencies> sectors;
};


} // namespace fapi_adaptor
} // namespace ocudu
