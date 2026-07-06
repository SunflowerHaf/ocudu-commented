// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/modulation/ofdm_prach_demodulator_impl.h  (50 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/slotted_array.h"
#include "ocudu/phy/generic_functions/dft_processor.h"
#include "ocudu/phy/lower/modulation/ofdm_prach_demodulator.h"
#include "ocudu/phy/lower/sampling_rate.h"
#include "ocudu/phy/support/prach_buffer.h"
#include "ocudu/ran/prach/prach_subcarrier_spacing.h"
#include "ocudu/support/error_handling.h"


namespace ocudu {

/// Describes a generic OFDM PRACH demodulator.

/// Describes a generic OFDM PRACH demodulator.
class ofdm_prach_demodulator_impl : public ofdm_prach_demodulator
{
public:
  using dft_processors_table = slotted_id_table<prach_subcarrier_spacing,
                                                std::unique_ptr<dft_processor>,
                                                static_cast<unsigned>(prach_subcarrier_spacing::invalid)>;

  /// \brief Builds a PRACH OFDM demodulator.
  ///
  /// \param[in] srate_          Sampling rate.
  /// \param[in] dft_processors_ Table with one DFT processor for each of the possible RA subcarrier spacings.
  /// \remark An assertion is triggered if \c dft_processors_ do not contain a valid DFT processor for each of the
  /// possible random access subcarrier spacings.

  /// \brief Builds a PRACH OFDM demodulator.
  ///
  /// \param[in] srate_          Sampling rate.
  /// \param[in] dft_processors_ Table with one DFT processor for each of the possible RA subcarrier spacings.
  /// \remark An assertion is triggered if \c dft_processors_ do not contain a valid DFT processor for each of the
  /// possible random access subcarrier spacings.
  ofdm_prach_demodulator_impl(sampling_rate srate_, dft_processors_table dft_processors_) :
    srate(srate_), dft_processors(std::move(dft_processors_))
  {
    for (const auto& dft_proc : dft_processors) {
      ocudu_assert(dft_proc, "Invalid DFT processor.");
      ocudu_assert(dft_proc->get_direction() == dft_processor::direction::DIRECT, "Invalid DFT processor direction.");
    }
  }

  // See interface for documentation.

  // See interface for documentation.
  void demodulate(prach_buffer& buffer, span<const cf_t> input, const configuration& config) override;


private:
  /// Sampling rate.
  /// Sampling rate.
  sampling_rate srate;
  /// DFT processor table.
  /// DFT processor table.
  dft_processors_table dft_processors;
};


} // namespace ocudu
