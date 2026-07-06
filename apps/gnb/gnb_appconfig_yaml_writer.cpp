// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_yaml_writer.cpp
 * @brief Implementation of gNB config serialisation back to YAML, for debug logging.
 *
 * Called from gnb.cpp's main() when the CONFIG logger is set to debug
 * level, to dump the complete effective configuration (including every
 * default value) to the log. This is purely a diagnostic/debugging tool —
 * it has no effect on actual system behaviour.
 *
 * Three local helper functions handle the sections that need custom
 * formatting (HAL/DPDK args, expert execution thread/CPU settings, remote
 * control server settings); everything else either delegates to another
 * module's own yaml_writer function, or is a simple direct field assignment.
 */

#include "gnb_appconfig_yaml_writer.h"
#include "apps/helpers/logger/logger_appconfig_yaml_writer.h"
#include "apps/helpers/tracing/tracer_appconfig_yaml_writer.h"
#include "apps/services/app_execution_metrics/executor_metrics_config_yaml_writer.h"
#include "apps/services/app_resource_usage/app_resource_usage_config_yaml_writer.h"
#include "apps/services/buffer_pool/buffer_pool_config_yaml_writer.h"
#include "apps/services/metrics/metrics_config_yaml_writer.h"
#include "gnb_appconfig.h"


using namespace ocudu;


/**
 * @brief Writes the [hal] section, if a HAL config is present.
 *
 * @param node    The YAML node to write into.
 * @param config  The optional HAL config (only present if DPDK is compiled
 *                in and a [hal] section was in the original config file).
 */
static void fill_gnb_appconfig_hal_section(YAML::Node node, const std::optional<hal_appconfig>& config)
{
  if (!config.has_value()) {
    return;
  }
  YAML::Node hal_node  = node["hal"];
  hal_node["eal_args"] = config.value().eal_args;
}


/**
 * @brief Writes the [expert_execution] section: CPU affinity and thread settings.
 *
 * @param node    The YAML node to write into.
 * @param config  The expert execution config containing affinity and thread settings.
 */
static void fill_gnb_appconfig_expert_execution_section(YAML::Node node, const expert_execution_appconfig& config)
{
  {
    YAML::Node affinities_node = node["affinities"];


    // Only write the CPU mask if it's actually set (any() returns true if
    // at least one bit is set) — an empty mask means "use the default" and
    // doesn't need to be written explicitly.
    if (config.affinities.main_pool_cpu_cfg.mask.any()) {
      affinities_node["main_pool_cpus"] =
          fmt::format("{:,}", span<const size_t>(config.affinities.main_pool_cpu_cfg.mask.get_cpu_ids()));
    }
    affinities_node["main_pool_pinning"] = to_string(config.affinities.main_pool_cpu_cfg.pinning_policy);
  }


  {
    YAML::Node threads_node   = node["threads"];
    YAML::Node main_pool_node = threads_node["main_pool"];
    if (config.threads.main_pool.nof_threads.has_value()) {
      main_pool_node["nof_threads"] = config.threads.main_pool.nof_threads.value();
    }
    main_pool_node["task_queue_size"] = config.threads.main_pool.task_queue_size;
    main_pool_node["backoff_period"]  = config.threads.main_pool.backoff_period;
  }
}


/**
 * @brief Writes the [remote_control] section.
 *
 * @param node    The YAML node to write into.
 * @param config  The remote control server config.
 */
static void fill_gnb_appconfig_remote_control_section(YAML::Node node, const remote_control_appconfig& config)
{
  node["enabled"]   = config.enabled;
  node["bind_addr"] = config.bind_addr;
  node["port"]      = config.port;
}


/**
 * @brief Serialises the complete gNB application configuration into the given YAML node.
 *
 * Writes the top-level scalar fields directly, then delegates to each
 * subsystem's own yaml_writer function for its respective section
 * (resource usage metrics, central metrics service, executor metrics,
 * buffer pool, logging, tracing), and finally calls the three local helper
 * functions above for the HAL, expert execution, and remote control sections.
 *
 * @param node    The YAML node to populate (typically the root node, passed
 *                by reference so all subsystems write into the same tree).
 * @param config  The gNB configuration to serialise.
 */
void ocudu::fill_gnb_appconfig_in_yaml_schema(YAML::Node& node, const gnb_appconfig& config)
{
  node["gnb_id"]            = config.gnb_id.id;
  node["gnb_id_bit_length"] = static_cast<unsigned>(config.gnb_id.bit_length);
  node["ran_node_name"]     = config.ran_node_name;


  app_services::fill_app_resource_usage_config_in_yaml_schema(node, config.metrics_cfg.rusage_config);
  app_services::fill_metrics_appconfig_in_yaml_schema(node, config.metrics_cfg.metrics_service_cfg);
  app_services::fill_app_exec_metrics_config_in_yaml_schema(node, config.metrics_cfg.executors_metrics_cfg);
  node["metrics"]["autostart_stdout_metrics"] = config.metrics_cfg.autostart_stdout_metrics;
  app_services::fill_buffer_pool_config_in_yaml_schema(node, config.buffer_pool_config);
  fill_logger_appconfig_in_yaml_schema(node, config.log_cfg);
  fill_tracer_appconfig_in_yaml_schema(node, config.trace_cfg);
  fill_gnb_appconfig_hal_section(node, config.hal_config);
  fill_gnb_appconfig_expert_execution_section(node["expert_execution"], config.expert_execution_cfg);
  fill_gnb_appconfig_remote_control_section(node["remote_control"], config.remote_control_config);
}
