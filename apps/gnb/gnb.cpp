// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb.cpp
 * @brief Application entry point for the OCUDU co-located 5G gNB.
 *
 * This file contains main() and all the top-level startup/shutdown logic for
 * the gNB application. It is responsible for:
 *
 *   1. Parsing the YAML configuration file supplied on the command line.
 *   2. Validating all configuration values before anything is constructed.
 *   3. Initialising supporting services (logging, tracing, buffer pool, timers,
 *      IO broker, worker threads, metrics).
 *   4. Constructing the three protocol stack units: O-CU-CP, O-CU-UP, O-DU.
 *   5. Wiring them together via local (in-process) F1-C, F1-U, and E1 connectors.
 *   6. Starting each unit in the correct order and running the main event loop.
 *   7. Performing a clean, ordered shutdown when the application is interrupted.
 *
 * In this co-located deployment the CU and DU run in the same process. There
 * is no real SCTP connection between them — they communicate via in-memory
 * connectors. However, the N2 (CU-CP to AMF) and N3 (CU-UP to UPF) interfaces
 * go over the real network using standard SCTP/UDP ports.
 */

// ─── Standard library ────────────────────────────────────────────────────────

// ─── Application-level helpers ───────────────────────────────────────────────
#include "apps/helpers/e2/e2_config_translators.h" ///< Translates E2 config for monitoring interface
#include "apps/helpers/metrics/metrics_helpers.h" ///< Shared metrics utility functions
#include "apps/helpers/network/sctp_config_translators.h" ///< Translates SCTP socket config for XN-C gateways

// ─── Application services ────────────────────────────────────────────────────
#include "apps/services/app_execution_metrics/executor_metrics_manager.h" ///< Collects per-thread performance metrics
#include "apps/services/app_resource_usage/app_resource_usage.h" ///< Monitors OS-level CPU/memory usage
#include "apps/services/application_message_banners.h" ///< Prints startup/shutdown banners to log
#include "apps/services/application_tracer.h" ///< Records internal events to a trace file
#include "apps/services/buffer_pool/buffer_pool_manager.h" ///< Manages pre-allocated packet memory buffers
#include "apps/services/cmdline/cmdline_command_dispatcher.h" ///< Dispatches commands typed at the console
#include "apps/services/cmdline/stdout_metrics_command.h" ///< "metrics" console command implementation
#include "apps/services/metrics/metrics_manager.h" ///< Central metrics aggregation and reporting service
#include "apps/services/metrics/metrics_notifier_proxy.h" ///< Proxy that forwards metrics to the manager
#include "apps/services/remote_control/remote_server.h" ///< Optional external remote-control server
#include "apps/services/worker_manager/worker_manager.h" ///< Creates and manages all CPU worker threads

// ─── Application units (CU and DU) ──────────────────────────────────────────
#include "apps/units/flexible_o_du/flexible_o_du_application_unit.h" ///< Factory that creates the O-DU unit
#include "apps/units/flexible_o_du/o_du_high/du_high/du_high_config.h" ///< DU High configuration struct
#include "apps/units/flexible_o_du/o_du_high/o_du_high_unit_pcap_factory.h" ///< Creates PCAP (packet capture) files for DU
#include "apps/units/o_cu_cp/o_cu_cp_application_unit.h" ///< Factory that creates the O-CU-CP unit
#include "apps/units/o_cu_cp/o_cu_cp_unit_config.h" ///< CU-CP configuration struct
#include "apps/units/o_cu_cp/pcap_factory.h" ///< Creates PCAP files for CU-CP interfaces
#include "apps/units/o_cu_up/o_cu_up_application_unit.h" ///< Factory that creates the O-CU-UP unit
#include "apps/units/o_cu_up/o_cu_up_unit_config.h" ///< CU-UP configuration struct
#include "apps/units/o_cu_up/pcap_factory.h" ///< Creates PCAP files for CU-UP interfaces

// ─── gNB application config ──────────────────────────────────────────────────
#include "gnb_appconfig.h" ///< Top-level config struct (gnb_appconfig)
#include "gnb_appconfig_cli11_schema.h" ///< Registers config fields with the YAML/CLI parser
#include "gnb_appconfig_translators.h" ///< Converts app config to subsystem-specific configs
#include "gnb_appconfig_validators.h" ///< Validates the parsed config before use
#include "gnb_appconfig_yaml_writer.h" ///< Serialises config back to YAML for debug logging

// ─── Core OCUDU support library ──────────────────────────────────────────────
#include "ocudu/adt/scope_exit.h" ///< make_scope_exit(): runs code when leaving scope
#include "ocudu/cu_cp/cu_cp_operation_controller.h" ///< Start/stop interface for CU-CP
#include "ocudu/du/du_high/du_high_clock_controller.h" ///< Creates the DU timing source from PHY slot ticks
#include "ocudu/du/du_operation_controller.h" ///< Start/stop interface for DU
#include "ocudu/e1ap/gateways/e1_local_connector_factory.h" ///< Creates the in-process E1 link (CU-CP ↔ CU-UP)
#include "ocudu/e2/gateways/e2_network_client_factory.h" ///< Creates the E2 monitoring interface client
#include "ocudu/f1ap/gateways/f1c_local_connector_factory.h" ///< Creates the in-process F1-C link (CU-CP ↔ DU)
#include "ocudu/f1u/local_connector/f1u_local_connector.h" ///< Creates the in-process F1-U link (CU-UP ↔ DU)
#include "ocudu/gtpu/gtpu_teid_pool_factory.h" ///< Allocates GTP-U tunnel identifiers
#include "ocudu/ngap/gateways/n2_connection_client_factory.h" ///< (included transitively via cu_cp unit)
#include "ocudu/support/backtrace.h" ///< Enables printing a stack trace on crash
#include "ocudu/support/config_parsers.h" ///< create_yaml_config_parser() — parses YAML files
#include "ocudu/support/cpu_features.h" ///< Checks CPU instruction set at runtime
#include "ocudu/support/io/io_broker_factory.h" ///< Creates the epoll I/O event loop
#include "ocudu/support/signal_handling.h" ///< Registers OS signal handlers (SIGINT, SIGTERM)
#include "ocudu/support/signal_observer.h" ///< signal_dispatcher: notifies multiple handlers
#include "ocudu/support/sysinfo.h" ///< Checks CPU governor and kernel settings
#include "ocudu/support/versioning/build_info.h" ///< get_build_hash(): git hash of this build
#include "ocudu/support/versioning/version.h" ///< get_version(): human-readable version string
#include "ocudu/xnap/gateways/xnc_network_gateway_factory.h" ///< Creates XN-C gateways (inter-gNB interface)
#include <algorithm>
#include <atomic>

// ─── Optional DPDK support ───────────────────────────────────────────────────
#ifdef DPDK_FOUND
/// DPDK (Data Plane Development Kit) provides kernel-bypass networking for
/// very low-latency ethernet. Only compiled in when DPDK is available.
#include "ocudu/hal/dpdk/dpdk_eal_factory.h"
#endif
// Include ThreadSanitizer (TSAN) options if thread sanitization is enabled.
// This include is not unused - it helps prevent false alarms from the thread sanitizer.

