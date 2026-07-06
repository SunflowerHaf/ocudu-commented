// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Definition of the common functions used by all ACC100-accelerated channel processor function implementations.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/dpdk/dpdk.h  (41 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/hal
// Hardware Abstraction Layer (HAL) — DPDK and hardware PHY accelerator implementations. CONDITIONAL: only compiled when DPDK_FOUND=ON and a supported hardware accelerator (e.g. Intel ACC100/ACC200 via BBDEV) is present. In the standard USRP/UHD build this entire directory is excluded from compilation.
//
// Contents:
//   lib/hal/dpdk/         — DPDK EAL initialisation, mbuf pool management, BBDEV device open/config.
//   lib/hal/phy/upper/    — HW-accelerated PDSCH encoder (offloads LDPC encoding to the ACC100 FPGA) and PUSCH decoder (offloads LDPC decoding), plus external HARQ buffer context repository (stores soft bits in on-accelerator memory).
//
// When active, the HAL factories are passed into the upper PHY (lib/phy/) as hw_encoder_factory / hw_decoder_factory pointers; if nullptr, the software fallback LDPC implementations are used automatically.
// =============================================================================

/// \file
/// \brief Definition of the common functions used by all ACC100-accelerated channel processor function implementations.

#pragma once


#include "ocudu/hal/dpdk/dpdk_eal.h"
#include "ocudu/ocudulog/logger.h"
#include <rte_eal.h>
#include <rte_mbuf.h>


namespace ocudu {
namespace dpdk {

/// \file
/// \brief Common DPDK support functions.

/// EAL initialization (called at application init).
/// \param[in]  argc, argv Command line arguments.
/// \param[in]  logger     OCUDU logger.

/// \file
/// \brief Common DPDK support functions.

/// EAL initialization (called at application init).
/// \param[in]  argc, argv Command line arguments.
/// \param[in]  logger     OCUDU logger.
bool eal_init(int argc, char** argv, ocudulog::basic_logger& logger);

/// Creates a new memory pool for a given hardware-accelerator device.
/// \param[in]  pool_name          Unique ID for the new mbuf pool.
/// \param[in]  socket             Socket used by the bbdev accelerator.
/// \param[in]  n_mbuf             Number of elements in the mbuf pool.
/// \param[in]  mempool_cache_size Size of the per-core object cache.
/// \param[in]  mbuf_data_size     Size of data buffer in each mbuf.
/// \param[in]  logger             OCUDU logger.
/// \return Pointer to the created mbuf pool.

/// Creates a new memory pool for a given hardware-accelerator device.
/// \param[in]  pool_name          Unique ID for the new mbuf pool.
/// \param[in]  socket             Socket used by the bbdev accelerator.
/// \param[in]  n_mbuf             Number of elements in the mbuf pool.
/// \param[in]  mempool_cache_size Size of the per-core object cache.
/// \param[in]  mbuf_data_size     Size of data buffer in each mbuf.
/// \param[in]  logger             OCUDU logger.
/// \return Pointer to the created mbuf pool.
rte_mempool* create_mem_pool(const char*             pool_name,
                             int                     socket,
                             unsigned                n_mbuf,
                             unsigned                mempool_cache_size,
                             unsigned                mbuf_data_size,
                             ocudulog::basic_logger& logger);


} // namespace dpdk
} // namespace ocudu
