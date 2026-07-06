// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_factory.h
//
// Purpose (plain English):
//   Public interface for building an O-DU High unit. This header declares:
//
//     * o_du_high_unit — the "output" struct returned when the DU High is
//       built: it owns the running O-DU High object plus command handlers
//       and metric configs.
//     * o_du_high_unit_dependencies — the "input" struct listing every
//       external resource the DU High needs pointers/references to at
//       construction time (executors, F1 gateway, PCAPs, E2 client, metrics
//       notifier). These are supplied by higher-level factories.
//     * make_o_du_high_unit() — the factory function that consumes the
//       config + dependencies and returns a ready-to-run DU High.
//     * announce_du_high_cells() — a helper that prints the cell parameters
//       (PCI, bandwidth, ARFCN, MIMO layout) to stdout and the log at boot.
//
//   All the heavy lifting is in the .cpp file; this header is deliberately
//   sparse and full of forward declarations to keep compile times reasonable
//   (avoiding a transitive include of the entire DU High machinery).
// =============================================================================

#pragma once


#include "apps/services/metrics/metrics_config.h"
#include "apps/units/application_unit_commands.h"
#include "ocudu/du/du_high/o_du_high.h"
#include "ocudu/du/du_high/o_du_high_config.h"


namespace ocudu {
// Forward decl: full definition lives in o_du_high_unit_config.h.
struct o_du_high_unit_config;


// ------- Forward declarations for the app_services namespace types -----------
namespace app_services {
class metrics_notifier;
class remote_server_metrics_gateway;
} // namespace app_services


// ------- Forward declarations for the O-DU internal types --------------------
// These live in the odu namespace (the "core" O-DU library, distinct from the
// application-level wrappers in this folder).
namespace odu {
class du_high_executor_mapper;
struct o_du_high_config;
struct o_du_high_dependencies;
class f1c_connection_client;
class f1u_du_gateway;
} // namespace odu


// ------- Forward declarations for miscellaneous supporting types -------------
class du_high_executor_mapper;
template <typename ConnectorType, typename NotifierType, typename InterfaceType>
class e2_metric_connector_manager;
class e2_du_metrics_connector;
class e2_du_metrics_notifier;
class e2_du_metrics_interface;
class e2_connection_client;
class mac_pcap;
class rlc_pcap;
class timer_manager;
struct du_high_unit_config;
struct du_high_wrapper_config;
struct du_high_wrapper_dependencies;
struct o_du_high_unit_config;

// Convenience alias for the specific instantiation of the templated
// e2_metric_connector_manager we use in the DU High.
using e2_du_metrics_connector_manager =
    e2_metric_connector_manager<e2_du_metrics_connector, e2_du_metrics_notifier, e2_du_metrics_interface>;

/// Prints basic DU info in the stdout and in the GNB logs.

/// \brief Prints one line per configured cell (PCI, bandwidth, MIMO layout,
///        DL/UL ARFCN, band, SSB ARFCN) to stdout and to the GNB log.
///
/// This is what the user sees on their terminal when the gNB starts up. It's
/// the first sanity check that the config was interpreted correctly.
void announce_du_high_cells(const du_high_unit_config& du_high_unit_cfg);

/// O-RAN DU high unit.

/// \brief Everything produced by make_o_du_high_unit().
///
/// Wraps the running O-DU High object, the remote-command handlers registered
/// with it, and its metric configs (each of which describes a metric producer
/// plus one or more consumers such as stdout/log/JSON/E2).
struct o_du_high_unit {
  std::unique_ptr<odu::o_du_high>           o_du_hi; ///< The actual O-DU High runtime.
  application_unit_commands                 commands; ///< Cmdline + remote commands this unit exposes.
  std::vector<app_services::metrics_config> metrics; ///< Metrics this unit produces.
};

/// O-RAN DU high unit dependencies.

/// \brief Everything make_o_du_high_unit() needs from its parent.
///
/// The DU High doesn't own any of these — they belong to the split-8 factory
/// or the app-level services. It just holds references/pointers for the
/// lifetime of the run.
struct o_du_high_unit_dependencies {
  odu::du_high_executor_mapper&                execution_mapper; ///< Thread-pool executor map.
  odu::f1c_connection_client&                  f1c_client_handler; ///< F1AP (control) client to the CU-CP.
  gtpu_teid_pool&                              f1u_teid_allocator; ///< Allocates GTP-U TEIDs for F1-U tunnels.
  odu::f1u_du_gateway&                         f1u_gw; ///< F1-U (user plane) gateway to the CU-UP.
  mac_clock_controller&                        timer_ctrl; ///< Controls the MAC subframe timer.
  mac_pcap&                                    mac_p; ///< MAC PCAP writer.
  rlc_pcap&                                    rlc_p; ///< RLC PCAP writer.
  e2_connection_client&                        e2_client_handler; ///< SCTP client to the E2 RIC.
  e2_du_metrics_connector_manager&             e2_metric_connectors; ///< Bridges DU metrics into the E2 agent.
  app_services::metrics_notifier&              metrics_notifier; ///< Metrics fan-out for JSON/log/stdout.
  app_services::remote_server_metrics_gateway* remote_metrics_gateway = nullptr; ///< HTTP JSON metrics gateway (nullable).
  odu::o_du_high_dependencies                  o_du_hi_dependencies; ///< Bag of pointers the O-DU High core needs.
};

/// Creates the O-RAN DU high unit with the given configuration.

/// \brief Builds and returns a fully-wired O-DU High unit.
///
/// Consumes the dependencies (by rvalue) — after this call they belong to the
/// returned unit and must not be referenced by the caller again.
o_du_high_unit make_o_du_high_unit(const o_du_high_unit_config&  o_du_high_unit_cfg,
                                   o_du_high_unit_dependencies&& dependencies);


} // namespace ocudu
