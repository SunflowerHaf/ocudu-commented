// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/mac_fapi_sector_fastpath_adaptor_impl.cpp  (28 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "mac_fapi_sector_fastpath_adaptor_impl.h"
#include "ocudu/support/ocudu_assert.h"


using namespace ocudu;
using namespace fapi_adaptor;


mac_fapi_sector_fastpath_adaptor_impl::mac_fapi_sector_fastpath_adaptor_impl(
    std::unique_ptr<mac_fapi_p5_sector_fastpath_adaptor> p5_adaptor_,
    std::unique_ptr<mac_fapi_p7_sector_fastpath_adaptor> p7_adaptor_) :
  p5_adaptor(std::move(p5_adaptor_)), p7_adaptor(std::move(p7_adaptor_))
{
  ocudu_assert(p5_adaptor, "Invalid MAC-FAPI P5 sector adaptor");
  ocudu_assert(p7_adaptor, "Invalid MAC-FAPI P7 sector adaptor");
}


mac_fapi_p5_sector_fastpath_adaptor& mac_fapi_sector_fastpath_adaptor_impl::get_p5_sector_fastpath_adaptor()
{
  return *p5_adaptor;
}


mac_fapi_p7_sector_fastpath_adaptor& mac_fapi_sector_fastpath_adaptor_impl::get_p7_sector_adaptor()
{
  return *p7_adaptor;
}
