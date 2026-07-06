// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_factory_sdr_impl.cpp
 * @brief Implementation of create_sdr_ru() — the core SDR Radio Unit construction function.
 *
 * This is the lowest-level construction function in the radio stack. It is
 * called from ru_sdr_factories.cpp (in apps/units/.../split_8/helpers/) and
 * performs the actual object construction:
 *
 *   1. Creates the ru_sdr_impl object (adapters, controller, metrics).
 *   2. Opens the radio session via the radio factory (selects UHD, ZMQ, etc.
 *      based on the device_driver string).
 *   3. Connects the radio session to ru_sdr_impl.
 *   4. Creates one lower_phy_sector per configured cell, wiring each one's
 *      dependencies (executors, notifiers, baseband gateway) from both the
 *      configuration and the already-constructed ru_sdr_impl.
 *   5. Hands the completed sector list to ru_sdr_impl.
 *
 * Note: only the first sector's timing notifier is wired to fire timing
 * events — in a multi-cell deployment, all cells are synchronised to the
 * same slot clock, so only one notification path is needed to drive the DU's
 * shared timer.
 */

#include "lower_phy/lower_phy_factory.h"
#include "ru_lower_phy_error_adapter.h"
#include "ru_radio_event_handler.h"
#include "ru_sdr_impl.h"
#include "ocudu/radio/radio_factory.h" ///< create_radio_factory() — selects UHD/ZMQ/etc. backend
#include "ocudu/ru/sdr/ru_sdr_configuration.h" ///< ru_sdr_configuration — internal config format
#include "ocudu/ru/sdr/ru_sdr_factory.h" ///< create_sdr_ru() declaration


using namespace ocudu;

/// Creates a radio session with the given parameters.

/**
 * @brief Opens and configures a radio session using the appropriate backend factory.
 *
 * The device_driver string ("uhd", "zmq", etc.) selects which radio_factory
 * implementation to instantiate. For this deployment, device_driver is "uhd",
 * so create_radio_factory("uhd") returns the UHD-backed factory that knows
 * how to open and configure a USRP device.
 *
 * Before creating the session, the configuration is validated by the
 * factory's own validator (e.g. checking that the requested sample rate and
 * gain values are within the USRP's hardware capabilities).
 *
 * @param executor       Thread executor for asynchronous (non-real-time) radio calls.
 * @param radio_handler   Receives radio hardware event notifications (errors, etc.).
 * @param config          Radio configuration: frequencies, gains, sample rate, device args.
 * @param device_driver   Backend selector string: "uhd" for USRP hardware.
 * @return The opened radio session, or nullptr if the factory or device could not be created.
 */
static std::unique_ptr<radio_session> create_radio_session(task_executor&                    executor,
                                                           radio_event_notifier&             radio_handler,
                                                           const radio_configuration::radio& config,
                                                           const std::string&                device_driver)
{
  // Print the list of compiled-in radio backends (for diagnostics in the log).
  print_available_radio_factories();


  // Instantiate the requested backend factory (UHD in this deployment).
  std::unique_ptr<radio_factory> factory = create_radio_factory(device_driver);
  if (!factory) {
    return nullptr;
  }


  // Validate the configuration against this backend's capabilities before
  // attempting to open the hardware — catches incompatible settings early
  // with a clear error rather than a cryptic UHD exception.
  if (!factory->get_configuration_validator().is_configuration_valid(config)) {
    report_error("Invalid radio configuration.");
  }


  // Open the radio session (for UHD: opens the USRP device, applies config).
  return factory->create(config, executor, radio_handler);
}


/**
 * @brief Constructs the complete SDR Radio Unit: ru_sdr_impl, radio session, and lower PHY sectors.
 *
 * This is the function called by create_sdr_radio_unit() (in the apps layer).
 * It performs the full two-phase construction described in ru_sdr_impl.h:
 *
 *   Phase 1: Construct ru_sdr_impl with its adapters and controller.
 *   Phase 2: Open the radio session and attach it via set_radio().
 *   Phase 3: Build one lower_phy_sector per cell and attach them via
 *            set_lower_phy_sectors().
 *
 * @param config        Internal SDR RU configuration (translated from the
 *                      user-facing YAML config by generate_ru_sdr_config()).
 * @param dependencies  Thread executors and notifier callback references.
 * @return The fully constructed radio unit (as a radio_unit interface pointer).
 */
