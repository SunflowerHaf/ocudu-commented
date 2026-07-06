// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_sdr_executor_mapper.cpp
 * @brief Maps lower PHY processing tasks to specific CPU thread executors.
 *
 * The "executor mapper" is the bridge between the abstract concept of "I need
 * a thread for downlink processing" and the actual worker_manager-created
 * thread pools. It implements the four lower_phy_thread_profile variants
 * described in ru_sdr_config.h (blocking, single, dual, triple), each
 * assigning Tx, Rx, downlink, uplink, and PRACH processing to different
 * combinations of threads:
 *
 *   SEQUENTIAL (blocking — ZMQ only): All tasks except Tx/Rx run inline
 *     (on whichever thread calls them) — used only for the synchronous ZMQ
 *     loopback backend, never for real hardware since it can't meet real-time
 *     deadlines.
 *
 *   SINGLE (< 4 CPU cores): Downlink and PRACH run on a shared high-priority
 *     thread; uplink runs inline; Tx and Rx share one baseband executor per cell.
 *
 *   DUAL (4-7 CPU cores): Same as single, but Tx and Rx get separate dedicated
 *     executors per cell (still no dedicated uplink thread).
 *
 *   TRIPLE (8+ CPU cores): Full separation — downlink, uplink, PRACH, Tx, and
 *     Rx each get their own dedicated thread per cell. Minimises inter-thread
 *     contention and gives the lowest processing latency.
 *
 * This file is purely an internal implementation detail; the public interface
 * (ru_sdr_executor_mapper, ru_sdr_sector_executor_mapper) is declared in
 * include/ocudu/ru/sdr/ru_sdr_executor_mapper.h.
 */

#include "ocudu/ru/sdr/ru_sdr_executor_mapper.h"
#include "ocudu/support/executors/inline_task_executor.h" ///< inline_task_executor — runs tasks synchronously, no thread hop
#include "ocudu/support/ocudu_assert.h"


using namespace ocudu;


namespace {


/**
 * @brief Per-sector executor mapper: holds the five thread executors for one cell.
 *
 * Each cell sector needs five different processing roles. This class simply
 * stores references to the chosen executors for one sector and exposes them
 * via the ru_sdr_sector_executor_mapper interface.
 */
class ru_sdr_sector_executor_mapper_impl : public ru_sdr_sector_executor_mapper
{
public:
  /**
   * @param dl_exec_     Executor for downlink OFDM modulation tasks.
   * @param ul_exec_     Executor for uplink OFDM demodulation tasks.
   * @param prach_exec_  Executor for PRACH preamble detection tasks.
   * @param tx_exec_     Executor for sending IQ samples to the radio.
   * @param rx_exec_     Executor for receiving IQ samples from the radio.
   */
  ru_sdr_sector_executor_mapper_impl(task_executor& dl_exec_,
                                     task_executor& ul_exec_,
                                     task_executor& prach_exec_,
                                     task_executor& tx_exec_,
                                     task_executor& rx_exec_) :


    dl_exec(dl_exec_), ul_exec(ul_exec_), prach_exec(prach_exec_), tx_exec(tx_exec_), rx_exec(rx_exec_)
  {
  }


