// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/tx_scheme_configuration.h  (73 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_integer.h"
#include <variant>


namespace ocudu {

/// \brief Subset of PMIs addressed by TPMI, where PMIs are those supported by UEs with maximum coherence capabilities.
///
/// The UE maximum coherence capability is given by TS38.331 higher layer capability parameter \e pusch-TransCoherence
/// in TS38.331 Section 6.3.2, Information Element \e MIMO-ParametersPerBand.
///
/// The PUSCH transmission scheme codebook subset is given by the higher layer parameter \e codebookSubset in TS38.331
/// Section 6.3.2, Information Element \e PUSCH-Config.
///
/// See TS38.214, Section 6.1.1.1 for related physical layer procedures.

/// \brief Subset of PMIs addressed by TPMI, where PMIs are those supported by UEs with maximum coherence capabilities.
///
/// The UE maximum coherence capability is given by TS38.331 higher layer capability parameter \e pusch-TransCoherence
/// in TS38.331 Section 6.3.2, Information Element \e MIMO-ParametersPerBand.
///
/// The PUSCH transmission scheme codebook subset is given by the higher layer parameter \e codebookSubset in TS38.331
/// Section 6.3.2, Information Element \e PUSCH-Config.
///
/// See TS38.214, Section 6.1.1.1 for related physical layer procedures.
enum class tx_scheme_codebook_subset : unsigned {
  fully_and_partial_and_non_coherent,
  partial_and_non_coherent,
  non_coherent
};

/// Converts a transmitter scheme codebook subset to a constant string.

/// Converts a transmitter scheme codebook subset to a constant string.
inline const char* to_string(tx_scheme_codebook_subset subset)
{
  switch (subset) {
    case tx_scheme_codebook_subset::fully_and_partial_and_non_coherent:
      return "fully-and-partial-and-non-coherent";
    case tx_scheme_codebook_subset::partial_and_non_coherent:
      return "partial-and-non-coherent";
    case tx_scheme_codebook_subset::non_coherent:
    default:
      return "non-coherent";
  }
}

/// \defgroup tx_schemes PUSCH transmission schemes defined in TS 38.214 Section 6.1.1.
/// @{
/// \brief Codebook based transmit scheme.

/// \defgroup tx_schemes PUSCH transmission schemes defined in TS 38.214 Section 6.1.1.
/// @{
/// \brief Codebook based transmit scheme.
struct tx_scheme_codebook {
  /// \brief Maximum number of layers in PUSCH. Values {1,..,4}.
  ///
  /// The parameter is given by the field \e maxRank in the TS 38.331 Section 6.3.2, Information Element \e
  /// PUSCH-Config.
  /// \brief Maximum number of layers in PUSCH. Values {1,..,4}.
  ///
  /// The parameter is given by the field \e maxRank in the TS 38.331 Section 6.3.2, Information Element \e
  /// PUSCH-Config.
  bounded_integer<uint8_t, 1, 4> max_rank;
  /// \brief PUSCH precoding codebook subset.
  ///
  /// Restricts the available PMIs to those supported by the UE, according to its coherence capabilities. Its value is
  /// indicated by the higher layer parameter \e codebookSubset (see TS38.331 Section 6.3.2, Information Element \e
  /// PUSCH-Config).
  /// \brief PUSCH precoding codebook subset.
  ///
  /// Restricts the available PMIs to those supported by the UE, according to its coherence capabilities. Its value is
  /// indicated by the higher layer parameter \e codebookSubset (see TS38.331 Section 6.3.2, Information Element \e
  /// PUSCH-Config).
  tx_scheme_codebook_subset codebook_subset;


  bool operator==(const tx_scheme_codebook& rhs) const
  {
    return rhs.max_rank == max_rank && codebook_subset == rhs.codebook_subset;
  }
};
/// Non-codebook based transmission scheme.
/// Non-codebook based transmission scheme.
struct tx_scheme_non_codebook {
  // Empty.

  // Empty.

  bool operator==(const tx_scheme_non_codebook& rhs) const { return true; }
};
/// @}

/// PUSCH transmit scheme configuration.
/// @}

/// PUSCH transmit scheme configuration.
using pusch_tx_scheme_configuration = std::variant<tx_scheme_codebook, tx_scheme_non_codebook>;


} // namespace ocudu
