// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/compression_factory.cpp  (162 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#include "ocudu/ofh/compression/compression_factory.h"
#include "iq_compression_bfp_impl.h"
#include "iq_compression_death_impl.h"
#include "iq_compression_none_impl.h"
#include "iq_compressor_selector.h"
#include "iq_decompressor_selector.h"
#include "ocudu/support/cpu_features.h"
#include "ocudu/support/error_handling.h"


#ifdef __x86_64__
#include "iq_compression_bfp_avx2.h"
#include "iq_compression_bfp_avx512.h"
#include "iq_compression_none_avx2.h"
#include "iq_compression_none_avx512.h"
#endif


#ifdef __ARM_NEON
#include "iq_compression_bfp_neon.h"
#include "iq_compression_none_neon.h"
#endif // __ARM_NEON


using namespace ocudu;
using namespace ofh;


std::unique_ptr<iq_compressor> ocudu::ofh::create_iq_compressor(compression_type        type,
                                                                ocudulog::basic_logger& logger,
                                                                float                   iq_scaling,
                                                                const std::string&      impl_type)
{
  switch (type) {
    case compression_type::none:
#ifdef __x86_64__
    {
      bool supports_avx2   = cpu_supports_feature(cpu_feature::avx2);
      bool supports_avx512 = cpu_supports_feature(cpu_feature::avx512f) &&
                             cpu_supports_feature(cpu_feature::avx512vl) && cpu_supports_feature(cpu_feature::avx512bw);
      if (((impl_type == "avx512") || (impl_type == "auto")) && supports_avx512) {
        return std::make_unique<iq_compression_none_avx512>(logger, iq_scaling);
      }
      if (((impl_type == "avx2") || (impl_type == "auto")) && supports_avx2) {
        return std::make_unique<iq_compression_none_avx2>(logger, iq_scaling);
      }
    }
#endif
#ifdef __ARM_NEON
      if ((impl_type == "neon") || (impl_type == "auto")) {
        return std::make_unique<iq_compression_none_neon>(logger, iq_scaling);
      }
#endif // __ARM_NEON
      return std::make_unique<iq_compression_none_impl>(logger, iq_scaling);
    case compression_type::BFP:
#ifdef __x86_64__
    {
      bool supports_avx2   = cpu_supports_feature(cpu_feature::avx2);
      bool supports_avx512 = cpu_supports_feature(cpu_feature::avx512f) &&
                             cpu_supports_feature(cpu_feature::avx512vl) &&
                             cpu_supports_feature(cpu_feature::avx512bw) &&
                             cpu_supports_feature(cpu_feature::avx512dq) && cpu_supports_feature(cpu_feature::avx512cd);
      if (((impl_type == "avx512") || (impl_type == "auto")) && supports_avx512) {
        return std::make_unique<iq_compression_bfp_avx512>(logger, iq_scaling);
      }
      if (((impl_type == "avx2") || (impl_type == "auto")) && supports_avx2) {
        return std::make_unique<iq_compression_bfp_avx2>(logger, iq_scaling);
      }
    }
#endif
#ifdef __ARM_NEON
      if ((impl_type == "neon") || (impl_type == "auto")) {
        return std::make_unique<iq_compression_bfp_neon>(logger, iq_scaling);
      }
#endif // __ARM_NEON
      return std::make_unique<iq_compression_bfp_impl>(logger, iq_scaling);
    case compression_type::block_scaling:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::mu_law:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::modulation:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::bfp_selective:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::mod_selective:
      return std::make_unique<iq_compression_death_impl>();
    default:
      report_fatal_error("Compression type '{}' is not implemented", to_string(type));
  }
}


std::unique_ptr<iq_decompressor>
ocudu::ofh::create_iq_decompressor(compression_type type, ocudulog::basic_logger& logger, const std::string& impl_type)
{
  switch (type) {
    case compression_type::none:
#ifdef __x86_64__
    {
      bool supports_avx2 = cpu_supports_feature(cpu_feature::avx2);
      bool supports_avx512 =
          cpu_supports_feature(cpu_feature::avx512f) && cpu_supports_feature(cpu_feature::avx512vl) &&
          cpu_supports_feature(cpu_feature::avx512bw) && cpu_supports_feature(cpu_feature::avx512vbmi);
      if (((impl_type == "avx512") || (impl_type == "auto")) && supports_avx512) {
        return std::make_unique<iq_compression_none_avx512>(logger);
      }
      if (((impl_type == "avx2") || (impl_type == "auto")) && supports_avx2) {
        return std::make_unique<iq_compression_none_avx2>(logger);
      }
    }
#endif
#ifdef __ARM_NEON
      if ((impl_type == "neon") || (impl_type == "auto")) {
        return std::make_unique<iq_compression_none_neon>(logger);
      }
#endif // __ARM_NEON
      return std::make_unique<iq_compression_none_impl>(logger);
    case compression_type::BFP:
#ifdef __x86_64__
    {
      bool supports_avx2 = cpu_supports_feature(cpu_feature::avx2);
      bool supports_avx512 =
          cpu_supports_feature(cpu_feature::avx512f) && cpu_supports_feature(cpu_feature::avx512vl) &&
          cpu_supports_feature(cpu_feature::avx512bw) && cpu_supports_feature(cpu_feature::avx512vbmi);
      if (((impl_type == "avx512") || (impl_type == "auto")) && supports_avx512) {
        return std::make_unique<iq_compression_bfp_avx512>(logger);
      }
      if (((impl_type == "avx2") || (impl_type == "auto")) && supports_avx2) {
        return std::make_unique<iq_compression_bfp_avx2>(logger);
      }
    }
#endif
#ifdef __ARM_NEON
      if ((impl_type == "neon") || (impl_type == "auto")) {
        return std::make_unique<iq_compression_bfp_neon>(logger);
      }
#endif // __ARM_NEON
      return std::make_unique<iq_compression_bfp_impl>(logger);
    case compression_type::block_scaling:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::mu_law:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::modulation:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::bfp_selective:
      return std::make_unique<iq_compression_death_impl>();
    case compression_type::mod_selective:
      return std::make_unique<iq_compression_death_impl>();
    default:
      report_fatal_error("Compression type '{}' is not implemented", to_string(type));
  }
}


std::unique_ptr<iq_decompressor> ocudu::ofh::create_iq_decompressor_selector(
    std::array<std::unique_ptr<iq_decompressor>, NOF_COMPRESSION_TYPES_SUPPORTED> decompressors)
{
  return std::make_unique<iq_decompressor_selector>(std::move(decompressors));
}


std::unique_ptr<iq_compressor> ocudu::ofh::create_iq_compressor_selector(
    std::array<std::unique_ptr<iq_compressor>, NOF_COMPRESSION_TYPES_SUPPORTED> compressors)
{
  return std::make_unique<iq_compressor_selector>(std::move(compressors));
}
