// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Transform precoding interfaces.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/generic_functions/transform_precoding/transform_precoder.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Transform precoding interfaces.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"


namespace ocudu {

/// \brief Transform precoder interface.
///
/// The transform precoding process is described in TS38.211 Section 6.3.1.4 for PUSCH and Section 6.3.2.6.4 for PUCCH.
///

/// \brief Transform precoder interface.
///
/// The transform precoding process is described in TS38.211 Section 6.3.1.4 for PUSCH and Section 6.3.2.6.4 for PUCCH.
///
class transform_precoder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~transform_precoder() = default;

  /// \brief Reverts the transform precoding for a single OFDM symbol.
  ///
  /// The number of elements to deprecode \f$M_{sc}\f$ determines the number of resource blocks
  /// \f$M_{RB} = \frac{M_{sc}}{N_{sc}^{RB}}\f$.
  ///
  /// The function \ref transform_precoding::is_nof_prbs_valid determines whether a number of resource blocks is valid.
  ///
  /// \param[out] out Transform deprecoding output.
  /// \param[in]  in  Transform deprecoding input.
  /// \remark An assertion is triggered if the size of \c in and \c out are not equal.
  /// \remark An assertion is triggered if the number of RB to deprecode is invalid.
  /// \remark An assertion is triggered if the number of RB exceeds the maximum initialized number of RB.

  /// \brief Reverts the transform precoding for a single OFDM symbol.
  ///
  /// The number of elements to deprecode \f$M_{sc}\f$ determines the number of resource blocks
  /// \f$M_{RB} = \frac{M_{sc}}{N_{sc}^{RB}}\f$.
  ///
  /// The function \ref transform_precoding::is_nof_prbs_valid determines whether a number of resource blocks is valid.
  ///
  /// \param[out] out Transform deprecoding output.
  /// \param[in]  in  Transform deprecoding input.
  /// \remark An assertion is triggered if the size of \c in and \c out are not equal.
  /// \remark An assertion is triggered if the number of RB to deprecode is invalid.
  /// \remark An assertion is triggered if the number of RB exceeds the maximum initialized number of RB.
  virtual void deprecode_ofdm_symbol(span<cf_t> out, span<const cf_t> in) = 0;

  /// \brief Calculates the resultant noise variance after reverting the transform precoding operation.
  ///
  /// Noise variances that are NaN, infinite or negative are not taken into account neither for the calculation of mean
  /// nor overwriting.
  /// \param[out] out Resultant noise variance.
  /// \param[in]  in  Input noise variance for each resource element.

  /// \brief Calculates the resultant noise variance after reverting the transform precoding operation.
  ///
  /// Noise variances that are NaN, infinite or negative are not taken into account neither for the calculation of mean
  /// nor overwriting.
  /// \param[out] out Resultant noise variance.
  /// \param[in]  in  Input noise variance for each resource element.
  virtual void deprecode_ofdm_symbol_noise(span<float> out, span<const float> in) = 0;
};


} // namespace ocudu
