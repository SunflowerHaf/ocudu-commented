// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig.h
 * @brief Top-level configuration data structures for the OCUDU gNB application.
 *
 * This file defines the C++ structs that represent every configurable option
 * available in the gNB YAML configuration file. When the application starts,
 * the YAML parser (gnb_appconfig_cli11_schema.cpp) reads the config file and
 * fills in a gnb_appconfig object, which is then passed to validators and
 * translators before being used to construct the rest of the system.
 *
 * Think of this file as the "form" that the config file fills in.
 */

#pragma once


// Pull in configuration structures for each major service area.
// Each of these files defines a sub-struct used as a field in gnb_appconfig below.
#include "apps/helpers/hal/hal_appconfig.h" ///< Hardware Abstraction Layer config (e.g. DPDK)
#include "apps/helpers/logger/logger_appconfig.h" ///< Log level and log file settings
#include "apps/helpers/tracing/tracer_appconfig.h" ///< Performance tracing / event recording config
#include "apps/services/app_execution_metrics/executor_metrics_config.h" ///< CPU thread metrics collection config
#include "apps/services/app_resource_usage/app_resource_usage_config.h" ///< OS-level resource usage reporting config
#include "apps/services/buffer_pool/buffer_pool_appconfig.h" ///< Memory buffer pool sizing config
#include "apps/services/metrics/metrics_appconfig.h" ///< General metrics service config
#include "apps/services/remote_control/remote_control_appconfig.h" ///< Remote control server config
#include "apps/services/worker_manager/worker_manager_appconfig.h" ///< Thread pool and CPU affinity config
#include "ocudu/ran/gnb_id.h" ///< gnb_id_t type: identifies this base station on the network
#include <string>


namespace ocudu {


/**
 * @brief Configuration for the CU-UP (Centralised Unit — User Plane).
 *
 * The CU-UP handles user data plane traffic: it forwards packets between
 * the core network (UPF) and the DU. Currently only controls whether to
 * print a warning when packets are dropped due to congestion.
 */
struct cu_up_appconfig {
  /// If true, print a warning log whenever a packet is dropped because
  /// the output queue is full. Useful for diagnosing congestion issues.
  bool warn_on_drop = false;
};

/// Metrics report configuration.

/**
 * @brief Configuration for all metrics reporting.
 *
 * Metrics are periodic measurements that the system reports about its own
 * performance — e.g. throughput, latency, CPU usage. This struct groups
 * together the various metrics-related config options.
 */
struct metrics_appconfig {
  /// Configuration for OS-level resource usage reporting (CPU %, memory, etc.).
  app_services::app_resource_usage_config rusage_config;
  /// Configuration for the central metrics service (reporting interval, output format).
  app_services::metrics_appconfig         metrics_service_cfg;
  /// Configuration for per-thread executor metrics (measures how busy each worker thread is).
  app_services::executor_metrics_config   executors_metrics_cfg;
  /// If true, metrics will automatically start printing to stdout when the application starts.
  /// If false, metrics must be manually enabled via the command-line interface.
  bool                                    autostart_stdout_metrics = false;
};

/// Monolithic gnb application configuration.

/**
 * @brief Top-level configuration struct for the entire gNB application.
 *
 * This is the root configuration object. Every option that can be set in
 * the YAML config file ends up here (directly or in one of its sub-structs).
 * An instance of this struct is created in main() and populated by the
 * CLI11/YAML parser before any other objects are constructed.
 *
 * Default values are set here so the application can run with a minimal
 * config file that only overrides what the user needs to change.
 */
struct gnb_appconfig {
  /// Default constructor to update the log filename.
  /// Constructor: sets the default log file path to /tmp/gnb.log.
  /// All other fields use their own in-class default values.
  gnb_appconfig() { log_cfg.filename = "/tmp/gnb.log"; }
  /// Loggers configuration.

  /// Logging configuration: log file path, log level per subsystem, hex dump size.
  logger_appconfig log_cfg;
  /// Tracers configuration.

  /// Tracing configuration: whether to record a trace file of internal events
  /// (useful for post-hoc performance analysis).
  tracer_appconfig trace_cfg;
  /// Metrics configuration.

  /// Metrics configuration: how and where to report performance measurements.
  metrics_appconfig metrics_cfg;
  /// gNodeB identifier.

  /// The gNB's network identity. gnb_id_t contains the gNB ID value (411)
  /// and the number of bits used to encode it (22). This identifies the base
  /// station uniquely within its PLMN on the 5G network.
  gnb_id_t gnb_id = {411, 22};
  /// Node name.

  /// Human-readable name for this node, used in log output and management interfaces.
  std::string ran_node_name = "gnb01";
  /// Buffer pool configuration.

  /// Memory buffer pool configuration: sizes and counts of pre-allocated
  /// packet buffers. Tuning this affects memory usage and allocation latency.
  app_services::buffer_pool_appconfig buffer_pool_config;
  /// Expert configuration.

  /// Expert execution configuration: CPU thread counts, CPU core affinities,
  /// and task queue sizes. This is where real-time performance tuning is done.
  expert_execution_appconfig expert_execution_cfg;
  /// HAL configuration.

  /// Optional Hardware Abstraction Layer config. Only present (non-empty) if
  /// DPDK is compiled in and the user has configured it. DPDK provides
  /// kernel-bypass networking for very low-latency ethernet.
  std::optional<hal_appconfig> hal_config;
  /// Remote control configuration.

  /// Remote control server configuration: enables an external process to
  /// send commands to the running gNB (e.g. to query metrics or change parameters).
  remote_control_appconfig remote_control_config;
  /// Dry run mode enabled flag.

  /// If true, the application parses and validates the config then exits
  /// immediately without actually starting the gNB. Used to check config
  /// files for errors without running the system.
  bool enable_dryrun = false;
};


} // namespace ocudu
