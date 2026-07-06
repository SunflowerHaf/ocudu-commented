// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/p7/mac_fapi_p7_sector_fastpath_adaptor_factory_impl.cpp  (17 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "mac_fapi_p7_sector_fastpath_adaptor_factory_impl.h"
#include "mac_fapi_p7_sector_fastpath_adaptor_impl.h"
#include "mac_fapi_p7_sector_fastpath_adaptor_impl_config.h"


using namespace ocudu;
using namespace fapi_adaptor;


std::unique_ptr<mac_fapi_p7_sector_fastpath_adaptor> ocudu::fapi_adaptor::create_mac_fapi_p7_sector_fastpath_adaptor(
    const mac_fapi_p7_sector_fastpath_adaptor_config&     config,
    mac_fapi_p7_sector_fastpath_adaptor_impl_dependencies dependencies)
{
  return std::make_unique<mac_fapi_p7_sector_fastpath_adaptor_impl>(config, std::move(dependencies));
}
