// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/serdes/ofh_uplane_message_decoder_properties.h  (54 lines)
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


#include "ocudu/adt/complex.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_properties.h"
#include "ocudu/ran/resource_block.h"
#include <optional>


namespace ocudu {
namespace ofh {

/// Maximum number of supported sections.

/// Maximum number of supported sections.
constexpr unsigned MAX_NOF_SUPPORTED_SECTIONS = 1U;

/// Open Fronthaul User-Plane section parameters.

/// Open Fronthaul User-Plane section parameters.
struct uplane_section_params {
  /// Section identifier.
  /// Section identifier.
  unsigned section_id;
  /// Resource block indicator.
  /// Resource block indicator.
  bool is_every_rb_used;
  /// Symbol number increment command.
  /// Symbol number increment command.
  bool use_current_symbol_number;
  /// Start PRB.
  /// Start PRB.
  unsigned start_prb;
  /// Number of PRBs (though a value of 0 signals more than 255 PRBs in the OFH specification, this field always
  /// contains the real amount of PRBs).
  /// Number of PRBs (though a value of 0 signals more than 255 PRBs in the OFH specification, this field always
  /// contains the real amount of PRBs).
  unsigned nof_prbs;
  /// User data compression header.
  /// User data compression header.
  ru_compression_params ud_comp_hdr;
  /// User data compression length.
  /// User data compression length.
  std::optional<unsigned> ud_comp_len;
  /// User data compression parameter.
  /// \note For simplicity, all the PRBs use the same compression parameters.
  /// User data compression parameter.
  /// \note For simplicity, all the PRBs use the same compression parameters.
  std::optional<unsigned> ud_comp_param;
  /// IQ samples for the number of PRBs indicated by \c nof_prbs.
  /// IQ samples for the number of PRBs indicated by \c nof_prbs.
  static_vector<cbf16_t, MAX_NOF_SUBCARRIERS> iq_samples;
};

/// Open Fronthaul User-Plane message decoder results.

/// Open Fronthaul User-Plane message decoder results.
struct uplane_message_decoder_results {
  /// Maximum number of sections supported by this result.
  /// Maximum number of sections supported by this result.
  static constexpr unsigned RESULTS_MAX_NOF_SUPPORTED_SECTIONS = 2U;

  /// Open Fronthaul User-Plane message parameters.

  /// Open Fronthaul User-Plane message parameters.
  uplane_message_params params;
  /// User-Plane message sections.
  /// User-Plane message sections.
  static_vector<uplane_section_params, RESULTS_MAX_NOF_SUPPORTED_SECTIONS> sections;
};


} // namespace ofh
} // namespace ocudu
