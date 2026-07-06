// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_factory.cpp
 * @brief Builds the complete OFDM processing chain for one cell's lower PHY.
 *
 * This is where the actual signal processing pipeline is assembled. The
 * pipeline is built bottom-up from a chain of factories, each producing one
 * stage of the processing chain:
 *
 *   DFT factory                → FFT/IFFT implementation (FFTW if available,
 *                                otherwise a generic fallback implementation).
 *   OFDM modulator factory     → builds the IFFT-based downlink modulator,
 *                                wrapped in a pool factory so multiple symbol
 *                                modulations can run without reallocating buffers.
 *   OFDM demodulator factory   → builds the FFT-based uplink demodulator.
 *   PRACH demodulator factory  → builds the random-access preamble demodulator
 *                                (uses a different DFT size/window than data symbols).
 *   Amplitude controller       → clipping or scaling, depending on config
 *     factory                    (see ru_sdr_unit_config::amplitude_cfg).
 *   PDxCH processor factory    → combines the OFDM modulator and amplitude
 *                                controller into the downlink "Physical
 *                                Downlink shared/control Channel" processor.
 *   PRACH processor factory    → combines the PRACH demodulator with the
 *                                async executor for preamble detection.
 *   PUxCH processor factory    → combines the OFDM demodulator into the
 *                                uplink "Physical Uplink shared/control
 *                                Channel" processor.
 *   Downlink/uplink processor  → top-level processors combining all the
 *     factories                  above into the complete Tx/Rx chains.
 *
 * Finally, create_lower_phy_factory_sw() assembles everything into the
 * software lower PHY factory, which create_lower_phy_sector() uses to
 * instantiate the actual lower_phy object for this cell.
 */

#include "lower_phy_factory.h"


using namespace ocudu;


/**
 * @brief Builds the lower PHY factory: the complete chain of sub-factories
 *        needed to construct the OFDM processing engine for one cell.
 *
 * @param config                Per-cell lower PHY configuration.
 * @param prach_async_executor  Thread for asynchronous PRACH preamble detection.
 * @return The assembled lower PHY factory, or nullptr if any sub-factory failed
 *         to build (in which case report_fatal_error_if_not() has already
 *         terminated the process with a descriptive message).
 */
static std::shared_ptr<lower_phy_factory> create_lower_phy_factory(const lower_phy_configuration& config,
                                                                   task_executor&                 prach_async_executor)
{
  // Deduce frequency range from the subcarrier spacing.
  // Determine frequency range from subcarrier spacing: SCS > 60kHz implies
  // FR2 (mmWave); otherwise FR1 (sub-6GHz). This affects PRACH processing
  // parameters since FR2 uses different timing/window characteristics.
  frequency_range fr = frequency_range::FR1;
  if (config.scs > subcarrier_spacing::kHz60) {
    fr = frequency_range::FR2;
  }

  // Create DFT factory. It tries to create a FFTW based factory. If FFTW library is not available, it creates a generic
  // DFT factory.

  // Create the DFT (Fourier transform) factory. Prefers FFTW (a fast,
  // well-optimised FFT library) if available at compile time; falls back to
  // a generic (slower but dependency-free) implementation otherwise.
  std::shared_ptr<dft_processor_factory> dft_factory = create_dft_processor_factory_fftw_fast();
  if (dft_factory == nullptr) {
    dft_factory = create_dft_processor_factory_generic();
  }
  report_fatal_error_if_not(dft_factory, "Failed to create DFT factory.");

  // Create OFDM modulator factory.

  // Create the OFDM modulator factory (performs the IFFT for downlink).
  ofdm_factory_generic_configuration      ofdm_common_config = {.dft_factory = dft_factory};
  std::shared_ptr<ofdm_modulator_factory> modulator_factory = create_ofdm_modulator_factory_generic(ofdm_common_config);
  report_fatal_error_if_not(modulator_factory, "Failed to create OFDM modulator factory.");

  // Wrap the OFDM modulator factory with a pool factory.

  // Wrap the modulator factory in a pool factory: pre-allocates a pool of
  // modulator instances sized for the maximum number of OFDM symbols per
  // slot times the number of Tx antenna ports, avoiding per-symbol allocation.
  modulator_factory =
      create_ofdm_modulator_pool_factory(std::move(modulator_factory), MAX_NSYMB_PER_SLOT * config.nof_tx_ports);
  report_fatal_error_if_not(modulator_factory, "Failed to create OFDM modulator pool factory.");

  // Create OFDM demodulator factory.

  // Create the OFDM demodulator factory (performs the FFT for uplink).
  std::shared_ptr<ofdm_demodulator_factory> demodulator_factory =
      create_ofdm_demodulator_factory_generic(ofdm_common_config);
  report_fatal_error_if_not(demodulator_factory, "Failed to create OFDM demodulator factory.");

  // Create OFDM PRACH demodulator factory.

  // Create the PRACH demodulator factory — uses its own DFT instance sized
  // for the PRACH preamble's specific subcarrier spacing and duration,
  // distinct from the data-symbol OFDM demodulator above.
  std::shared_ptr<ofdm_prach_demodulator_factory> prach_demodulator_factory =
      create_ofdm_prach_demodulator_factory_sw(dft_factory, config.srate, fr);
  report_fatal_error_if_not(prach_demodulator_factory, "Failed to create PRACH demodulator factory.");

  // Create amplitude control factory.

  // Create the amplitude controller factory. Two modes are supported:
  //   clipping: hard-clips samples exceeding the power ceiling.
  //   scaling:  applies a fixed gain back-off, never exceeding the ceiling.
  // The choice is made in the YAML config (amplitude_cfg.enable_clipping).
  std::shared_ptr<amplitude_controller_factory> amplitude_control_factory;
  if (config.amplitude_config.enable_clipping) {
    amplitude_control_factory = create_amplitude_controller_clipping_factory(config.amplitude_config);
  } else {
    amplitude_control_factory = create_amplitude_controller_scaling_factory(config.amplitude_config.input_gain_dB);
  }
  report_fatal_error_if_not(amplitude_control_factory, "Failed to create amplitude controller factory.");

  // Create PDxCH processor factory.

  // PDxCH = Physical Downlink shared/Control CHannel processor. Combines the
  // OFDM modulator with the amplitude controller to produce the final
  // downlink IQ sample stream ready for the radio.
  std::shared_ptr<pdxch_processor_factory> pdxch_proc_factory =
      create_pdxch_processor_factory_sw(modulator_factory, amplitude_control_factory);
  report_fatal_error_if_not(pdxch_proc_factory, "Failed to create PDxCH processor factory.");

  // Create PRACH processor factory.

  // PRACH processor: ties the PRACH demodulator to its async executor and
  // configures the maximum number of simultaneous capture requests.
  std::shared_ptr<prach_processor_factory> prach_proc_factory =
      create_prach_processor_factory_sw(prach_demodulator_factory,
                                        prach_async_executor,
                                        config.srate,
                                        config.nof_rx_ports,
                                        config.max_nof_prach_concurrent_requests);
  report_fatal_error_if_not(prach_proc_factory, "Failed to create PRACH processor factory.");

  // Create PUxCH processor factory.

  // PUxCH = Physical Uplink shared/Control CHannel processor. Wraps the OFDM
  // demodulator for processing received uplink data symbols.
  std::shared_ptr<puxch_processor_factory> puxch_proc_factory = create_puxch_processor_factory_sw(demodulator_factory);
  report_fatal_error_if_not(puxch_proc_factory, "Failed to create PUxCH processor factory.");

  // Create Downlink processor factory.

  // Top-level downlink processor: combines PDxCH processing into the
  // complete downlink chain (resource grid in, IQ samples out).
  std::shared_ptr<lower_phy_downlink_processor_factory> downlink_proc_factory =
      create_downlink_processor_factory_sw(pdxch_proc_factory);
  report_fatal_error_if_not(downlink_proc_factory, "Failed to create downlink processor factory.");

  // Create Uplink processor factory.

  // Top-level uplink processor: combines PRACH and PUxCH processing into the
  // complete uplink chain (IQ samples in, resource grid + PRACH detections out).
  std::shared_ptr<lower_phy_uplink_processor_factory> uplink_proc_factory =
      create_uplink_processor_factory_sw(prach_proc_factory, puxch_proc_factory);
  report_fatal_error_if_not(uplink_proc_factory, "Failed to create uplink processor factory.");


  // Assemble the final lower PHY factory from the downlink and uplink processor factories.
  return create_lower_phy_factory_sw(downlink_proc_factory, uplink_proc_factory);
}


