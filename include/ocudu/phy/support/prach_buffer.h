// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/prach_buffer.h  (61 lines)
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

/// \brief PRACH buffer interface.
///
/// Provides access to frequency-domain PRACH sequences.
///
/// A buffer for storing long PRACH sequences (\f$L_{RA}=839\f$), for a maximum of 4 OFDM symbols, can be created with
/// the factory function create_prach_buffer_long(). A buffer for storing short PRACH sequences (\f$L_{RA}=129\f$), for
/// a maximum of 12 OFDM symbols, can be created with the factory function create_prach_buffer_short().

/// \brief PRACH buffer interface.
///
/// Provides access to frequency-domain PRACH sequences.
///
/// A buffer for storing long PRACH sequences (\f$L_{RA}=839\f$), for a maximum of 4 OFDM symbols, can be created with
/// the factory function create_prach_buffer_long(). A buffer for storing short PRACH sequences (\f$L_{RA}=129\f$), for
/// a maximum of 12 OFDM symbols, can be created with the factory function create_prach_buffer_short().
class prach_buffer
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~prach_buffer() = default;

  /// Gets the maximum number of ports.

  /// Gets the maximum number of ports.
  virtual unsigned get_max_nof_ports() const = 0;

  /// Gets the maximum number of time domain occasions.

  /// Gets the maximum number of time domain occasions.
  virtual unsigned get_max_nof_td_occasions() const = 0;

  /// Gets the maximum number of frequency domain occasions.

  /// Gets the maximum number of frequency domain occasions.
  virtual unsigned get_max_nof_fd_occasions() const = 0;

  /// Gets the maximum number of symbols.

  /// Gets the maximum number of symbols.
  virtual unsigned get_max_nof_symbols() const = 0;

  /// Gets the sequence length.

  /// Gets the sequence length.
  virtual unsigned get_sequence_length() const = 0;

  /// \brief Gets a read-write PRACH symbol for a given port, occasion and symbol.
  ///
  /// \param[in] i_port        Port identifier.
  /// \param[in] i_td_occasion Time-domain occasion.
  /// \param[in] i_fd_occasion Frequency-domain occasion.
  /// \param[in] i_symbol      Symbol index within the occasion.
  /// \return A read-write view of a PRACH OFDM symbol.

  /// \brief Gets a read-write PRACH symbol for a given port, occasion and symbol.
  ///
  /// \param[in] i_port        Port identifier.
  /// \param[in] i_td_occasion Time-domain occasion.
  /// \param[in] i_fd_occasion Frequency-domain occasion.
  /// \param[in] i_symbol      Symbol index within the occasion.
  /// \return A read-write view of a PRACH OFDM symbol.
  virtual span<cbf16_t>
  get_symbol(unsigned i_port, unsigned i_td_occasion, unsigned i_fd_occasion, unsigned i_symbol) = 0;

  /// \brief Gets a read-only PRACH symbol for a given port, occasion and symbol.
  ///
  /// \param[in] i_port        Port identifier.
  /// \param[in] i_td_occasion Time-domain occasion.
  /// \param[in] i_fd_occasion Frequency-domain occasion.
  /// \param[in] i_symbol      Symbol index within the occasion.
  /// \return A read-only view of a PRACH OFDM symbol.

  /// \brief Gets a read-only PRACH symbol for a given port, occasion and symbol.
  ///
  /// \param[in] i_port        Port identifier.
  /// \param[in] i_td_occasion Time-domain occasion.
  /// \param[in] i_fd_occasion Frequency-domain occasion.
  /// \param[in] i_symbol      Symbol index within the occasion.
  /// \return A read-only view of a PRACH OFDM symbol.
  virtual span<const cbf16_t>
  get_symbol(unsigned i_port, unsigned i_td_occasion, unsigned i_fd_occasion, unsigned i_symbol) const = 0;
};


} // namespace ocudu
