// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/compression/compression_properties.h  (33 lines)
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


#include "ocudu/ofh/compression/compression_params.h"
#include "ocudu/ran/resource_block.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace ofh {

/// Returns true if the compression parameter is present based on the given compression type.

/// Returns true if the compression parameter is present based on the given compression type.
constexpr bool is_compression_param_present(compression_type type)
{
  return (type == compression_type::BFP) || (type == compression_type::mu_law) ||
         (type == compression_type::bfp_selective) || (type == compression_type::mod_selective);
}

/// Returns size of a PRB compressed according to the given compression parameters.

/// Returns size of a PRB compressed according to the given compression parameters.
inline units::bytes get_compressed_prb_size(const ru_compression_params& params)
{
  static constexpr units::bytes compr_param_size{1};


  unsigned prb_size = NOF_SUBCARRIERS_PER_RB * 2 * params.data_width;
  if (is_compression_param_present(params.type)) {
    prb_size += compr_param_size.to_bits().value();
  }
  return units::bits(prb_size).round_up_to_bytes();
}


} // namespace ofh
} // namespace ocudu
