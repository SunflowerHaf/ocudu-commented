// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/uci_part1_to_part2_correspondence.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/uci/uci_part2_size_description.h"


namespace ocudu {
namespace fapi {

/// UCI information for determining UCI Part1 to Part2 correspondence.

/// UCI information for determining UCI Part1 to Part2 correspondence.
struct uci_part1_to_part2_correspondence {
  struct part2_info {
    static_vector<uint16_t, 4> param_offsets;
    static_vector<uint8_t, 4>  param_sizes;
    uint16_t                   part2_size_map_index;
  };


  static_vector<part2_info, uci_part2_size_description::max_nof_entries> part2;
};


} // namespace fapi
} // namespace ocudu
