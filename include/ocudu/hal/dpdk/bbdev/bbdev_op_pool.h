// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/bbdev/bbdev_op_pool.h  (39 lines)
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


#include "ocudu/support/ocudu_assert.h"
#include <rte_mempool.h>


namespace ocudu {
namespace dpdk {

/// RAII wrapping for dpdk bbdev operation pool structures.

/// RAII wrapping for dpdk bbdev operation pool structures.
class bbdev_op_pool
{
public:
  /// Constructor.
  /// \param[in] pool_ Pointer to a dpdk memory pool.
  /// Constructor.
  /// \param[in] pool_ Pointer to a dpdk memory pool.
  explicit bbdev_op_pool(::rte_mempool* pool_) : pool(*pool_) { ocudu_assert(pool_, "Invalid bbdev op pool."); }
  /// Destructor.
  /// Destructor.
  ~bbdev_op_pool()
  {
    // Free the memory buffer pool.
    // Free the memory buffer pool.
    ::rte_mempool_free(&pool);
  }

  // Returns a pointer to the actual memory pool object.
  /// \return Pointer to the memory pool.

  // Returns a pointer to the actual memory pool object.
  /// \return Pointer to the memory pool.
  ::rte_mempool* get_pool() { return &pool; }

  // Returns a pointer to a constant memory pool object.
  /// \return Pointer to a constant memory pool.

  // Returns a pointer to a constant memory pool object.
  /// \return Pointer to a constant memory pool.
  const ::rte_mempool* get_pool() const { return &pool; }


private:
  ::rte_mempool& pool;
};


} // namespace dpdk
} // namespace ocudu
