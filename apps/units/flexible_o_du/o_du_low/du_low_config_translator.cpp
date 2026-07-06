// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_config_translator.cpp
//
// Purpose (plain English):
//   Translates the user-facing DU-Low config (plain struct from the YAML
//   parser) into two internal representations:
//
//   1. odu::o_du_low_config  — fed to the core O-DU Low factory. The heavy
//      work is in generate_du_low_config() which:
//        * Populates the "common upper PHY" config: algorithm choices, log
//          settings, LDPC type selections, etc. This block is shared by all
//          cells.
//        * Selects the PDSCH processor implementation (flexible / generic)
//          and its batch size.
//        * For each cell: derives all the buffer-size parameters from the
//          cell's bandwidth, SCS, TDD pattern, and HARQ constraints — see
//          the annotated loop below for the maths.
//
//   2. worker_manager_config — tells the worker manager how many thread-pool
//      slots to create for PDSCH, PUCCH, PUSCH+SRS, and executor tracing.
//      If a hardware accelerator is present, the concurrency is pinned to
//      the number of hardware queues rather than the user's configured max.
// =============================================================================

#include "du_low_config_translator.h"
#include "apps/services/worker_manager/worker_manager_config.h"
#include "du_low_config.h"
#include "ocudu/phy/upper/channel_coding/ldpc/ldpc.h"
#include "ocudu/phy/upper/upper_phy_factories.h"
#include "ocudu/ran/duplex_mode.h"
#include "ocudu/ran/prach/prach_configuration.h"
#include "ocudu/ran/pusch/pusch_constants.h"


using namespace ocudu;


