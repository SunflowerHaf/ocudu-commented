// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_sdr_ntn_doppler_compensation_handler_impl.cpp
 * @brief Implementation of NTN Doppler compensation request handling.
 */

#include "ru_sdr_ntn_doppler_compensation_handler_impl.h"
#include "fmt/chrono.h" ///< Enables {:%T} time formatting in log messages


using namespace ocudu;


/**
 * @brief Constructor. Fetches the "RU" logger for Doppler compensation messages.
 *
 * @param ru_ctrl_  The Radio Unit controller this handler will issue commands through.
 */
ru_sdr_ntn_doppler_compensation_handler_impl::ru_sdr_ntn_doppler_compensation_handler_impl(ru_controller& ru_ctrl_) :
  logger(ocudulog::fetch_basic_logger("RU")), ru_ctrl(ru_ctrl_)
{
}


/**
 * @brief Applies a downlink Doppler compensation request to the Tx CFO controller.
 *
 * @param request  Contains the sector ID, frequency offset (Hz), drift rate
 *                 (Hz/s), and the time at which compensation should begin.
 * @return true if applied; false if no CFO controller is available.
 */
bool ru_sdr_ntn_doppler_compensation_handler_impl::handle_dl_doppler_compensation(
    const ocudu_ntn::doppler_compensation_request& request)
{
  // Not all radio backends support CFO compensation — check before proceeding.
  if (not ru_ctrl.get_cfo_controller()) {
    logger.warning("NTN: CFO controller not available, cannot apply DL Doppler compensation");
    return false;
  }


  // Translate from the NTN-specific request type to the generic CFO request type.
  cfo_compensation_request cfo_reqs;
  cfo_reqs.cfo_hz          = request.cfo_hz;
  cfo_reqs.cfo_drift_hz_s  = request.cfo_drift_hz_s;
  cfo_reqs.start_timestamp = request.start_timestamp;

  // Apply the pre-calculated DL Doppler compensation values to TX.

  // Apply the compensation to the Tx (downlink) path for the given sector.
  ru_ctrl.get_cfo_controller()->set_tx_cfo(request.sector_id, cfo_reqs);


  logger.debug("NTN: Apply DL Doppler compensation: {:.1f} Hz (drift: {:.1f} Hz/s) at {:%T}",
               cfo_reqs.cfo_hz,
               cfo_reqs.cfo_drift_hz_s,
               cfo_reqs.start_timestamp.value());


  return true;
}


/**
 * @brief Applies an uplink Doppler compensation request to the Rx CFO controller.
 *
 * @param request  Contains the sector ID, frequency offset (Hz), drift rate
 *                 (Hz/s), and the time at which compensation should begin.
 * @return true if applied; false if no CFO controller is available.
 */
bool ru_sdr_ntn_doppler_compensation_handler_impl::handle_ul_doppler_compensation(
    const ocudu_ntn::doppler_compensation_request& request)
{
  if (not ru_ctrl.get_cfo_controller()) {
    logger.warning("NTN: CFO controller not available, cannot apply UL Doppler compensation");
    return false;
  }


  cfo_compensation_request cfo_reqs;
  cfo_reqs.cfo_hz          = request.cfo_hz;
  cfo_reqs.cfo_drift_hz_s  = request.cfo_drift_hz_s;
  cfo_reqs.start_timestamp = request.start_timestamp;

  // Apply the pre-calculated UL Doppler compensation values to RX.

  // Apply the compensation to the Rx (uplink) path for the given sector.
  ru_ctrl.get_cfo_controller()->set_rx_cfo(request.sector_id, cfo_reqs);


  logger.debug("NTN: Apply UL Doppler compensation: {:.1f} Hz (drift: {:.1f} Hz/s) at {:%T}",
               cfo_reqs.cfo_hz,
               cfo_reqs.cfo_drift_hz_s,
               cfo_reqs.start_timestamp.value());


  return true;
}
