// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/uci_part2_correspondence_repository.cpp  (17 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/fapi_adaptor/uci_part2_correspondence_repository.h"


using namespace ocudu;
using namespace fapi_adaptor;


span<const uint16_t> uci_part2_correspondence_repository::get_uci_part2_correspondence(unsigned index) const
{
  ocudu_assert(index < repo_map.size(),
               "Invalid UCI Part2 correspondence index, index value is '{}' while repository size has '{}' entries",
               index,
               repo_map.size());


  return repo_map[index];
}