// =============================================================================
// generate_du_low_config()  (internal static)
//   Core translator: turns the flat user config + per-cell param list into
//   the odu::du_low_config the core factory expects.
// =============================================================================
static odu::du_low_config generate_du_low_config(const du_low_unit_config&                       du_low,
                                                 span<const o_du_low_unit_config::du_low_config> cells)
{
  odu::du_low_config out_config;
  out_config.cells.reserve(cells.size());


  // ---- Step 1: find the "worst case" bandwidth + antenna counts across
  //              all cells.  These dimension shared upper-PHY pools.
  unsigned max_ul_bw_rb         = 0;
  unsigned pusch_max_nof_layers = 0;
  unsigned max_nof_rx_antennas  = 0;
  for (unsigned i = 0, e = cells.size(); i != e; ++i) {
    const o_du_low_unit_config::du_low_config& cell = cells[i];
    max_ul_bw_rb                                    = std::max(cell.bw_rb, max_ul_bw_rb);
    pusch_max_nof_layers                            = std::max(cell.pusch_max_nof_layers, pusch_max_nof_layers);
    max_nof_rx_antennas                             = std::max(cell.nof_rx_antennas, max_nof_rx_antennas);
  }


  // ---- Step 2: populate the shared "upper PHY factory config" -------------
  upper_phy_factory_configuration& upper_phy_factory_config = out_config.upper_phy_common_config;

  upper_phy_factory_config.log_level                        = du_low.loggers.phy_level;
  upper_phy_factory_config.enable_logging_broadcast         = du_low.loggers.broadcast_enabled;
  upper_phy_factory_config.logger_max_hex_size              = du_low.loggers.hex_max_size;
  upper_phy_factory_config.enable_metrics                   = du_low.metrics_cfg.enable_du_low;

  // Convert the SINR-method string (e.g. "post_equalization") to the
  // internal enum used by the channel-state-information module.
  upper_phy_factory_config.pusch_sinr_calc_method =
      channel_state_information::sinr_type_from_string(du_low.expert_phy_cfg.pusch_sinr_calc_method);

  // IQ dump settings.
  upper_phy_factory_config.rx_symbol_printer_filename = du_low.loggers.phy_rx_symbols_filename;
  upper_phy_factory_config.rx_symbol_printer_port     = du_low.loggers.phy_rx_symbols_port;
  upper_phy_factory_config.rx_symbol_printer_prach    = du_low.loggers.phy_rx_symbols_prach;

  // "auto" lets the factory pick the best available SIMD-optimised
  // implementation of LDPC at build time (AVX-512, AVX2, NEON, generic).
  upper_phy_factory_config.ldpc_encoder_type          = "auto";
  upper_phy_factory_config.ldpc_decoder_type          = "auto";
  upper_phy_factory_config.ldpc_rate_dematcher_type   = "auto";
  upper_phy_factory_config.crc_calculator_type        = "auto";

  // Channel-estimator algorithm parameters (straight pass-through from user config).
  upper_phy_factory_config.pusch_channel_estimator_fd_strategy =
      du_low.expert_phy_cfg.pusch_channel_estimator_fd_strategy;
  upper_phy_factory_config.pusch_channel_estimator_td_strategy =
      du_low.expert_phy_cfg.pusch_channel_estimator_td_strategy;
  upper_phy_factory_config.pusch_channel_estimator_compensate_cfo =
      du_low.expert_phy_cfg.pusch_channel_estimator_cfo_compensation;
  upper_phy_factory_config.pusch_channel_equalizer_algorithm = du_low.expert_phy_cfg.pusch_channel_equalizer_algorithm;

  // LDPC decoder: max iterations and early-stop are the "quality vs speed" knobs.
  upper_phy_factory_config.ldpc_decoder_iterations           = du_low.expert_phy_cfg.pusch_decoder_max_iterations;
  upper_phy_factory_config.ldpc_decoder_early_stop           = du_low.expert_phy_cfg.pusch_decoder_early_stop;
  upper_phy_factory_config.ldpc_decoder_force_decoding       = du_low.expert_phy_cfg.pusch_decoder_force_decoding;

  // Shared buffer dimensions (sized to the worst-case cell).
  upper_phy_factory_config.nof_rx_ports                      = max_nof_rx_antennas;
  upper_phy_factory_config.ul_bw_rb                          = max_ul_bw_rb;
  upper_phy_factory_config.pusch_max_nof_layers              = pusch_max_nof_layers;
  upper_phy_factory_config.enable_metrics                    = du_low.metrics_cfg.enable_du_low;
  upper_phy_factory_config.ldpc_decoder_type                 = "auto";

  // PHY tap plugin (diagnostic hook — normally disabled).
  if (du_low.expert_phy_cfg.enable_phy_tap) {
    upper_phy_factory_config.phy_tap_arguments = du_low.expert_phy_cfg.phy_tap_arguments;
    if (cells[0].tdd_pattern) {
      upper_phy_factory_config.phy_tap_tdd_pattern = cells[0].tdd_pattern;
    }
  }

  // The flexible PDSCH processor implementation will be used by default.

  // ---- Step 3: choose the PDSCH processor implementation -----------------
  const auto& upper_phy_threads_cfg = du_low.expert_execution_cfg.threads;
  if ((upper_phy_threads_cfg.pdsch_processor_type == "auto") ||
      (upper_phy_threads_cfg.pdsch_processor_type == "flexible")) {
    // Set the batch size for synchronous operation by default. Override it if the PDSCH codeblock processor operation
    // is asynchronous.
    // Default is synchronous (each slot processed by its scheduler thread).
    // If the user chose asynchronous (smaller batch size), that enables the
    // parallel codeblock path where multiple threads split up the codeblocks.
    unsigned cb_batch_length = pdsch_processor_flexible_configuration::synchronous_cb_batch_length;
    if (upper_phy_threads_cfg.pdsch_cb_batch_length != du_low_unit_expert_threads_config::synchronous_cb_batch_length) {
      cb_batch_length = upper_phy_threads_cfg.pdsch_cb_batch_length;
    }

    // Emplace configuration parameters.

    // Emplace the flexible config variant (std::variant, so emplace<T> is needed).
    upper_phy_factory_config.pdsch_processor.emplace<pdsch_processor_flexible_configuration>(
        pdsch_processor_flexible_configuration{.cb_batch_length = cb_batch_length});

  } else if (upper_phy_threads_cfg.pdsch_processor_type == "generic") {
    // The hardware-accelerated DU does not currently support the 'generic' PDSCH processor implementation.
    // "generic" is the unoptimised reference path. It is incompatible with
    // hardware-accelerated PDSCH (the accelerator needs the flexible path).
    bool hw_acc_pdsch = false;
    if (du_low.hal_config.has_value()) {
      const du_low_unit_hal_config& hal_config = *du_low.hal_config;
      if (hal_config.bbdev_hwacc.has_value()) {
        const bbdev_appconfig& bbdev_hwacc = *hal_config.bbdev_hwacc;
        hw_acc_pdsch                       = bbdev_hwacc.pdsch_enc.has_value();
      }
    }
    report_error_if_not(!hw_acc_pdsch,
                        "The hardware-accelerated DU does not support the 'generic' PDSCH processor type.");
    upper_phy_factory_config.pdsch_processor.emplace<pdsch_processor_generic_configuration>();
  }


  // ---- Step 4: per-cell buffer / pipeline calculations -------------------
  for (unsigned i = 0, e = cells.size(); i != e; ++i) {
    const o_du_low_unit_config::du_low_config& cell           = cells[i];
    upper_phy_configuration&                   upper_phy_cell = out_config.cells.emplace_back().upper_phy_cfg;

    // Get bandwidth in PRB.

    const unsigned bw_rb = cell.bw_rb;
    // Deduce the number of slots per subframe.

    // -- Slots-per-frame and slots-per-hyper-system-frame ------------------
    // nof_slots_per_subframe = 1 (for 15 kHz SCS), 2 (30 kHz), 4 (60 kHz),
    //                           8 (120 kHz), 16 (240 kHz).
    const unsigned nof_slots_per_subframe = get_nof_slots_per_subframe(cell.scs_common);
    // Deduce the number of slots per frame.
    // One radio frame = 10 subframes.
    unsigned nof_slots_per_frame = nof_slots_per_subframe * NOF_SUBFRAMES_PER_FRAME;
    // Number of slots per hyper system frame.
    // One "hyper system frame" = 1024 radio frames (SFN rolls at 1023).
    unsigned nof_slots_per_hyper_system_frame = NOF_SFNS * nof_slots_per_frame;
    // PUSCH HARQ process lifetime in slots. It assumes the maximum lifetime is 100ms.

    // -- PUSCH HARQ process lifetime ---------------------------------------
    // The 3GPP spec allows HARQ retransmissions up to 100 ms. We add the
    // pipeline depth so that processes that are just starting when the timer
    // expires are still considered live.
    unsigned expire_pusch_harq_timeout_slots =
        100 * nof_slots_per_subframe + du_low.expert_phy_cfg.max_processing_delay_slots;
    // In a NTN cell, extend the HARQ process lifetime by the cell-specific-k-offset.

    // NTN (Non-Terrestrial Network / satellite) adds a cell-specific
    // K-offset to compensate for propagation delay. The HARQ lifetime must
    // be extended accordingly.
    if (cell.ntn_cs_koffset) {
      expire_pusch_harq_timeout_slots += cell.ntn_cs_koffset->count() * nof_slots_per_subframe;
    }

    // Calculate the number of UL slots in a frame and in a PUSCH HARQ process lifetime.

    // -- How many UL slots fit in one HARQ process lifetime? ---------------
    // For FDD this is simply the number of slots (every slot is a UL slot).
    // For TDD we count only the actual UL slots in the repeating TDD pattern.
    unsigned nof_ul_slots_in_harq_lifetime = expire_pusch_harq_timeout_slots;
    if (cell.duplex == duplex_mode::TDD && cell.tdd_pattern.has_value()) {
      const tdd_ul_dl_pattern& pattern1     = cell.tdd_pattern->pattern1;
      unsigned                 period_slots = pattern1.dl_ul_tx_period_nof_slots;
      // A slot is counted as UL if it has any UL symbols.
      unsigned                 nof_ul_slots = pattern1.nof_ul_slots + ((pattern1.nof_ul_symbols != 0) ? 1 : 0);

      // There can be up to two interleaved TDD patterns.
      if (cell.tdd_pattern->pattern2) {
        const tdd_ul_dl_pattern& pattern2 = *cell.tdd_pattern->pattern2;
        period_slots += pattern2.dl_ul_tx_period_nof_slots;
        nof_ul_slots += pattern2.nof_ul_slots + ((pattern2.nof_ul_symbols != 0) ? 1 : 0);
      }
      // Scale: total UL slots = (periods in lifetime) × (UL slots per period).
      nof_ul_slots_in_harq_lifetime = divide_ceil(expire_pusch_harq_timeout_slots, period_slots) * nof_ul_slots;
    }

    // Deduce the maximum number of codeblocks that can be scheduled for PUSCH in one slot assuming:
    // - The maximum number of resource elements used for data for each scheduled resource block;
    // - the cell bandwidth;
    // - the highest modulation order possible; and
    // - the maximum coding rate.

    // -- Maximum codeblocks per PUSCH slot --------------------------------
    // Worst-case: full bandwidth, all REs used for data, QAM-256, max rate.
    // ldpc::MAX_MESSAGE_SIZE is the largest payload per LDPC codeblock.
    const unsigned max_nof_pusch_cb_slot =
        divide_ceil(pusch_constants::MAX_NRE_PER_RB * bw_rb * get_bits_per_symbol(modulation_scheme::QAM256),
                    ldpc::MAX_MESSAGE_SIZE);

    // Calculate the maximum number of active PUSCH HARQ processes from:
    // - the maximum number of users per slot; and
    // - the number of PUSCH occasions in a HARQ process lifetime.

    // -- PUSCH receive buffer size ----------------------------------------
    // nof_buffers: one buffer per active HARQ process (max UEs × UL occasions).
    const unsigned nof_buffers = cell.max_puschs_per_slot * nof_ul_slots_in_harq_lifetime;

    // Calculate the maximum number of receive codeblocks. It is equal to the product of:
    // - the maximum number of codeblocks that can be scheduled in one slot; and
    // - the number of PUSCH occasions in a HARQ process lifetime.

    // max_rx_nof_codeblocks: total codeblock slots the buffer must hold.
    const unsigned max_rx_nof_codeblocks = nof_ul_slots_in_harq_lifetime * max_nof_pusch_cb_slot;

    // Determine processing downlink pipeline depth. Make sure the number of slots per system frame is divisible by the
    // pipeline depth.

    // -- DL pipeline depth ------------------------------------------------
    // We want a pipeline depth that is a multiple of the slot grid frame
    // count (so that processing windows align with SFN boundaries).
    // Start at 4 × delay_slots and increment until divisible.
    unsigned dl_pipeline_depth = 4 * du_low.expert_phy_cfg.max_processing_delay_slots;
    while (nof_slots_per_hyper_system_frame % dl_pipeline_depth != 0) {
      ++dl_pipeline_depth;
    }

    // The uplink pipeline depth is set equal to the number of slots per frame for reusing uplink processors every
    // 10 ms.

    // UL pipeline is one frame deep (10 ms), so processors can be reused
    // every system frame boundary.
    unsigned ul_pipeline_depth = nof_slots_per_frame;


    // -- PRACH detector configuration ------------------------------------
    // Look up the PRACH configuration table (TS38.211, Table 6.3.3.2-2 or
    // similar) using the PRACH config index, frequency range, and duplex.
    const prach_configuration prach_cfg =
        prach_configuration_get(cell.freq_range, cell.duplex, cell.prach_config_index);
    ocudu_assert(prach_cfg.format != prach_format_type::invalid,
                 "Unsupported PRACH configuration index (i.e., {}) for the given frequency range (i.e., {}) and "
                 "duplex mode (i.e., {}).",
                 cell.prach_config_index,
                 to_string(cell.freq_range),
                 to_string(cell.duplex));


    // -- Populate the per-cell upper PHY configuration --------------------
    upper_phy_cell.nof_tx_ports               = cell.nof_tx_antennas;
    upper_phy_cell.nof_rx_ports               = cell.nof_rx_antennas;
    // Resource-grid pool: depth (slots) + 2 for double-buffering.
    upper_phy_cell.nof_dl_rg                  = dl_pipeline_depth + 2;
    upper_phy_cell.nof_ul_rg                  = ul_pipeline_depth;
    // PRACH buffer count: enough to cover the pipeline plus a margin for late arrivals.
    upper_phy_cell.nof_prach_buffer           = du_low.expert_phy_cfg.max_processing_delay_slots + 2;
    upper_phy_cell.max_nof_td_prach_occasions = prach_cfg.nof_occasions_within_slot; // From the standard table.
    upper_phy_cell.max_nof_fd_prach_occasions = 1; // One freq-domain occasion per slot in typical configs.
    upper_phy_cell.is_prach_long_format       = is_long_preamble(prach_cfg.format);
    upper_phy_cell.nof_dl_processors          = dl_pipeline_depth;
    upper_phy_cell.dl_bw_rb                   = bw_rb;
    upper_phy_cell.ul_bw_rb                   = bw_rb;
    upper_phy_cell.pusch_max_nof_layers       = cell.pusch_max_nof_layers;
    upper_phy_cell.active_scs                 = {};
    // Mark this cell's SCS as active (bit array indexed by numerology value).
    upper_phy_cell.active_scs[to_numerology_value(cell.scs_common)] = true;

    // Rx buffer config (PUSCH HARQ soft-bits storage).
    upper_phy_cell.rx_buffer_config.nof_buffers                     = nof_buffers;
    upper_phy_cell.rx_buffer_config.nof_codeblocks                  = max_rx_nof_codeblocks;
    upper_phy_cell.rx_buffer_config.max_codeblock_size              = ldpc::MAX_CODEBLOCK_SIZE;
    upper_phy_cell.rx_buffer_config.expire_timeout_slots            = expire_pusch_harq_timeout_slots;
    // false = soft bits live in host memory, not on an external accelerator.
    upper_phy_cell.rx_buffer_config.external_soft_bits              = false;


    // Final validity gate — if any computed value is out of range, abort cleanly.
    if (!is_valid_upper_phy_config(upper_phy_cell)) {
      report_error("Invalid upper PHY configuration.\n");
    }
  }


  return out_config;
}


