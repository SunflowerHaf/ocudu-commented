// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/support/resource_usage/powercap_energy_reader_impl.h  (30 lines)
//
// LIBRARY: lib/support
// General-purpose C++ utilities: async task executors, thread pools, timer manager, memory pools, span/expected/bounded_integer types, signal dispatcher, config parsers, format helpers, synchronisation primitives (stop_event, sync_event), and versioning. Not 5G-specific — these could be a standalone C++ utility library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "ocudu/support/resource_usage/power_consumption.h"


namespace ocudu {
namespace resource_usage_utils {

/// This class reads energy consumption using Powercap RAPL (Run Time Average Power Limiting) sysfs.

/// This class reads energy consumption using Powercap RAPL (Run Time Average Power Limiting) sysfs.
class sysfs_powercap_reader : public energy_consumption_reader
{
public:
  // See interface for documentation.
  // See interface for documentation.
  energy_consumption read_consumed_energy() const override;


private:
  /// Converts string read from sysfs to uint64.
  /// Converts string read from sysfs to uint64.
  uint64_t parse_uint64(const std::string& value) const;

  /// Read value from the given file and store its value in the provided variable.

  /// Read value from the given file and store its value in the provided variable.
  void read_value_from_sysfs(const std::string& sysfs_path, uint64_t& value_uj) const;
};

/// Creates Powercap RAPL sysfs reader if it is supported by the system.

/// Creates Powercap RAPL sysfs reader if it is supported by the system.
std::unique_ptr<energy_consumption_reader> build_sysfs_powercap_reader(ocudulog::basic_logger& logger);


} // namespace resource_usage_utils
} // namespace ocudu
