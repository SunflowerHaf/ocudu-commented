// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/modulation/ofdm_modulator_impl.h  (95 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "phase_compensation_lut.h"
#include "ocudu/phy/generic_functions/dft_processor.h"
#include "ocudu/phy/lower/modulation/ofdm_modulator.h"
#include "ocudu/ran/cyclic_prefix.h"


namespace ocudu {

/// OFDM modulator dependencies. Provides the necessary dependency instances.

/// OFDM modulator dependencies. Provides the necessary dependency instances.
struct ofdm_modulator_dependencies {
  /// DFT instance. The ownership is transferred to the modulator.
  /// DFT instance. The ownership is transferred to the modulator.
  std::unique_ptr<dft_processor> dft;
};

/// Describes a generic OFDM symbol modulator.

/// Describes a generic OFDM symbol modulator.
class ofdm_symbol_modulator_impl : public ofdm_symbol_modulator
{
  /// Indicates the DFT size.
  /// Indicates the DFT size.
  unsigned dft_size;
  /// Indicates the resource grid bandwidth in resource elements.
  /// Indicates the resource grid bandwidth in resource elements.
  unsigned rg_size;
  /// Cyclic prefix type.
  /// Cyclic prefix type.
  cyclic_prefix cp;
  /// Numerology.
  /// Numerology.
  subcarrier_spacing scs;
  /// Sampling rate in Hz.
  /// Sampling rate in Hz.
  unsigned sampling_rate_Hz;
  /// Scaling factor at the DFT output.
  /// Scaling factor at the DFT output.
  float scale;
  /// DFT processor.
  /// DFT processor.
  std::unique_ptr<dft_processor> dft;
  /// Phase compensation look-up table.
  /// Phase compensation look-up table.
  phase_compensation_lut phase_compensation_table;
  /// Current center frequency in Hertz.
  /// Current center frequency in Hertz.
  double current_center_freq_Hz;
  /// Next center frequency in Hertz.
  /// Next center frequency in Hertz.
  std::atomic<double> next_center_freq_Hz;


public:
  /// \brief Constructs an OFDM symbol modulator.
  /// \param[in] ofdm_config  Provides generic OFDM configuration parameters.
  /// \param[in] dependencies Provides specific dependencies.
  /// \brief Constructs an OFDM symbol modulator.
  /// \param[in] ofdm_config  Provides generic OFDM configuration parameters.
  /// \param[in] dependencies Provides specific dependencies.
  ofdm_symbol_modulator_impl(const ofdm_modulator_configuration& ofdm_config, ofdm_modulator_dependencies dependencies);

  // See the interface for documentation.

  // See the interface for documentation.
  unsigned get_symbol_size(unsigned symbol_index) const override
  {
    return cp.get_length(symbol_index, scs).to_samples(sampling_rate_Hz) + dft_size;
  }

  // See the interface for documentation.

  // See the interface for documentation.
  void set_center_frequency(double center_frequency_Hz) override
  {
    next_center_freq_Hz.store(center_frequency_Hz, std::memory_order_relaxed);
  }

  // See the interface for documentation.

  // See the interface for documentation.
  void
  modulate(span<cf_t> ouput, const resource_grid_reader& grid, unsigned port_index, unsigned symbol_index) override;
};

/// Describes a generic OFDM slot modulator.

/// Describes a generic OFDM slot modulator.
class ofdm_slot_modulator_impl : public ofdm_slot_modulator
{
  /// Cyclic prefix type.
  /// Cyclic prefix type.
  cyclic_prefix cp;
  /// Resource grid numerology.
  /// Resource grid numerology.
  unsigned numerology;
  /// Instance of symbol modulator.
  /// Instance of symbol modulator.
  std::unique_ptr<ofdm_symbol_modulator> symbol_modulator;


public:
  /// \brief Constructs an OFDM slot modulator.
  /// \param[in] ofdm_config       OFDM factory parameters.
  /// \param[in] symbol_modulator_ OFDM symbol modulator instance.
  /// \brief Constructs an OFDM slot modulator.
  /// \param[in] ofdm_config       OFDM factory parameters.
  /// \param[in] symbol_modulator_ OFDM symbol modulator instance.
  ofdm_slot_modulator_impl(const ofdm_modulator_configuration&    ofdm_config,
                           std::unique_ptr<ofdm_symbol_modulator> symbol_modulator_) :
    cp(ofdm_config.cp), numerology(ofdm_config.numerology), symbol_modulator(std::move(symbol_modulator_))
  {
    ocudu_assert(symbol_modulator, "Invalid OFDM symbol modulator.");
  }

  // See interface for documentation;

  // See interface for documentation;
  unsigned get_slot_size(unsigned slot_index) const override;

  // See interface for documentation;

  // See interface for documentation;
  void modulate(span<cf_t> output, const resource_grid_reader& grid, unsigned port_index, unsigned slot_index) override;
};


} // namespace ocudu
