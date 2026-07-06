// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/generic_functions/dft_processor.h  (57 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"


namespace ocudu {

/// \brief Describes a Discrete Fourier Transform (DFT) processor.
/// \remark The DFT processor allocates the input and output buffers for optimization purposes.
/// \remark The input buffer is available using get_input().
/// \remark The output buffer is available using run().

/// \brief Describes a Discrete Fourier Transform (DFT) processor.
/// \remark The DFT processor allocates the input and output buffers for optimization purposes.
/// \remark The input buffer is available using get_input().
/// \remark The output buffer is available using run().
class dft_processor
{
public:
  /// Indicates the DFT direction.
  /// Indicates the DFT direction.
  enum class direction {
    /// \brief Converts a time domain signal into frequency domain.
    /// \remark For the FFTW based libraries, it is equivalent to \c FFTW_FORWARD sign.
    /// \brief Converts a time domain signal into frequency domain.
    /// \remark For the FFTW based libraries, it is equivalent to \c FFTW_FORWARD sign.
    DIRECT = 0,
    /// \brief Converts a frequency domain signal into frequency (inverse DFT).
    /// \remark For the FFTW based libraries, it is equivalent to \c FFTW_BACKWARD sign.
    /// \brief Converts a frequency domain signal into frequency (inverse DFT).
    /// \remark For the FFTW based libraries, it is equivalent to \c FFTW_BACKWARD sign.
    INVERSE
  };

  /// Describes the DFT parameters.

  /// Describes the DFT parameters.
  struct configuration {
    /// Indicates the DFT size.
    /// Indicates the DFT size.
    unsigned size;
    /// Indicates if the DFT is direct or inverse.
    /// Indicates if the DFT is direct or inverse.
    direction dir;
  };

  /// Converts a DFT direction to string.

  /// Converts a DFT direction to string.
  static std::string direction_to_string(direction dir) { return dir == direction::DIRECT ? "direct" : "inverse"; }

  /// Default destructor.

  /// Default destructor.
  virtual ~dft_processor() = default;

  /// \brief Gets the DFT direction.

  /// \brief Gets the DFT direction.
  virtual direction get_direction() const = 0;

  /// \brief Gets the DFT number of points.

  /// \brief Gets the DFT number of points.
  virtual unsigned get_size() const = 0;

  /// \brief Gets a view of the internal input DFT buffer.

  /// \brief Gets a view of the internal input DFT buffer.
  virtual span<cf_t> get_input() = 0;

  /// \brief Executes the DFT from the internal input data.
  /// \return A view of the internal output DFT buffer.

  /// \brief Executes the DFT from the internal input data.
  /// \return A view of the internal output DFT buffer.
  virtual span<const cf_t> run() = 0;
};


} // namespace ocudu