// =============================================================================
// generate_o_du_low_config()  — public entry point.
//   Just a thin wrapper delegating to the static generate_du_low_config().
// =============================================================================
void ocudu::generate_o_du_low_config(odu::o_du_low_config&                           out_config,
                                     const du_low_unit_config&                       du_low_unit_cfg,
                                     span<const o_du_low_unit_config::du_low_config> cells)
{
  out_config.du_low_cfg = generate_du_low_config(du_low_unit_cfg, cells);
}


// =============================================================================
// fill_du_low_worker_manager_config()  — public entry point.
//   Tells the worker manager what thread-pool slots the DU-Low needs.
//   If HW-accel (BBDEV) is present, the concurrency limits are pinned to the
//   number of hardware queues because there's no benefit adding more software
//   threads than hardware queues.
// =============================================================================
void ocudu::fill_du_low_worker_manager_config(worker_manager_config&    config,
                                              const du_low_unit_config& unit_cfg,
                                              unsigned                  is_blocking_mode_active,
                                              span<const unsigned>      nof_dl_antennas,
                                              span<const unsigned>      nof_ul_antennas)
{
  // Sanity: the caller should pass one antenna count per cell.
  report_error_if_not(nof_dl_antennas.size() == nof_ul_antennas.size(),
                      "The length of nof_dl_antennas ({}) must be equal to the length of nof_ul_antennas ({}), which "
                      "should match the number of cells.",
                      nof_dl_antennas.size(),
                      nof_ul_antennas.size());


  // Add the DU-Low section to the global worker manager config.
  auto& du_low_cfg = config.du_low_cfg.emplace();


  du_low_cfg.is_sequential_mode_active = is_blocking_mode_active;
  // Copy per-cell antenna counts (the worker manager sizes its pools with these).
  du_low_cfg.cell_nof_dl_antennas.assign(nof_dl_antennas.begin(), nof_dl_antennas.end());
  du_low_cfg.cell_nof_ul_antennas.assign(nof_ul_antennas.begin(), nof_ul_antennas.end());


  // Start with whatever the user requested.
  unsigned max_pdsch_concurrency         = unit_cfg.expert_execution_cfg.threads.max_pdsch_concurrency;
  unsigned max_pusch_and_srs_concurrency = unit_cfg.expert_execution_cfg.threads.max_pusch_and_srs_concurrency;

  // Override PDSCH and PUSCH maximum concurrency if hardware acceleration is present.

  // ---- Override concurrency if a hardware accelerator is present ----------
  // The hardware has a fixed number of queues; adding more software threads
  // than queues just causes contention, so we clamp to the HW queue count.
  if (unit_cfg.hal_config.has_value()) {
    const du_low_unit_hal_config& hal_config = *unit_cfg.hal_config;
    if (hal_config.bbdev_hwacc.has_value()) {
      const bbdev_appconfig& bbdev_hwacc = *hal_config.bbdev_hwacc;

      // Override PDSCH concurrency to the number of encoder HW functions.
      if (bbdev_hwacc.pdsch_enc.has_value()) {
        const hwacc_pdsch_appconfig& pdsch_enc = *bbdev_hwacc.pdsch_enc;
        if (max_pdsch_concurrency != pdsch_enc.nof_hwacc) {
          fmt::print("Warning: the configured maximum PDSCH concurrency ({}) is overridden by the number of PDSCH "
                     "encoder hardware accelerated functions ({})\n",
                     max_pdsch_concurrency,
                     pdsch_enc.nof_hwacc);
          max_pdsch_concurrency = pdsch_enc.nof_hwacc;
        }
      }

      // Override PUSCH+SRS concurrency to the number of decoder HW functions.
      if (bbdev_hwacc.pusch_dec.has_value()) {
        const hwacc_pusch_appconfig& pusch_dec = *bbdev_hwacc.pusch_dec;
        if (max_pusch_and_srs_concurrency != pusch_dec.nof_hwacc) {
          fmt::print("Warning: the configured maximum PUSCH and SRS concurrency ({}) is overridden by the number of "
                     "PUSCH decoder hardware accelerated functions ({})\n",
                     max_pusch_and_srs_concurrency,
                     pusch_dec.nof_hwacc);
          max_pusch_and_srs_concurrency = pusch_dec.nof_hwacc;
        }
      }
    }
  }


  du_low_cfg.max_pdsch_concurrency         = max_pdsch_concurrency;
  du_low_cfg.max_pucch_concurrency         = unit_cfg.expert_execution_cfg.threads.max_pucch_concurrency;
  du_low_cfg.max_pusch_and_srs_concurrency = max_pusch_and_srs_concurrency;
  du_low_cfg.executor_tracing_enable       = unit_cfg.tracer.executor_tracing_enable;
}
