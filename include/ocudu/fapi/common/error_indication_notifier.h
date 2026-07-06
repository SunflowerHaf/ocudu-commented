// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/common/error_indication_notifier.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {
namespace fapi {


struct error_indication;

/// \brief Error-specific message notifier interface.
///
/// This interface listens to FAPI error indication events and translates them to the suitable data types
/// for the MAC layer.

/// \brief Error-specific message notifier interface.
///
/// This interface listens to FAPI error indication events and translates them to the suitable data types
/// for the MAC layer.
class error_indication_notifier
{
public:
  virtual ~error_indication_notifier() = default;

  /// \brief Notifies the reception of an error indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of an error indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_error_indication(const error_indication& msg) = 0;
};


} // namespace fapi
} // namespace ocudu
