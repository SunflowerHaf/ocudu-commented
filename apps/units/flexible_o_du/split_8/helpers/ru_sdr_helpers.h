// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/helpers/ru_sdr_helpers.h  (19 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/subcarrier_spacing.h"
#include <cmath>


namespace ocudu {

/// Calculates the dBFS calibration value as sqrt(sampling rate / subcarrier spacing). This factor is the magnitude of a
/// single subcarrier in normalized PHY linear units equivalent to a constant signal with a power of 0 dBFS.

/// Calculates the dBFS calibration value as sqrt(sampling rate / subcarrier spacing). This factor is the magnitude of a
/// single subcarrier in normalized PHY linear units equivalent to a constant signal with a power of 0 dBFS.
inline float calculate_dBFS_calibration_value(double sampling_rate_MHz, subcarrier_spacing scs)
{
  return std::sqrt(sampling_rate_MHz * 1e3 / scs_to_khz(scs));
}


} // namespace ocudu
