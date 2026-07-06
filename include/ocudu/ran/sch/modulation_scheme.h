// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Modulation schemes and orders.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/sch/modulation_scheme.h  (91 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Modulation schemes and orders.

#pragma once


#include "ocudu/support/ocudu_assert.h"
#include <string>


namespace ocudu {

/// Maximum number of bits per symbol.

/// Maximum number of bits per symbol.
constexpr unsigned MODULATION_MAX_BITS_PER_SYMBOL = 8;

/// \brief Modulation schemes as described in TS38.211 Section 5.1.
///
/// Each modulation identifier is mapped to the corresponding modulation order.

/// \brief Modulation schemes as described in TS38.211 Section 5.1.
///
/// Each modulation identifier is mapped to the corresponding modulation order.
enum class modulation_scheme {
  /// 90-degree shifting Binary Phase Shift Keying (π/2-BPSK) described in TS38.211 Section 5.1.1.
  /// 90-degree shifting Binary Phase Shift Keying (π/2-BPSK) described in TS38.211 Section 5.1.1.
  PI_2_BPSK = 0,
  /// Binary Phase Shift Keying (BPSK) modulation described in TS38.211 Section 5.1.2.
  /// Binary Phase Shift Keying (BPSK) modulation described in TS38.211 Section 5.1.2.
  BPSK = 1,
  /// Quadrature Phase Shift Keying (QPSK) modulation described in TS38.211 Section 5.1.3.
  /// Quadrature Phase Shift Keying (QPSK) modulation described in TS38.211 Section 5.1.3.
  QPSK = 2,
  /// 16-point Quadrature Amplitude Modulation (16-QAM) described in TS38.211 Section 5.1.4.
  /// 16-point Quadrature Amplitude Modulation (16-QAM) described in TS38.211 Section 5.1.4.
  QAM16 = 4,
  /// 64-point Quadrature Amplitude Modulation (64-QAM) described in TS38.211 Section 5.1.5.
  /// 64-point Quadrature Amplitude Modulation (64-QAM) described in TS38.211 Section 5.1.5.
  QAM64 = 6,
  /// 256-point Quadrature Amplitude Modulation (256-QAM) described in TS38.211 Section 5.1.6.
  /// 256-point Quadrature Amplitude Modulation (256-QAM) described in TS38.211 Section 5.1.6.
  QAM256 = MODULATION_MAX_BITS_PER_SYMBOL
};


inline std::string to_string(modulation_scheme mod)
{
  switch (mod) {
    case modulation_scheme::PI_2_BPSK:
      return "pi/2-BPSK";
    case modulation_scheme::BPSK:
      return "BPSK";
    case modulation_scheme::QPSK:
      return "QPSK";
    case modulation_scheme::QAM16:
      return "16QAM";
    case modulation_scheme::QAM64:
      return "64QAM";
    case modulation_scheme::QAM256:
    default:
      return "256QAM";
  }
}

/// \brief Converts a string into a modulation scheme.
/// \param[in] mod_scheme_string input string.
/// \returns The corresponding \c modulation_scheme.

/// \brief Converts a string into a modulation scheme.
/// \param[in] mod_scheme_string input string.
/// \returns The corresponding \c modulation_scheme.
inline modulation_scheme modulation_scheme_from_string(const std::string& mod_scheme_string)
{
  modulation_scheme mod_scheme = modulation_scheme::QAM256;
  if (mod_scheme_string == "pi/2-BPSK") {
    mod_scheme = modulation_scheme::PI_2_BPSK;
  } else if (mod_scheme_string == "BPSK") {
    mod_scheme = modulation_scheme::BPSK;
  } else if (mod_scheme_string == "QPSK") {
    mod_scheme = modulation_scheme::QPSK;
  } else if (mod_scheme_string == "16QAM") {
    mod_scheme = modulation_scheme::QAM16;
  } else if (mod_scheme_string == "64QAM") {
    mod_scheme = modulation_scheme::QAM64;
  } else if (mod_scheme_string == "256QAM") {
    mod_scheme = modulation_scheme::QAM256;
  } else {
    ocudu_assertion_failure("Invalid modulation scheme: {}", mod_scheme_string);
  }
  return mod_scheme;
}

/// \brief Bits per symbol for a given modulation scheme.
/// \param[in] mod Modulation scheme.
/// \returns The number of bits per modulated symbol (sometimes referred to as modulation order).

/// \brief Bits per symbol for a given modulation scheme.
/// \param[in] mod Modulation scheme.
/// \returns The number of bits per modulated symbol (sometimes referred to as modulation order).
constexpr unsigned get_bits_per_symbol(modulation_scheme mod)
{
  if (mod == modulation_scheme::PI_2_BPSK) {
    return 1;
  }


  return static_cast<unsigned>(mod);
}


} // namespace ocudu
