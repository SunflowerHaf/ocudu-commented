// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/helpers/ru_sdr_logger_registrator.h  (24 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ru_sdr_config.h"


namespace ocudu {

/// Registers the SDR Radio Unit loggers in the logger service.

/// Registers the SDR Radio Unit loggers in the logger service.
inline void register_ru_sdr_logs(const ru_sdr_unit_logger_config& log_cfg)
{
  ocudulog::basic_logger& phy_logger = ocudulog::fetch_basic_logger("PHY", true);
  phy_logger.set_level(log_cfg.phy_level);


  ocudulog::basic_logger& rf_logger = ocudulog::fetch_basic_logger("RF", false);
  rf_logger.set_level(log_cfg.radio_level);


  ocudulog::basic_logger& ru_logger = ocudulog::fetch_basic_logger("RU", true);
  ru_logger.set_level(log_cfg.radio_level);
}


} // namespace ocudu
