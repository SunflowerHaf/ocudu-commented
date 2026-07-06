// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_controller_sdr_impl.cpp
 * @brief Implementation of the SDR Radio Unit's start/stop and runtime control logic.
 *
 * The most important function here is start(), which computes the precise
 * timestamp at which the radio and lower PHY should begin operating, ensuring
 * all sectors and the radio hardware are synchronised to a common slot boundary.
 */

#include "ru_controller_sdr_impl.h"
#include "lower_phy/lower_phy_sector.h"
#include "ocudu/gateways/baseband/baseband_gateway_receiver.h"
#include "ocudu/gateways/baseband/baseband_gateway_transmitter.h"
#include "ocudu/gateways/baseband/baseband_gateway_transmitter_metadata.h"
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_reader.h"
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_writer.h"
#include "ocudu/phy/lower/lower_phy_controller.h"
#include "ocudu/phy/lower/processors/lower_phy_center_freq_controller.h"
#include "ocudu/phy/lower/processors/lower_phy_cfo_controller.h"
#include "ocudu/phy/lower/processors/lower_phy_tx_time_offset_controller.h"
#include "ocudu/radio/radio_session.h"
#include "ocudu/support/math/math_utils.h" ///< divide_ceil()
#include <thread>


using namespace ocudu;


/**
 * @brief Constructor. Stores sample rate and optional start time for later use in start().
 */
ru_controller_sdr_impl::ru_controller_sdr_impl(double                                               srate_MHz_,
                                               std::optional<std::chrono::system_clock::time_point> start_time_) :
  srate_MHz(srate_MHz_), start_time(start_time_)
{
}


/**
 * @brief Starts the radio and all lower PHY sectors at a synchronised timestamp.
 *
 * There are two start modes:
 *
 *   1. SYNCHRONISED START (start_time has a value):
 *      Used when multiple OCUDU instances need to begin transmitting at exactly
 *      the same wall-clock moment (e.g. for coordinated multi-cell testing).
 *      The function sleeps until the configured start_time, then computes a
 *      precise radio timestamp aligned to the next 1PPS (one-pulse-per-second)
 *      rising edge — this requires the USRP to have a GPS or external clock
 *      reference for the 1PPS signal to be meaningful. Streaming begins 10ms
 *      before the 1PPS edge so the system has time to "warm up" before the
 *      aligned boundary arrives. The SFN (System Frame Number) zero reference
 *      time is also computed here, ensuring frame numbering is synchronised
 *      across all cells/instances.
 *
 *   2. SIMPLE START (no start_time configured — the normal case):
 *      Starts 100ms from the current radio time, rounded up to the next
 *      subframe boundary. This is simpler and sufficient for single-instance
 *      deployments where exact wall-clock synchronisation isn't required.
 *
 * In both cases, the radio is started first, then each lower PHY sector's
 * controller is started at the same timestamp — ensuring the lower PHY's
 * internal slot counter and the radio's actual sample stream begin in lockstep.
 */
