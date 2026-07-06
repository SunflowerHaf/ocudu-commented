// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/uplink_processor_notifier.h  (37 lines)
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
struct lower_phy_timing_context;

/// \brief Lower physical layer uplink processor - Notifier interface.
///
/// Notifies time boundary events.

/// \brief Lower physical layer uplink processor - Notifier interface.
///
/// Notifies time boundary events.
class uplink_processor_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplink_processor_notifier() = default;

  /// \brief Notifies that an uplink half slot has been received and processed by the lower PHY.
  ///
  /// See \ref lower_phy_timing_notifier::on_ul_half_slot_boundary for more information.
  /// \param[in] context Timing context.

  /// \brief Notifies that an uplink half slot has been received and processed by the lower PHY.
  ///
  /// See \ref lower_phy_timing_notifier::on_ul_half_slot_boundary for more information.
  /// \param[in] context Timing context.
  virtual void on_half_slot(const lower_phy_timing_context& context) = 0;

  /// \brief Notifies that an uplink full slot has been received and processed by the lower PHY.
  ///
  /// See \ref lower_phy_timing_notifier::on_ul_full_slot_boundary for more information.
  /// \param[in] context Timing context.

  /// \brief Notifies that an uplink full slot has been received and processed by the lower PHY.
  ///
  /// See \ref lower_phy_timing_notifier::on_ul_full_slot_boundary for more information.
  /// \param[in] context Timing context.
  virtual void on_full_slot(const lower_phy_timing_context& context) = 0;

  /// \brief Notifies a new measurement of uplink baseband metrics.

  /// \brief Notifies a new measurement of uplink baseband metrics.
  virtual void on_new_metrics(const lower_phy_baseband_metrics& metrics) = 0;
};


} // namespace ocudu