  task_executor& downlink_executor() override { return dl_exec; }
  task_executor& uplink_executor() override { return ul_exec; }
  task_executor& prach_executor() override { return prach_exec; }
  task_executor& transmitter_executor() override { return tx_exec; }
  task_executor& receiver_executor() override { return rx_exec; }


private:
  task_executor& dl_exec;
  task_executor& ul_exec;
  task_executor& prach_exec;
  task_executor& tx_exec;
  task_executor& rx_exec;
};


/**
 * @brief Top-level executor mapper: holds one ru_sdr_sector_executor_mapper_impl per cell.
 *
 * Has four constructors, one for each lower_phy_thread_profile (sequential,
 * single, dual, triple). Each constructor implements the assignment strategy
 * for that profile, building the appropriate executor references for every
 * configured sector.
 */
class ru_sdr_executor_mapper_impl : public ru_sdr_executor_mapper
{
public:
  /**
   * @brief SEQUENTIAL profile constructor — used only for ZMQ (blocking mode).
   *
   * All processing runs synchronously on the inline_executor (i.e. directly
   * on whichever thread calls into the lower PHY) except Tx and Rx, which
   * use the shared common_exec. Not suitable for real-time hardware operation.
   *
   * @param config  Sequential mode config: a common executor for Tx/Rx and
   *                an asynchronous executor for UHD driver calls.
   */
  explicit ru_sdr_executor_mapper_impl(const ru_sdr_executor_mapper_sequential_configuration& config)
  {
    ocudu_assert(config.asynchronous_exec != nullptr, "Invalid asynchronous executor.");
    ocudu_assert(config.common_exec != nullptr, "Invalid common executor.");


    async_exec = config.asynchronous_exec;


    for (unsigned i_sector = 0; i_sector != config.nof_sectors; ++i_sector) {
      task_executor& dl_exec    = inline_executor; // Synchronous — no real-time guarantee
      task_executor& ul_exec    = inline_executor; // Synchronous
      task_executor& prach_exec = inline_executor; // Synchronous
      task_executor& tx_exec    = *config.common_exec; // Shared across all sectors
      task_executor& rx_exec    = *config.common_exec; // Shared across all sectors
      sectors.emplace_back(dl_exec, ul_exec, prach_exec, tx_exec, rx_exec);
    }
  }


  /**
   * @brief SINGLE profile constructor — used when < 4 CPU cores are available.
   *
   * One dedicated high-priority thread handles downlink and PRACH for ALL
   * sectors. Uplink runs inline (synchronously, no dedicated thread). Each
   * sector gets its own baseband executor shared between Tx and Rx.
   *
   * @param config  Single mode config: a radio executor (async UHD calls),
   *                a high-priority executor (shared dl/prach), and one
   *                baseband executor per sector (shared tx/rx).
   */
  explicit ru_sdr_executor_mapper_impl(const ru_sdr_executor_mapper_single_configuration& config)
  {
    ocudu_assert(config.radio_exec != nullptr, "Invalid radio executor.");
    ocudu_assert(config.high_prio_executor != nullptr, "Invalid high priority executor.");


    async_exec = config.radio_exec;


    for (const auto& baseband_exec : config.baseband_exec) {
      ocudu_assert(baseband_exec != nullptr, "Invalid baseband cell executor.");


      task_executor& dl_exec    = *config.high_prio_executor; // Shared across sectors
      task_executor& ul_exec    = inline_executor; // No dedicated thread
      task_executor& prach_exec = *config.high_prio_executor; // Shared across sectors
      task_executor& tx_exec    = *baseband_exec; // One per sector, shared Tx/Rx
      task_executor& rx_exec    = *baseband_exec; // Same executor as Tx


      sectors.emplace_back(dl_exec, ul_exec, prach_exec, tx_exec, rx_exec);
    }
  }


  /**
   * @brief DUAL profile constructor — used when 4-7 CPU cores are available.
   *
   * Same downlink/PRACH sharing as SINGLE, but Tx and Rx now get separate
   * dedicated executors per sector instead of sharing one — reducing
   * contention between transmit and receive processing.
   *
   * @param config  Dual mode config: radio executor, high-priority executor
   *                (shared dl/prach), and per-sector tx/rx baseband executors.
   */
  explicit ru_sdr_executor_mapper_impl(const ru_sdr_executor_mapper_dual_configuration& config)
  {
    ocudu_assert(config.radio_exec != nullptr, "Invalid radio executor.");
    ocudu_assert(config.high_prio_executor != nullptr, "Invalid high priority executor.");


    async_exec = config.radio_exec;


    for (const auto& baseband_exec : config.baseband_exec) {
      ocudu_assert(baseband_exec.rx_exec != nullptr, "Invalid receive baseband cell executor.");
      ocudu_assert(baseband_exec.tx_exec != nullptr, "Invalid transmit baseband cell executor.");


      task_executor& dl_exec    = *config.high_prio_executor; // Shared across sectors
      task_executor& ul_exec    = inline_executor; // Still no dedicated thread
      task_executor& prach_exec = *config.high_prio_executor; // Shared across sectors
      task_executor& tx_exec    = *baseband_exec.tx_exec; // Dedicated per sector
      task_executor& rx_exec    = *baseband_exec.rx_exec; // Dedicated per sector, separate from Tx


      sectors.emplace_back(dl_exec, ul_exec, prach_exec, tx_exec, rx_exec);
    }
  }


