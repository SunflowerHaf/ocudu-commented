// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/dpdk/dpdk.cpp  (41 lines)
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

#include "dpdk.h"


using namespace ocudu;
using namespace dpdk;

/// \file
/// \brief EAL functions.


/// \file
/// \brief EAL functions.

bool dpdk::eal_init(int argc, char** argv, ocudulog::basic_logger& logger)
{
  if (::rte_eal_init(argc, argv) < 0) {
    logger.error("dpdk: rte_eal_init failed");
    return false;
  }


  return true;
}

/// \file
/// \brief Common memory pool functions.


/// \file
/// \brief Common memory pool functions.

::rte_mempool* dpdk::create_mem_pool(const char*             pool_name,
                                     int                     socket,
                                     unsigned                n_mbuf,
                                     unsigned                mempool_cache_size,
                                     unsigned                mbuf_data_size,
                                     ocudulog::basic_logger& logger)
{
  // Create a new mbuf pool for the hardware-accelerated functions.
  // Create a new mbuf pool for the hardware-accelerated functions.
  ::rte_mempool* mbuf_pool =
      ::rte_pktmbuf_pool_create(pool_name, n_mbuf, mempool_cache_size, 0, mbuf_data_size, socket);


  if (mbuf_pool == nullptr) {
    logger.error("dpdk: create_mbuf_pool '{}' failed (size {})", pool_name, mbuf_data_size);
  }


  return mbuf_pool;
}
