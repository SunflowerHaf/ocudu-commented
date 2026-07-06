// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: ntn/ntn_logger_registrator.h
//
// Purpose (plain English):
//   Registers the "NTN" log channel with the logger service. NTN stands for
//   Non-Terrestrial Network — the feature that allows the gNB to serve UEs
//   via satellite (LEO or GEO). The NTN channel logs satellite orbit
//   propagation, Doppler compensation calculations, and SIB19 updates.
//   Only registered when at least one cell has an [ntn] YAML block.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ocudulog/ocudulog.h"


namespace ocudu {

/// Registers the NTN loggers in the logger service.

/// Registers the NTN logger channel at the requested log level.
inline void register_ntn_loggers(const ocudulog::basic_levels& ntn_level)
{
  auto& ntn_logger = ocudulog::fetch_basic_logger("NTN", true);
  ntn_logger.set_level(ntn_level);
}


} // namespace ocudu
