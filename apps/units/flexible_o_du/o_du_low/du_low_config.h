// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_config.h
//
// Purpose (plain English):
//   Defines the configuration struct for the "O-DU Low" — the lower half of
//   the O-RAN Distributed Unit. The DU Low is responsible for the **upper
//   physical layer**: it takes MAC-layer transport blocks (from the DU High
//   above it) and does channel coding, rate matching, scrambling, modulation
//   mapping, layer mapping, precoding, and resource-grid mapping. The output
//   is a frequency-domain resource grid that is then handed to the Radio
//   Unit (RU) — which in split-8 is the lower PHY + UHD driver, in the same
//   process.
//
//   This header contains ONLY plain data structs — no logic. It defines:
//
//     * du_low_unit_expert_upper_phy_config — every "expert" knob a
//       researcher might want to tune: LDPC decoder iterations, PUSCH
//       equaliser algorithm (ZF vs MMSE), channel-estimator smoothing
//       strategy, DL processing pipeline depth, etc.
//
//     * du_low_unit_logger_config — log levels for the PHY and HAL
//       (hardware-abstraction-layer) channels.
//
//     * du_low_unit_tracer_config — enables Tracy-style tracing of PHY
//       executor tasks for performance debugging.
//
//     * du_low_unit_expert_threads_config — concurrency limits for PDSCH,
//       PUCCH, PUSCH+SRS processing. Defaults auto-scale with CPU count.
//
//     * du_low_unit_expert_execution_config — wraps the threads config.
//
//     * hwacc_pdsch_appconfig / hwacc_pusch_appconfig / bbdev_appconfig /
//       du_low_unit_hal_config — configuration for optional hardware
//       accelerators (e.g. Intel ACC100 via DPDK BBDEV). NOT USED in your
//       UHD/USRP build; these are for FPGA/ASIC PHY acceleration setups.
//
//     * du_low_unit_metrics_config — enables/disables DU-Low metrics.
//
//     * du_low_unit_config — the top-level struct that aggregates everything.
// =============================================================================

#pragma once


#include "apps/helpers/metrics/metrics_config.h"
#include "apps/services/worker_manager/os_sched_affinity_manager.h"
#include <optional>
#include <string>


