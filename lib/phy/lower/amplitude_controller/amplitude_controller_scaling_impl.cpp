// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/amplitude_controller/amplitude_controller_scaling_impl.cpp  (19 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "amplitude_controller_scaling_impl.h"
#include "ocudu/ocuduvec/sc_prod.h"


using namespace ocudu;


amplitude_controller_metrics amplitude_controller_scaling_impl::process(span<cf_t> output, span<const cf_t> input)
{
  ocudu_ocuduvec_assert_size(output, input);

  // Apply scaling factor.

  // Apply scaling factor.
  ocuduvec::sc_prod(output, input, amplitude_gain);

  // Return empty metrics.

  // Return empty metrics.
  return {0.0F, 0.0F, 0.0F, 0.0F, 0UL, 0UL, 0.0, false};
}
