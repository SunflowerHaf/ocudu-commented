// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/ofh/ru_ofh_executor_mapper_factory.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ru/ofh/ru_ofh_executor_mapper.h"
#include <memory>
#include <vector>


namespace ocudu {


class task_executor;

/// Configuration of the Open Fronthaul RU executor mapper.

/// Configuration of the Open Fronthaul RU executor mapper.
struct ru_ofh_executor_mapper_config {
  /// Number of sectors.
  /// Number of sectors.
  unsigned nof_sectors;
  /// Executor dedicated to IQ sample compression and OFH message serialization.
  /// Executor dedicated to IQ sample compression and OFH message serialization.
  task_executor* downlink_executor;
  /// Executor dedicated to IQ sample decompression and OFH message deserialization.
  /// Executor dedicated to IQ sample decompression and OFH message deserialization.
  task_executor* uplink_executor;
  /// Set of executors dedicated to Ethernet messages reception and transmission for all configured sectors.
  /// Set of executors dedicated to Ethernet messages reception and transmission for all configured sectors.
  std::vector<task_executor*> txrx_executors;
  /// A single timing executor for all sectors.
  /// A single timing executor for all sectors.
  task_executor* timing_executor = nullptr;
};

/// \brief Creates an executor mapper for the Open Fronthaul RU implementation.
///
/// \remark An assertion is triggered if number of downlink and uplink executors doesn't match the number of sectors.

/// \brief Creates an executor mapper for the Open Fronthaul RU implementation.
///
/// \remark An assertion is triggered if number of downlink and uplink executors doesn't match the number of sectors.
std::unique_ptr<ru_ofh_executor_mapper> create_ofh_ru_executor_mapper(const ru_ofh_executor_mapper_config& config);


} // namespace ocudu
