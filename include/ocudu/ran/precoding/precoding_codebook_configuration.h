// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/precoding/precoding_codebook_configuration.h  (63 lines)
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
#include "ocudu/ran/precoding/precoding_codebook_properties.h"
#include <variant>

/// \file
///
/// \brief Defines the codebook configuration for generating the precoding codebooks and reporting the
/// Precoding Matrix Indicator (PMI).


/// \file
///
/// \brief Defines the codebook configuration for generating the precoding codebooks and reporting the
/// Precoding Matrix Indicator (PMI).

namespace ocudu {

/// Precoding Matrix Indicator (PMI) codebook configuration for one CSI-RS antenna port.

/// Precoding Matrix Indicator (PMI) codebook configuration for one CSI-RS antenna port.
struct pmi_codebook_one_port {};

/// Precoding Matrix Indicator (PMI) codebook configuration for two CSI-RS antenna ports.

/// Precoding Matrix Indicator (PMI) codebook configuration for two CSI-RS antenna ports.
struct pmi_codebook_two_port {};

/// \brief Precoding Matrix Indicator (PMI) codebook configuration for Type I single-panel.
///
/// The configuration is given by higher layer parameters <em>n1-n2</em> and \e codebookMode in the Information Element
/// \e CodebookConfig in TS38.331 Section 6.3.2.

/// \brief Precoding Matrix Indicator (PMI) codebook configuration for Type I single-panel.
///
/// The configuration is given by higher layer parameters <em>n1-n2</em> and \e codebookMode in the Information Element
/// \e CodebookConfig in TS38.331 Section 6.3.2.
struct pmi_codebook_typeI_single_panel {
  /// Single-panel configuration.
  /// Single-panel configuration.
  pmi_codebook_single_panel_config n1_n2;
  /// Codebook mode.
  /// Codebook mode.
  pmi_codebook_typeI_mode mode;
};

/// Defines the PMI codebook configuration types.

/// Defines the PMI codebook configuration types.
using pmi_codebook_config =
    std::variant<std::monostate, pmi_codebook_one_port, pmi_codebook_two_port, pmi_codebook_typeI_single_panel>;

/// \brief PMI codebook configuration identifier.
///
/// Each combination of PMI codebook parameters is mapped onto a unique identifier.
///
/// The codebooks are mapped as follows:
/// - 0: one port codebook (and monostate)
/// - 1: two port codebook
/// - [2, 14]: Type I single-panel, mode 1 codebook
///
/// \remark Any other combination triggers an assertion.

/// \brief PMI codebook configuration identifier.
///
/// Each combination of PMI codebook parameters is mapped onto a unique identifier.
///
/// The codebooks are mapped as follows:
/// - 0: one port codebook (and monostate)
/// - 1: two port codebook
/// - [2, 14]: Type I single-panel, mode 1 codebook
///
/// \remark Any other combination triggers an assertion.
using pmi_codebook_id = bounded_integer<unsigned, 0, 14>;

/// Converts the codebook configuration to an identifier.

/// Converts the codebook configuration to an identifier.
pmi_codebook_id to_pmi_codebook_identifier(const pmi_codebook_config& codebook);

/// Converts a PMI codebook identifier to a PMI codebook configuration.

/// Converts a PMI codebook identifier to a PMI codebook configuration.
const pmi_codebook_config& to_pmi_codebook_config(pmi_codebook_id identifier);

/// Converts the PMI codebook configuration to a string.

/// Converts the PMI codebook configuration to a string.
const char* to_string(const pmi_codebook_config& codebook);

/// Gets the number of CSI-RS antenna ports from the PMI codebook configuration.

/// Gets the number of CSI-RS antenna ports from the PMI codebook configuration.
unsigned get_precoding_codebook_antenna_ports(const pmi_codebook_config& pmi_codebook);


} // namespace ocudu
