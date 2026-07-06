// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_translators.cpp
 * @brief Implementation of gNB-level config translation into the worker manager format.
 *
 * This file is small but important: it's where the gNB-level (shared/main)
 * thread pool settings from the YAML config become part of the
 * worker_manager_config that actually drives thread creation in main().
 *
 * It's called from gnb.cpp's main() after the CU-CP, CU-UP, and DU units
 * have already filled in their own portions of the worker_manager_config —
 * this function fills in the remaining "main pool" fields, which is the
 * shared thread pool used for tasks that aren't specific to any one of the
 * three protocol stack units (e.g. the command-line interface thread,
 * general I/O tasks).
 */

#include "gnb_appconfig_translators.h"
#include "apps/services/worker_manager/worker_manager_config.h"
#include "gnb_appconfig.h"


using namespace ocudu;
using namespace std::chrono_literals;


/**
 * @brief Fills the gNB-level (main pool) fields of the worker manager config.
 *
 * Asserts that the CU-UP and DU High worker configs have already been
 * filled in by the time this runs — this function only adds to an
 * already-partially-populated config, it doesn't create it from scratch.
 *
 * Copies four values directly from the YAML config's expert_execution
 * section into the worker_manager_config:
 *   - Number of threads in the shared main pool.
 *   - The main pool's task queue size (how many pending tasks can be
 *     queued before backpressure kicks in).
 *   - The backoff period (how long a thread waits before retrying when its
 *     queue is empty — a power-saving/CPU-efficiency tuning knob).
 *   - The CPU affinity configuration (which cores the main pool threads are
 *     pinned to).
 *
 * @param config   The worker_manager_config to update (modified in place).
 * @param app_cfg  The gNB application config containing the source values.
 */
void ocudu::fill_gnb_worker_manager_config(worker_manager_config& config, const gnb_appconfig& app_cfg)
{
  ocudu_assert(config.cu_up_cfg, "CU-UP worker config does not exist");
  ocudu_assert(config.du_hi_cfg, "DU high worker config does not exist");


  config.nof_main_pool_threads     = app_cfg.expert_execution_cfg.threads.main_pool.nof_threads;
  config.main_pool_task_queue_size = app_cfg.expert_execution_cfg.threads.main_pool.task_queue_size;
  config.main_pool_backoff_period =
      std::chrono::microseconds{app_cfg.expert_execution_cfg.threads.main_pool.backoff_period};
  config.main_pool_affinity_cfg = app_cfg.expert_execution_cfg.affinities.main_pool_cpu_cfg;
}