/// ThreadSanitizer options. This include is not unused — it installs compile-time
/// options that suppress false positives from the thread sanitizer tool.
#include "ocudu/support/tsan_options.h"


using namespace ocudu;

/// \file
/// \brief Application of a co-located gNB with combined distributed unit (DU) and centralized unit (CU).
///
/// This application runs a gNB without the the F1 connection between CU and DU and without the E1 connection
/// between the CU-CP and CU-UP going over a real SCTP connection. However, its does expose the N2 and N3 interface
/// to the AMF and UPF over the standard SCTP ports.
/// The app serves as an example for a all-integrated, small-cell-style gNB.


/// Path to the YAML configuration file, set by the -c command-line argument.
static std::string config_file;

/// Flag that indicates if the application is running or being shutdown.

/// Atomic flag indicating whether the application is running.
/// Set to false by the interrupt signal handler to trigger a clean shutdown.
/// Atomic ensures the main loop reads the current value even across threads.
static std::atomic<bool> is_app_running = {true};
/// Maximum number of configuration files allowed to be concatenated in the command line.

/// Maximum number of YAML config files that can be concatenated on the command
/// line (the -c flag can be specified multiple times and their contents merged).
static constexpr unsigned MAX_CONFIG_FILES = 10;


/**
 * @brief Registers the version flag and config file argument with the CLI11 parser.
 *
 * After this call, running `./gnb --version` prints the version string and exits,
 * and `./gnb -c config.yaml` sets the config_file path for later parsing.
 *
 * @param app  The CLI11 application object managing command-line argument parsing.
 */
static void populate_cli11_generic_args(CLI::App& app)
{
  // Build the version string: "OCUDU 5G gNB version X.Y.Z (gitabc123)"
  fmt::memory_buffer buffer;
  format_to(std::back_inserter(buffer), "OCUDU 5G gNB version {} ({})", get_version(), get_build_hash());
  // Register -v/--version to print the version string and exit.
  app.set_version_flag("-v,--version", ocudu::to_c_str(buffer));
  // Register -c to accept 1–MAX_CONFIG_FILES YAML file paths.
  app.set_config("-c,", config_file, "Read config from file", false)->expected(1, MAX_CONFIG_FILES);
}

/// Function to call when the application is interrupted.

/**
 * @brief Signal handler called when the application receives SIGINT or SIGTERM.
 *
 * Sets the is_app_running flag to false, which causes the main event loop to
 * exit on its next iteration, triggering the ordered shutdown sequence.
 *
 * @param signal  The signal number received (SIGINT=2, SIGTERM=15). Unused here
 *                but required by the signal handler function signature.
 */
static void interrupt_signal_handler(int signal)
{
  is_app_running = false;
}


/// Dispatcher that notifies multiple handlers when a cleanup signal is received.
/// Allows different parts of the system to register their own cleanup callbacks.
static signal_dispatcher cleanup_signal_dispatcher;

/// Function to call when the application is going to be forcefully shutdown.

/**
 * @brief Signal handler called on SIGABRT or other fatal signals.
 *
 * Performs an emergency flush of the log buffer so that log messages written
 * just before the crash are not lost, then notifies all registered cleanup
 * handlers via the dispatcher.
 *
 * @param signal  The fatal signal number received.
 */
static void cleanup_signal_handler(int signal)
{
  cleanup_signal_dispatcher.notify_signal(signal);
  ocudulog::fetch_basic_logger("APP").error("Emergency flush of the logger");
  ocudulog::flush();
}

/// Function to call when an error is reported by the application.

/**
 * @brief Error report handler called when report_error() is invoked anywhere.
 *
 * Flushes the log to ensure the error message is written to disk before
 * the process potentially exits.
 */
static void app_error_report_handler()
{
  ocudulog::fetch_basic_logger("APP").error("Emergency flush of the logger");
  ocudulog::flush();
}


/**
 * @brief Initialises the logging system.
 *
 * Creates a log sink — either a file on disk or stdout — and sets it as the
 * default destination for all log output. Must be called before any subsystem
 * starts logging.
 *
 * @param filename  Path to the log file, or the string "stdout" to log to the terminal.
 */
static void initialize_log(const std::string& filename)
{
  // Create the appropriate sink type based on the filename.
  ocudulog::sink* log_sink =
      (filename == "stdout") ? ocudulog::create_stdout_sink() : ocudulog::create_file_sink(filename);
  if (log_sink == nullptr) {
    report_error("Could not create application main log sink.\n");
  }
  ocudulog::set_default_sink(*log_sink);
  ocudulog::init();
}


/**
 * @brief Configures log levels for all subsystems from the application config.
 *
 * Each protocol layer and service has its own named logger. This function sets
 * the log level (none/error/warning/info/debug) and hex dump limit for each,
 * based on what the user specified in the YAML config file.
 *
 * @param gnb_cfg       Top-level gNB config (provides the logger_appconfig).
 * @param cu_cp_app_unit  CU-CP unit — registers its own layer-specific loggers.
 * @param cu_up_app_unit  CU-UP unit — registers its own layer-specific loggers.
 * @param du_app_unit     DU unit — registers its own layer-specific loggers.
 */
static void register_app_logs(const gnb_appconfig&            gnb_cfg,
                              o_cu_cp_application_unit&       cu_cp_app_unit,
                              o_cu_up_application_unit&       cu_up_app_unit,
                              flexible_o_du_application_unit& du_app_unit)
{
  const logger_appconfig& log_cfg = gnb_cfg.log_cfg;
  // Set log-level of app and all non-layer specific components to app level.

  // Set the log level for generic / infrastructure components to the
  // library-wide level specified by lib_level in the config.
  for (const auto& id : {"ALL", "SCTP-GW", "IO-EPOLL", "UDP-GW", "PCAP", "ASN1"}) {
    auto& logger = ocudulog::fetch_basic_logger(id, false);
    logger.set_level(log_cfg.lib_level);
    logger.set_hex_dump_max_size(log_cfg.hex_max_size);
  }


  // Set up the top-level GNB logger. First set to info so the build info
  // banner is always printed, then set to the configured level afterwards.
  auto& app_logger = ocudulog::fetch_basic_logger("GNB", false);
  app_logger.set_level(ocudulog::basic_levels::info);
  app_services::application_message_banners::log_build_info(app_logger);
  app_logger.set_level(log_cfg.all_level);
  app_logger.set_hex_dump_max_size(log_cfg.hex_max_size);


  // General application logger — used for startup/shutdown messages.
  {
    auto& logger = ocudulog::fetch_basic_logger("APP", false);
    logger.set_level(log_cfg.all_level);
    logger.set_hex_dump_max_size(log_cfg.hex_max_size);
  }


  // Configuration logger — used to dump the effective config at startup.
  auto& config_logger = ocudulog::fetch_basic_logger("CONFIG", false);
  config_logger.set_level(log_cfg.config_level);
  config_logger.set_hex_dump_max_size(log_cfg.hex_max_size);


  // E2AP logger — for the RAN management interface to the SMO/RIC.
  auto& e2ap_logger = ocudulog::fetch_basic_logger("E2AP", false);
  e2ap_logger.set_level(log_cfg.e2ap_level);
  e2ap_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  // Metrics log channels.

  // Metrics output loggers (separate from the main log).
  const app_helpers::metrics_config& metrics_cfg = gnb_cfg.metrics_cfg.rusage_config.metrics_consumers_cfg;
  app_helpers::initialize_metrics_log_channels(metrics_cfg, log_cfg.hex_max_size);

  // Register units logs.

  // Each application unit registers its own protocol-layer loggers (e.g.
  // RRC, PDCP, MAC, PHY) with the levels from the config file.
  cu_cp_app_unit.on_loggers_registration();
  cu_up_app_unit.on_loggers_registration();
  du_app_unit.on_loggers_registration();
}


