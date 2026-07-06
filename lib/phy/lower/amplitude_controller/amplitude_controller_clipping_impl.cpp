// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/amplitude_controller/amplitude_controller_clipping_impl.cpp  (50 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "amplitude_controller_clipping_impl.h"
#include "ocudu/ocuduvec/clip.h"
#include "ocudu/ocuduvec/compare.h"
#include "ocudu/ocuduvec/dot_prod.h"
#include "ocudu/ocuduvec/sc_prod.h"


using namespace ocudu;


amplitude_controller_metrics amplitude_controller_clipping_impl::process(span<cf_t> output, span<const cf_t> input)
{
  ocudu_ocuduvec_assert_size(output, input);

  // Report clipping status.

  // Report clipping status.
  metrics.clipping_enabled = clipping_enabled;

  // Apply the gain factor.

  // Apply the gain factor.
  metrics.gain_dB = convert_amplitude_to_dB(amplitude_gain);
  ocuduvec::sc_prod(output, input, amplitude_gain);

  // Compute Mean and Peak signal power.

  // Compute Mean and Peak signal power.
  float avg_power  = ocuduvec::average_power(output);
  float peak_power = ocuduvec::max_abs_element(output).second;

  // Normalize power to full scale.

  // Normalize power to full scale.
  metrics.avg_power_fs  = avg_power / full_scale_pwr;
  metrics.peak_power_fs = peak_power / full_scale_pwr;


  if ((!std::isnormal(avg_power)) || (!std::isnormal(peak_power))) {
    // If the signal has zero power, do nothing.
    // If the signal has zero power, do nothing.
    metrics.papr_lin = 1.0F;
    return metrics;
  }

  // Compute signal PAPR.

  // Compute signal PAPR.
  metrics.papr_lin = peak_power / avg_power;


  if (clipping_enabled) {
    // Clip the signal and count the number of clipped and processed samples.
    // Clip the signal and count the number of clipped and processed samples.
    metrics.nof_processed_samples += input.size();
    metrics.nof_clipped_samples += ocuduvec::clip_iq(output, output, ceiling_lin);
    metrics.clipping_probability =
        static_cast<double>(metrics.nof_clipped_samples) / static_cast<double>(metrics.nof_processed_samples);
  }


  return metrics;
}
