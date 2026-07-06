// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/serdes/ofh_uplane_message_properties.h  (34 lines)
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
#include "ocudu/ofh/serdes/ofh_message_properties.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul User-Plane message parameters.

/// Open Fronthaul User-Plane message parameters.
struct uplane_message_params {
  /// Data direction.
  /// Data direction.
  data_direction direction;
  /// Frame, subframe and slot information.
  /// Frame, subframe and slot information.
  slot_point slot;
  /// Filter index.
  /// Filter index.
  filter_index_type filter_index;
  /// Initial PRB index used in the given /c symbol_id.
  /// Initial PRB index used in the given /c symbol_id.
  unsigned start_prb;
  /// Number of PRBs in this symbol.
  /// Number of PRBs in this symbol.
  unsigned nof_prb;
  /// Symbol identifier.
  /// Symbol identifier.
  unsigned symbol_id;
  /// Section type of the message to be built.
  /// Section type of the message to be built.
  section_type sect_type;
  /// IQ data compression parameters.
  /// IQ data compression parameters.
  ru_compression_params compression_params;
};


} // namespace ofh
} // namespace ocudu
