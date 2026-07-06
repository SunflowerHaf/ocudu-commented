// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/uci_part2_correspondence_generator.h  (17 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi_adaptor/uci_part2_correspondence_mapper.h"
#include "ocudu/fapi_adaptor/uci_part2_correspondence_repository.h"


namespace ocudu {
namespace fapi_adaptor {

/// Generates the UCI Part2 correspondence mapper and repository for the given number of CSI-RS resources.

/// Generates the UCI Part2 correspondence mapper and repository for the given number of CSI-RS resources.
std::pair<std::unique_ptr<uci_part2_correspondence_mapper>, std::unique_ptr<uci_part2_correspondence_repository>>
generate_uci_part2_correspondence(unsigned nof_csi_rs_resources);


} // namespace fapi_adaptor
} // namespace ocudu