/**
 * @brief Ensures the CU-CP's slice list covers all slices configured in the DU cells.
 *
 * A "slice" is a virtual partition of the 5G network identified by an S-NSSAI
 * (Single Network Slice Selection Assistance Information), consisting of an SST
 * (Slice/Service Type) and an optional SD (Slice Differentiator).
 *
 * The CU-CP must know about every slice the DU serves. If the DU config lists
 * a slice that the CU-CP config does not include, this function adds it
 * automatically so the user does not have to list slices in two places.
 *
 * @param du_hi_cfg   DU High config — source of cell/slice definitions.
 * @param cu_cp_config  CU-CP config — slice list is updated in place if needed.
 */
static void autoderive_slicing_args(du_high_unit_config& du_hi_cfg, cu_cp_unit_config& cu_cp_config)
{
  // Collect the unique set of S-NSSAIs from all DU cell configs.
  std::vector<s_nssai_t> du_slices;
  for (const auto& cell_cfg : du_hi_cfg.cells_cfg) {
    for (const auto& slice : cell_cfg.cell.slice_cfg) {
      s_nssai_t nssai{slice_service_type{slice.sst}, slice_differentiator::create(slice.sd).value()};
      // Only add if not already in the list (avoid duplicates across cells).
      if (du_slices.end() == std::find(du_slices.begin(), du_slices.end(), nssai)) {
        du_slices.push_back(nssai);
      }
    }
  }
  // NOTE: A CU-CP can serve more slices than slices configured in the DU cells.
  // [Implementation-defined] Ensure that all slices served by DU cells are part of CU-CP served slices.

  // A CU-CP can serve more slices than are configured in the DU cells, so we
  // only add missing ones — not remove extras.
  for (const auto& slice : du_slices) {
    if (cu_cp_config.slice_cfg.end() ==
        std::find(cu_cp_config.slice_cfg.begin(), cu_cp_config.slice_cfg.end(), slice)) {
      cu_cp_config.slice_cfg.push_back(slice);
    }
  }
}


/**
 * @brief Auto-fills CU-UP parameters that can be derived from the CU-CP config.
 *
 * Rather than requiring the user to duplicate information in both the cu_up
 * and cu_cp sections of the config file, this function derives CU-UP values
 * from the CU-CP config where the information is naturally shared.
 *
 * @param cu_up_cfg  CU-UP config — updated in place.
 * @param cu_cp_cfg  CU-CP config — read-only source of derived values.
 */
static void autoderive_cu_up_parameters_after_parsing(cu_up_unit_config& cu_up_cfg, const cu_cp_unit_config& cu_cp_cfg)
{
  // If no UPF is configured, we set the UPF configuration from the CU-CP AMF configuration.
  // If no UPF (User Plane Function / core network data plane) is explicitly
  // configured for the CU-UP, derive its bind address from the AMF config.
  // The AMF and UPF are typically on the same network, so the same bind address works.
  if (cu_up_cfg.ngu_cfg.ngu_socket_cfg.empty()) {
    cu_up_unit_ngu_socket_config sock_cfg;
    // If multiple AMF addresses are configured for SCTP multihoming, we use first address from the list.
    // Use the first AMF address if multiple are configured (SCTP multihoming).
    sock_cfg.bind_addr = cu_cp_cfg.amf_config.amf.bind_addrs[0];
    cu_up_cfg.ngu_cfg.ngu_socket_cfg.push_back(sock_cfg);
  }
  // If no PLMN list is configured, derive it from the CU-CP supported TAs.

  // If no PLMN list is configured for the CU-UP, derive it from the set of
  // PLMNs in the CU-CP's supported tracking areas.
  if (cu_up_cfg.plmn_list.empty()) {
    for (const auto& ta : cu_cp_cfg.amf_config.amf.supported_tas) {
      for (const auto& plmn_item : ta.plmn_list) {
        // Avoid duplicates — the same PLMN may appear in multiple TAs.
        if (std::find(cu_up_cfg.plmn_list.begin(), cu_up_cfg.plmn_list.end(), plmn_item.plmn_id) ==
            cu_up_cfg.plmn_list.end()) {
          cu_up_cfg.plmn_list.push_back(plmn_item.plmn_id);
        }
      }
    }
  }
}


// ─────────────────────────────────────────────────────────────────────────────
/**
 * @brief Application entry point.
 *
 * Orchestrates the full lifecycle of the gNB application:
 *   1. Register signal handlers and enable crash backtrace.
 *   2. Parse command-line arguments and the YAML config file.
 *   3. Run auto-derivation and validation on the parsed config.
 *   4. Initialise logging, tracing, timers, thread pools, and memory pools.
 *   5. Construct O-CU-CP, O-CU-UP, and O-DU objects.
 *   6. Wire them together and start them in order.
 *   7. Block in the main event loop until interrupted.
 *   8. Stop all units in reverse order and exit cleanly.
 *
 * @param argc  Number of command-line arguments.
 * @param argv  Array of command-line argument strings.
 * @return 0 on clean exit; non-zero if a fatal error occurred.
 */
