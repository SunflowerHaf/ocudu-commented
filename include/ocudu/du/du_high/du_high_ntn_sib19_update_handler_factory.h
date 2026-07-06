// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_high/du_high_ntn_sib19_update_handler_factory.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ntn/ntn_sib19_update_handler.h"
#include <memory>


namespace ocudu {


namespace odu {
class du_configurator;
}

/// \brief Create NTN SIB19 msg update handler.
///
/// \param du_cfgtr DU configurator interface.
/// \return NTN SIB19 msg update handler.

/// \brief Create NTN SIB19 msg update handler.
///
/// \param du_cfgtr DU configurator interface.
/// \return NTN SIB19 msg update handler.
std::unique_ptr<ocudu_ntn::ntn_sib19_update_handler> create_ntn_sib19_update_handler(odu::du_configurator& du_cfgtr);


} // namespace ocudu
