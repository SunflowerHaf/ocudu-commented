// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_cli11_schema.cpp
 * @brief Implementation of gNB-level CLI11/YAML config field registration.
 *
 * This file is largely a sequence of calls into other modules' own
 * "configure_cli11_with_X_appconfig_schema()" functions — each subsystem
 * (logger, tracer, buffer pool, worker manager, metrics services, HAL,
 * remote control) owns its own registration logic; this file just calls
 * them all in the right order so the entire [gnb]-section schema is built up.
 */

#include "gnb_appconfig_cli11_schema.h"
#include "apps/helpers/hal/hal_cli11_schema.h"
#include "apps/helpers/logger/logger_appconfig_cli11_schema.h"
#include "apps/helpers/tracing/tracer_appconfig_cli11_schema.h"
#include "apps/services/app_execution_metrics/executor_metrics_config_cli11_schema.h"
#include "apps/services/app_resource_usage/app_resource_usage_config_cli11_schema.h"
#include "apps/services/buffer_pool/buffer_pool_appconfig_cli11_schema.h"
#include "apps/services/metrics/metrics_config_cli11_schema.h"
#include "apps/services/remote_control/remote_control_appconfig_cli11_schema.h"
#include "apps/services/worker_manager/worker_manager_cli11_schema.h"
#include "apps/units/flexible_o_du/o_du_high/du_high/du_high_config.h"
#include "apps/units/o_cu_cp/cu_cp/cu_cp_unit_config.h"
#include "gnb_appconfig.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/support/cli11_utils.h"
#include "CLI/CLI11.hpp"


using namespace ocudu;


/**
 * @brief Registers the "metrics" subcommand's single field: autostart_stdout_metrics.
 *
 * @param app             The metrics subcommand's CLI11 App object.
 * @param metrics_params  The metrics_appconfig struct to populate.
 */
static void configure_cli11_metrics_args(CLI::App& app, metrics_appconfig& metrics_params)
{
  add_option(
      app, "--autostart_stdout_metrics", metrics_params.autostart_stdout_metrics, "Autostart stdout metrics reporting")
      ->capture_default_str();
}


#ifdef DPDK_FOUND
/**
 * @brief Clears the optional HAL config if the [hal] section wasn't actually present in the YAML file.
 *
 * Since DPDK is compiled in, hal_config is always emplaced as a default
 * value before parsing (see configure_cli11_with_gnb_appconfig_schema()
 * below), so it can be filled if a [hal] section exists. This function runs
 * after parsing to detect whether that section was actually present in the
 * file, and if not, resets it back to empty — so downstream code can
 * correctly distinguish "DPDK compiled in but not configured" from "DPDK
 * compiled in and configured".
 *
 * @param app      The CLI11 app object (used to check section presence).
 * @param gnb_cfg  The gNB config to update.
 */
static void manage_hal_optional(CLI::App& app, gnb_appconfig& gnb_cfg)
{
  if (!is_hal_section_present(app)) {
    gnb_cfg.hal_config.reset();
  }
}
#endif


/**
 * @brief Registers every gnb_appconfig field with the CLI11/YAML parser.
 *
 * Order of registration:
 *
 *   1. Top-level scalar fields: dryrun flag, gNB ID, gNB ID bit length
 *      (constrained to 22-32 bits per 3GPP), RAN node name.
 *
 *   2. Logging section ([log]).
 *
 *   3. Tracing section ([tracing]).
 *
 *   4. Buffer pool section ([buffer_pool]).
 *
 *   5. Expert execution (worker thread/CPU affinity) section ([expert_execution]).
 *
 *   6. The "metrics" subcommand (a distinct configurable subcommand rather
 *      than a [metrics] section directly), plus the three metrics-related
 *      sub-services (executor metrics, app resource usage, central metrics service).
 *
 *   7. HAL section ([hal]) — only registered if DPDK was compiled in. If
 *      DPDK was NOT compiled in, a custom failure message handler is
 *      installed instead, so that if a user mistakenly includes a [hal]
 *      section in their config on a non-DPDK build, they get a clear
 *      explanation rather than a generic INI parse error.
 *
 *   8. Remote control server section ([remote_control]).
 *
 * @param app             The CLI11 application object.
 * @param gnb_parsed_cfg  The struct to be populated when parsing runs.
 */
