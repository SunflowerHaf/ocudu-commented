// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/phy/phy_fapi_fastpath_adaptor_factory.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/phy/phy_fapi_fastpath_adaptor.h"
#include "ocudu/fapi_adaptor/phy/phy_fapi_fastpath_adaptor_config.h"


namespace ocudu {
namespace fapi_adaptor {

/// Factory to create PHY-FAPI fastpath adaptors.

/// Factory to create PHY-FAPI fastpath adaptors.
class phy_fapi_fastpath_adaptor_factory
{
public:
  virtual ~phy_fapi_fastpath_adaptor_factory() = default;

  /// Creates a PHY-FAPI fastpath adaptor using the given configuration and dependencies.

  /// Creates a PHY-FAPI fastpath adaptor using the given configuration and dependencies.
  virtual std::unique_ptr<phy_fapi_fastpath_adaptor> create(const phy_fapi_fastpath_adaptor_config& config,
                                                            phy_fapi_fastpath_adaptor_dependencies  dependencies) = 0;
};

/// Creates a PHY-FAPI fastpath adaptor factory.

/// Creates a PHY-FAPI fastpath adaptor factory.
std::unique_ptr<phy_fapi_fastpath_adaptor_factory> create_phy_fapi_fastpath_adaptor_factory();


} // namespace fapi_adaptor
} // namespace ocudu
