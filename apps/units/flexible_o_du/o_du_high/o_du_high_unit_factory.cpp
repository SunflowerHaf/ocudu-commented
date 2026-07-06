// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_factory.cpp
//
// Purpose (plain English):
//   The implementation behind o_du_high_unit_factory.h. Three responsibilities:
//
//     1. announce_du_high_cells() — a boot-time helper that prints one line
//        per configured cell (PCI, bandwidth, MIMO layout, ARFCNs, ...) and
//        also writes an "SSB derived parameters" log block per cell.
//
//     2. build_du_metrics() / build_rlc_du_metrics() — wire up the metric
//        producers (DU scheduler + MAC, and RLC) to their consumers (stdout,
//        log file, JSON HTTP, E2 RIC). Everything is optional depending on
//        the YAML config toggles.
//
//     3. make_o_du_high_unit() — the top-level factory: translates the "unit"
//        config into the internal odu::du_high_configuration, sanity-checks
//        derived parameters (PRACH/PUCCH overlap warning), builds the
//        metrics, calls the core odu::make_o_du_high() factory, and finally
//        registers three "remote commands" (SSB change, RRM policy change,
//        SIB update) so an operator can retune the running gNB via the
//        remote-control HTTP interface.
// =============================================================================

#include "o_du_high_unit_factory.h"
#include "apps/helpers/e2/e2_metric_connector_manager.h"
#include "apps/helpers/metrics/metrics_helpers.h"
#include "du_high/commands/du_high_cmdline_commands.h"
#include "du_high/commands/du_high_remote_commands.h"
#include "du_high/du_high_config_translators.h"
#include "du_high/metrics/du_high_rlc_metrics.h"
#include "du_high/metrics/du_high_rlc_metrics_consumers.h"
#include "du_high/metrics/du_high_rlc_metrics_producer.h"
#include "du_high/metrics/du_metrics.h"
#include "du_high/metrics/du_metrics_consumers.h"
#include "du_high/metrics/du_metrics_producer.h"
#include "e2/o_du_high_e2_config_translators.h"
#include "o_du_high_unit_config.h"
#include "ocudu/du/du_high/du_high.h"
#include "ocudu/du/du_high/du_high_configuration.h"
#include "ocudu/du/du_high/o_du_high_config.h"
#include "ocudu/du/du_high/o_du_high_factory.h"
#include "ocudu/du/du_update_config_helpers.h"
#include "ocudu/e2/e2_du_metrics_connector.h"
#include "ocudu/ran/prach/prach_configuration.h"
#include "ocudu/ran/prach/prach_frequency_mapping.h"


using namespace ocudu;


