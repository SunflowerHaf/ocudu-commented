// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/mac/p7/mac_fapi_p7_sector_adaptor.h  (39 lines)
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


namespace fapi {
class error_indication_notifier;
class p7_indications_notifier;
class p7_slot_indication_notifier;
} // namespace fapi


namespace fapi_adaptor {

/// \brief MAC-FAPI bidirectional P7 adaptor sector interface.
///
/// This adaptor is a collection of interfaces to get the FAPI message notifiers from the MAC-FAPI sector adaptor
/// to connect them to the PHY-FAPI sector adaptor, so this sector adaptor receives FAPI notifications.
///
/// Note: This interface is used to integrate a third-party L2.

/// \brief MAC-FAPI bidirectional P7 adaptor sector interface.
///
/// This adaptor is a collection of interfaces to get the FAPI message notifiers from the MAC-FAPI sector adaptor
/// to connect them to the PHY-FAPI sector adaptor, so this sector adaptor receives FAPI notifications.
///
/// Note: This interface is used to integrate a third-party L2.
class mac_fapi_p7_sector_adaptor
{
public:
  virtual ~mac_fapi_p7_sector_adaptor() = default;

  /// Returns a reference to the P7 slot indication notifier used by the adaptor.

  /// Returns a reference to the P7 slot indication notifier used by the adaptor.
  virtual fapi::p7_slot_indication_notifier& get_p7_slot_indication_notifier() = 0;

  /// Returns a reference to the error notifier used by the adaptor.

  /// Returns a reference to the error notifier used by the adaptor.
  virtual fapi::error_indication_notifier& get_error_indication_notifier() = 0;

  /// Returns a reference to the P7 indications notifier used by the adaptor.

  /// Returns a reference to the P7 indications notifier used by the adaptor.
  virtual fapi::p7_indications_notifier& get_p7_indications_notifier() = 0;
};


} // namespace fapi_adaptor
} // namespace ocudu
