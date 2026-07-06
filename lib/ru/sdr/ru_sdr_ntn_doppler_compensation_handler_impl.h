// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_sdr_ntn_doppler_compensation_handler_impl.h
 * @brief Applies pre-calculated NTN Doppler compensation requests to the radio's CFO controller.
 *
 * The NTN configuration manager (running on a periodic timer) calculates the
 * required frequency offset and drift rate to compensate for satellite
 * Doppler shift, then calls this handler to actually apply the values to the
 * radio. This class is the bridge between the high-level NTN logic
 * (ephemeris tracking, propagation delay calculation) and the low-level
 * CFO controller that issues the actual compensation commands.
 *
 * Separate handlers exist for downlink (Tx CFO) and uplink (Rx CFO) since
 * the Doppler shift differs slightly between transmit and receive paths
 * (frequency-dependent and direction-dependent effects).
 *
 * Not used in standard terrestrial deployments — only invoked when at least
 * one cell has NTN configuration.
 */

#pragma once


#include "ocudu/ntn/ntn_doppler_compensation_handler.h" ///< Base interface this class implements
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/ru/ru_controller.h" ///< ru_controller — provides access to the CFO controller


namespace ocudu {

/// RU-side implementation of NTN Doppler compensation handler.
/// This class handles NTN Doppler compensation requests by applying them to the RU controller.

/**
 * @brief Applies NTN Doppler compensation requests via the RU's CFO controller.
 */
class ru_sdr_ntn_doppler_compensation_handler_impl : public ocudu_ntn::ntn_doppler_compensation_handler
{
public:
  /**
   * @param ru_ctrl  The Radio Unit controller, used to access the CFO controller.
   */
  explicit ru_sdr_ntn_doppler_compensation_handler_impl(ru_controller& ru_ctrl);

  /// \brief Handle DL Doppler compensation request.
  ///
  /// \param dl_request Pre-calculated DL Doppler compensation request containing time, frequency, and drift values.
  /// \return True if the request was successfully handled; false otherwise.

  /**
   * @brief Applies a downlink Doppler compensation request.
   *
   * Forwards the request to the CFO controller's set_tx_cfo() method.
   * Fails gracefully (returns false with a warning log) if the radio unit
   * does not provide a CFO controller — some radio backends may not support
   * frequency offset compensation.
   *
   * @param dl_request  Pre-calculated frequency offset, drift rate, and start time.
   * @return true if successfully applied; false if the CFO controller is unavailable.
   */
  bool handle_dl_doppler_compensation(const ocudu_ntn::doppler_compensation_request& dl_request) override;

  /// \brief Handle UL Doppler compensation request.
  ///
  /// \param ul_request Pre-calculated UL Doppler compensation request containing time, frequency, and drift values.
  /// \return True if the request was successfully handled; false otherwise.

  /**
   * @brief Applies an uplink Doppler compensation request.
   *
   * Forwards the request to the CFO controller's set_rx_cfo() method.
   *
   * @param ul_request  Pre-calculated frequency offset, drift rate, and start time.
   * @return true if successfully applied; false if the CFO controller is unavailable.
   */
  bool handle_ul_doppler_compensation(const ocudu_ntn::doppler_compensation_request& ul_request) override;


private:
  /// Logger for NTN Doppler compensation events and warnings.
  ocudulog::basic_logger& logger;
  /// The Radio Unit controller — provides access to the CFO controller.
  ru_controller&          ru_ctrl;
};


} // namespace ocudu