namespace ocudu {

/// Expert upper physical layer configuration.

/// \brief "Expert" knobs for the upper physical layer.
///
/// These control performance/quality trade-offs in the upper PHY: how deep
/// the DL processing pipeline is (more depth = better throughput under
/// stress, worse latency), which algorithm the equaliser uses, how the
/// channel estimator handles noisy / fast-fading channels, and so on.
/// Sensible defaults are provided; most users won't touch these.
struct du_low_unit_expert_upper_phy_config {
  /// \brief Sets the maximum allowed downlink processing delay in slots.
  ///
  /// Higher values increase the downlink processing pipeline length, which improves performance and stability for
  /// demanding cell configurations, such as using large bandwidths or higher order MIMO. Higher values also increase
  /// the round trip latency of the radio link.
  /// \brief Maximum allowed downlink processing delay in slots.
  ///
  /// A "pipeline depth". Higher values increase the downlink processing
  /// pipeline length, which improves performance and stability for
  /// demanding cell configurations (large bandwidths, higher-order MIMO)
  /// because more slots can be processed in parallel. But higher values
  /// also increase the round-trip latency of the radio link. Default 5.
  unsigned max_processing_delay_slots = 5U;
  /// Number of PUSCH LDPC decoder iterations.
  /// LDPC decoder iterations for PUSCH. More = better decode chances at
  /// low SNR, at the cost of CPU time.
  unsigned pusch_decoder_max_iterations = 6;
  /// Set to true to enable the PUSCH LDPC decoder early stop.
  /// Allow the LDPC decoder to stop as soon as parity checks pass, instead
  /// of always doing the maximum iterations. Set true unless benchmarking.
  bool pusch_decoder_early_stop = true;
  /// Set to true for forcing the LDPC decoder to decode even if the number of soft bits is insufficient.
  /// Force decoding even if there aren't enough soft bits. Diagnostic only.
  bool pusch_decoder_force_decoding = false;
  /// \brief Selects a PUSCH SINR calculation method.
  ///
  /// Available methods:
  /// -\c channel_estimator: SINR is calculated by the channel estimator using the DM-RS.
  /// -\c post_equalization: SINR is calculated using the post-equalization noise variances of the equalized RE.
  /// -\c evm: SINR is obtained from the EVM of the PUSCH symbols.
  /// \brief PUSCH SINR calculation method.
  /// - channel_estimator: from the DM-RS pilots (before equalisation).
  /// - post_equalization: from the noise variance after equalising each RE.
  /// - evm:              from the error-vector magnitude of PUSCH symbols.
  std::string pusch_sinr_calc_method = "post_equalization";
  /// \brief PUSCH channel estimator frequency-domain smoothing strategy.
  ///
  /// Use one of these options:
  /// - \c filter: applies a low pass filter to the channel estimates, or
  /// - \c mean: averages the channel estimates, or
  /// - \c none: it does not apply any smoothing strategy.
  /// \brief PUSCH channel estimator frequency-domain smoothing strategy.
  /// - filter: low-pass filter across subcarriers (default; balances noise vs bias).
  /// - mean:   simple average across DM-RS positions.
  /// - none:   no smoothing at all.
  std::string pusch_channel_estimator_fd_strategy = "filter";
  /// \brief PUSCH channel estimator time-domain interpolation strategy.
  ///
  /// Use one of these options:
  /// - \c average: averages the DM-RS in time domain, or
  /// - \c interpolate: performs linear interpolation between the OFDM symbols containing DM-RS.
  ///
  /// The \c average strategy is more robust against noise and interference while \c interpolate is more robust for
  /// fast fading channels.
  /// \brief PUSCH channel estimator time-domain interpolation strategy.
  /// - average:     average DM-RS symbols in time (robust vs noise).
  /// - interpolate: linear interpolation between DM-RS symbols (robust vs fast fading).
  std::string pusch_channel_estimator_td_strategy = "average";
  /// PUSCH channel estimator CFO compensation.
  /// Whether to compensate carrier frequency offset in the channel estimator.
  bool pusch_channel_estimator_cfo_compensation = true;
  /// \brief PUSCH channel equalizer algorithm.
  ///
  /// Use one of these options:
  /// - \c zf: use zero-forcing algorithm, or
  /// - \c mmse: use minimum mean square error algorithm.
  /// \brief PUSCH channel equaliser algorithm.
  /// - zf:   zero-forcing (lower complexity, worse at low SNR).
  /// - mmse: minimum mean square error (better SNR, higher complexity).
  std::string pusch_channel_equalizer_algorithm = "zf";
  /// \brief Request headroom size in slots.
  ///
  /// The request headroom size is the number of delayed slots that the upper physical layer will accept, ie, if the
  /// current slot is M, the upper phy will consider the slot M - nof_slots_request_headroom as valid and process it.
  /// \brief Request headroom size in slots.
  ///
  /// How far "in the past" the upper PHY still accepts requests. If we're
  /// in slot M, slot M - nof_slots_request_headroom is still considered
  /// valid. Nonzero when downstream systems occasionally run late.
  unsigned nof_slots_request_headroom = 0U;
  /// \brief Allows resource grid requests on empty uplink slots.
  ///
  /// An uplink slot is considered empty when it does not contain PUCCH/PUSCH/SRS PDUs.
  /// If true, the PHY will honour empty-uplink-slot resource-grid requests
  /// (an uplink slot with no PUCCH/PUSCH/SRS PDUs). Diagnostic use.
  bool allow_request_on_empty_uplink_slot = false;
  /// Enables the PHY tap plugin if present.
  /// Enables the PHY tap plugin (an optional diagnostic hook).
  bool enable_phy_tap = false;
  /// PHY tap plugin arguments.
  /// Arguments passed to the PHY tap plugin.
  std::string phy_tap_arguments = "";
};

/// DU low logging functionalities.

/// DU-Low log-channel levels + PHY-symbol dumping options.
struct du_low_unit_logger_config {
  /// Upper physical layer log level.
  /// Upper PHY log level. Default warning to avoid drowning the log at info.
  ocudulog::basic_levels phy_level = ocudulog::basic_levels::warning;
  /// Hardware Abstraction Layer log level.
  /// HAL log level.
  ocudulog::basic_levels hal_level = ocudulog::basic_levels::warning;
  /// Set to true to log broadcasting messages and all PRACH opportunities.
  /// Also log broadcast messages (SIB, SSB) and every PRACH opportunity.
  bool broadcast_enabled = false;
  /// Maximum number of bytes to write when dumping hex arrays.
  /// Cap on how many bytes to dump for hex-encoded fields in the log.
  int hex_max_size = 0;
  /// Set to a valid file path to print the received symbols.
  /// If non-empty, path to a file where received PHY symbols are dumped.
  std::string phy_rx_symbols_filename;
  /// Set to a valid Rx port number or empty for all ports.
  /// If set, only dump this Rx port's symbols; empty = all ports.
  std::optional<unsigned> phy_rx_symbols_port = 0;
  /// If true, prints the PRACH frequency-domain symbols.
  /// If true, also dump PRACH frequency-domain symbols.
  bool phy_rx_symbols_prach = false;
};

/// DU low tracing functionalities.

/// DU-Low tracing (Tracy-style profiler) options.
struct du_low_unit_tracer_config {
  /// \brief Whether to enable tracing of the physical layer executors.
  /// Enable tracing of the physical-layer executors (task dispatch, latency).
  bool executor_tracing_enable = false;
};

/// Expert threads configuration of the gNB app.

/// \brief Thread-concurrency limits for the DU-Low.
///
/// Constructor auto-scales the defaults with the number of available CPUs.
struct du_low_unit_expert_threads_config {
  du_low_unit_expert_threads_config()
  {
    // Query the CPU topology to size PUSCH+SRS concurrency sensibly.
    unsigned nof_threads = cpu_architecture_info::get().get_host_nof_available_cpus();


    max_pucch_concurrency = 0; // 0 = no limit; PUCCH is cheap.
    if (nof_threads <= 4) {
      max_pusch_and_srs_concurrency = 1;
    } else if (nof_threads < 8) {
      max_pusch_and_srs_concurrency = 2;
    } else if (nof_threads < 16) {
      max_pusch_and_srs_concurrency = 2;
    } else {
      max_pusch_and_srs_concurrency = 4;
    }
  }

