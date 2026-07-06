// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/ru_downlink_plane.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct resource_grid_context;
class shared_resource_grid;

/// \brief Radio Unit resource grid handler interface.
///
/// The resource grid handler modulates and transmits the given downlink resource grid through the underlying radio
/// device.

/// \brief Radio Unit resource grid handler interface.
///
/// The resource grid handler modulates and transmits the given downlink resource grid through the underlying radio
/// device.
class ru_downlink_plane_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ru_downlink_plane_handler() = default;

  /// \brief Handles the given downlink data to be transmitted.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid Downlink data to transmit.

  /// \brief Handles the given downlink data to be transmitted.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] grid Downlink data to transmit.
  virtual void handle_dl_data(const resource_grid_context& context, const shared_resource_grid& grid) = 0;
};


} // namespace ocudu
