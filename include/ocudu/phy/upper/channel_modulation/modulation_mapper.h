// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_modulation/modulation_mapper.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bit_buffer.h"
#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"
#include "ocudu/ran/sch/modulation_scheme.h"


namespace ocudu {

/// \brief Modulation mapper public interface.
///
/// Maps bits to complex symbols as specified in TS38.211 Section 5.1.

/// \brief Modulation mapper public interface.
///
/// Maps bits to complex symbols as specified in TS38.211 Section 5.1.
class modulation_mapper
{
public:
  /// Gets the modulation scaling factor.
  /// Gets the modulation scaling factor.
  static float get_modulation_scaling(modulation_scheme);

  /// Default destructor.

  /// Default destructor.
  virtual ~modulation_mapper() = default;

  /// \brief Maps a sequence of bits to a sequence of floating point complex symbols according to the given modulation
  /// scheme.
  ///
  /// \param[in]  input   The sequence of bits. Each entry corresponds to a single bit.
  /// \param[out] symbols The resulting sequence of complex-valued symbols.
  /// \param[in]  scheme  The modulation scheme determining the mapping.
  /// \remark The length of \c input should be equal to the length of \c symbols times the modulation order (that is,
  /// the number of bits per modulated symbol).

  /// \brief Maps a sequence of bits to a sequence of floating point complex symbols according to the given modulation
  /// scheme.
  ///
  /// \param[in]  input   The sequence of bits. Each entry corresponds to a single bit.
  /// \param[out] symbols The resulting sequence of complex-valued symbols.
  /// \param[in]  scheme  The modulation scheme determining the mapping.
  /// \remark The length of \c input should be equal to the length of \c symbols times the modulation order (that is,
  /// the number of bits per modulated symbol).
  virtual void modulate(span<cf_t> symbols, const bit_buffer& input, modulation_scheme scheme) = 0;

  /// \brief Maps a sequence of bits to a sequence of 8-bit integer complex symbols according to the given modulation
  /// scheme.
  ///
  /// \param[in]  input   The sequence of bits. Each entry corresponds to a single bit.
  /// \param[out] symbols The resulting sequence of complex-valued symbols.
  /// \param[in]  scheme  The modulation scheme determining the mapping.
  /// \remark The length of \c input should be equal to the length of \c symbols times the modulation order (that is,
  /// the number of bits per modulated symbol).
  /// \return The scaling factor applied to the mapped symbols.

  /// \brief Maps a sequence of bits to a sequence of 8-bit integer complex symbols according to the given modulation
  /// scheme.
  ///
  /// \param[in]  input   The sequence of bits. Each entry corresponds to a single bit.
  /// \param[out] symbols The resulting sequence of complex-valued symbols.
  /// \param[in]  scheme  The modulation scheme determining the mapping.
  /// \remark The length of \c input should be equal to the length of \c symbols times the modulation order (that is,
  /// the number of bits per modulated symbol).
  /// \return The scaling factor applied to the mapped symbols.
  virtual float modulate(span<ci8_t> symbols, const bit_buffer& input, modulation_scheme scheme) = 0;
};


} // namespace ocudu
