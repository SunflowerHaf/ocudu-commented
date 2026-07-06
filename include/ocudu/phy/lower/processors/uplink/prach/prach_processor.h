// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/prach/prach_processor.h  (41 lines)
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


class prach_processor_baseband;
class prach_processor_notifier;
class prach_processor_request_handler;

/// \brief PRACH processor main interface.
///
/// Provides a single access point to all PRACH-related interfaces, that is \ref prach_processor_notifier,
/// \ref prach_processor_request_handler and \ref prach_processor_baseband.
///
/// \note All implementations of this interface must trigger an assertion error if the PRACH processor is not connected
/// to a notifier before calling \ref get_request_handler() or \ref get_baseband().

/// \brief PRACH processor main interface.
///
/// Provides a single access point to all PRACH-related interfaces, that is \ref prach_processor_notifier,
/// \ref prach_processor_request_handler and \ref prach_processor_baseband.
///
/// \note All implementations of this interface must trigger an assertion error if the PRACH processor is not connected
/// to a notifier before calling \ref get_request_handler() or \ref get_baseband().
class prach_processor
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~prach_processor() = default;

  /// Connects the PRACH processor with a notifier.

  /// Connects the PRACH processor with a notifier.
  virtual void connect(prach_processor_notifier& notifier) = 0;

  /// Stops the processor.

  /// Stops the processor.
  virtual void stop() = 0;

  /// \brief Gets the PRACH processor request handler.
  /// \return A reference to the internal PRACH processor request handler.

  /// \brief Gets the PRACH processor request handler.
  /// \return A reference to the internal PRACH processor request handler.
  virtual prach_processor_request_handler& get_request_handler() = 0;

  /// \brief Gets the PRACH processor baseband interface.
  /// \return A reference to the internal PRACH processor baseband interface.

  /// \brief Gets the PRACH processor baseband interface.
  /// \return A reference to the internal PRACH processor baseband interface.
  virtual prach_processor_baseband& get_baseband() = 0;
};


} // namespace ocudu
