// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_up/o_cu_up_factory.h  (18 lines)
//
// INTERFACE HEADER — include/ocudu/cu_up
// CU-UP public interfaces: o_cu_up (top-level), cu_up_operation_controller, the GTP-U tunnel management interface, and the N3 endpoint interface. These are the seams between the CU-UP library and the application layer above it.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_up/o_cu_up.h"
#include "ocudu/cu_up/o_cu_up_config.h"
#include <memory>


namespace ocudu {
namespace ocuup {

/// O-RAN CU-UP interface with the given configuration and dependencies.

/// O-RAN CU-UP interface with the given configuration and dependencies.
std::unique_ptr<o_cu_up> create_o_cu_up(const o_cu_up_config& config, o_cu_up_dependencies&& dependencies);


} // namespace ocuup
} // namespace ocudu
