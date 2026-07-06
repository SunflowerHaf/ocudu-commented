// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/helpers/ru_sdr_config_validator.h  (33 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ru_sdr_config.h"
#include "ocudu/ran/bs_channel_bandwidth.h"
#include "ocudu/ran/duplex_mode.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/prach/prach_preamble_information.h"
#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {

/// SDR cell configuration for validation.

/// SDR cell configuration for validation.
struct ru_sdr_cell_validation_config {
  /// Cell subcarrier spacing.
  /// Cell subcarrier spacing.
  subcarrier_spacing common_scs;
  /// PRACH format.
  /// PRACH format.
  prach_format_type prach_format;
  /// PRACH preamble information.
  /// PRACH preamble information.
  prach_preamble_information preamble_info;
  /// Channel bandwidth in MHz.
  /// Channel bandwidth in MHz.
  bs_channel_bandwidth channel_bw_mhz;
  /// Duplex mode.
  /// Duplex mode.
  duplex_mode dplx_mode;
};

/// Validates the given SDR Radio Unit configuration. Returns true on success, false otherwise.

/// Validates the given SDR Radio Unit configuration. Returns true on success, false otherwise.
bool validate_ru_sdr_config(const ru_sdr_unit_config& config, span<const ru_sdr_cell_validation_config> cell_config);


} // namespace ocudu
