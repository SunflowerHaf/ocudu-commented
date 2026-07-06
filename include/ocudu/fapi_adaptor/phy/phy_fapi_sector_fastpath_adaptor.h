// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/phy/phy_fapi_sector_fastpath_adaptor.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace fapi_adaptor {


class phy_fapi_p5_sector_adaptor;
class phy_fapi_p7_sector_fastpath_adaptor;

/// \brief PHY-FAPI bidirectional sector adaptor interface.
///
/// This adaptor represents a sector in FAPI, containing P5 (control/configuration) and P7 (user/slot) FAPI data planes.

/// \brief PHY-FAPI bidirectional sector adaptor interface.
///
/// This adaptor represents a sector in FAPI, containing P5 (control/configuration) and P7 (user/slot) FAPI data planes.
class phy_fapi_sector_fastpath_adaptor
{
public:
  virtual ~phy_fapi_sector_fastpath_adaptor() = default;

  /// Returns the P5 sector adaptor of this PHY-FAPI sector adaptor.

  /// Returns the P5 sector adaptor of this PHY-FAPI sector adaptor.
  virtual phy_fapi_p5_sector_adaptor& get_p5_sector_adaptor() = 0;

  /// Returns the P7 sector adaptor of this PHY-FAPI sector adaptor.

  /// Returns the P7 sector adaptor of this PHY-FAPI sector adaptor.
  virtual phy_fapi_p7_sector_fastpath_adaptor& get_p7_sector_adaptor() = 0;
};


} // namespace fapi_adaptor
} // namespace ocudu
