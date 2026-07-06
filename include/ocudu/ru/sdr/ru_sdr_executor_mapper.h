// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/sdr/ru_sdr_executor_mapper.h  (133 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/executors/task_executor.h"
#include <memory>
#include <vector>


namespace ocudu {


class task_executor;

/// Interface used to access different executors used in an SDR Radio Unit sector.

/// Interface used to access different executors used in an SDR Radio Unit sector.
class ru_sdr_sector_executor_mapper
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ru_sdr_sector_executor_mapper() = default;

  /// Retrieves lower physical layer executor for downlink modulation.

  /// Retrieves lower physical layer executor for downlink modulation.
  virtual task_executor& downlink_executor() = 0;

  /// Retrieves lower physical layer executor for uplink demodulation.

  /// Retrieves lower physical layer executor for uplink demodulation.
  virtual task_executor& uplink_executor() = 0;

  /// Retrieves lower physical layer executor for PRACH demodulation.

  /// Retrieves lower physical layer executor for PRACH demodulation.
  virtual task_executor& prach_executor() = 0;

  /// Retrieves lower physical layer executor for baseband transmission.

  /// Retrieves lower physical layer executor for baseband transmission.
  virtual task_executor& transmitter_executor() = 0;

  /// Retrieves lower physical layer executor for baseband reception.

  /// Retrieves lower physical layer executor for baseband reception.
  virtual task_executor& receiver_executor() = 0;
};

/// \brief SDR RU executor mapper interface.
///
/// Provides access to the different sector executor mappers.

/// \brief SDR RU executor mapper interface.
///
/// Provides access to the different sector executor mappers.
class ru_sdr_executor_mapper
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ru_sdr_executor_mapper() = default;

  /// \brief Retrieves the sector executor mapper for a given sector index.
  ///
  /// \remark An assertion is triggered if the sector index exceeds the number of executor configurations.

  /// \brief Retrieves the sector executor mapper for a given sector index.
  ///
  /// \remark An assertion is triggered if the sector index exceeds the number of executor configurations.
  virtual ru_sdr_sector_executor_mapper& get_sector_mapper(unsigned index) = 0;

  /// Retrieves the sector executor mapper via closed braces operator.

  /// Retrieves the sector executor mapper via closed braces operator.
  ru_sdr_sector_executor_mapper& operator[](unsigned cell_index) { return get_sector_mapper(cell_index); }

  /// Retrieves baseband radio house-keeping executor.

  /// Retrieves baseband radio house-keeping executor.
  virtual task_executor& asynchronous_radio_executor() = 0;
};

/// Collects the SDR RU executor mapper dependencies for sequential baseband operation.

/// Collects the SDR RU executor mapper dependencies for sequential baseband operation.
struct ru_sdr_executor_mapper_sequential_configuration {
  /// Asynchronous executor.
  /// Asynchronous executor.
  task_executor* asynchronous_exec;
  /// Common executor for all sectors.
  /// Common executor for all sectors.
  task_executor* common_exec;
  /// Number of sectors.
  /// Number of sectors.
  unsigned nof_sectors;
};

/// Collects the SDR RU executor mapper dependencies for a single baseband thread.

/// Collects the SDR RU executor mapper dependencies for a single baseband thread.
struct ru_sdr_executor_mapper_single_configuration {
  /// Common radio executor.
  /// Common radio executor.
  task_executor* radio_exec;
  /// High priority executor for downlink modulation, and uplink demodulation.
  /// High priority executor for downlink modulation, and uplink demodulation.
  task_executor* high_prio_executor;
  /// Dedicated baseband executor per cell basis.
  /// Dedicated baseband executor per cell basis.
  std::vector<task_executor*> baseband_exec;
};

/// Collects the SDR RU executor mapper dependencies for a dual baseband executor.

/// Collects the SDR RU executor mapper dependencies for a dual baseband executor.
struct ru_sdr_executor_mapper_dual_configuration {
  /// Collects transmit and receive baseband executors.
  /// Collects transmit and receive baseband executors.
  struct cell_executors {
    /// Baseband transmitter executor.
    /// Baseband transmitter executor.
    task_executor* tx_exec;
    /// Baseband receiver executor.
    /// Baseband receiver executor.
    task_executor* rx_exec;
  };

  /// Common radio executor.

  /// Common radio executor.
  task_executor* radio_exec;
  /// High priority executor for downlink modulation, and uplink demodulation.
  /// High priority executor for downlink modulation, and uplink demodulation.
  task_executor* high_prio_executor;
  /// Dedicated baseband executor per cell basis.
  /// Dedicated baseband executor per cell basis.
  std::vector<cell_executors> baseband_exec;
};

/// Collects the SDR RU executor mapper dependencies for a triple baseband executor.

/// Collects the SDR RU executor mapper dependencies for a triple baseband executor.
struct ru_sdr_executor_mapper_triple_configuration {
  /// Collects transmit and receive baseband executors.
  /// Collects transmit and receive baseband executors.
  struct cell_executors {
    /// Baseband transmitter executor.
    /// Baseband transmitter executor.
    task_executor* tx_exec;
    /// Baseband receiver executor.
    /// Baseband receiver executor.
    task_executor* rx_exec;
    /// Baseband uplink executor.
    /// Baseband uplink executor.
    task_executor* ul_exec;
  };

  /// Common radio executor.

  /// Common radio executor.
  task_executor* radio_exec;
  /// High priority executor for downlink modulation, and uplink demodulation.
  /// High priority executor for downlink modulation, and uplink demodulation.
  task_executor* high_prio_executor;
  /// Dedicated baseband executor per cell basis.
  /// Dedicated baseband executor per cell basis.
  std::vector<cell_executors> baseband_exec;
};

/// Creates an SDR RU executor mapper from a sequential baseband executor configuration.

/// Creates an SDR RU executor mapper from a sequential baseband executor configuration.
std::unique_ptr<ru_sdr_executor_mapper>
create_ru_sdr_executor_mapper(const ru_sdr_executor_mapper_sequential_configuration& config);

/// Creates an SDR RU executor mapper from a single baseband executor configuration.

/// Creates an SDR RU executor mapper from a single baseband executor configuration.
std::unique_ptr<ru_sdr_executor_mapper>
create_ru_sdr_executor_mapper(const ru_sdr_executor_mapper_single_configuration& config);

/// Creates an SDR RU executor mapper from a dual baseband executor configuration.

/// Creates an SDR RU executor mapper from a dual baseband executor configuration.
std::unique_ptr<ru_sdr_executor_mapper>
create_ru_sdr_executor_mapper(const ru_sdr_executor_mapper_dual_configuration& config);

/// Creates an SDR RU executor mapper from a triple baseband executor configuration.

/// Creates an SDR RU executor mapper from a triple baseband executor configuration.
std::unique_ptr<ru_sdr_executor_mapper>
create_ru_sdr_executor_mapper(const ru_sdr_executor_mapper_triple_configuration& config);


} // namespace ocudu
