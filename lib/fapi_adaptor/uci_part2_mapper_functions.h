// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/uci_part2_mapper_functions.h  (28 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "ocudu/ran/csi_report/csi_report_configuration.h"


namespace ocudu {
namespace fapi_adaptor {


constexpr unsigned MAX_NUM_RI_RESTRICTIONS = (1U << 4);
constexpr unsigned MAX_NUM_CSI_RESOURCES   = 1;
constexpr unsigned MAX_NUM_CODEBOOKS       = 3;
constexpr unsigned MAX_NUM_QUANTITIES      = static_cast<unsigned>(csi_report_quantities::other);

/// Returns the UCI Part2 correspondence index using the given parameters.

/// Returns the UCI Part2 correspondence index using the given parameters.
inline unsigned get_uci_part2_correspondence_index(unsigned nof_csi_resources,
                                                   unsigned pmi_codebook,
                                                   unsigned ri_restriction,
                                                   unsigned quantities)
{
  return (MAX_NUM_RI_RESTRICTIONS * MAX_NUM_CSI_RESOURCES * MAX_NUM_CODEBOOKS * quantities) +
         (MAX_NUM_CSI_RESOURCES * MAX_NUM_CODEBOOKS * ri_restriction) + (MAX_NUM_CSI_RESOURCES * pmi_codebook) +
         nof_csi_resources;
}


} // namespace fapi_adaptor
} // namespace ocudu
