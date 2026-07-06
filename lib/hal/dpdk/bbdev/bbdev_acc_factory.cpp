// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/dpdk/bbdev/bbdev_acc_factory.cpp  (20 lines)
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

#include "ocudu/hal/dpdk/bbdev/bbdev_acc_factory.h"
#include "ocudu/hal/dpdk/bbdev/bbdev.h"


using namespace ocudu;
using namespace dpdk;


std::shared_ptr<bbdev_acc> ocudu::dpdk::create_bbdev_acc(const bbdev_acc_configuration& cfg,
                                                         ocudulog::basic_logger&        logger)
{
  // bbdev device start procedure.
  // bbdev device start procedure.
  expected<::rte_bbdev_info> info = bbdev_start(cfg, logger);
  if (not info.has_value()) {
    return nullptr;
  }


  return std::make_shared<bbdev_acc>(cfg, info.value(), logger);
}
