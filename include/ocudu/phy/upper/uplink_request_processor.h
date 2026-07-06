// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/uplink_request_processor.h  (39 lines)
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


struct prach_buffer_context;
class resource_grid;
struct resource_grid_context;
class shared_resource_grid;

/// \brief Interface of the uplink request processor.
///
/// The uplink request processor is in charge of setting up the PHY block responsible for the execution of an uplink
/// request (e.g., PRACH detection or PUSCH decoding).

/// \brief Interface of the uplink request processor.
///
/// The uplink request processor is in charge of setting up the PHY block responsible for the execution of an uplink
/// request (e.g., PRACH detection or PUSCH decoding).
class uplink_request_processor
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplink_request_processor() = default;

  /// \brief Processes the PRACH request using the given configuration and context.
  ///
  /// The PRACH detection results will be notified by the \ref upper_phy_rx_results_notifier::on_new_prach_results
  /// "on_new_prach_results" event notification.
  ///
  /// \param[in] context Context used by the underlying PRACH detector.

  /// \brief Processes the PRACH request using the given configuration and context.
  ///
  /// The PRACH detection results will be notified by the \ref upper_phy_rx_results_notifier::on_new_prach_results
  /// "on_new_prach_results" event notification.
  ///
  /// \param[in] context Context used by the underlying PRACH detector.
  virtual void process_prach_request(const prach_buffer_context& context) = 0;

  /// \brief Processes the uplink request using the given context and grid.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid    Grid in which to store the captured data.

  /// \brief Processes the uplink request using the given context and grid.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid    Grid in which to store the captured data.
  virtual void process_uplink_slot_request(const resource_grid_context& context, const shared_resource_grid& grid) = 0;
};


} // namespace ocudu