void ru_controller_sdr_impl::start()
{
  ocudu_assert(radio, "Null radio");
  ocudu_assert(!lower_phy_sectors.empty(), "Empty list of lower phy sectors");

  // Start streaming at the given time.

  // ── Synchronised start mode ──────────────────────────────────────────────────
  if (start_time.has_value()) {
    // Sleep until the start time.
    // Block until the configured wall-clock start time arrives.
    std::this_thread::sleep_until(*start_time);

    // Get current radio timestamp.

    // Read the radio's current internal sample counter (timestamp).
    baseband_gateway_timestamp current_radio_ts = radio->read_current_time();

    // Calculate some constants that depend on the sampling rate.

    // Compute timing constants from the sample rate.
    uint64_t nof_ticks_per_second  = static_cast<uint64_t>(srate_MHz * 1e6);
    uint64_t nof_ticks_subframe    = nof_ticks_per_second / 1000; // 1ms subframe
    // A "super-frame" here spans all radio frames until SFN wraps around
    // (NOF_SFNS distinct SFN values, each NOF_SUBFRAMES_PER_FRAME subframes long).
    uint64_t nof_ticks_super_frame = NOF_SUBFRAMES_PER_FRAME * NOF_SFNS * nof_ticks_subframe;
    // Start streaming 10ms (in radio sample ticks) before the 1PPS edge.
    uint64_t start_advance_10ms    = nof_ticks_per_second / 100;

    // Round time to the next 1PPS rising-edge.

    // Round the current radio time up to the next exact 1-second boundary
    // (the next 1PPS rising edge, assuming the radio is referenced to GPS/external clock).
    baseband_gateway_timestamp time_next_pps =
        divide_ceil(current_radio_ts, nof_ticks_per_second) * nof_ticks_per_second;

    // Calculate the SFN0 reference time for matching the SFN0 to the 1PPS rising edge.

    // Compute the SFN=0 reference time: where in the super-frame cycle does
    // the next 1PPS edge fall? This anchors frame numbering to the 1PPS signal.
    baseband_gateway_timestamp sfn0_ref_time = time_next_pps % nof_ticks_super_frame;

    // Start streaming 10-ms before the 1PPS rising edge.

    // Actual streaming start time: 10ms before the 1PPS edge, giving the
    // system time to stabilise before the synchronisation point arrives.
    baseband_gateway_timestamp time_start = time_next_pps - start_advance_10ms;

    // Start radio and lower physical layer at the given timestamp.

    // Start the radio and every lower PHY sector at the same timestamp.
    radio->start(time_start);
    for (auto& sector : lower_phy_sectors) {
      sector->get_controller().start(time_start, sfn0_ref_time);
    }


    return;
  }

  // Calculate starting time from the radio current time plus one hundred milliseconds.

  // ── Simple start mode (default — no synchronised start time configured) ──────
  // Start 100ms from now, rounded up to the next subframe boundary.
  double                     delay_s      = 0.1; // 100ms
  baseband_gateway_timestamp current_time = radio->read_current_time();
  baseband_gateway_timestamp start_ts     = current_time + static_cast<uint64_t>(delay_s * srate_MHz * 1e6);

  // Round start time to the next subframe.

  // Round the start timestamp up to the next 1ms subframe boundary.
  uint64_t sf_duration = static_cast<uint64_t>(srate_MHz * 1e3);
  start_ts             = divide_ceil(start_ts, sf_duration) * sf_duration;

  // Start radio and lower physical layer at the given timestamp.

  // Start the radio and every lower PHY sector at the computed timestamp.
  radio->start(start_ts);
  for (auto& sector : lower_phy_sectors) {
    sector->get_controller().start(start_ts);
  }
}


/**
 * @brief Stops the radio and all lower PHY sectors.
 *
 * The radio is stopped first to halt IQ streaming, then each lower PHY
 * sector's controller is stopped to cease processing.
 */
void ru_controller_sdr_impl::stop()
{
  radio->stop();


  for (auto& sector : lower_phy_sectors) {
    sector->get_controller().stop();
  }
}


/**
 * @brief Constructs the four sub-controllers from the lower PHY sector list.
 *
 * Called once after all lower PHY sectors have been built. Builds new
 * instances of each sub-controller, passing the appropriate sector pointers
 * and/or radio pointer.
 *
 * @param sectors  The lower PHY sectors, one per configured cell.
 */
void ru_controller_sdr_impl::set_lower_phy_sectors(std::vector<lower_phy_sector*> sectors)
{
  ocudu_assert(!sectors.empty(), "Could not set empty sectors");


  lower_phy_sectors = std::move(sectors);


  // Gain controller only needs access to the radio (UHD gain calls).
  gain_controller           = ru_gain_controller_sdr_impl(&radio);
  // CFO controller acts on the lower PHY sectors directly.
  cfo_controller            = ru_cfo_controller_sdr_impl(lower_phy_sectors);
  // Centre frequency controller needs both the radio (for the LO) and the
  // lower PHY sectors (for CFO/Doppler tracking reference).
  center_freq_controller    = ru_center_frequency_controller_sdr_impl(lower_phy_sectors, &radio);
  // Tx timing offset controller acts on the lower PHY sectors directly.
  tx_time_offset_controller = ru_tx_time_offset_controller_sdr_impl(lower_phy_sectors);
}


