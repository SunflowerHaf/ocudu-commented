// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/phy/phy_fapi_adaptor.h  (43 lines)
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
class phy_fapi_p7_sector_adaptor;

/// \brief PHY-FAPI bidirectional sector adaptor interface.
///
/// This adaptor represents a sector in FAPI, containing P5 (control/configuration) and P7 (user/slot) FAPI data planes.

/// \brief PHY-FAPI bidirectional sector adaptor interface.
///
/// This adaptor represents a sector in FAPI, containing P5 (control/configuration) and P7 (user/slot) FAPI data planes.
class phy_fapi_sector_adaptor
{
public:
  virtual ~phy_fapi_sector_adaptor() = default;

  /// Returns the P5 sector adaptor of this PHY-FAPI sector adaptor.

  /// Returns the P5 sector adaptor of this PHY-FAPI sector adaptor.
  virtual phy_fapi_p5_sector_adaptor& get_p5_sector_adaptor() = 0;

  // :TODO: remove start/stop.

  // :TODO: remove start/stop.
  virtual void start() = 0;
  virtual void stop()  = 0;

  /// Returns the P7 sector adaptor of this PHY-FAPI sector adaptor.

  /// Returns the P7 sector adaptor of this PHY-FAPI sector adaptor.
  virtual phy_fapi_p7_sector_adaptor& get_p7_sector_adaptor() = 0;
};

/// PHY-FAPI bidirectional adaptor interface.

/// PHY-FAPI bidirectional adaptor interface.
class phy_fapi_adaptor
{
public:
  virtual ~phy_fapi_adaptor() = default;

  /// Returns the PHY-FAPI sector adaptor for the given cell id.

  /// Returns the PHY-FAPI sector adaptor for the given cell id.
  virtual phy_fapi_sector_adaptor& get_sector_adaptor(unsigned cell_id) = 0;
};


} // namespace fapi_adaptor
} // namespace ocudu
