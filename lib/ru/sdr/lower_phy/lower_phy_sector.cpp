// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_sector.cpp
 * @brief Pass-through implementation forwarding to the underlying lower PHY engine.
 *
 * Every method here simply delegates to the wrapped lower_phy object. The
 * sector class exists as a thin wrapper to add metrics collection and safe
 * timing notification (see lower_phy_sector.h), not to change the underlying
 * lower PHY behaviour itself.
 */

#include "lower_phy_sector.h"


using namespace ocudu;


/// Forwards to the underlying lower PHY's uplink request handler.
lower_phy_uplink_request_handler& lower_phy_sector::get_uplink_request_handler()
{
  return lower_phy->get_uplink_request_handler();
}


/// Forwards to the underlying lower PHY's downlink handler.
lower_phy_downlink_handler& lower_phy_sector::get_downlink_handler()
{
  return lower_phy->get_downlink_handler();
}


/// Forwards to the underlying lower PHY's start/stop controller.
lower_phy_controller& lower_phy_sector::get_controller()
{
  return lower_phy->get_controller();
}


/// Forwards to the underlying lower PHY's Tx CFO controller.
lower_phy_cfo_controller& lower_phy_sector::get_tx_cfo_control()
{
  return lower_phy->get_tx_cfo_control();
}


/// Forwards to the underlying lower PHY's Rx CFO controller.
lower_phy_cfo_controller& lower_phy_sector::get_rx_cfo_control()
{
  return lower_phy->get_rx_cfo_control();
}


/// Forwards to the underlying lower PHY's Tx centre frequency controller.
lower_phy_center_freq_controller& lower_phy_sector::get_tx_center_freq_control()
{
  return lower_phy->get_tx_center_freq_control();
}


/// Forwards to the underlying lower PHY's Rx centre frequency controller.
lower_phy_center_freq_controller& lower_phy_sector::get_rx_center_freq_control()
{
  return lower_phy->get_rx_center_freq_control();
}


/// Forwards to the underlying lower PHY's Tx timing offset controller.
lower_phy_tx_time_offset_controller& lower_phy_sector::get_tx_time_offset_control()
{
  return lower_phy->get_tx_time_offset_control();
}
