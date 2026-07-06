// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/qos/packet_error_rate.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cmath>
#include <cstdint>


namespace ocudu {

/// \brief Representation of the Packet Error Rate (PER) as defined in TS 38.473 and TS 23.501, 5.7.3.5.
///
/// The Packet Error Rate (PER) defines an upper bound for the rate of PDUs (e.g. IP packets) that have been processed
/// by the sender of a link layer protocol (e.g. RLC in RAN of a 3GPP access) but that are not successfully delivered
/// by the corresponding receiver to the upper layer (e.g. PDCP in RAN of a 3GPP access). Thus, the PER defines an
/// upper bound for a rate of non-congestion related packet losses.

/// \brief Representation of the Packet Error Rate (PER) as defined in TS 38.473 and TS 23.501, 5.7.3.5.
///
/// The Packet Error Rate (PER) defines an upper bound for the rate of PDUs (e.g. IP packets) that have been processed
/// by the sender of a link layer protocol (e.g. RLC in RAN of a 3GPP access) but that are not successfully delivered
/// by the corresponding receiver to the upper layer (e.g. PDCP in RAN of a 3GPP access). Thus, the PER defines an
/// upper bound for a rate of non-congestion related packet losses.
struct packet_error_rate_t {
  uint8_t scalar   = 0;
  uint8_t exponent = 0;


  constexpr packet_error_rate_t() = default;
  constexpr packet_error_rate_t(uint8_t scalar_, uint8_t exponent_) : scalar(scalar_), exponent(exponent_) {}


  static packet_error_rate_t make(double per_)
  {
    ocudu_assert(per_ > 0 and per_ < 1.0, "Invalid PER value {}", per_);
    double exp_val = std::floor(std::log10(per_));
    double scalar  = std::round(per_ / std::pow(10, exp_val));
    return packet_error_rate_t{static_cast<uint8_t>(scalar), static_cast<uint8_t>(-exp_val)};
  }


  double to_double() const { return static_cast<double>(scalar) * std::pow(10, -static_cast<int>(exponent)); }


  bool operator==(const packet_error_rate_t& other) const
  {
    return scalar == other.scalar and exponent == other.exponent;
  }
};


} // namespace ocudu
