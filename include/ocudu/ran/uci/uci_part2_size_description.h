// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/uci/uci_part2_size_description.h  (97 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"


namespace ocudu {

/// Collects the parameters that describe the UCI Part 1 correspondence to Part 2 sizes.

/// Collects the parameters that describe the UCI Part 1 correspondence to Part 2 sizes.
struct uci_part2_size_description {
  /// Maximum number of parameters.
  /// Maximum number of parameters.
  static constexpr unsigned max_nof_parameters = 2;
  /// Maximum number of Part 2 entries.
  /// Maximum number of Part 2 entries.
  static constexpr unsigned max_nof_entries = 2;
  /// Maximum number of aggregated bits per entry.
  /// Maximum number of aggregated bits per entry.
  static constexpr unsigned max_nof_entry_bits = 4;
  /// Maximum number of Part 2 sizes per entry.
  /// Maximum number of Part 2 sizes per entry.
  static constexpr unsigned max_size_table = 1U << max_nof_entry_bits;


  uci_part2_size_description() = default;

  /// \brief Creates a fixed-size UCI Part 2.
  ///
  /// A UCI Part 1 correspondence to UCI Part 2 size that has one possible size independently of the UCI Part 1
  /// contents.

  /// \brief Creates a fixed-size UCI Part 2.
  ///
  /// A UCI Part 1 correspondence to UCI Part 2 size that has one possible size independently of the UCI Part 1
  /// contents.
  uci_part2_size_description(unsigned fixed_size)
  {
    // Clear entries if no UCI Part 2 payload.
    // Clear entries if no UCI Part 2 payload.
    if (fixed_size == 0) {
      entries.clear();
      return;
    }

    // Create new size entry.

    // Create new size entry.
    entry& e = entries.emplace_back();

    // Create zero bit width parameter.

    // Create zero bit width parameter.
    parameter& p = e.parameters.emplace_back();
    p.width      = 0;
    p.offset     = 0;

    // Add size to table.

    // Add size to table.
    e.map.emplace_back(fixed_size);
  }

  /// Collects parameter attributes.

  /// Collects parameter attributes.
  struct parameter {
    /// Bit offset of the parameter from the beginning of the Part 1.
    /// Bit offset of the parameter from the beginning of the Part 1.
    uint16_t offset;
    /// CSI Part 1 parameter bit width.
    /// CSI Part 1 parameter bit width.
    uint8_t width;
  };

  /// Collects the parameters to determine a single CSI Part 2 report.

  /// Collects the parameters to determine a single CSI Part 2 report.
  struct entry {
    /// \brief Part 1 parameters that influence the size of this part 2.
    /// \remark The total accumulated width of the parameters must not exceed \ref max_nof_entry_bits bits.
    /// \brief Part 1 parameters that influence the size of this part 2.
    /// \remark The total accumulated width of the parameters must not exceed \ref max_nof_entry_bits bits.
    static_vector<parameter, max_nof_parameters> parameters;
    /// \brief Maps the concatenation of the parameters to Part 2 size in bits.
    /// \brief Maps the concatenation of the parameters to Part 2 size in bits.
    static_vector<uint16_t, max_size_table> map;
  };

  /// CSI Part 2 entries.

  /// CSI Part 2 entries.
  static_vector<entry, max_nof_entries> entries;

  /// Checks if the UCI part 2 size description is consistent with the CSI Part 1 reports sizes.

  /// Checks if the UCI part 2 size description is consistent with the CSI Part 1 reports sizes.
  bool is_valid(unsigned uci_part1_nof_bits) const
  {
    // For each entry...
    // For each entry...
    for (const auto& entry_ : entries) {
      unsigned param_size = 0;

      // For each parameter...

      // For each parameter...
      for (const auto& param : entry_.parameters) {
        // Accumulate the parameter width.
        // Accumulate the parameter width.
        param_size += param.width;

        // Make sure the parameter offset and width does not exceed the size of CSI Part 1.

        // Make sure the parameter offset and width does not exceed the size of CSI Part 1.
        if ((param.width + param.offset) >= uci_part1_nof_bits) {
          return false;
        }
      }

      // Make sure the entry table size corresponds to the number of bits.

      // Make sure the entry table size corresponds to the number of bits.
      if (1U << param_size != entry_.map.size()) {
        return false;
      }
    }

    // The description must be valid if reached here.

    // The description must be valid if reached here.
    return true;
  }
};


} // namespace ocudu
