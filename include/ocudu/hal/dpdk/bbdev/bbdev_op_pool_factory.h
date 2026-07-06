// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/bbdev/bbdev_op_pool_factory.h  (21 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/hal
// HAL (Hardware Abstraction Layer) public interface headers. CONDITIONAL: only required when building with DPDK_FOUND=ON. In the standard USRP/UHD build these headers are not included by any active code path.
//
// Contents:
//   hal/dpdk/             — DPDK EAL handle, mbuf pool, BBDEV device interfaces.
//   hal/hw_accelerator.h  — Base hardware accelerator interface (submit_op, retrieve_op, get capabilities).
//   hal/phy/upper/        — hw_accelerator_pdsch_enc (offload PDSCH LDPC encoding) and hw_accelerator_pusch_dec (offload PUSCH LDPC decoding) abstract interfaces, plus their factory types and the external HARQ buffer context repository interface.
// =============================================================================

#pragma once


#include "ocudu/hal/dpdk/bbdev/bbdev_op_pool.h"
#include "ocudu/ocudulog/logger.h"
#include <rte_bbdev_op.h>


namespace ocudu {
namespace dpdk {

/// Returns a bbdev_op_pool instance on success, otherwise returns nullptr.

/// Returns a bbdev_op_pool instance on success, otherwise returns nullptr.
std::unique_ptr<bbdev_op_pool> create_bbdev_op_pool(const char*             pool_name,
                                                    ::rte_bbdev_op_type     op_type,
                                                    uint16_t                nof_elements,
                                                    int                     socket,
                                                    ocudulog::basic_logger& logger);


} // namespace dpdk
} // namespace ocudu