int main(int argc, char** argv)
{
  // Set the application error handler.
  // Install the error handler first — if report_error() is called during
  // startup, we want the log flushed even before logging is fully set up.
  set_error_handler(app_error_report_handler);


  static constexpr std::string_view app_name = "gNB";
  // Print startup banner: application name and version to stdout.
  app_services::application_message_banners::announce_app_and_version(app_name);

  // Set interrupt and cleanup signal handlers.

  // Register OS signal handlers:
  //   SIGINT (Ctrl+C) / SIGTERM → sets is_app_running = false for clean shutdown.
  //   SIGABRT / crash signals  → flush log and notify cleanup handlers.
  register_interrupt_signal_handler(interrupt_signal_handler);
  register_cleanup_signal_handler(cleanup_signal_handler);

  // Enable backtrace.

  // Enable printing a C++ stack backtrace to the log on crash.
  enable_backtrace();

  // Setup and configure config parsing.

  // ── Config parsing ──────────────────────────────────────────────────────────
  // Create the CLI11 argument parser and configure it to use our YAML parser.
  CLI::App app("OCUDU gNB application");
  app.config_formatter(create_yaml_config_parser()); // YAML file format for -c
  // Treat unrecognised config keys as errors (catches typos in the config file).
  app.allow_config_extras(CLI::config_extras_mode::error);
  // Fill the generic application arguments to parse.

  // Register the -v/--version and -c flags.
  populate_cli11_generic_args(app);


  // Create the top-level config struct and register all its fields with the parser.
  gnb_appconfig gnb_cfg;
  // Configure CLI11 with the gNB application configuration schema.
  configure_cli11_with_gnb_appconfig_schema(app, gnb_cfg);


  // Create the three application units and let each register its own config
  // fields with the parser. This means each unit's YAML section is parsed
  // directly into that unit's own config struct.
  auto o_cu_cp_app_unit = create_o_cu_cp_application_unit("gnb");
  o_cu_cp_app_unit->on_parsing_configuration_registration(app);


  auto o_cu_up_app_unit = create_o_cu_up_application_unit("gnb");
  o_cu_up_app_unit->on_parsing_configuration_registration(app);


  auto o_du_app_unit = create_flexible_o_du_application_unit("gnb");
  o_du_app_unit->on_parsing_configuration_registration(app);

  // Set the callback for the app calling all the autoderivation functions.

  // Register a callback that runs after CLI11 has parsed all arguments.
  // This is where auto-derivation happens — filling in values that can be
  // inferred from what the user explicitly set.
  app.callback([&app, &gnb_cfg, &o_du_app_unit, &o_cu_cp_app_unit, &o_cu_up_app_unit]() {
    // Fill any gNB-level auto-derived values (e.g. N2 bind address guesses).
    autoderive_gnb_parameters_after_parsing(app, gnb_cfg);


    cu_cp_unit_config& cu_cp_cfg = o_cu_cp_app_unit->get_o_cu_cp_unit_config().cucp_cfg;


    // Ensure CU-CP slice config covers all slices from DU cells.
    autoderive_slicing_args(o_du_app_unit->get_o_du_high_unit_config().du_high_cfg.config, cu_cp_cfg);
    // Let the DU unit auto-derive any of its own parameters.
    o_du_app_unit->on_configuration_parameters_autoderivation(app);

    // If test mode is enabled, we auto-enable "no_core" option and generate a amf config with no core.

    // Test mode: if the DU is in test mode (fake UEs, no real air interface),
    // automatically disable the requirement for a real AMF connection.
    if (o_du_app_unit->get_o_du_high_unit_config().du_high_cfg.config.is_testmode_enabled()) {
      cu_cp_cfg.amf_config.no_core = true;
    } else {
      // If no-core or the default supported tas are configured and we are not using testmode, this will set the
      // supported TAs from the DU cell configuration.
      // In normal operation: if the CU-CP has no explicit supported_tas or
      // is running without a core, derive them from the DU cell configuration.
      if (cu_cp_cfg.amf_config.no_core || cu_cp_cfg.amf_config.amf.is_default_supported_tas) {
        autoderive_supported_tas_for_amf_from_du_cells(o_du_app_unit->get_o_du_high_unit_config().du_high_cfg.config,
                                                       cu_cp_cfg);
      }
    }


    // Let CU-CP and CU-UP units auto-derive their own parameters.
    o_cu_cp_app_unit->on_configuration_parameters_autoderivation(app);
    o_cu_up_app_unit->on_configuration_parameters_autoderivation(app);
    // Derive CU-UP parameters that come from the CU-CP config (bind address, PLMNs).
    autoderive_cu_up_parameters_after_parsing(o_cu_up_app_unit->get_o_cu_up_unit_config().cu_up_cfg, cu_cp_cfg);
  });

  // Parse arguments.

  // Parse the command-line arguments (and YAML file pointed to by -c).
  // On error (bad arg, bad YAML, unrecognised key) this macro prints an error
  // and exits with a non-zero code.
  CLI11_PARSE(app, argc, argv);

  // Dry run mode, exit.

  // ── Dry run exit ────────────────────────────────────────────────────────────
  // If --dryrun was specified, we exit here having only parsed and validated the
  // config. Useful for CI checks that the config file is valid.
  if (gnb_cfg.enable_dryrun) {
    return 0;
  }


  // Warn if JSON metrics are enabled but the remote server is off — JSON metrics
  // are only delivered via the remote server, so they would be silently dropped.
  if (gnb_cfg.metrics_cfg.rusage_config.metrics_consumers_cfg.enable_json_metrics &&
      !gnb_cfg.remote_control_config.enabled) {
    fmt::println("NOTE: No JSON metrics will be generated as the remote server is disabled");
  }

  // Check the modified configuration.

  // ── Config validation ────────────────────────────────────────────────────────
  // Validate the fully-parsed and auto-derived config before building anything.
  // report_error() exits the process with an error message if this fails.
  if (!validate_appconfig(gnb_cfg) || !o_cu_cp_app_unit->on_configuration_validation() ||
      !o_cu_up_app_unit->on_configuration_validation(not gnb_cfg.trace_cfg.filename.empty()) ||
      !o_du_app_unit->on_configuration_validation() ||
      !validate_plmn_and_tacs(o_du_app_unit->get_o_du_high_unit_config().du_high_cfg.config,
                              o_cu_cp_app_unit->get_o_cu_cp_unit_config().cucp_cfg)) {
    report_error("Invalid configuration detected.\n");
  }

  // Set up logging.

  // ── Logging setup ────────────────────────────────────────────────────────────
  // Now that validation has passed, set up logging (can't log before this).
  initialize_log(gnb_cfg.log_cfg.filename);
  // Ensure the log is always flushed when leaving this scope (normal or crash).
  auto log_flusher = make_scope_exit([]() { ocudulog::flush(); });
  // Configure log levels for all subsystem loggers.
  register_app_logs(gnb_cfg, *o_cu_cp_app_unit, *o_cu_up_app_unit, *o_du_app_unit);

  // Check the metrics and metrics consumers.

  // ── Metrics flag ─────────────────────────────────────────────────────────────
  ocudulog::basic_logger& gnb_logger = ocudulog::fetch_basic_logger("GNB");
  // Check whether any unit has metrics enabled — used to warn if the user
  // configured metrics output but no metrics will actually be produced.
  bool metrics_enabled = o_cu_cp_app_unit->are_metrics_enabled() || o_cu_up_app_unit->are_metrics_enabled() ||
                         o_du_app_unit->are_metrics_enabled() || gnb_cfg.metrics_cfg.rusage_config.enable_app_usage;


  if (!metrics_enabled && gnb_cfg.metrics_cfg.rusage_config.metrics_consumers_cfg.enabled()) {
    gnb_logger.warning("Logger or JSON metrics output enabled but no metrics will be reported as no layer was enabled");
    fmt::println("Logger or JSON metrics output enabled but no metrics will be reported as no layer was enabled");
  }

  // Log input configuration.

  // ── Config dump to log ───────────────────────────────────────────────────────
  // At DEBUG level: dump the complete effective configuration (all values,
  // including defaults) so the user can see exactly what is running.
  // At INFO level: dump only the values that differ from defaults.
  ocudulog::basic_logger& config_logger = ocudulog::fetch_basic_logger("CONFIG");
  if (config_logger.debug.enabled()) {
    YAML::Node node;
    fill_gnb_appconfig_in_yaml_schema(node, gnb_cfg);
    o_cu_cp_app_unit->dump_config(node);
    o_cu_up_app_unit->dump_config(node);
    o_du_app_unit->dump_config(node);
    config_logger.debug("gNB input configuration (all values): \n{}", YAML::Dump(node));
  } else {
    config_logger.info("gNB input configuration (only non-default values): \n{}", app.config_to_str(false, false));
  }


  // ── Tracing ──────────────────────────────────────────────────────────────────
  // If a trace file was configured, start recording internal events.
  // Trace files are used for offline performance analysis.
  app_services::application_tracer app_tracer;
  if (not gnb_cfg.trace_cfg.filename.empty()) {
    app_tracer.enable_tracer(gnb_cfg.trace_cfg.filename,
                             gnb_cfg.trace_cfg.max_tracing_events_per_file,
                             gnb_cfg.trace_cfg.nof_tracing_events_after_severe,
                             gnb_logger);
  }


  // ── DPDK initialisation (optional) ──────────────────────────────────────────
#ifdef DPDK_FOUND
  std::unique_ptr<dpdk::dpdk_eal> eal;
  if (gnb_cfg.hal_config) {
    // Prepend the application name in argv[0] as it is expected by EAL.
    // Initialise DPDK's Environment Abstraction Layer (EAL).
    // argv[0] (the program name) is prepended as DPDK expects it as the first argument.
    eal = dpdk::create_dpdk_eal(std::string(argv[0]) + " " + gnb_cfg.hal_config->eal_args,
                                ocudulog::fetch_basic_logger("EAL", false));
  }
#endif

  // Buffer pool service.

  // ── Memory buffer pool ───────────────────────────────────────────────────────
  // Pre-allocate a pool of packet buffers. All subsystems borrow from this pool
  // rather than calling malloc/free on every packet, which is too slow for real-time.
  app_services::buffer_pool_manager buffer_pool_service(gnb_cfg.buffer_pool_config);

  // Log CPU architecture.

  // ── CPU features check ───────────────────────────────────────────────────────
  // Log which SIMD instruction sets (e.g. AVX2, AVX-512) were compiled in.
  cpu_architecture_info::get().print_cpu_info(gnb_logger);

  // Check and log included CPU features and check support by current CPU

  // Verify that the CPU running the binary supports the SIMD instructions
  // that were compiled in. If not, the binary will crash with an illegal
  // instruction error at runtime — better to catch it here with a clear message.
  if (cpu_supports_included_features()) {
    gnb_logger.debug("Required CPU features: {}", get_cpu_feature_info());
  } else {
    // Quit here until we complete selection of the best matching implementation for the current CPU at runtime.
    gnb_logger.error("The CPU does not support the required CPU features that were configured during compile time: {}",
                     get_cpu_feature_info());
    report_error("The CPU does not support the required CPU features that were configured during compile time: {}\n",
                 get_cpu_feature_info());
  }

  // Check some common causes of performance issues and print a warning if required.

  // ── Performance warnings ─────────────────────────────────────────────────────
  // Check for common OS misconfigurations that hurt real-time performance and
  // log warnings if found.
  check_cpu_governor(gnb_logger); // Warns if CPU governor is not "performance"
  check_drm_kms_polling(gnb_logger); // Warns if the GPU driver is polling (causes CPU jitter)

  // Setup application timers.

  // ── Timer manager ────────────────────────────────────────────────────────────
  // Central timer wheel shared by CU and DU. 1024 = number of timer slots.
  // DU timing is driven by PHY slot ticks; CU timing piggybacks on the same wheel.
  timer_manager app_timers{1024};


  // ── Metrics infrastructure ───────────────────────────────────────────────────
  // The notifier proxy sits between metrics producers (CU, DU, RU) and the
  // central metrics manager. It is connected to the manager after the manager
  // is created (below), because the manager depends on app_timers being ready.
  app_services::metrics_notifier_proxy_impl metrics_notifier_forwarder;


  // ── Remote control server (optional) ─────────────────────────────────────────
  // If enabled, creates a server that accepts external commands (e.g. via a
  // REST API or socket) for metrics queries and parameter changes at runtime.
  std::unique_ptr<app_services::remote_server> remote_control_server =
      app_services::create_remote_server(gnb_cfg.remote_control_config);
  app_services::remote_server_metrics_gateway* remote_server_gateway =
      remote_control_server ? remote_control_server->get_metrics_gateway() : nullptr;

  // Instantiate executor metrics service.

  // ── Executor metrics service ─────────────────────────────────────────────────
  // Measures how busy each worker thread is (queue depth, processing time).
  // Useful for diagnosing whether threads are overloaded.
  app_services::executor_metrics_service_and_metrics exec_metrics_service = build_executor_metrics_service(
      metrics_notifier_forwarder, app_timers, gnb_cfg.metrics_cfg.executors_metrics_cfg, remote_server_gateway);


  // Collect all metrics configs into one list — added to by each unit below.
  std::vector<app_services::metrics_config> metrics_configs = std::move(exec_metrics_service.metrics);

  // Instantiate worker manager.

  // ── Worker thread manager ─────────────────────────────────────────────────────
  // Creates all the CPU worker threads used by CU-CP, CU-UP, and DU.
  // Thread counts, CPU affinities, and queue sizes come from the config.
  worker_manager_config worker_manager_cfg;
  o_cu_cp_app_unit->fill_worker_manager_config(worker_manager_cfg);
  o_cu_up_app_unit->fill_worker_manager_config(worker_manager_cfg);
  o_du_app_unit->fill_worker_manager_config(worker_manager_cfg);
  fill_gnb_worker_manager_config(worker_manager_cfg, gnb_cfg); // gNB-level thread pool settings
  worker_manager_cfg.app_timers                    = &app_timers;
  worker_manager_cfg.exec_metrics_channel_registry = exec_metrics_service.channel_registry;
  // Constructing worker_manager actually creates and starts the threads.
  worker_manager workers{worker_manager_cfg};

  // Create IO broker.

  // ── I/O broker (epoll) ────────────────────────────────────────────────────────
  // The I/O broker manages asynchronous network I/O events using Linux epoll.
  // Network sockets (SCTP to AMF, UDP for GTP-U) are registered here and
  // processed without blocking.
  const auto&                main_pool_cpu_mask = gnb_cfg.expert_execution_cfg.affinities.main_pool_cpu_cfg.mask;
  io_broker_config           io_broker_cfg(os_thread_realtime_priority::min() + 5, main_pool_cpu_mask);
  std::unique_ptr<io_broker> epoll_broker = create_io_broker(io_broker_type::epoll, io_broker_cfg);

  // Create a DU-high timer source.

  // ── DU High clock controller ──────────────────────────────────────────────────
  // Creates the timing source for the DU. PHY slot ticks (from the radio hardware)
  // drive this clock, which in turn advances the timer_manager and triggers
  // time-sensitive operations like the MAC scheduler.
  auto time_ctrl = odu::create_du_high_clock_controller(app_timers, *epoll_broker, workers.get_timer_source_executor());

  // Create layer specific PCAPs.
  // In the gNB app, there is no point in instantiating two pcaps for each node of E1 and F1.
  // We disable one accordingly.

  // ── PCAP (packet capture) files ───────────────────────────────────────────────
  // PCAP files record protocol messages for offline debugging with Wireshark.
  // In the co-located gNB, F1 and E1 are in-process so we disable the
  // corresponding PCAPs on one side to avoid recording each message twice.
  auto on_pcap_close = make_scope_exit([&gnb_logger]() { gnb_logger.info("PCAP files successfully closed."); });
  o_cu_up_app_unit->get_o_cu_up_unit_config().cu_up_cfg.pcap_cfg.disable_e1_pcaps();
  o_du_app_unit->get_o_du_high_unit_config().du_high_cfg.config.pcaps.disable_f1_pcaps();
  o_cu_cp_dlt_pcaps cu_cp_dlt_pcaps = create_o_cu_cp_dlt_pcap(
      o_cu_cp_app_unit->get_o_cu_cp_unit_config(), workers.get_cu_cp_pcap_executors(), cleanup_signal_dispatcher);
  o_cu_up_dlt_pcaps cu_up_dlt_pcaps = create_o_cu_up_dlt_pcaps(
      o_cu_up_app_unit->get_o_cu_up_unit_config(), workers.get_cu_up_pcap_executors(), cleanup_signal_dispatcher);
  flexible_o_du_pcaps du_pcaps = create_o_du_pcaps(
      o_du_app_unit->get_o_du_high_unit_config(), workers.get_du_pcap_executors(), cleanup_signal_dispatcher);
  auto on_pcap_close_init = make_scope_exit([&gnb_logger]() { gnb_logger.info("Closing PCAP files..."); });

  // Create XN-C GWs. (TODO cleanup port and PPID args with factory)

  // ── XN-C gateways ────────────────────────────────────────────────────────────
  // XN-C is the interface between neighbouring gNBs for handover coordination.
  // One gateway is created per configured peer gNB address.
  cu_cp_unit_config cp_unit_cfg = o_cu_cp_app_unit->get_o_cu_cp_unit_config().cucp_cfg;
  std::vector<std::unique_ptr<ocucp::xnc_connection_gateway>> xnc_gws;
  for (const auto& gw_cfg : cp_unit_cfg.xnap_config.gateways) {
    sctp_network_gateway_config xnc_sctp_cfg = {};
    xnc_sctp_cfg.if_name                     = "XN-C";
    xnc_sctp_cfg.non_blocking_mode           = true;
    xnc_sctp_cfg.bind_addresses              = gw_cfg.bind_addrs;
    fill_sctp_network_gateway_config_socket_params(xnc_sctp_cfg, gw_cfg.sctp);
    xnc_sctp_cfg.bind_port = XNAP_PORT; // Standard XnAP SCTP port
    xnc_sctp_cfg.ppid      = XNAP_PPID; // XnAP SCTP Payload Protocol Identifier
    xnc_sctp_gateway_config xnc_server_cfg({xnc_sctp_cfg,
                                            *epoll_broker,
                                            workers.get_cu_cp_executor_mapper().xnc_rx_executor(),
                                            workers.get_cu_cp_executor_mapper().ctrl_executor(),
                                            *cu_cp_dlt_pcaps.xnap});

    xnc_gws.push_back(create_xnc_connection_gateway(xnc_server_cfg));
  }


  // ── Local F1-C and E1 connectors ──────────────────────────────────────────────
  // Since CU and DU are co-located (same process), F1-C (control plane between
  // CU-CP and DU) and E1 (control plane between CU-CP and CU-UP) use in-memory
  // connectors rather than real SCTP sockets. This eliminates network overhead.
  std::unique_ptr<f1c_local_connector> f1c_gw =
      create_f1c_local_connector(f1c_local_connector_config{*cu_cp_dlt_pcaps.f1ap});
  std::unique_ptr<e1_local_connector> e1_gw =
      create_e1_local_connector(e1_local_connector_config{*cu_cp_dlt_pcaps.e1ap});

  // Create manager of timers for DU, CU-CP and CU-UP, which will be driven by the PHY slot ticks.

  // ── Timer selection for test mode ─────────────────────────────────────────────
  // In test mode (fake UEs), the DU drives its own timing artificially.
  // We give the CU layers a separate dummy timer manager so they do not
  // see slot ticks from the PHY — they would interpret them as real time passing.
  timer_manager*                 cu_timers = &app_timers;
  std::unique_ptr<timer_manager> dummy_timers;
  if (o_du_app_unit->get_o_du_high_unit_config().du_high_cfg.config.is_testmode_enabled()) {
    // In case test mode is enabled, we pass dummy timers to the upper layers.
    dummy_timers = std::make_unique<timer_manager>(256);
    cu_timers    = dummy_timers.get();
  }

  // Create F1-U TEID allocator (CU-UP)

  // ── GTP-U TEID allocators ─────────────────────────────────────────────────────
  // GTP-U tunnels (used to carry user data between CU-UP and UPF/DU) are
  // identified by TEIDs (Tunnel Endpoint Identifiers). Each allocator manages
  // a pool of TEIDs and hands them out as tunnels are created.
  gtpu_allocator_creation_request cu_f1u_alloc_msg = {
      .max_nof_teids = o_cu_up_app_unit->get_o_cu_up_unit_config().cu_up_cfg.max_nof_ues * MAX_NOF_PDU_SESSIONS,
      .teid_release_linger_time = GTPU_DEFAULT_TEID_RELEASE_LINGER_TIME,
      .timers                   = *cu_timers};
  std::unique_ptr<gtpu_teid_pool> cu_f1u_teid_allocator = create_gtpu_allocator(cu_f1u_alloc_msg);

  // Create F1-U TEID allocator (DU)
  gtpu_allocator_creation_request du_f1u_alloc_msg      = {.max_nof_teids            = MAX_NOF_DU_UES * MAX_NOF_DRBS,

                                                           .teid_release_linger_time = GTPU_DEFAULT_TEID_RELEASE_LINGER_TIME,
                                                           .timers                   = time_ctrl->get_timer_manager()};
  std::unique_ptr<gtpu_teid_pool> du_f1u_teid_allocator = create_gtpu_allocator(du_f1u_alloc_msg);

  // Create F1-U connector

  // ── F1-U user-plane connector ─────────────────────────────────────────────────
  // F1-U carries user data between CU-UP and DU. Like F1-C, it is in-memory
  // in the co-located deployment.
  std::unique_ptr<f1u_local_connector> f1u_conn = std::make_unique<f1u_local_connector>();

  // Create app-level resource usage service and metrics.

  // ── App-level resource usage metrics ─────────────────────────────────────────
  // Measures overall application CPU and memory usage and reports it via the
  // metrics system.
  auto app_resource_usage_service = app_services::build_app_resource_usage_service(
      metrics_notifier_forwarder, gnb_cfg.metrics_cfg.rusage_config, gnb_logger, remote_server_gateway);

  for (auto& metric : app_resource_usage_service.metrics) {
    metrics_configs.push_back(std::move(metric));
  }


  // Add buffer pool metrics (reports pool utilisation — important for detecting
  // buffer exhaustion which can cause packet drops).
  buffer_pool_service.add_metrics_to_metrics_service(
      metrics_configs, gnb_cfg.buffer_pool_config.metrics_config, metrics_notifier_forwarder, remote_server_gateway);

  // Instantiate E2AP client gateways.

  // ── E2 monitoring clients ──────────────────────────────────────────────────────
  // E2 is the O-RAN interface to the RAN Intelligent Controller (RIC) / SMO.
  // Separate E2 clients are created for DU, CU-CP, and CU-UP, each identified
  // by a different PPID (Payload Protocol Identifier) on the SCTP connection.
  std::unique_ptr<e2_connection_client> e2_gw_du = create_e2_gateway_client(
      generate_e2_client_gateway_config(o_du_app_unit->get_o_du_high_unit_config().e2_cfg.base_cfg,
                                        *epoll_broker,
                                        workers.get_du_high_executor_mapper().e2_rx_executor(),
                                        *du_pcaps.e2ap,
                                        E2_DU_PPID));
  std::unique_ptr<e2_connection_client> e2_gw_cu_cp = create_e2_gateway_client(
      generate_e2_client_gateway_config(o_cu_cp_app_unit->get_o_cu_cp_unit_config().e2_cfg.base_config,
                                        *epoll_broker,
                                        workers.get_cu_cp_executor_mapper().e2_rx_executor(),
                                        *cu_cp_dlt_pcaps.e2ap,
                                        E2_CP_PPID));
  std::unique_ptr<e2_connection_client> e2_gw_cu_up = create_e2_gateway_client(
      generate_e2_client_gateway_config(o_cu_up_app_unit->get_o_cu_up_unit_config().e2_cfg.base_config,
                                        *epoll_broker,
                                        workers.get_cu_up_executor_mapper().e2_rx_executor(),
                                        *cu_up_dlt_pcaps.e2ap,
                                        E2_UP_PPID));

  // Create O-CU-CP dependencies.

  // ── Construct O-CU-CP ─────────────────────────────────────────────────────────
  // The CU-CP (Control Plane) manages radio resource control (RRC), UE mobility,
  // and the N2 interface to the AMF (core network control plane).
  o_cu_cp_unit_dependencies o_cucp_deps;
  o_cucp_deps.executor_mapper = &workers.get_cu_cp_executor_mapper();
  o_cucp_deps.timers          = cu_timers;
  o_cucp_deps.ngap_pcap       = cu_cp_dlt_pcaps.ngap.get();
  o_cucp_deps.broker          = epoll_broker.get();
  for (auto& gw : xnc_gws) {
    o_cucp_deps.xnc_gws.push_back(gw.get());
  }
  o_cucp_deps.metrics_notifier       = &metrics_notifier_forwarder;
  o_cucp_deps.e2_gw                  = e2_gw_cu_cp.get();
  o_cucp_deps.remote_metrics_gateway = remote_server_gateway;

  // Create O-CU-CP.

  auto            o_cucp_unit = o_cu_cp_app_unit->create_o_cu_cp(o_cucp_deps);
  ocucp::o_cu_cp& o_cucp_obj  = *o_cucp_unit.unit;
  for (auto& metric : o_cucp_unit.metrics) {
    metrics_configs.push_back(std::move(metric));
  }

  // Create O-CU-UP dependencies.

  // ── Construct O-CU-UP ─────────────────────────────────────────────────────────
  // The CU-UP (User Plane) handles the N3 interface to the UPF (core network
  // user plane), carrying actual user data (internet traffic).
  o_cu_up_unit_dependencies o_cuup_unit_deps;
  o_cuup_unit_deps.workers = &workers;
  o_cuup_unit_deps.e1ap_conn_client.push_back(e1_gw.get());
  o_cuup_unit_deps.f1u_teid_allocator     = cu_f1u_teid_allocator.get();
  o_cuup_unit_deps.f1u_gateway            = f1u_conn->get_f1u_cu_up_gateway();
  o_cuup_unit_deps.gtpu_pcap              = cu_up_dlt_pcaps.n3.get();
  o_cuup_unit_deps.timers                 = cu_timers;
  o_cuup_unit_deps.io_brk                 = epoll_broker.get();
  o_cuup_unit_deps.e2_gw                  = e2_gw_cu_up.get();
  o_cuup_unit_deps.metrics_notifier       = &metrics_notifier_forwarder;
  o_cuup_unit_deps.remote_metrics_gateway = remote_server_gateway;

  // Create O-CU-UP.

  auto            o_cuup_unit = o_cu_up_app_unit->create_o_cu_up_unit(o_cuup_unit_deps);
  ocuup::o_cu_up& o_cuup_obj  = *o_cuup_unit.unit;
  for (auto& metric : o_cuup_unit.metrics) {
    metrics_configs.push_back(std::move(metric));
  }
  // Create O-DU dependencies.

  // ── Construct O-DU ────────────────────────────────────────────────────────────
  // The O-DU (Distributed Unit) contains the real-time radio processing layers:
  // MAC scheduler, RLC, upper PHY, lower PHY, and (in split-8) the UHD radio driver.
  o_du_unit_dependencies odu_dependencies;
  odu_dependencies.workers                = &workers;
  odu_dependencies.f1c_client_handler     = f1c_gw.get();
  odu_dependencies.f1u_teid_allocator     = du_f1u_teid_allocator.get();
  odu_dependencies.f1u_gw                 = f1u_conn->get_f1u_du_gateway();
  odu_dependencies.timer_ctrl             = time_ctrl.get();
  odu_dependencies.mac_p                  = du_pcaps.mac.get();
  odu_dependencies.rlc_p                  = du_pcaps.rlc.get();
  odu_dependencies.e2_client_handler      = e2_gw_du.get();
  odu_dependencies.metrics_notifier       = &metrics_notifier_forwarder;
  odu_dependencies.remote_metrics_gateway = remote_server_gateway;
  odu_dependencies.fapi_logger            = &ocudulog::fetch_basic_logger("FAPI");

  // Create O-DU.

  auto     o_du_unit = o_du_app_unit->create_flexible_o_du_unit(odu_dependencies);
  odu::du& o_du_obj  = *o_du_unit.unit;
  for (auto& metric : o_du_unit.metrics) {
    metrics_configs.push_back(std::move(metric));
  }

  // Create metrics manager.

  // ── Metrics manager ───────────────────────────────────────────────────────────
  // Aggregates metrics from all units and reports them periodically.
  // The notifier proxy is connected here — from this point, metrics produced
  // by any unit flow through the proxy to this manager.
  app_services::metrics_manager metrics_mngr(
      ocudulog::fetch_basic_logger("GNB"),
      workers.get_metrics_executor(),
      metrics_configs,
      app_timers,
      std::chrono::milliseconds(gnb_cfg.metrics_cfg.metrics_service_cfg.app_usage_report_period));

  // Connect the forwarder to the metrics manager.
  metrics_notifier_forwarder.connect(metrics_mngr);


  // ── Command-line interface ─────────────────────────────────────────────────────
  // Allows an operator to type commands while the gNB is running (e.g. to print
  // current metrics or trigger a handover).
  std::vector<std::unique_ptr<app_services::cmdline_command>> commands;
  commands.reserve(o_cucp_unit.commands.cmdline.commands.size() + o_du_unit.commands.cmdline.commands.size());
  for (auto& cmd : o_cucp_unit.commands.cmdline.commands) {
    commands.push_back(std::move(cmd));
  }
  for (auto& cmd : o_du_unit.commands.cmdline.commands) {
    commands.push_back(std::move(cmd));
  }

  // Add the metrics STDOUT command.
  // Add the "metrics" command that prints metrics to stdout on demand.
  if (std::unique_ptr<app_services::cmdline_command> cmd = app_services::create_stdout_metrics_app_command(
          {{o_du_unit.commands.cmdline.metrics_subcommands}, {o_cucp_unit.commands.cmdline.metrics_subcommands}},
          gnb_cfg.metrics_cfg.autostart_stdout_metrics)) {
    commands.push_back(std::move(cmd));
  }

  // Create console helper object for commands and metrics printing.
  // The dispatcher reads from stdin on a dedicated thread and calls the appropriate command.
  app_services::cmdline_command_dispatcher command_parser(*epoll_broker, workers.get_cmd_line_executor(), commands);

  // Connect E1AP to O-CU-CP.

  // ── Wire CU components together ───────────────────────────────────────────────
  // Attach the in-process E1 connector to the CU-CP so the CU-CP can send
  // E1AP messages to the CU-UP.
  e1_gw->attach_cu_cp(o_cucp_obj.get_cu_cp().get_e1_handler());

  // Connect each XN-C gateway to O-CU-CP and start listening for new XN-C connection requests.

  // Attach each XN-C gateway to the CU-CP and start listening for peer gNB connections.
  for (auto& gw : xnc_gws) {
    gw->attach_cu_cp(o_cucp_obj.get_cu_cp().get_xnc_handler());
  }

  // Start O-CU-CP.

  // ── Start the stack ───────────────────────────────────────────────────────────
  // Units are started in order: CU-CP first (it must connect to the AMF before
  // the DU tries to register), then CU-UP, then DU (which starts the radio).

  gnb_logger.info("Starting CU-CP...");
  o_cucp_obj.get_operation_controller().start();
  gnb_logger.info("CU-CP started successfully");

  // Check connection to AMF.

  // Verify the CU-CP has successfully connected to the AMF. If not, the DU
  // cannot register cells so there is no point starting it.
  if (not o_cucp_obj.get_cu_cp().get_ng_handler().amfs_are_connected()) {
    report_error("CU-CP failed to connect to AMF");
  }

  // Configure the remote commands and start the service.

  // Start the remote control server (if configured) and register DU commands with it.
  if (remote_control_server) {
    remote_control_server->add_commands(o_du_unit.commands.remote);
    remote_control_server->get_operation_controller().start();
  }

  // Connect F1-C to O-CU-CP and start listening for new F1-C connection requests.

  // Attach the F1-C connector to the CU-CP and start listening for DU F1 Setup requests.
  f1c_gw->attach_cu_cp(o_cucp_obj.get_cu_cp().get_f1c_handler());

  // Start O-CU-UP.

  // Start the CU-UP (connects to CU-CP via E1, ready to handle user data).
  o_cuup_obj.get_operation_controller().start();

  // Start processing.

  // Start the DU — this triggers the radio to start, cells to come up, and
  // the F1 Setup procedure to complete with the CU-CP.
  o_du_obj.get_operation_controller().start();

  // Start metrics manager.

  // Start periodic metrics reporting.
  metrics_mngr.start();


  // ── Main event loop ───────────────────────────────────────────────────────────
  {
    // Print the "gNB is running" banner to the log and stdout.
    app_services::application_message_banners app_banner(
        app_name,
        gnb_cfg.log_cfg.filename == "stdout" ? std::string_view() : gnb_cfg.log_cfg.filename,
        gnb_logger,
        gnb_cfg.log_cfg.all_level);


    // Start collecting executor (thread) performance metrics.
    auto exec_metrics_session = exec_metrics_service.service
                                    ? exec_metrics_service.service->create_session(workers.get_metrics_executor())
                                    : app_services::app_executor_metrics_service::create_dummy_session();


    // Spin here until is_app_running is set to false by the interrupt signal handler.
    // Sleep 250ms per iteration — real work is done on worker threads, not here.
    while (is_app_running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  } // app_banner destructor prints the "shutting down" message here.

  // Stop metrics manager.

  // ── Ordered shutdown ──────────────────────────────────────────────────────────
  // Units are stopped in reverse start order: metrics first (no new data needed),
  // then DU (stops the radio), then CU-UP, then CU-CP (last to disconnect from AMF).

  metrics_mngr.stop();

  // Stop remote control server.

  if (remote_control_server) {
    remote_control_server->get_operation_controller().stop();
  }

  // Stop DU activity.

  // Stop DU — sends F1 Release to CU-CP, stops the radio, stops PHY processing.
  o_du_obj.get_operation_controller().stop();

  // Stop O-CU-UP activity.

  // Stop CU-UP — tears down GTP-U tunnels and closes N3 socket.
  o_cuup_obj.get_operation_controller().stop();

  // Stop O-CU-CP activity.

  // Stop CU-CP — sends NG Release to AMF, closes N2 SCTP connection.
  o_cucp_obj.get_operation_controller().stop();

  // Stop gateway SCTP servers.

  // Stop the in-process F1-C and E1 gateways.
  f1c_gw->stop();
  e1_gw->stop();
  // Xn-C gateway is stopped by Xn-C connection manager.

  // XN-C gateways are stopped internally by the XN-C connection manager.

  return 0;
  // log_flusher scope_exit fires here: final log flush before process exits.
}
