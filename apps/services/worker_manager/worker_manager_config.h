// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/worker_manager/worker_manager_config.h
//
// Purpose (plain English):
//   The central configuration bag for the worker manager: nested structs for each subsystem's thread-pool requirements (RU-SDR, RU-OFH, DU-Low, DU-High, CU-UP, CU-CP), PCAP executor flags, CPU affinity masks, and the main thread pool size. Populated piecemeal by fill_*_worker_manager_config() calls during startup.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "os_sched_affinity_manager.h"


namespace ocudu {


class timer_manager;
class executor_metrics_channel_registry;

/// Worker manager configuration.

/// Worker manager configuration.
struct worker_manager_config {
  /// RU OFH worker configuration.
  /// RU OFH worker configuration.
  struct ru_ofh_config {
    /// Number of cells.
    /// Number of cells.
    unsigned nof_cells;
    /// RU timing CPU affinity mask.
    /// RU timing CPU affinity mask.
    os_sched_affinity_bitmask ru_timing_cpu;
    /// Vector of affinities for the txrx workers.
    /// Vector of affinities for the txrx workers.
    std::vector<os_sched_affinity_bitmask> txrx_affinities;
  };

  /// RU SDR worker configuration.

  /// RU SDR worker configuration.
  struct ru_sdr_config {
    /// Lower physical layer thread profiles.
    /// Lower physical layer thread profiles.
    enum class lower_phy_thread_profile {
      /// Sequential mode - it guarantees that the entire physical layer operates in sequential mode using a single
      /// executor. This mode might not satisfy with real-time timings.
      /// Sequential mode - it guarantees that the entire physical layer operates in sequential mode using a single
      /// executor. This mode might not satisfy with real-time timings.
      sequential = 0,
      /// Single task worker for all the baseband processing.
      /// Single task worker for all the baseband processing.
      single,
      /// Two task workers - one for baseband reception and another for baseband transmission.
      /// Two task workers - one for baseband reception and another for baseband transmission.
      dual,
      /// Dedicated task workers for each of the subtasks (transmission, reception and demodulation).
      /// Dedicated task workers for each of the subtasks (transmission, reception and demodulation).
      triple
    };


    lower_phy_thread_profile profile;
    unsigned                 nof_cells;
  };

  /// RU dummy worker configuration.

  /// RU dummy worker configuration.
  struct ru_dummy_config {};

  /// DU low worker configuration.

  /// DU low worker configuration.
  struct du_low_config {
    bool     is_sequential_mode_active;
    unsigned max_pucch_concurrency;
    unsigned max_pusch_and_srs_concurrency;
    unsigned max_pdsch_concurrency;
    /// Number of downlink antennas indexed by cell. The vector size must match the number of cells.
    /// Number of downlink antennas indexed by cell. The vector size must match the number of cells.
    std::vector<unsigned> cell_nof_dl_antennas;
    /// Number of uplink antennas indexed by cell. The vector size must match the number of cells.
    /// Number of uplink antennas indexed by cell. The vector size must match the number of cells.
    std::vector<unsigned> cell_nof_ul_antennas;
    /// Whether to enable task tracing.
    /// Whether to enable task tracing.
    bool executor_tracing_enable;
  };

  /// DU high executor configuration.

  /// DU high executor configuration.
  struct du_high_config {
    /// DU-high UE data related tasks queue size.
    /// DU-high UE data related tasks queue size.
    unsigned ue_data_tasks_queue_size;
    /// DU high number of cells.
    /// DU high number of cells.
    unsigned nof_cells;
    /// Real-time mode enabled flag.
    /// Real-time mode enabled flag.
    bool is_rt_mode_enabled;
    /// Whether to enable task tracing.
    /// Whether to enable task tracing.
    bool executor_tracing_enable;
  };

  /// CU-UP executor configuration

  /// CU-UP executor configuration
  struct cu_up_config {
    unsigned max_nof_ue_strands = 16;
    /// UE task queue size.
    /// UE task queue size.
    uint32_t dl_ue_executor_queue_size   = 2048;
    uint32_t ul_ue_executor_queue_size   = 2048;
    uint32_t ctrl_ue_executor_queue_size = 2048;
    /// Maximum batch size used in CU-UP strands.
    /// Maximum batch size used in CU-UP strands.
    unsigned strand_batch_size = 256;
    /// Wether to offload socket TX to a dedicated strand.
    /// Wether to offload socket TX to a dedicated strand.
    bool dedicated_io_ul_strand = true;
    /// Whether to enable task tracing.
    /// Whether to enable task tracing.
    bool executor_tracing_enable = false;
    /// Whether to skip CU-UP executors when executors logging is enabled application wide.
    /// Whether to skip CU-UP executors when executors logging is enabled application wide.
    bool skip_cu_up_executor = true;
  };

  /// CU-CP executor configuration.

  /// CU-CP executor configuration.
  struct cu_cp_config {};

  /// PCAP worker configuration.

  /// PCAP worker configuration.
  struct pcap_config {
    bool is_f1ap_enabled = false;
    bool is_ngap_enabled = false;
    bool is_e1ap_enabled = false;
    bool is_xnap_enabled = false;
    bool is_e2ap_enabled = false;
    bool is_n3_enabled   = false;
    bool is_f1u_enabled  = false;
    bool is_mac_enabled  = false;
    bool is_rlc_enabled  = false;
  };

  /// Size, in number of threads, of the main thread pool.

  /// Size, in number of threads, of the main thread pool.
  std::optional<unsigned> nof_main_pool_threads;
  /// Main thread pool task queue size.
  /// Main thread pool task queue size.
  unsigned main_pool_task_queue_size;
  /// Main thread pool back-off period, in microseconds, when the task queue is empty.
  /// Main thread pool back-off period, in microseconds, when the task queue is empty.
  std::chrono::microseconds main_pool_backoff_period{50};
  /// Main thread pool CPU bitmasks.
  /// Main thread pool CPU bitmasks.
  os_sched_affinity_config main_pool_affinity_cfg;
  /// PCAP configuration.
  /// PCAP configuration.
  pcap_config pcap_cfg;
  /// Timer config.
  /// Timer config.
  timer_manager* app_timers = nullptr;
  /// Vector of affinities mask indexed by cell.
  /// Vector of affinities mask indexed by cell.
  std::vector<std::vector<os_sched_affinity_config>> config_affinities;
  /// Split 6 enabled flag.
  /// Split 6 enabled flag.
  bool is_split6_enabled = false;
  /// CU-UP configuration.
  /// CU-UP configuration.
  std::optional<cu_up_config> cu_up_cfg;
  /// CU-CP configuration.
  /// CU-CP configuration.
  std::optional<cu_cp_config> cu_cp_cfg;
  /// DU high configuration.
  /// DU high configuration.
  std::optional<du_high_config> du_hi_cfg;
  /// DU low configuration
  /// DU low configuration
  std::optional<du_low_config> du_low_cfg;
  /// RU SDR configuration.
  /// RU SDR configuration.
  std::optional<ru_sdr_config> ru_sdr_cfg;
  /// RU OFH configuration.
  /// RU OFH configuration.
  std::optional<ru_ofh_config> ru_ofh_cfg;
  /// RU dummy configuration.
  /// RU dummy configuration.
  std::optional<ru_dummy_config> ru_dummy_cfg;
  /// Executor metrics channel registry.
  /// Executor metrics channel registry.
  executor_metrics_channel_registry* exec_metrics_channel_registry;
};


} // namespace ocudu
