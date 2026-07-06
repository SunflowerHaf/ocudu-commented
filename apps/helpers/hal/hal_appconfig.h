// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/hal/hal_appconfig.h
//
// Purpose (plain English):
//   The top-level application-layer config for the Hardware Abstraction Layer
//   (HAL). In this codebase the HAL currently means DPDK (Data Plane
//   Development Kit) — the Intel-maintained high-performance networking
//   library also used to drive FPGA/ASIC accelerators.
//
//   eal_args is the raw string of DPDK EAL (Environment Abstraction Layer)
//   command-line arguments passed when DPDK is initialised. For example:
//     "--lcores 0@2,1@3 --no-shconf"
//   The exact content depends entirely on the server's NIC and CPU topology.
//   In standard UHD/USRP builds without DPDK this struct is never populated.
// =============================================================================
#pragma once

#include <string>

namespace ocudu {

/// HAL configuration of the application.
struct hal_appconfig {
  /// EAL configuration arguments.
  std::string eal_args; ///< DPDK EAL initialisation argument string.
};

} // namespace ocudu