// =============================================================================
// announce_du_high_cells()
//   Prints a one-line summary per cell to stdout, and a multi-line "SSB
//   derived parameters" block per cell to the "GNB" log. This is the first
//   feedback the operator sees when they start the gNB.
// =============================================================================
void ocudu::announce_du_high_cells(const du_high_unit_config& du_high_unit_cfg)
{
  // Fetch the shared "GNB" logger channel. "false" = don't create it if it
  // doesn't already exist — startup code ensures it does.
  ocudulog::basic_logger& logger = ocudulog::fetch_basic_logger("GNB", false);

  // Generate DU cells.

  // Turn the user's high-level cell config into the low-level cell config
  // used by the RAN core. This resolves things like ARFCN → SSB offsets.
  auto cells = generate_du_cell_config(du_high_unit_cfg);


  // Loop over every cell and print its summary line.
  for (const auto& cell : cells) {
    fmt::print("Cell pci={}, bw={} MHz, {}T{}R, dl_arfcn={} (n{}), dl_freq={} MHz, dl_ssb_arfcn={}, ul_freq={} MHz\n",
               cell.ran.pci, // Physical Cell ID (0..1007)
               bs_channel_bandwidth_to_MHz(cell.ran.dl_carrier.carrier_bw), // e.g. 20, 40, 100 MHz
               cell.ran.dl_carrier.nof_ant, // DL antennas (T = transmit)
               cell.ran.ul_carrier.nof_ant, // UL antennas (R = receive)
               cell.ran.dl_carrier.arfcn_f_ref, // DL centre ARFCN
               nr_band_to_uint(cell.ran.dl_carrier.band), // NR band number (e.g. n78)
               band_helper::nr_arfcn_to_freq(cell.ran.dl_carrier.arfcn_f_ref) / 1e6, // DL frequency in MHz
               cell.ran.dl_cfg_common.freq_info_dl.absolute_frequency_ssb, // SSB ARFCN
               band_helper::nr_arfcn_to_freq(cell.ran.ul_carrier.arfcn_f_ref) / 1e6); // UL frequency in MHz


    // Look up the CORESET#0 and SearchSpace#0 indices for MIB decoding. These
    // must exist in any valid config — abort if not.
    const auto ss0_idx = cell.ran.dl_cfg_common.init_dl_bwp.pdcch_common.get_searchspace0();
    ocudu_assert(ss0_idx.has_value(), "SearchSpace#0 not found in common SearchSpace list");
    const auto cs0_idx = cell.ran.dl_cfg_common.init_dl_bwp.pdcch_common.get_coreset0();
    ocudu_assert(cs0_idx.has_value(), "CORESET#0 index not found in common PDCCH configuration");


    // Emit the "SSB derived parameters" block for this cell. Everything here
    // is derived by the config generator, not entered directly by the user,
    // so logging it is essential for debugging PRACH/SSB alignment issues.
    logger.info(
        "SSB derived parameters for cell: {}, band: {}, dl_arfcn:{}, nof_crbs: {} scs:{}, ssb_scs:{}:\n\t - SSB offset "
        "pointA:{} \n\t - k_SSB:{} \n\t - SSB arfcn:{} \n\t - Coreset index:{} \n\t - Searchspace index:{}",
        cell.ran.pci,
        fmt::underlying(cell.ran.dl_carrier.band),
        cell.ran.dl_carrier.arfcn_f_ref,
        cell.ran.dl_cfg_common.init_dl_bwp.generic_params.crbs.length(), // Bandwidth in Common Resource Blocks.
        to_string(cell.ran.dl_cfg_common.init_dl_bwp.generic_params.scs), // Subcarrier spacing (e.g. 30 kHz).
        to_string(cell.ran.ssb_cfg.scs), // SSB subcarrier spacing.
        cell.ran.ssb_cfg.offset_to_point_A.value(), // SSB offset from PRB 0 (in RBs).
        cell.ran.ssb_cfg.k_ssb.value(), // Sub-carrier fine offset for SSB.
        cell.ran.dl_cfg_common.freq_info_dl.absolute_frequency_ssb, // SSB ARFCN.
        cs0_idx.value(), // CORESET#0 index (table lookup).
        ss0_idx.value()); // SearchSpace#0 index.
  }


  fmt::print("\n");
}


// =============================================================================
// validates_derived_du_params()
//   Post-derivation sanity check. Warns if the user's chosen PRACH frequency
//   overlaps the PUCCH region — this doesn't stop the run (the config is
//   legal in the sense that it will start) but the operator should know
//   they'll see interference and reduced RACH success.
// =============================================================================
static void validates_derived_du_params(span<const odu::du_cell_config> cells)
{
  ocudulog::basic_logger& logger = ocudulog::fetch_basic_logger("DU", false);


  for (const auto& cell_cfg : cells) {
    const rach_config_common& rach_cfg = cell_cfg.ran.ul_cfg_common.init_ul_bwp.rach_cfg_common.value();


    // Determine frequency range (FR1/FR2) and duplex mode (FDD/TDD) for
    // this cell's band — both feed into the PRACH configuration table lookup.
    frequency_range freq_range = band_helper::get_freq_range(cell_cfg.ran.dl_carrier.band);
    duplex_mode     dplx_mode  = band_helper::get_duplex_mode(cell_cfg.ran.dl_carrier.band);


    // Look up the PRACH configuration (format, periodicity, subframe pattern)
    // from the standard TS38.211 table using the config index the user chose.
    const auto prach_cfg = prach_configuration_get(freq_range, dplx_mode, rach_cfg.rach_cfg_generic.prach_config_index);


    // Ask config_helpers where the largest contiguous PRB block *without*
    // PUCCH is — that's the region PRACH ought to sit in.
    prb_interval prb_interval_no_pucch = config_helpers::find_largest_prb_interval_without_pucch(
        cell_cfg.ran.init_bwp.pucch.resources, cell_cfg.ran.ul_cfg_common.init_ul_bwp.generic_params.crbs.length());

    // This is to preserve a guardband between the PUCCH and PRACH.

    // Long PRACH preambles are wideband anyway; short ones need a 3-PRB
    // guardband from PUCCH to avoid leakage.
    const unsigned pucch_to_prach_guardband = is_long_preamble(prach_cfg.format) ? 0U : 3U;


    // If the user's PRACH start is *before* the safe zone, warn (do not fail).
    if (rach_cfg.rach_cfg_generic.msg1_frequency_start < prb_interval_no_pucch.start() + pucch_to_prach_guardband) {
      fmt::print("Warning: With the given prach_frequency_start={}, the PRACH opportunities overlap with the PUCCH "
                 "resources/guardband in prbs=[0, {}). Some interference between PUCCH and PRACH should be "
                 "expected\n",
                 rach_cfg.rach_cfg_generic.msg1_frequency_start,
                 prb_interval_no_pucch.start() + pucch_to_prach_guardband);


      // Also log it so the warning is captured in the log file, not just stdout.
      logger.warning(
          "With the given prach_frequency_start={}, the PRACH opportunities overlap with the PUCCH resources/guardband "
          "in prbs=[0, {}). Some interference between PUCCH and PRACH should be expected",
          rach_cfg.rach_cfg_generic.msg1_frequency_start,
          prb_interval_no_pucch.start() + pucch_to_prach_guardband);
    }
  }
}


