// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_factory.h
 * @brief Declarations for building one cell's lower_phy_sector and its dependencies.
 *
 * The lower PHY processing chain is built from several smaller factories
 * (DFT, OFDM modulator, OFDM demodulator, PRACH demodulator, amplitude
 * controller, downlink/uplink processors). This file declares the
 * dependencies struct that bundles the executors and notifiers a single
 * sector needs, plus the function that assembles everything into a complete
 * lower_phy_sector for one cell.
 */

#pragma once


#include "lower_phy_sector.h"
#include "ocudu/phy/lower/lower_phy_factory.h" ///< lower_phy_factory and lower_phy_dependencies (internal building blocks)
#include <memory>


namespace ocudu {


struct lower_phy_configuration; ///< Per-cell config: SCS, bandwidth, antenna counts, sample rate

/// Lower phy sector dependencies.

/**
 * @brief External dependencies needed to construct one cell's lower PHY sector.
 *
 * These come from the thread executor mapper (ru_sdr_executor_mapper) and
 * the already-constructed ru_sdr_impl notifiers (error, timing, rx symbol).
 */
struct lower_phy_sector_dependencies {
  /// Logger for this cell's lower PHY messages.
  ocudulog::basic_logger&       logger;
  /// Dedicated thread for processing received IQ samples from the radio.
  task_executor&                rx_task_executor;
  /// Dedicated thread for sending IQ samples to the radio.
  task_executor&                tx_task_executor;
  /// Dedicated (or shared) thread for downlink OFDM modulation tasks.
  task_executor&                dl_task_executor;
  /// Dedicated (or shared/inline) thread for uplink OFDM demodulation tasks.
  task_executor&                ul_task_executor;
  /// Thread for asynchronous PRACH preamble detection.
  task_executor&                prach_async_executor;
  /// Receives real-time failure notifications (late data, overflows).
  lower_phy_error_notifier&     error_notifier;
  /// Receives slot timing notifications. Nullptr for sectors other than the
  /// first (only one sector drives the shared DU timer).
  lower_phy_timing_notifier*    timing_notifier;
  /// The baseband gateway: where this sector's IQ samples are sent/received
  /// to/from the radio hardware.
  baseband_gateway&             bb_gateway;
  /// Receives demodulated uplink symbol notifications.
  lower_phy_rx_symbol_notifier& rx_symbol_notifier;
};

/// Helper class that creates the lower PHY sector using the given configuration.

/**
 * @brief Constructs a complete lower_phy_sector for one cell.
 *
 * Internally builds the chain of sub-factories (DFT, OFDM modulator/demodulator,
 * PRACH demodulator, amplitude controller, downlink/uplink processors),
 * assembles the lower_phy implementation, and wraps it in a lower_phy_sector.
 *
 * @param lower_phy_config  Per-cell configuration: SCS, sample rate, antenna
 *                          counts, amplitude control settings, etc.
 * @param sector_deps       Thread executors and notifier callback references.
 * @return The fully constructed lower_phy_sector for this cell.
 */
std::unique_ptr<lower_phy_sector> create_lower_phy_sector(const lower_phy_configuration&       lower_phy_config,
                                                          const lower_phy_sector_dependencies& sector_deps);


} // namespace ocudu
