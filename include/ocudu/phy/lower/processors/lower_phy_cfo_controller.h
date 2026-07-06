// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/lower_phy_cfo_controller.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <chrono>


namespace ocudu {

/// Lower physical layer carrier frequency offset controller interface.

/// Lower physical layer carrier frequency offset controller interface.
class lower_phy_cfo_controller
{
public:
  /// Data type used for point in time.
  /// Data type used for point in time.
  using time_point = std::chrono::system_clock::time_point;

  /// Default destructor.

  /// Default destructor.
  virtual ~lower_phy_cfo_controller() = default;

  /// \brief Schedules a CFO command.
  /// \param time Time at which the CFO value is applied.
  /// \param cfo_Hz New CFO value in Hertz.
  /// \param cfo_drift_Hz_s New CFO drift value in Hertz per second.

  /// \brief Schedules a CFO command.
  /// \param time Time at which the CFO value is applied.
  /// \param cfo_Hz New CFO value in Hertz.
  /// \param cfo_drift_Hz_s New CFO drift value in Hertz per second.
  virtual bool schedule_cfo_command(time_point time, float cfo_Hz, float cfo_drift_Hz_s = 0) = 0;
};


} // namespace ocudu
