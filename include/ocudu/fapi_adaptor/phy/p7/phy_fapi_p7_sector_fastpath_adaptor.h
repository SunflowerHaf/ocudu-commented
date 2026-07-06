// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/phy/p7/phy_fapi_p7_sector_fastpath_adaptor.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/phy/p7/phy_fapi_p7_sector_adaptor.h"


namespace ocudu {


class upper_phy_error_notifier;
class upper_phy_timing_notifier;
class upper_phy_rx_results_notifier;


namespace fapi_adaptor {

/// \brief PHY-FAPI bidirectional P7 sector fastpath adaptor interface.
///
/// This adaptor is a collection of interfaces to translate FAPI messages into their PHY layer counterpart and vice
/// versa.

/// \brief PHY-FAPI bidirectional P7 sector fastpath adaptor interface.
///
/// This adaptor is a collection of interfaces to translate FAPI messages into their PHY layer counterpart and vice
/// versa.
class phy_fapi_p7_sector_fastpath_adaptor : public phy_fapi_p7_sector_adaptor
{
public:
  /// Returns a reference to the error notifier used by the adaptor.
  /// Returns a reference to the error notifier used by the adaptor.
  virtual upper_phy_error_notifier& get_error_notifier() = 0;

  /// Returns a reference to the timing notifier used by the adaptor.

  /// Returns a reference to the timing notifier used by the adaptor.
  virtual upper_phy_timing_notifier& get_timing_notifier() = 0;

  /// Returns a reference to the results notifier used by the adaptor.

  /// Returns a reference to the results notifier used by the adaptor.
  virtual upper_phy_rx_results_notifier& get_rx_results_notifier() = 0;
};


} // namespace fapi_adaptor
} // namespace ocudu