/**
 * @brief Constructs the complete lower_phy_sector for one cell.
 *
 * Builds the lower_phy_sector wrapper first (so its timing notifier and
 * metrics collector exist), then uses create_lower_phy_factory() to build
 * the full processing chain, and finally constructs the actual lower_phy
 * object using that chain — wiring it into the sector via set_lower_phy().
 *
 * @param lower_phy_config  Per-cell configuration: SCS, sample rate, antenna
 *                          counts, amplitude control, PRACH limits.
 * @param sector_deps       Thread executors and notifier references.
 * @return The fully constructed lower_phy_sector for this cell.
 */
std::unique_ptr<lower_phy_sector> ocudu::create_lower_phy_sector(const lower_phy_configuration&       lower_phy_config,
                                                                 const lower_phy_sector_dependencies& sector_deps)
{
  // Create the sector wrapper first — its timing_handler needs to exist
  // before we can pass a reference to it into lower_phy_dependencies below.
  auto sector = std::make_unique<lower_phy_sector>(sector_deps.timing_notifier);

  lower_phy_dependencies dependencies = {.logger               = sector_deps.logger,

  // Assemble the dependencies the lower PHY implementation itself needs,
  // pulling some from the sector (timing notifier, metrics collector) and
  // some directly from sector_deps (executors, gateways, error/rx notifiers).
                                         .bb_gateway           = sector_deps.bb_gateway,
                                         .rx_symbol_notifier   = sector_deps.rx_symbol_notifier,
                                         .timing_notifier      = sector->get_timing_notifier(), // The safe wrapper, not the raw pointer
                                         .error_notifier       = sector_deps.error_notifier,
                                         .metric_notifier      = sector->get_metrics_collector(),
                                         .rx_task_executor     = sector_deps.rx_task_executor,
                                         .tx_task_executor     = sector_deps.tx_task_executor,
                                         .dl_task_executor     = sector_deps.dl_task_executor,
                                         .ul_task_executor     = sector_deps.ul_task_executor,
                                         .prach_async_executor = sector_deps.prach_async_executor};

  // Create lower PHY factory.

  // Build the full chain of sub-factories described above.
  auto lphy_factory = create_lower_phy_factory(lower_phy_config, dependencies.prach_async_executor);
  report_error_if_not(lphy_factory, "Failed to create lower PHY factory.");

  // Create lower PHY.

  // Instantiate the actual lower PHY object using the assembled factory chain.
  auto phy = lphy_factory->create(lower_phy_config, dependencies);
  report_error_if_not(phy, "Unable to create lower PHY.");

  // Move PHY to the sector.

  // Wire the constructed lower PHY into the sector wrapper.
  sector->set_lower_phy(std::move(phy));


  return sector;
}
