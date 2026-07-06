// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Amplitude controller implementation using clipping.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/amplitude_controller/amplitude_controller_clipping_impl.h  (51 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Amplitude controller implementation using clipping.

#pragma once


#include "ocudu/phy/lower/amplitude_controller/amplitude_controller.h"
#include "ocudu/support/math/math_utils.h"


namespace ocudu {

/// Clipping amplitude controller implementation.

/// Clipping amplitude controller implementation.
class amplitude_controller_clipping_impl : public amplitude_controller
{
  /// Enables or disables the clipping process.
  /// Enables or disables the clipping process.
  bool clipping_enabled;
  /// Gain factor applied to the input signal, before the clipping process.
  /// Gain factor applied to the input signal, before the clipping process.
  float amplitude_gain;
  /// Squared value of the amplitude corresponding to the radio device's full scale power.
  /// Squared value of the amplitude corresponding to the radio device's full scale power.
  float full_scale_pwr;
  /// Maximum amplitude allowed by the clipping.
  /// Maximum amplitude allowed by the clipping.
  float ceiling_lin;
  /// Runtime metrics reported by the amplitude controller.
  /// Runtime metrics reported by the amplitude controller.
  amplitude_controller_metrics metrics = {0.0F, 0.0F, 0.0F, 0.0F, 0UL, 0UL, 0.0, false};


public:
  /// \brief Constructs an amplitude controller.
  /// \param[in] enable_clipping Enables or disables the clipping process.
  /// \param[in] input_gain_dB  Sets the gain factor in dB applied to the input signal.
  /// \param[in] full_scale_lin Sets the full scale amplitude reference used to determine the amplitude ceiling.
  /// \param[in] ceiling_dBFS Sets the clipping amplitude ceiling in dB, relative to the full scale amplitude.
  /// \brief Constructs an amplitude controller.
  /// \param[in] enable_clipping Enables or disables the clipping process.
  /// \param[in] input_gain_dB  Sets the gain factor in dB applied to the input signal.
  /// \param[in] full_scale_lin Sets the full scale amplitude reference used to determine the amplitude ceiling.
  /// \param[in] ceiling_dBFS Sets the clipping amplitude ceiling in dB, relative to the full scale amplitude.
  amplitude_controller_clipping_impl(bool  enable_clipping,
                                     float input_gain_dB,
                                     float full_scale_lin,
                                     float ceiling_dBFS) :
    clipping_enabled(enable_clipping),
    amplitude_gain(convert_dB_to_amplitude(input_gain_dB)),
    full_scale_pwr(full_scale_lin * full_scale_lin),
    ceiling_lin(full_scale_lin * convert_dB_to_amplitude(ceiling_dBFS))
  {
    // Do nothing.
    // Do nothing.
  }

  // See interface for documentation.

  // See interface for documentation.
  amplitude_controller_metrics process(span<cf_t> output, span<const cf_t> input) override;
};


} // namespace ocudu.
