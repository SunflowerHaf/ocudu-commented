// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/downlink/downlink_processor.h  (53 lines)
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


class downlink_processor_baseband;
class downlink_processor_notifier;
class lower_phy_center_freq_controller;
class lower_phy_cfo_controller;
class lower_phy_tx_time_offset_controller;
class pdxch_processor_notifier;
class pdxch_processor_request_handler;

/// \brief Downlink processor main interface.
///
/// Provides a single access point to all downlink-related interfaces, that is \ref downlink_processor_notifier,
/// \ref downlink_processor_request_handler and \ref downlink_processor_baseband.
///
/// \note All implementations of this interface must trigger an assertion error if the downlink processor is not
/// connected to a notifier before calling \ref get_downlink_request_handler() or \ref get_baseband().

/// \brief Downlink processor main interface.
///
/// Provides a single access point to all downlink-related interfaces, that is \ref downlink_processor_notifier,
/// \ref downlink_processor_request_handler and \ref downlink_processor_baseband.
///
/// \note All implementations of this interface must trigger an assertion error if the downlink processor is not
/// connected to a notifier before calling \ref get_downlink_request_handler() or \ref get_baseband().
class lower_phy_downlink_processor
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~lower_phy_downlink_processor() = default;

  /// Connects the downlink processor with notifiers.

  /// Connects the downlink processor with notifiers.
  virtual void connect(downlink_processor_notifier& notifier, pdxch_processor_notifier& pdxch_notifier) = 0;

  /// Stops the processor.

  /// Stops the processor.
  virtual void stop() = 0;

  /// Gets the carrier frequency offset controller interface.

  /// Gets the carrier frequency offset controller interface.
  virtual lower_phy_cfo_controller& get_cfo_control() = 0;

  /// Gets the carrier center frequency controller interface.

  /// Gets the carrier center frequency controller interface.
  virtual lower_phy_center_freq_controller& get_carrier_center_frequency_control() = 0;

  /// Gets the downlink processor request handler.

  /// Gets the downlink processor request handler.
  virtual pdxch_processor_request_handler& get_downlink_request_handler() = 0;

  /// Gets the transmit time offset controller interface.

  /// Gets the transmit time offset controller interface.
  virtual lower_phy_tx_time_offset_controller& get_tx_time_offset_control() = 0;

  /// \brief Gets the downlink processor baseband interface.
  /// \return A reference to the internal downlink processor baseband interface.

  /// \brief Gets the downlink processor baseband interface.
  /// \return A reference to the internal downlink processor baseband interface.
  virtual downlink_processor_baseband& get_baseband() = 0;
};


} // namespace ocudu
