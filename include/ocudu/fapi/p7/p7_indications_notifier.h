// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/p7_indications_notifier.h  (50 lines)
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


struct crc_indication;
struct rach_indication;
struct rx_data_indication;
struct srs_indication;
struct uci_indication;

/// \brief Slot-based, data-specific message notifier interface.
///
/// This interface notifies the reception of slot-based, P7 FAPI indications from the underlying PHY.

/// \brief Slot-based, data-specific message notifier interface.
///
/// This interface notifies the reception of slot-based, P7 FAPI indications from the underlying PHY.
class p7_indications_notifier
{
public:
  virtual ~p7_indications_notifier() = default;

  /// \brief Notifies the reception of a RX data indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a RX data indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_rx_data_indication(const rx_data_indication& msg) = 0;

  /// \brief Notifies the reception of a CRC indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a CRC indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_crc_indication(const crc_indication& msg) = 0;

  /// \brief Notifies the reception of a UCI indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a UCI indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_uci_indication(const uci_indication& msg) = 0;

  /// \brief Notifies the reception of a SRS indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a SRS indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_srs_indication(const srs_indication& msg) = 0;

  /// \brief Notifies the reception of a RACH indication message.
  ///
  /// \param[in] msg Message contents.

  /// \brief Notifies the reception of a RACH indication message.
  ///
  /// \param[in] msg Message contents.
  virtual void on_rach_indication(const rach_indication& msg) = 0;
};


} // namespace fapi
} // namespace ocudu