  /**
   * @brief TRIPLE profile constructor — used when 8+ CPU cores are available.
   *
   * Full separation: every sector gets its own dedicated downlink, uplink,
   * PRACH, Tx, and Rx executor. This is the lowest-latency, highest
   * isolation configuration, recommended for production deployments with
   * sufficient CPU resources.
   *
   * @param config  Triple mode config: radio executor, high-priority executor
   *                (shared dl/prach), and per-sector tx/rx/ul baseband executors.
   */
  explicit ru_sdr_executor_mapper_impl(const ru_sdr_executor_mapper_triple_configuration& config)
  {
    ocudu_assert(config.radio_exec != nullptr, "Invalid radio executor.");
    ocudu_assert(config.high_prio_executor != nullptr, "Invalid high priority executor.");


    async_exec = config.radio_exec;


    for (const auto& baseband_exec : config.baseband_exec) {
      ocudu_assert(baseband_exec.rx_exec != nullptr, "Invalid receive baseband cell executor.");
      ocudu_assert(baseband_exec.tx_exec != nullptr, "Invalid transmit baseband cell executor.");
      ocudu_assert(baseband_exec.ul_exec != nullptr, "Invalid baseband demodulator cell executor.");


      task_executor& dl_exec    = *config.high_prio_executor; // Shared across sectors
      task_executor& ul_exec    = *baseband_exec.ul_exec; // Dedicated per sector (unlike single/dual)
      task_executor& prach_exec = *config.high_prio_executor; // Shared across sectors
      task_executor& tx_exec    = *baseband_exec.tx_exec; // Dedicated per sector
      task_executor& rx_exec    = *baseband_exec.rx_exec; // Dedicated per sector


      sectors.emplace_back(dl_exec, ul_exec, prach_exec, tx_exec, rx_exec);
    }
  }


  /// Returns the executor mapper for the given sector index.
  ru_sdr_sector_executor_mapper& get_sector_mapper(unsigned index) override { return sectors[index]; }


  /// Returns the asynchronous radio executor (for non-real-time UHD driver calls).
  task_executor& asynchronous_radio_executor() override { return *async_exec; }


private:
  /// One executor mapper per configured sector.
  std::vector<ru_sdr_sector_executor_mapper_impl> sectors;
  /// Executor for asynchronous (non-real-time) UHD driver calls.
  task_executor*                                  async_exec;
  /// Shared inline (synchronous) executor used by profiles that don't assign
  /// a dedicated thread to a particular task (e.g. uplink in single/dual mode).
  inline_task_executor                            inline_executor;
};


} // namespace


/// Creates the executor mapper for the SEQUENTIAL (blocking/ZMQ) profile.
std::unique_ptr<ru_sdr_executor_mapper>
ocudu::create_ru_sdr_executor_mapper(const ru_sdr_executor_mapper_sequential_configuration& config)
{
  return std::make_unique<ru_sdr_executor_mapper_impl>(config);
}


/// Creates the executor mapper for the SINGLE thread profile.
std::unique_ptr<ru_sdr_executor_mapper>
ocudu::create_ru_sdr_executor_mapper(const ocudu::ru_sdr_executor_mapper_single_configuration& config)
{
  return std::make_unique<ru_sdr_executor_mapper_impl>(config);
}


/// Creates the executor mapper for the DUAL thread profile.
std::unique_ptr<ru_sdr_executor_mapper>
ocudu::create_ru_sdr_executor_mapper(const ocudu::ru_sdr_executor_mapper_dual_configuration& config)
{
  return std::make_unique<ru_sdr_executor_mapper_impl>(config);
}


/// Creates the executor mapper for the TRIPLE thread profile.
std::unique_ptr<ru_sdr_executor_mapper>
ocudu::create_ru_sdr_executor_mapper(const ocudu::ru_sdr_executor_mapper_triple_configuration& config)
{
  return std::make_unique<ru_sdr_executor_mapper_impl>(config);
}
