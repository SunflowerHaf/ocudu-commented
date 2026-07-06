// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/mac/p7/mac_fapi_p7_sector_fastpath_adaptor_config.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi_adaptor/precoding_matrix_mapper.h"
#include "ocudu/fapi_adaptor/uci_part2_correspondence_mapper.h"
#include "ocudu/ran/subcarrier_spacing.h"
#include <memory>


namespace ocudu {


class task_executor;


namespace fapi {
class p7_last_request_notifier;
class p7_requests_gateway;
} // namespace fapi


namespace fapi_adaptor {

/// MAC-FAPI P7 sector fastpath adaptor configuration.

/// MAC-FAPI P7 sector fastpath adaptor configuration.
struct mac_fapi_p7_sector_fastpath_adaptor_config {
  /// Base station sector identifier.
  /// Base station sector identifier.
  unsigned sector_id;
  /// Cell number of resource blocks.
  /// Cell number of resource blocks.
  unsigned cell_nof_prbs;
  /// Subcarrier spacing as per TS38.331 Section 6.2.2.
  /// Subcarrier spacing as per TS38.331 Section 6.2.2.
  subcarrier_spacing scs;
};

/// MAC-FAPI P7 sector fastpath adaptor dependencies.

/// MAC-FAPI P7 sector fastpath adaptor dependencies.
struct mac_fapi_p7_sector_fastpath_adaptor_dependencies {
  /// FAPI P7 requests gateway.
  /// FAPI P7 requests gateway.
  fapi::p7_requests_gateway& p7_gateway;
  /// P7 last requests notifier.
  /// P7 last requests notifier.
  fapi::p7_last_request_notifier& p7_last_req_notifier;
  /// Precoding matrix mapper.
  /// Precoding matrix mapper.
  std::unique_ptr<precoding_matrix_mapper> pm_mapper;
  /// UCI Part2 mapper.
  /// UCI Part2 mapper.
  std::unique_ptr<uci_part2_correspondence_mapper> part2_mapper;
  /// FAPI logger.
  /// FAPI logger.
  ocudulog::basic_logger& fapi_logger;
};


} // namespace fapi_adaptor
} // namespace ocudu
