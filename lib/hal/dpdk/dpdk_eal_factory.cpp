// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/dpdk/dpdk_eal_factory.cpp  (43 lines)
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

#include "ocudu/hal/dpdk/dpdk_eal_factory.h"
#include "dpdk.h"
#include <sstream>


using namespace ocudu;
using namespace dpdk;

/// Splits the input string into a vector of substrings separated by space characters.

/// Splits the input string into a vector of substrings separated by space characters.
static std::vector<std::string> split_string_by_space(const std::string& input)
{
  std::vector<std::string> strings;


  std::istringstream ss(input);
  while (ss.good()) {
    std::string substr;
    std::getline(ss, substr, ' ');


    if (!substr.empty()) {
      strings.push_back(std::move(substr));
    }
  }


  return strings;
}


std::unique_ptr<dpdk_eal> ocudu::dpdk::create_dpdk_eal(const std::string& args, ocudulog::basic_logger& logger)
{
  auto               strings = split_string_by_space(args);
  std::vector<char*> argv;
  for (const auto& s : strings) {
    argv.push_back(const_cast<char*>(s.c_str()));
  }

  // EAL initialization.

  // EAL initialization.
  if (!::eal_init(argv.size(), argv.data(), logger)) {
    return nullptr;
  }


  return std::make_unique<dpdk_eal>(logger);
}
