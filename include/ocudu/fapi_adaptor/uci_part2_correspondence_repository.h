// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/uci_part2_correspondence_repository.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/ran/uci/uci_part2_size_description.h"


namespace ocudu {
namespace fapi_adaptor {

/// \brief UCI Part2 sizes repository.
///
/// The repository stores arrays of Part2 sizes as a function of Part1 parameters.

/// \brief UCI Part2 sizes repository.
///
/// The repository stores arrays of Part2 sizes as a function of Part1 parameters.
class uci_part2_correspondence_repository
{
  /// Each entry contains a list of UCI Part2 sizes.
  /// Each entry contains a list of UCI Part2 sizes.
  std::vector<static_vector<uint16_t, uci_part2_size_description::max_size_table>> repo_map;


public:
  explicit uci_part2_correspondence_repository(
      std::vector<static_vector<uint16_t, uci_part2_size_description::max_size_table>> repo_map_) :
    repo_map(std::move(repo_map_))
  {
    ocudu_assert(!repo_map.empty(), "Empty container");
  }

  /// \brief Returns a list of Part2 sizes related to Part1 parameters associated to the given index.
  ///
  /// \note Index value must be valid.

  /// \brief Returns a list of Part2 sizes related to Part1 parameters associated to the given index.
  ///
  /// \note Index value must be valid.
  span<const uint16_t> get_uci_part2_correspondence(unsigned index) const;
};


} // namespace fapi_adaptor
} // namespace ocudu
