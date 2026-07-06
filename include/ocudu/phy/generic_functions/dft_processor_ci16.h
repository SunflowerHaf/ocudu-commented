// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/generic_functions/dft_processor_ci16.h  (52 lines)
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

/// \brief Describes a Discrete Fourier Transform (DFT) processor interface for 16-bit complex integer values.
///
/// The DFT in 16-bit complex integer output is divided by the DFT size independently of the direction.

/// \brief Describes a Discrete Fourier Transform (DFT) processor interface for 16-bit complex integer values.
///
/// The DFT in 16-bit complex integer output is divided by the DFT size independently of the direction.
class dft_processor_ci16
{
public:
  /// DFT algorithm direction.
  /// DFT algorithm direction.
  enum class direction {
    /// Converts a time-domain signal into a frequency-domain signal.
    /// Converts a time-domain signal into a frequency-domain signal.
    direct = 0,
    /// Converts a frequency-domain signal into a time-domain signal.
    /// Converts a frequency-domain signal into a time-domain signal.
    inverse
  };

  /// Collects the DFT parameters.

  /// Collects the DFT parameters.
  struct configuration {
    /// DFT size.
    /// DFT size.
    unsigned size;
    /// DFT direction (direct or inverse).
    /// DFT direction (direct or inverse).
    direction dir;
  };

  /// Converts a DFT direction to string.

  /// Converts a DFT direction to string.
  static std::string direction_to_string(direction dir) { return dir == direction::direct ? "direct" : "inverse"; }

  /// Default destructor.

  /// Default destructor.
  virtual ~dft_processor_ci16() = default;

  /// Gets the DFT direction.

  /// Gets the DFT direction.
  virtual direction get_direction() const = 0;

  /// Gets the DFT number of points.

  /// Gets the DFT number of points.
  virtual unsigned get_size() const = 0;

  /// \brief Executes the DFT from the internal input data.
  /// \return A view of the internal output DFT buffer.
  /// \remark An assertion is triggered if the input and output sizes do not match the DFT size.

  /// \brief Executes the DFT from the internal input data.
  /// \return A view of the internal output DFT buffer.
  /// \remark An assertion is triggered if the input and output sizes do not match the DFT size.
  virtual void run(span<ci16_t> out, span<const ci16_t> in) = 0;
};


} // namespace ocudu