// =============================================================================
// build_rlc_du_metrics()
//   Builds the RLC metric config: one producer that emits samples, plus zero
//   or more consumers (log, JSON, E2 RIC) depending on what's enabled in the
//   YAML config. Returns a pointer to the producer as a notifier interface
//   so the DU High core can hand samples to it, or nullptr if RLC metrics
//   are disabled entirely.
// =============================================================================
static rlc_metrics_notifier* build_rlc_du_metrics(std::vector<app_services::metrics_config>&   metrics,
                                                  app_services::metrics_notifier&              metrics_notifier,
                                                  app_services::remote_server_metrics_gateway* remote_metrics_gateway,
                                                  const o_du_high_unit_config&                 o_du_high_unit_cfg,
                                                  e2_du_metrics_notifier&                      e2_notifier)
{
  rlc_metrics_notifier*      out       = nullptr;
  const du_high_unit_config& du_hi_cfg = o_du_high_unit_cfg.du_high_cfg.config;

  // RLC metrics not enabled, do not add metrics configuration.

  // Fast exit: RLC metrics disabled.
  if (!du_hi_cfg.metrics.layers_cfg.enable_rlc) {
    return out;
  }


  // Add a new metrics_config entry to the caller's vector, and grab a
  // reference so we can populate it in place.
  app_services::metrics_config& rlc_metrics_cfg = metrics.emplace_back();
  rlc_metrics_cfg.metric_name                   = rlc_metrics_properties_impl().name();
  rlc_metrics_cfg.callback                      = rlc_metrics_callback;

  // Fill the generator.

  // Create the producer (the object the DU High will push samples into).
  auto rlc_metric_gen = std::make_unique<rlc_metrics_producer_impl>(metrics_notifier);
  out                 = &(*rlc_metric_gen); // Save raw pointer before moving.
  rlc_metrics_cfg.producers.push_back(std::move(rlc_metric_gen));


  const app_helpers::metrics_config& metrics_config = du_hi_cfg.metrics.common_metrics_cfg;
  // Consumers.

  // ---- Consumer: log file -------------------------------------------------
  if (metrics_config.enable_log_metrics) {
    rlc_metrics_cfg.consumers.push_back(
        std::make_unique<rlc_metrics_consumer_log>(app_helpers::fetch_logger_metrics_log_channel()));
  }


  // ---- Consumer: JSON over HTTP -------------------------------------------
  // Requires the remote-server gateway to be up. If the user asked for JSON
  // metrics but forgot to enable the remote server, abort with a clear msg.
  if (metrics_config.enable_json_metrics) {
    report_error_if_not(remote_metrics_gateway,
                        "Invalid remote server gateway for sending JSON metrics. Check that remote server is enabled");
    rlc_metrics_cfg.consumers.push_back(std::make_unique<rlc_metrics_consumer_json>(*remote_metrics_gateway));
  }


  // ---- Consumer: E2 RIC ---------------------------------------------------
  if (o_du_high_unit_cfg.e2_cfg.base_cfg.enable_unit_e2) {
    rlc_metrics_cfg.consumers.push_back(std::make_unique<rlc_metrics_consumer_e2>(e2_notifier));
  }


  return out;
}


