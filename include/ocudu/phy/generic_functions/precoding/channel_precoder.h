// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Channel precoder interface.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/generic_functions/precoding/channel_precoder.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Channel precoder interface.

#pragma once


#include "ocudu/phy/support/precoding_configuration.h"
#include "ocudu/phy/support/re_buffer.h"


namespace ocudu {

/// Channel precoder interface.

/// Channel precoder interface.
class channel_precoder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~channel_precoder() = default;

  /// \brief Applies a set of precoding weights to the input resource elements.
  ///
  /// \param[out] output   Output symbols, indexed by RE and antenna port.
  /// \param[in] input     Input symbols, indexed by RE and transmit layer.
  /// \param[in] precoding Precoding coefficients arranged in matrix form, indexed by transmit layer and antenna port.
  /// \remark An assertion is triggered if the output buffer does not have the same number of RE per port as the number
  /// of RE per layer of the input buffer.
  /// \remark An assertion is triggered if the precoding matrix dimensions do not match the number of layers of the
  /// input buffer and the number of antenna ports of the output buffer.

  /// \brief Applies a set of precoding weights to the input resource elements.
  ///
  /// \param[out] output   Output symbols, indexed by RE and antenna port.
  /// \param[in] input     Input symbols, indexed by RE and transmit layer.
  /// \param[in] precoding Precoding coefficients arranged in matrix form, indexed by transmit layer and antenna port.
  /// \remark An assertion is triggered if the output buffer does not have the same number of RE per port as the number
  /// of RE per layer of the input buffer.
  /// \remark An assertion is triggered if the precoding matrix dimensions do not match the number of layers of the
  /// input buffer and the number of antenna ports of the output buffer.
  virtual void apply_precoding(re_buffer_writer<cbf16_t>&     output,
                               const re_buffer_reader<>&      input,
                               const precoding_weight_matrix& precoding) const = 0;

  /// \brief Maps the input symbols into layers and applies a set of precoding weights.
  /// \param[out] output   Output symbols, indexed by RE and antenna port.
  /// \param[in] input     Input symbols.
  /// \param[in] precoding Precoding coefficients arranged in matrix form, indexed by transmit layer and antenna port.
  /// \remark An assertion is triggered if the output buffer does not have the same number of RE per port as the number
  /// of RE per layer of the input buffer.
  /// \remark An assertion is triggered if the precoding matrix dimensions are not consistent with input buffer size and
  /// the number of antenna ports of the output buffer.

  /// \brief Maps the input symbols into layers and applies a set of precoding weights.
  /// \param[out] output   Output symbols, indexed by RE and antenna port.
  /// \param[in] input     Input symbols.
  /// \param[in] precoding Precoding coefficients arranged in matrix form, indexed by transmit layer and antenna port.
  /// \remark An assertion is triggered if the output buffer does not have the same number of RE per port as the number
  /// of RE per layer of the input buffer.
  /// \remark An assertion is triggered if the precoding matrix dimensions are not consistent with input buffer size and
  /// the number of antenna ports of the output buffer.
  virtual void apply_layer_map_and_precoding(re_buffer_writer<cbf16_t>&     output,
                                             span<const ci8_t>              input,
                                             const precoding_weight_matrix& precoding) const = 0;
};


} // namespace ocudu
