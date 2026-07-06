// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/uci_part2_correspondence_mapper.cpp  (30 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/fapi_adaptor/uci_part2_correspondence_mapper.h"
#include "uci_part2_mapper_functions.h"
#include "ocudu/ran/csi_report/csi_report_configuration.h"


using namespace ocudu;
using namespace fapi_adaptor;


span<const uci_part2_correspondence_information>
uci_part2_correspondence_mapper::map(const csi_report_configuration& csi_report) const
{
  ocudu_assert(csi_report.nof_csi_rs_resources && csi_report.nof_csi_rs_resources <= MAX_NUM_CSI_RESOURCES,
               "Unsupported number of CSI-RS resources");
  ocudu_assert(!csi_report.ri_restriction.empty(), "Empty RI restriction field");
  ocudu_assert(csi_report.ri_restriction.to_uint64() < MAX_NUM_RI_RESTRICTIONS, "Unsupported RI restriction value");


  unsigned index = get_uci_part2_correspondence_index(csi_report.nof_csi_rs_resources,
                                                      to_pmi_codebook_identifier(csi_report.pmi_codebook).value(),
                                                      static_cast<unsigned>(csi_report.ri_restriction.to_uint64()),
                                                      static_cast<unsigned>(csi_report.quantities));


  ocudu_assert(index < correspondence_map.size(),
               "Invalid UCI Part2 correspondence calculated index, index value is '{}' while map size has '{}' entries",
               index,
               correspondence_map.size());


  return correspondence_map[index];
}
