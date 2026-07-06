// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ecpri/ecpri_factories.h  (26 lines)
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


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ecpri/ecpri_packet_builder.h"
#include "ocudu/ofh/ecpri/ecpri_packet_decoder.h"
#include <memory>


namespace ocudu {
namespace ecpri {

/// Creates and returns an eCPRI packet builder.

/// Creates and returns an eCPRI packet builder.
std::unique_ptr<packet_builder> create_ecpri_packet_builder();

/// Creates and returns an eCPRI packet decoder utilizing payload size encoded in eCPRI header.

/// Creates and returns an eCPRI packet decoder utilizing payload size encoded in eCPRI header.
std::unique_ptr<packet_decoder> create_ecpri_packet_decoder_using_payload_size(ocudulog::basic_logger& logger,
                                                                               unsigned                sector);

/// Creates and returns an eCPRI packet decoder ignoring payload size encoded in eCPRI header.

/// Creates and returns an eCPRI packet decoder ignoring payload size encoded in eCPRI header.
std::unique_ptr<packet_decoder> create_ecpri_packet_decoder_ignoring_payload_size(ocudulog::basic_logger& logger,
                                                                                  unsigned                sector);


} // namespace ecpri
} // namespace ocudu
