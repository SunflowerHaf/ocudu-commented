// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/phy/phy_fapi_sector_fastpath_adaptor_impl.h  (36 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/phy/p5/phy_fapi_p5_sector_adaptor.h"
#include "ocudu/fapi_adaptor/phy/p7/phy_fapi_p7_sector_fastpath_adaptor.h"
#include "ocudu/fapi_adaptor/phy/phy_fapi_sector_fastpath_adaptor.h"
#include <memory>


namespace ocudu {
class uplink_request_processor;


namespace fapi_adaptor {

/// PHY-FAPI bidirectional sector fastpath adaptor implementation.

/// PHY-FAPI bidirectional sector fastpath adaptor implementation.
class phy_fapi_sector_fastpath_adaptor_impl : public phy_fapi_sector_fastpath_adaptor
{
public:
  phy_fapi_sector_fastpath_adaptor_impl(std::unique_ptr<phy_fapi_p5_sector_adaptor>          p5_adaptor_,
                                        std::unique_ptr<phy_fapi_p7_sector_fastpath_adaptor> p7_adaptor_);

  // See interface for documentation.

  // See interface for documentation.
  phy_fapi_p5_sector_adaptor& get_p5_sector_adaptor() override;

  // See interface for documentation.

  // See interface for documentation.
  phy_fapi_p7_sector_fastpath_adaptor& get_p7_sector_adaptor() override;


private:
  std::unique_ptr<phy_fapi_p5_sector_adaptor>          p5_adaptor;
  std::unique_ptr<phy_fapi_p7_sector_fastpath_adaptor> p7_adaptor;
};


} // namespace fapi_adaptor
} // namespace ocudu