// =============================================================================
// build_du_metrics()
//   Same shape as build_rlc_du_metrics() but for scheduler + MAC metrics.
//   Also registers a stdout consumer and a "toggle stdout metrics" cmdline
//   subcommand so the operator can turn the live stdout metric printer on
//   and off from the console without restarting the gNB.
// =============================================================================
static odu::du_metrics_notifier*
build_du_metrics(std::vector<app_services::metrics_config>& metrics,
                 std::vector<std::unique_ptr<app_services::toggle_stdout_metrics_app_command::metrics_subcommand>>&
                                                              metrics_subcommands,
                 app_services::metrics_notifier&              metrics_notifier,
                 app_services::remote_server_metrics_gateway* remote_metrics_gateway,
                 const o_du_high_unit_config&                 o_du_high_unit_cfg,
                 e2_du_metrics_notifier&                      e2_notifier)
{
  const du_high_unit_config& du_hi_cfg = o_du_high_unit_cfg.du_high_cfg.config;

  // Scheduler or MAC metrics not enabled, do not create consumers and producers.

  // Skip if both MAC and scheduler metrics are disabled — no point building
  // producers with no data flowing.
  if (!du_hi_cfg.metrics.layers_cfg.enable_mac && !du_hi_cfg.metrics.layers_cfg.enable_scheduler) {
    return nullptr;
  }


  odu::du_metrics_notifier* out = nullptr;


  app_services::metrics_config& du_metrics_cfg = metrics.emplace_back();
  du_metrics_cfg.metric_name                   = du_metrics_properties_impl().name();
  du_metrics_cfg.callback                      = du_metrics_callback;

  // Fill the generator.

  // Producer.
  auto du_metric_gen = std::make_unique<du_metrics_producer_impl>(metrics_notifier);
  out                = &(*du_metric_gen);
  du_metrics_cfg.producers.push_back(std::move(du_metric_gen));

  // Create the consumer for STDOUT. Also create the command for toggle the metrics.

  // ---- Consumer: stdout + a cmdline "toggle" subcommand -------------------
  // We always create the stdout consumer, but the user can suppress its
  // output at runtime via the "t" console command (implemented by the
  // subcommand pushed here).
  auto metrics_stdout = std::make_unique<du_metrics_consumer_stdout>();
  metrics_subcommands.push_back(std::make_unique<du_high_metrics_subcommand_stdout>(*metrics_stdout));
  du_metrics_cfg.consumers.push_back(std::move(metrics_stdout));


  const app_helpers::metrics_config& metrics_config = du_hi_cfg.metrics.common_metrics_cfg;

  // ---- Consumer: log -------------------------------------------------------
  if (metrics_config.enable_log_metrics) {
    du_metrics_cfg.consumers.push_back(
        std::make_unique<du_metrics_consumer_log>(app_helpers::fetch_logger_metrics_log_channel()));
  }


  // ---- Consumer: JSON ------------------------------------------------------
  if (metrics_config.enable_json_metrics) {
    report_error_if_not(remote_metrics_gateway,
                        "Invalid remote server gateway for sending JSON metrics. Check that remote server is enabled");
    du_metrics_cfg.consumers.push_back(std::make_unique<du_metrics_consumer_json>(*remote_metrics_gateway));
  }

  // Connect E2 agent to DU Scheduler UE metrics.

  // ---- Consumer: E2 RIC ----------------------------------------------------
  if (o_du_high_unit_cfg.e2_cfg.base_cfg.enable_unit_e2) {
    du_metrics_cfg.consumers.push_back(std::make_unique<du_metrics_consumer_e2>(e2_notifier));
  }


  return out;
}


