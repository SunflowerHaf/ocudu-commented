// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/lower_phy_controller.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gateways/baseband/baseband_gateway_timestamp.h"


namespace ocudu {

/// \brief Lower physical layer - control interface.
///
/// Provides a start and stop methods.
///
/// \remark The methods \c start() and \c stop() must be called in order and only once; other uses will result in
/// undefined behavior.

/// \brief Lower physical layer - control interface.
///
/// Provides a start and stop methods.
///
/// \remark The methods \c start() and \c stop() must be called in order and only once; other uses will result in
/// undefined behavior.
class lower_phy_controller
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_controller() = default;

  /// \brief Starts the lower physical layer operation.
  ///
  /// The fist uplink processing block is expected at \c init_time and the first downlink processing block transmission
  /// will be relative to this time.
  ///
  /// \param[in] init_time     Initial time in clock ticks.
  /// \param[in] sfn0_ref_time System Frame Number (SFN) zero reference time.

  /// \brief Starts the lower physical layer operation.
  ///
  /// The fist uplink processing block is expected at \c init_time and the first downlink processing block transmission
  /// will be relative to this time.
  ///
  /// \param[in] init_time     Initial time in clock ticks.
  /// \param[in] sfn0_ref_time System Frame Number (SFN) zero reference time.
  virtual void start(baseband_gateway_timestamp init_time, baseband_gateway_timestamp sfn0_ref_time = 0) = 0;

  /// \brief Stops the lower physical layer operation.
  ///
  /// Waits for all asynchronous processes to be over before returning.

  /// \brief Stops the lower physical layer operation.
  ///
  /// Waits for all asynchronous processes to be over before returning.
  virtual void stop() = 0;
};


} // namespace ocudu