std::unique_ptr<radio_unit> ocudu::create_sdr_ru(const ru_sdr_configuration& config,
                                                 const ru_sdr_dependencies&  dependencies)
{
  ru_sdr_impl_config ru_config = {.srate_MHz           = config.radio_cfg.sampling_rate_Hz * 1e-6,
  // ── Phase 1: Construct ru_sdr_impl ───────────────────────────────────────────
      // Internal config stores sample rate in Hz; ru_sdr_impl wants MHz.
                                  .start_time          = config.start_time,
                                  .are_metrics_enabled = config.are_metrics_enabled};

  ru_sdr_impl_dependencies ru_dependencies = {.rx_symbol_handler = dependencies.symbol_notifier,

                                              .timing_handler    = dependencies.timing_notifier,
      // The RU-level logger uses the first sector's logger (same logger
      // instance is shared across sectors in practice).
                                              .logger            = dependencies.sector_dependencies.front().logger,
                                              .radio_logger      = dependencies.rf_logger,
                                              .error_notifier    = dependencies.error_notifier};


  auto ru = std::make_unique<ru_sdr_impl>(ru_config, ru_dependencies);


  // ── Phase 2: Open the radio session ──────────────────────────────────────────
  // Uses ru->get_radio_event_notifier() so that radio hardware events (late
  // packets, overflows) are routed to the RU's combined event dispatcher
  // (which feeds both the metrics collector and the logger).
  auto radio = create_radio_session(
      dependencies.radio_exec, ru->get_radio_event_notifier(), config.radio_cfg, config.device_driver);
  report_error_if_not(radio, "Unable to create radio session.");


  ru->set_radio(std::move(radio));


  // ── Phase 3: Build the lower PHY sectors (one per cell) ──────────────────────
  std::vector<std::unique_ptr<lower_phy_sector>> phy_sectors;
  for (unsigned sector_id = 0, sector_end = config.lower_phy_config.size(); sector_id != sector_end; ++sector_id) {
    const lower_phy_configuration&    lower_phy_cfg  = config.lower_phy_config[sector_id];
    const ru_sdr_sector_dependencies& ru_sector_deps = dependencies.sector_dependencies[sector_id];


    lower_phy_sector_dependencies lophy_sector_deps = {
        .logger               = ru_sector_deps.logger,
        .rx_task_executor     = ru_sector_deps.rx_task_executor,
        .tx_task_executor     = ru_sector_deps.tx_task_executor,
        .dl_task_executor     = ru_sector_deps.dl_task_executor,
        .ul_task_executor     = ru_sector_deps.ul_task_executor,
        .prach_async_executor = ru_sector_deps.prach_async_executor,
        // All sectors share the same error notifier path.
        .error_notifier       = ru->get_error_notifier(),
        // Only the first sector is used to report timing events using the RU notifier.
        // Only the first sector (sector_id == 0) is wired to fire timing
        // notifications — since all cells share one synchronised slot clock,
        // only one notification path is needed to drive the DU's timer.
        // Other sectors get nullptr here (handled by a dummy notifier internally).
        .timing_notifier    = sector_id ? nullptr : &ru->get_timing_notifier(),
        // Each sector gets its own baseband gateway (its own USRP channel/antenna).
        .bb_gateway         = ru->get_baseband_gateway(sector_id),
        .rx_symbol_notifier = ru->get_rx_symbol_notifier()};


    phy_sectors.push_back(create_lower_phy_sector(lower_phy_cfg, lophy_sector_deps));
  }

  // Add lower PHY sector dependencies.

  // Hand the completed sector list to ru_sdr_impl, which wires its internal
  // handler/controller/metrics objects to point at each sector.
  ru->set_lower_phy_sectors(std::move(phy_sectors));


  return ru;
}
