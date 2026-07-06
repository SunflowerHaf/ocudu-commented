// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/compression/compression_params.h  (114 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/ofh
// Open Fronthaul public interface headers. CONDITIONAL: linked into the binary via a temporary dependency (see lib/ofh note) but not used at runtime in split-8. These headers define the OFH contract between the lib/ofh library and its callers (primarily lib/ru/ofh).
//
// Contents:
//   ofh/compression/      — IQ compressor/decompressor abstract interfaces and compression parameter types (scheme, data width, BFP exponent).
//   ofh/ecpri/            — eCPRI packet builder, decoder, and property types.
//   ofh/ethernet/         — Ethernet frame builder/receiver interfaces, VLAN tag types, and port configuration.
//   ofh/ofh_factories.h   — Top-level OFH sector factory.
//   ofh/ofh_sector.h      — OFH sector interface (one per radio sector/cell).
//   ofh/receiver/         — OFH uplink receiver interface (delivers received IQ).
//   ofh/serdes/           — C-plane and U-plane message serialiser interfaces.
//   ofh/timing/           — OFH timing controller interface (slot indication source).
//   ofh/transmitter/      — OFH downlink transmitter interface.
// =============================================================================

#pragma once


#include "ocudu/support/ocudu_assert.h"
#include <algorithm>
#include <string>


namespace ocudu {
namespace ofh {

/// Maximum allowed bit width of compressed IQ data.

/// Maximum allowed bit width of compressed IQ data.
constexpr unsigned MAX_IQ_WIDTH = 16U;

/// Bit width used by quantization of input complex IQ samples.

/// Bit width used by quantization of input complex IQ samples.
constexpr unsigned Q_BIT_WIDTH = MAX_IQ_WIDTH;

/// Number of compression types supported.

/// Number of compression types supported.
constexpr unsigned NOF_COMPRESSION_TYPES_SUPPORTED = 7U;

/// Compression type used to (de)compress IQ samples.

/// Compression type used to (de)compress IQ samples.
enum class compression_type {
  /// No compression.
  /// No compression.
  none,
  /// Block floating point compression (BFP).
  /// Block floating point compression (BFP).
  BFP,
  /// Block scaling compression.
  /// Block scaling compression.
  block_scaling,
  /// Mu-law compression.
  /// Mu-law compression.
  mu_law,
  /// Modulation compression.
  /// Modulation compression.
  modulation,
  /// BFP + selective RE sending.
  /// BFP + selective RE sending.
  bfp_selective,
  /// Modulation compression + selective RE sending.
  /// Modulation compression + selective RE sending.
  mod_selective,
  /// Reserved value.
  /// Reserved value.
  reserved
};

/// Converts and returns the given compression type into an integer.

/// Converts and returns the given compression type into an integer.
constexpr unsigned to_value(compression_type c)
{
  return static_cast<unsigned>(c);
}

/// IQ data compression parameters.

/// IQ data compression parameters.
struct ru_compression_params {
  /// IQ data compression used in the packet.
  /// IQ data compression used in the packet.
  compression_type type;
  /// Width of I and Q sample in the packet.
  /// Width of I and Q sample in the packet.
  unsigned data_width;
};


constexpr compression_type to_compression_type(unsigned compr_value)
{
  return (compr_value < static_cast<unsigned>(compression_type::reserved)) ? static_cast<compression_type>(compr_value)
                                                                           : compression_type::reserved;
}


inline compression_type to_compression_type(const std::string& compr)
{
  std::string compr_lower = compr;
  std::transform(compr.begin(), compr.end(), compr_lower.begin(), [](char c) { return std::tolower(c); });


  if (compr_lower == "none") {
    return compression_type::none;
  }
  if (compr_lower == "bfp") {
    return compression_type::BFP;
  }
  if (compr_lower == "bfp selective") {
    return compression_type::bfp_selective;
  }
  if (compr_lower == "block scaling") {
    return compression_type::block_scaling;
  }
  if (compr_lower == "mu law") {
    return compression_type::mu_law;
  }
  if (compr_lower == "modulation") {
    return compression_type::modulation;
  }
  if (compr_lower == "modulation selective") {
    return compression_type::mod_selective;
  }


  ocudu_assert(0, "Unknown compression method={}", compr);
  return compression_type::none;
}


inline std::string to_string(compression_type c)
{
  switch (c) {
    case compression_type::none:
      return "none";
    case compression_type::BFP:
      return "BFP";
    case compression_type::bfp_selective:
      return "BFP selective";
    case compression_type::block_scaling:
      return "Block scaling";
    case compression_type::mu_law:
      return "Mu law";
    case compression_type::modulation:
      return "Modulation";
    default:
      return "Modulation selective";
  }
}


} // namespace ofh
} // namespace ocudu
