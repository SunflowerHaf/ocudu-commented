// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/srs/srs_information.h  (47 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/srs/srs_resource_configuration.h"


namespace ocudu {

/// \brief Collects Sounding Reference Signal information.
///
/// Contains the derived parameters that are used for the SRS sequence generation and mapping, as per TS38.211 Sections
/// 6.4.1.4.2 and 6.4.1.4.3.
///
/// The parameters describe the sequence and its allocation for a certain transmission port and OFDM symbol.

/// \brief Collects Sounding Reference Signal information.
///
/// Contains the derived parameters that are used for the SRS sequence generation and mapping, as per TS38.211 Sections
/// 6.4.1.4.2 and 6.4.1.4.3.
///
/// The parameters describe the sequence and its allocation for a certain transmission port and OFDM symbol.
struct srs_information {
  /// Sequence length, parameter \f$M_{sc,b}^{SRS}\f$.
  /// Sequence length, parameter \f$M_{sc,b}^{SRS}\f$.
  unsigned sequence_length;
  /// Sequence group, parameter \f$u\f$.
  /// Sequence group, parameter \f$u\f$.
  unsigned sequence_group;
  /// Sequence number, parameter \f$v\f$.
  /// Sequence number, parameter \f$v\f$.
  unsigned sequence_number;
  /// Sequence cyclic shift, parameter \f$n_{SRS}^{cs,i}\f$.
  /// Sequence cyclic shift, parameter \f$n_{SRS}^{cs,i}\f$.
  unsigned n_cs;
  /// Sequence maximum cyclic shift, parameter \f$n_{SRS}^{cs,max}\f$.
  /// Sequence maximum cyclic shift, parameter \f$n_{SRS}^{cs,max}\f$.
  unsigned n_cs_max;
  /// First subcarrier used for mapping the sequence within the BWP, parameter \f$k_{0}^{(p_i)}\f$.
  /// First subcarrier used for mapping the sequence within the BWP, parameter \f$k_{0}^{(p_i)}\f$.
  unsigned mapping_initial_subcarrier;
  /// Comb size, parameter \f$K_{TC}\f$.
  /// Comb size, parameter \f$K_{TC}\f$.
  unsigned comb_size;

  /// Gets the sequence cyclic shift, parameter \f$\alpha\f$.

  /// Gets the sequence cyclic shift, parameter \f$\alpha\f$.
  float get_alpha() const { return static_cast<float>(2 * M_PI * n_cs) / static_cast<float>(n_cs_max); }
};

/// \brief Get Sounding Reference Signal information.
///
/// Simplified SRS information. It does not implement sequence, group or frequency hopping.
///
/// \param resource       SRS resource configuration.
/// \param i_antenna_port Transmit antenna 0-based port index.
/// \return The SRS information.
/// \remark An assertion is triggered if one or more resource parameters are invalid or not supported.

/// \brief Get Sounding Reference Signal information.
///
/// Simplified SRS information. It does not implement sequence, group or frequency hopping.
///
/// \param resource       SRS resource configuration.
/// \param i_antenna_port Transmit antenna 0-based port index.
/// \return The SRS information.
/// \remark An assertion is triggered if one or more resource parameters are invalid or not supported.
srs_information get_srs_information(const srs_resource_configuration& resource, unsigned i_antenna_port);


} // namespace ocudu
