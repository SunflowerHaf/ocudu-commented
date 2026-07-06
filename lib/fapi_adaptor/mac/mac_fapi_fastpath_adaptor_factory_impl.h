// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/mac_fapi_fastpath_adaptor_factory_impl.h  (22 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/mac/mac_fapi_fastpath_adaptor_factory.h"


namespace ocudu {
namespace fapi_adaptor {

/// Implementation of the MAC-FAPI adaptor factory.

/// Implementation of the MAC-FAPI adaptor factory.
class mac_fapi_fastpath_adaptor_factory_impl : public mac_fapi_fastpath_adaptor_factory
{
public:
  // See interface for documentation.
  // See interface for documentation.
  std::unique_ptr<mac_fapi_fastpath_adaptor> create(const mac_fapi_fastpath_adaptor_config& config,
                                                    mac_fapi_fastpath_adaptor_dependencies  dependencies) override;
};


} // namespace fapi_adaptor
} // namespace ocudu