/**
 * @brief Sets the transmit gain on the USRP via the radio's management plane.
 */
bool ru_gain_controller_sdr_impl::set_tx_gain(unsigned port_id, double gain_dB)
{
  return (*radio)->get_management_plane().set_tx_gain(port_id, gain_dB);
}


/**
 * @brief Sets the receive gain on the USRP via the radio's management plane.
 */
bool ru_gain_controller_sdr_impl::set_rx_gain(unsigned port_id, double gain_dB)
{
  return (*radio)->get_management_plane().set_rx_gain(port_id, gain_dB);
}


/**
 * @brief Schedules a Tx CFO compensation command on the given sector.
 *
 * If no explicit start_timestamp was provided in the request, defaults to
 * "now" (std::chrono::system_clock::now()).
 */
bool ru_cfo_controller_sdr_impl::set_tx_cfo(unsigned sector_id, const cfo_compensation_request& cfo_request)
{
  if (sector_id < phy_sectors.size()) {
    return phy_sectors[sector_id]->get_tx_cfo_control().schedule_cfo_command(
        cfo_request.start_timestamp.value_or(std::chrono::system_clock::now()),
        cfo_request.cfo_hz,
        cfo_request.cfo_drift_hz_s);
  }
  return false;
}


/**
 * @brief Schedules an Rx CFO compensation command on the given sector.
 */
bool ru_cfo_controller_sdr_impl::set_rx_cfo(unsigned sector_id, const cfo_compensation_request& cfo_request)
{
  if (sector_id < phy_sectors.size()) {
    return phy_sectors[sector_id]->get_rx_cfo_control().schedule_cfo_command(
        cfo_request.start_timestamp.value_or(std::chrono::system_clock::now()),
        cfo_request.cfo_hz,
        cfo_request.cfo_drift_hz_s);
  }
  return false;
}


/**
 * @brief Sets the downlink centre frequency on both the radio hardware and the lower PHY.
 *
 * Note: the radio frequency change is always attempted, but the lower PHY
 * update (and thus the function's return value) only succeeds if sector_id
 * is valid.
 */
bool ru_center_frequency_controller_sdr_impl::set_tx_center_frequency(unsigned sector_id, double center_freq_Hz)
{
  (*radio)->get_management_plane().set_tx_freq(sector_id, center_freq_Hz);
  if (sector_id < phy_sectors.size()) {
    return phy_sectors[sector_id]->get_tx_center_freq_control().set_carrier_center_frequency(center_freq_Hz);
  }
  return false;
}


/**
 * @brief Sets the uplink centre frequency on both the radio hardware and the lower PHY.
 */
bool ru_center_frequency_controller_sdr_impl::set_rx_center_frequency(unsigned sector_id, double center_freq_Hz)
{
  (*radio)->get_management_plane().set_rx_freq(sector_id, center_freq_Hz);
  if (sector_id < phy_sectors.size()) {
    return phy_sectors[sector_id]->get_rx_center_freq_control().set_carrier_center_frequency(center_freq_Hz);
  }
  return false;
}


/**
 * @brief Sets the Tx timing offset on the given sector's lower PHY.
 */
bool ru_tx_time_offset_controller_sdr_impl::set_tx_time_offset(unsigned sector_id, phy_time_unit tx_time_offset)
{
  if (sector_id < phy_sectors.size()) {
    phy_sectors[sector_id]->get_tx_time_offset_control().set_tx_time_offset(tx_time_offset);
    return true;
  }
  return false;
}
