// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/mac/p5/mac_fapi_p5_sector_adaptor.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/mac/p5/mac_fapi_p5_sector_base_adaptor.h"


namespace ocudu {
namespace fapi_adaptor {


class operation_controller;

/// \brief MAC-FAPI P5 sector adaptor interface.
///
/// The MAC-FAPI P5 sector adaptor provides an operator controller that allows to start/stop a cell using FAPI
/// procedures.
///
/// Note: This interface is used to integrate a third-party L2.

/// \brief MAC-FAPI P5 sector adaptor interface.
///
/// The MAC-FAPI P5 sector adaptor provides an operator controller that allows to start/stop a cell using FAPI
/// procedures.
///
/// Note: This interface is used to integrate a third-party L2.
class mac_fapi_p5_sector_adaptor : public mac_fapi_p5_sector_base_adaptor
{
public:
  /// Returns the operation controller of this adaptor.
  /// Returns the operation controller of this adaptor.
  virtual operation_controller& get_operation_controller() = 0;
};


} // namespace fapi_adaptor
} // namespace ocudu