// =============================================================================
// make_o_du_high_unit()
//   The main factory. Translates the unit config into the internal O-DU High
//   config, wires up dependencies, builds metrics, delegates to the core
//   odu::make_o_du_high() to actually construct the runtime, then registers
//   three remote commands so the RIC or an operator can retune the running
//   gNB dynamically.
// =============================================================================
o_du_high_unit ocudu::make_o_du_high_unit(const o_du_high_unit_config&  o_du_high_unit_cfg,
                                          o_du_high_unit_dependencies&& dependencies)
{
  // Allocate the internal O-DU High config; we'll populate it in place.
  odu::o_du_high_config       o_du_high_cfg;
  odu::du_high_configuration& du_hi_cfg        = o_du_high_cfg.du_hi;
  const du_high_unit_config&  du_high_unit_cfg = o_du_high_unit_cfg.du_high_cfg.config;

  // Generate DU high config from the unit config.

  // Translate the user-facing "unit" config into the internal DU High config.
  // This includes cell derivations (SSB, PRACH, PUCCH), MAC/RLC/PDCP params,
  // logging, and F1AP identity fields.
  generate_du_high_config(du_hi_cfg, du_high_unit_cfg);

  // Validates the derived parameters.

  // Post-derivation sanity check: warns on PRACH/PUCCH overlap.
  validates_derived_du_params(du_hi_cfg.ran.cells);


  // ---- Wire up the "inner" dependencies the core O-DU High needs ----------
  // These pointers are stored inside the o_du_hi_dependencies bag the caller
  // handed us. The core DU High will keep these references for its lifetime.
  odu::du_high_dependencies& du_hi_deps = dependencies.o_du_hi_dependencies.du_hi;
  du_hi_deps.exec_mapper                = &dependencies.execution_mapper;
  du_hi_deps.f1c_client                 = &dependencies.f1c_client_handler;
  du_hi_deps.f1u_teid_allocator         = &dependencies.f1u_teid_allocator;
  du_hi_deps.f1u_gw                     = &dependencies.f1u_gw;
  du_hi_deps.phy_adapter                = nullptr; // Set later by the O-DU Low when it registers.
  du_hi_deps.timer_ctrl                 = &dependencies.timer_ctrl;
  du_hi_deps.mac_p                      = &dependencies.mac_p;
  du_hi_deps.rlc_p                      = &dependencies.rlc_p;


  // ---- Optional E2 wiring --------------------------------------------------
  if (o_du_high_unit_cfg.e2_cfg.base_cfg.enable_unit_e2) {
    // Connect E2 agent to RLC metric source.
    // Give the core O-DU High a handle on the E2 SCTP client.
    dependencies.o_du_hi_dependencies.e2_client = &dependencies.e2_client_handler;

    // Convert the user's E2 config into the internal e2ap_config used by the
    // E2 agent. Uses the gNB ID, PLMN of the first cell, and the DU ID.
    o_du_high_cfg.e2ap_config                   = generate_e2_config(o_du_high_unit_cfg.e2_cfg,
                                                   du_high_unit_cfg.gnb_id,
                                                   du_high_unit_cfg.cells_cfg.front().cell.plmn,
                                                   du_hi_cfg.ran.gnb_du_id);

    // Attach the E2 metric interface for DU index 0 (we only run one DU).
    dependencies.o_du_hi_dependencies.e2_du_metric_iface =
        &(dependencies.e2_metric_connectors.get_e2_metrics_interface(0));
  }

  // DU high metrics.

  // ---- Build the metrics --------------------------------------------------
  o_du_high_unit odu_unit;


  // Scheduler+MAC metrics (may be nullptr if disabled).
  du_hi_deps.du_notifier = build_du_metrics(odu_unit.metrics,
                                            odu_unit.commands.cmdline.metrics_subcommands,
                                            dependencies.metrics_notifier,
                                            dependencies.remote_metrics_gateway,
                                            o_du_high_unit_cfg,
                                            dependencies.e2_metric_connectors.get_e2_metric_notifier(0));


  // RLC metrics (may be nullptr if disabled).
  du_hi_deps.rlc_metrics_notif = build_rlc_du_metrics(odu_unit.metrics,
                                                      dependencies.metrics_notifier,
                                                      dependencies.remote_metrics_gateway,
                                                      o_du_high_unit_cfg,
                                                      dependencies.e2_metric_connectors.get_e2_metric_notifier(0));

  // Create O-DU high.

  // ---- Build the actual O-DU High runtime ---------------------------------
  odu_unit.o_du_hi = odu::make_o_du_high(o_du_high_cfg, std::move(dependencies.o_du_hi_dependencies));
  report_error_if_not(odu_unit.o_du_hi, "Invalid O-DU high");

  // Create remote commands.

  // ---- Register the three "remote commands" -------------------------------
  // These let the RIC (or the remote-control HTTP endpoint) reconfigure the
  // live gNB without a restart:
  //   * SSB modify        — change the SSB transmit power or position.
  //   * RRM policy ratio  — reassign resource shares between slices.
  //   * SIB update        — push new SIB1 content (e.g. barred flag).
  odu_unit.commands.remote.push_back(
      std::make_unique<ssb_modify_remote_command>(odu_unit.o_du_hi->get_du_high().get_du_configurator()));
  odu_unit.commands.remote.push_back(
      std::make_unique<rrm_policy_ratio_remote_command>(odu_unit.o_du_hi->get_du_high().get_du_configurator()));
  odu_unit.commands.remote.push_back(
      std::make_unique<sib_update_remote_command>(odu_unit.o_du_hi->get_du_high().get_du_configurator()));


  return odu_unit;
}
