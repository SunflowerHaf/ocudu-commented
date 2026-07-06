// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/mbuf_pool_factory.h  (28 lines)
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


#include "ocudu/hal/dpdk/mbuf_pool.h"
#include "ocudu/ocudulog/logger.h"
#include <memory>


namespace ocudu {
namespace dpdk {

/// Configuration structure of a dpdk memory buffer pool.

/// Configuration structure of a dpdk memory buffer pool.
struct mempool_config {
  /// Number of elements in the mbuf pool.
  /// Number of elements in the mbuf pool.
  unsigned n_mbuf = 2048;
  /// Size of the per-core object cache.
  /// Size of the per-core object cache.
  unsigned mempool_cache_size = 128;
  /// Size of data buffer in each mbuf.
  /// Size of data buffer in each mbuf.
  unsigned mbuf_data_size = 2048;
};

/// Returns a mbuf_pool instance on success, otherwise returns nullptr.

/// Returns a mbuf_pool instance on success, otherwise returns nullptr.
std::unique_ptr<mbuf_pool>
create_mbuf_pool(const char* pool_name, int socket, const mempool_config& cfg, ocudulog::basic_logger& logger);


} // namespace dpdk
} // namespace ocudu
