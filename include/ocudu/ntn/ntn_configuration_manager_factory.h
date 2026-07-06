// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ntn/ntn_configuration_manager_factory.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/ntn
// NTN interface headers: orbit_propagator (interface for computing satellite positions at future times), the propagator factory, and the ephemeris data types used by the NTN Doppler compensation subsystem.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <memory>


namespace ocudu {


struct ntn_config;


namespace ocudu_ntn {


class ntn_configuration_manager;
struct ntn_configuration_manager_config;
struct ntn_configuration_manager_dependencies;

/// NTN Configuration Manager factory interface with the given configuration and dependencies.

/// NTN Configuration Manager factory interface with the given configuration and dependencies.
std::unique_ptr<ntn_configuration_manager>
create_ntn_configuration_manager(const ntn_configuration_manager_config& ntn_config,
                                 ntn_configuration_manager_dependencies  dependencies);


} // namespace ocudu_ntn
} // namespace ocudu