void ocudu::configure_cli11_with_gnb_appconfig_schema(CLI::App& app, gnb_appconfig& gnb_parsed_cfg)
{
  gnb_appconfig& gnb_cfg = gnb_parsed_cfg;
  app.add_flag("--dryrun", gnb_cfg.enable_dryrun, "Enable application dry run mode")->capture_default_str();


  add_option(app, "--gnb_id", gnb_cfg.gnb_id.id, "gNodeB identifier")->capture_default_str();
  add_option(app, "--gnb_id_bit_length", gnb_cfg.gnb_id.bit_length, "gNodeB identifier length in bits")
      ->capture_default_str()
      ->check(CLI::Range(22, 32));
  add_option(app, "--ran_node_name", gnb_cfg.ran_node_name, "RAN node name")->capture_default_str();

  // Loggers section.

  // Loggers section: delegates entirely to the shared logger config schema module.
  configure_cli11_with_logger_appconfig_schema(app, gnb_cfg.log_cfg);

  // Tracers section.

  // Tracers section.
  configure_cli11_with_tracer_appconfig_schema(app, gnb_cfg.trace_cfg);

  // Buffer pool section.

  // Buffer pool section.
  configure_cli11_with_buffer_pool_appconfig_schema(app, gnb_cfg.buffer_pool_config);

  // Expert execution section.

  // Expert execution section: thread counts, CPU affinity masks, queue sizes.
  configure_cli11_with_worker_manager_appconfig_schema(app, gnb_cfg.expert_execution_cfg);

  // Metrics section.

  // Metrics: registered as a distinct subcommand ("metrics"), configurable
  // so it can also appear as a YAML section, plus three related sub-services.
  CLI::App* metrics_subcmd = add_subcommand(app, "metrics", "Metrics configuration")->configurable();
  configure_cli11_metrics_args(*metrics_subcmd, gnb_cfg.metrics_cfg);
  app_services::configure_cli11_with_executor_metrics_appconfig_schema(app, gnb_cfg.metrics_cfg.executors_metrics_cfg);
  app_services::configure_cli11_with_app_resource_usage_config_schema(app, gnb_cfg.metrics_cfg.rusage_config);
  app_services::configure_cli11_with_metrics_appconfig_schema(app, gnb_cfg.metrics_cfg.metrics_service_cfg);


#ifdef DPDK_FOUND
  // HAL section.
  // HAL (DPDK) section — only registered when DPDK support is compiled in.
  // hal_config is pre-emplaced here with defaults; manage_hal_optional()
  // (called after parsing) clears it back to empty if no [hal] section was
  // actually present in the YAML file.
  gnb_cfg.hal_config.emplace();
  configure_cli11_with_hal_appconfig_schema(app, *gnb_cfg.hal_config);
#else
  // DPDK not compiled in: install a custom failure handler so that if the
  // user's config has a [hal] section anyway (e.g. copied from a DPDK-enabled
  // deployment), they get a clear explanation rather than a generic parse error.
  app.failure_message([](const CLI::App* application, const CLI::Error& e) -> std::string {
    if (std::string(e.what()).find("INI was not able to parse hal.++") == std::string::npos) {
      return CLI::FailureMessage::simple(application, e);
    }


    return "Invalid configuration detected, 'hal' section is present but the application was built without DPDK "
           "support\n" +
           CLI::FailureMessage::simple(application, e);
  });
#endif

  // Remote control section.

  // Remote control server section.
  configure_cli11_with_remote_control_appconfig_schema(app, gnb_cfg.remote_control_config);
}


/**
 * @brief Auto-derives gNB-level parameters after parsing has completed.
 *
 * Currently only handles the HAL config cleanup described above
 * (manage_hal_optional()) — only relevant when DPDK is compiled in.
 */
void ocudu::autoderive_gnb_parameters_after_parsing(CLI::App& app, gnb_appconfig& config)
{
#ifdef DPDK_FOUND
  manage_hal_optional(app, config);
#endif
}


/**
 * @brief Derives the CU-CP's supported Tracking Area list from the DU's cell definitions.
 *
 * If the DU has no cells configured, this is a no-op (nothing to derive
 * from). Otherwise, clears any existing supported_tas list and rebuilds it:
 * for each DU cell, adds one supported_ta entry containing that cell's TAC
 * and a single-PLMN entry with a default slice configuration (SST=1, no SD).
 *
 * This means the CU-CP automatically ends up configured to serve exactly
 * the PLMNs/TACs the DU's cells advertise, without the user needing to
 * specify this twice in the config file.
 *
 * @param du_hi_cfg  Source: the DU High config's cell definitions.
 * @param cu_cp_cfg  Destination: the CU-CP config's AMF supported_tas list, updated in place.
 */
void ocudu::autoderive_supported_tas_for_amf_from_du_cells(const du_high_unit_config& du_hi_cfg,
                                                           cu_cp_unit_config&         cu_cp_cfg)
{
  // If no cells are found in DU configuration.
  if (du_hi_cfg.cells_cfg.empty()) {
    return;
  }

  // Clear supported TAs.

  cu_cp_cfg.amf_config.amf.supported_tas.clear();
  cu_cp_cfg.amf_config.amf.is_default_supported_tas = false;

  // Derive supported TAs from DU cell configuration.

  for (const auto& cell : du_hi_cfg.cells_cfg) {
    cu_cp_unit_supported_ta_item supported_ta;
    supported_ta.tac = cell.cell.tac;
    // Default slice: SST=1 (eMBB), no SD (Slice Differentiator) — the
    // generic "best effort" mobile broadband slice.
    supported_ta.plmn_list.push_back({cell.cell.plmn, {cu_cp_unit_plmn_item::tai_slice_t{1}}});
    cu_cp_cfg.amf_config.amf.supported_tas.push_back(supported_ta);
  }
}
