// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/receiver/ofh_sequence_id_checker.h  (29 lines)
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


#include <cstdint>


namespace ocudu {
namespace ofh {

/// Open Fronthaul sequence identifier checker.

/// Open Fronthaul sequence identifier checker.
class sequence_id_checker
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~sequence_id_checker() = default;

  /// \brief Updates the expected sequence identifier value for the given eAxC and compares it with the given sequence
  /// identifier, returning the difference between them.
  ///
  /// A negative difference means that the sequence identifier is from the past.
  /// A difference of 0 means that the current sequence identifier matches the expected.
  /// A positive difference means that the sequence identifier belongs to the future. In this case, the expected
  /// sequence identifier is updated with the given sequence identifier.

  /// \brief Updates the expected sequence identifier value for the given eAxC and compares it with the given sequence
  /// identifier, returning the difference between them.
  ///
  /// A negative difference means that the sequence identifier is from the past.
  /// A difference of 0 means that the current sequence identifier matches the expected.
  /// A positive difference means that the sequence identifier belongs to the future. In this case, the expected
  /// sequence identifier is updated with the given sequence identifier.
  virtual int update_and_compare_seq_id(unsigned eaxc, uint8_t seq_id) = 0;
};


} // namespace ofh
} // namespace ocudu