  /// Codeblock batch length for ensuring synchronous processing within the flexible PDSCH processor implementation.

  /// Sentinel: "process the whole PDSCH synchronously" (largest possible batch).
  static constexpr unsigned synchronous_cb_batch_length = std::numeric_limits<unsigned>::max();
  /// Codeblock default batch length.
  /// Default codeblock batch length for the flexible PDSCH processor.
  static constexpr unsigned default_cb_batch_length = 4;

  /// \brief PDSCH processor type.
  ///
  /// Use of one of these options:
  /// - \c auto: selects \c flexible implementation, or
  /// - \c generic: for using unoptimized PDSCH processing, or
  /// - \c flexible: for using a memory optimized processor if the number of codeblocks is smaller than \c
  /// pdsch_cb_batch_length, or a performance-optimized implementation that processes code blocks in parallel otherwise.

  /// \brief PDSCH processor type.
  /// - auto:     picks flexible (default).
  /// - generic:  unoptimised reference implementation.
  /// - flexible: memory-optimised for small TBs, parallel for large TBs.
  std::string pdsch_processor_type = "auto";
  /// \brief PDSCH codeblock-batch length per thread (flexible PDSCH processor only).
  ///
  /// Set it to \c pdsch_cb_batch_length_sync for guaranteeing synchronous processing with the most memory-optimized
  /// processor.
  /// \brief PDSCH codeblock-batch length per thread (flexible processor only).
  ///
  /// Set to synchronous_cb_batch_length to force fully-synchronous processing
  /// with the most memory-optimised path.
  unsigned pdsch_cb_batch_length = default_cb_batch_length;
  /// \brief Maximum concurrency level for PUCCH.
  ///
  /// Maximum number of threads that can concurrently process Physical Uplink Control Channel (PUCCH). Set to zero for
  /// no limitation.
  /// Maximum threads that may concurrently process PUCCH. 0 = no limit.
  unsigned max_pucch_concurrency = 0;
  /// \brief Maximum joint concurrency level for PUSCH and SRS.
  ///
  /// Maximum number of threads that can concurrently process Physical Uplink Shared Channel (PUSCH) and Sounding
  /// Reference Signals (SRS). Set to zero for no limitation.
  /// Maximum threads that may concurrently process PUSCH + SRS (they share
  /// UL sample buffers, hence one limit for both). 0 = no limit.
  unsigned max_pusch_and_srs_concurrency = 1;
  /// \brief Maximum concurrency level for PDSCH processing.
  ///
  /// Maximum number of threads that can concurrently process Physical Downlink Shared Channel (PDSCH). Set to zero for
  /// no limitation.
  ///
  /// This parameter is necessary when hardware acceleration is used to limit the number of threads accessing the
  /// physical resources.
  /// Maximum threads that may concurrently process PDSCH. 0 = no limit.
  /// Non-zero is required when HW-accelerated PDSCH is in use to bound
  /// concurrent access to the accelerator.
  unsigned max_pdsch_concurrency = 0;
};

/// Expert configuration of the gNB app.

/// Wraps the threads config into a broader "expert execution" struct
/// (which may grow to include memory / NUMA affinity options later).
struct du_low_unit_expert_execution_config {
  /// Expert thread configuration of the gNB app.
  du_low_unit_expert_threads_config threads;
};

/// Hardware-accelerated PDSCH encoder configuration of the DU low.

// -----------------------------------------------------------------------------
// The following HAL (Hardware-Abstraction-Layer) config structs are only
// relevant when a hardware PHY accelerator (e.g. Intel ACC100 via DPDK BBDEV)
// is present. They are NOT used in the USRP + software PHY build path.
// -----------------------------------------------------------------------------

/// HW-accelerated PDSCH encoder settings.
struct hwacc_pdsch_appconfig {
  /// \brief Number of hardware-accelerated PDSCH encoding functions.
  /// Number of hardware PDSCH encoder functions to use.
  unsigned nof_hwacc;
  /// \brief Operation mode of the PDSCH encoder (CB = true, TB = false [default]).
  /// If true, submit one code-block at a time (CB mode). If false, submit
  /// a whole transport block (TB mode, less overhead).
  bool cb_mode = false;
  /// \brief Maximum supported buffer size in bytes (CB mode will be forced for larger TBs). Only used in TB mode to
  /// size the mbufs.
  ///
  /// Set to the maximum supported size by default.
  /// Max supported buffer size in bytes (in TB mode). Larger TBs are auto
  /// forced into CB mode. Default = accelerator's max.
  std::optional<unsigned> max_buffer_size;
  /// \brief Type of hardware queue usage (dedicated = true [default], shared = false). In case of a shared usage, the
  /// accelerated function needs to reserve a hardware-queue for each operation.
  /// Dedicated (true) vs shared (false) hardware queue.
  bool dedicated_queue = true;
};

/// Hardware-accelerated PUSCH decoder configuration of the DU low.

/// HW-accelerated PUSCH decoder settings.
struct hwacc_pusch_appconfig {
  /// \brief Number of hardware-accelerated PUSCH decoding functions.
  /// Number of hardware PUSCH decoder functions to use.
  unsigned nof_hwacc;
  /// \brief Size of the HARQ context repository.
  ///
  /// Set to the maximum number of CBs supported by the gNB config by default.
  /// Size of the HARQ context repository. Default = max CBs allowed by config.
  std::optional<unsigned> harq_context_size;
  /// \brief Force using the host memory to implement the HARQ buffer (disabled by default).
  /// Force HARQ buffer to live in host memory (default: on-accelerator).
  bool force_local_harq = false;
  /// \brief Type of hardware queue usage (dedicated = true [default], shared = false). In case of a shared usage, the
  /// accelerated function needs to reserve a hardware-queue for each operation.
  /// Dedicated (true) vs shared (false) hardware queue.
  bool dedicated_queue = true;
};

/// BBDEV configuration of the DU low.

/// BBDEV (Intel DPDK Baseband-Device) accelerator settings.
struct bbdev_appconfig {
  /// \brief Type of BBDEV hardware-accelerator.
  /// Accelerator type string, e.g. "acc100", "acc200".
  std::string hwacc_type;
  /// \brief ID of the BBDEV-based hardware-accelerator.
  /// BBDEV device ID.
  unsigned id;
  /// \brief Structure providing the configuration of hardware-accelerated PDSCH encoding functions.
  /// Optional PDSCH encoder acceleration.
  std::optional<hwacc_pdsch_appconfig> pdsch_enc;
  /// \brief Structure providing the configuration of hardware-accelerated PUSCH decoding functions.
  /// Optional PUSCH decoder acceleration.
  std::optional<hwacc_pusch_appconfig> pusch_dec;
  /// \brief Size (in bytes) of each DPDK memory buffer (mbuf) used to exchange unencoded and unrate-matched messages
  /// with the accelerator.
  ///
  /// Set to the maximum supported size by default.
  /// Size of each raw-message DPDK mbuf. Default = max supported.
  std::optional<unsigned> msg_mbuf_size;
  /// \brief Size (in bytes) of each DPDK memory buffer (mbuf) used to exchange encoded and rate-matched messages with
  /// the accelerator.
  ///
  /// Set to the maximum supported size by default.
  /// Size of each rate-matched-message DPDK mbuf. Default = max supported.
  std::optional<unsigned> rm_mbuf_size;
  /// \brief Number of DPDK memory buffers (mbufs) in each memory pool.
  ///
  /// Set to the maximum number of CBs supported by the gNB config by default.
  /// Number of DPDK mbufs per pool. Default = max CBs allowed by config.
  std::optional<unsigned> nof_mbuf;
};

/// HAL configuration of the DU low.

/// DU-Low HAL section: currently just BBDEV. Absent (optional) in software builds.
struct du_low_unit_hal_config {
  /// BBDEV-based hardware-accelerator arguments.
  std::optional<bbdev_appconfig> bbdev_hwacc;
};

/// Metrics configuration of the DU low.

/// Enables the DU-Low metrics feed (KPIs like PDSCH TBs/s, PUSCH BLER, etc.).
struct du_low_unit_metrics_config {
  app_helpers::metrics_config common_metrics_cfg;
  bool                        enable_du_low = false;
};

/// DU low configuration.

/// \brief Full DU-Low configuration — aggregates all the sections above.
struct du_low_unit_config {
  /// Loggers.
  du_low_unit_logger_config loggers; ///< Log levels + symbol dumps.
  /// Tracers.
  du_low_unit_tracer_config tracer; ///< Executor tracing.
  /// Expert physical layer configuration.
  du_low_unit_expert_upper_phy_config expert_phy_cfg; ///< PHY algorithm knobs.
  /// Expert execution parameters for the DU low.
  du_low_unit_expert_execution_config expert_execution_cfg; ///< Threads.
  /// HAL configuration.
  std::optional<du_low_unit_hal_config> hal_config; ///< HW-accel (unused in software builds).
  /// Metrics configuration.
  du_low_unit_metrics_config metrics_cfg; ///< Metrics.
};


} // namespace ocudu
