// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/lower_phy_metrics_notifier.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct lower_phy_baseband_metrics;

/// Lower physical layer interface used to notify basebend measurements.

/// Lower physical layer interface used to notify basebend measurements.
class lower_phy_metrics_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_metrics_notifier() = default;

  /// \brief Notifies a new transmit symbol measurement.
  ///
  /// \param[in] metrics Measurements of the transmitted symbol.

  /// \brief Notifies a new transmit symbol measurement.
  ///
  /// \param[in] metrics Measurements of the transmitted symbol.
  virtual void on_new_transmit_metrics(const lower_phy_baseband_metrics& metrics) = 0;

  /// \brief Notifies a new receive symbol measurement.
  ///
  /// \param[in] metrics Measurements of the received symbol.

  /// \brief Notifies a new receive symbol measurement.
  ///
  /// \param[in] metrics Measurements of the received symbol.
  virtual void on_new_receive_metrics(const lower_phy_baseband_metrics& metrics) = 0;
};


} // namespace ocudu
