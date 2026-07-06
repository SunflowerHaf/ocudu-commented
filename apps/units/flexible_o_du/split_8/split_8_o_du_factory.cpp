// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/split_8_o_du_factory.cpp  (22 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "split_8_o_du_factory.h"
#include "helpers/ru_sdr_factories.h"


using namespace ocudu;


split8_du_factory::split8_du_factory(const split_8_o_du_unit_config& config_) :
  flexible_o_du_factory({config_.odu_high_cfg,
                         config_.du_low_cfg,
                         {config_.ru_cfg.metrics_cfg.metrics_cfg, config_.ru_cfg.metrics_cfg.enable_ru_metrics}}),
  unit_config(config_)
{
}


std::unique_ptr<radio_unit> split8_du_factory::create_radio_unit(const flexible_o_du_ru_config&       ru_config,
                                                                 const flexible_o_du_ru_dependencies& ru_dependencies)
{
  return create_sdr_radio_unit(unit_config.ru_cfg, ru_config, ru_dependencies);
}
