// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/dummy/ru_dummy_executor_mapper.h  (29 lines)
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

/// Dummy RU executor mapper interface.

/// Dummy RU executor mapper interface.
class ru_dummy_executor_mapper
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ru_dummy_executor_mapper() = default;

  /// Retrieves the dummy RU executor reference.

  /// Retrieves the dummy RU executor reference.
  virtual task_executor& common_executor() = 0;
};

/// Creates an RU dummyu implementation executor mapper from a single task executor.

/// Creates an RU dummyu implementation executor mapper from a single task executor.
std::unique_ptr<ru_dummy_executor_mapper> create_ru_dummy_executor_mapper(task_executor& executor);


} // namespace ocudu
