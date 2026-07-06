// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/transmitter/ofh_transmitter_timing_parameters.h  (36 lines)
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


#include <chrono>
#include <cmath>


namespace ocudu {
namespace ofh {

/// Structure storing the transmission window timing parameters expressed in a number of symbols.

/// Structure storing the transmission window timing parameters expressed in a number of symbols.
struct tx_window_timing_parameters {
  /// Offset from the current OTA symbol to the first symbol at which DL Control-Plane message can be sent, or in
  /// other words it is the offset to the start of DL Control-Plane transmission window. Must be calculated based on
  /// \c T1a_max_cp_dl parameter.
  /// Offset from the current OTA symbol to the first symbol at which DL Control-Plane message can be sent, or in
  /// other words it is the offset to the start of DL Control-Plane transmission window. Must be calculated based on
  /// \c T1a_max_cp_dl parameter.
  unsigned sym_cp_dl_start;
  /// Offset from the current OTA symbol to the last symbol at which DL Control-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_min_cp_dl parameter.
  /// Offset from the current OTA symbol to the last symbol at which DL Control-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_min_cp_dl parameter.
  unsigned sym_cp_dl_end;
  /// Offset from the current OTA symbol to the first symbol at which UL Control-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_max_cp_ul parameter.
  /// Offset from the current OTA symbol to the first symbol at which UL Control-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_max_cp_ul parameter.
  unsigned sym_cp_ul_start;
  /// Offset from the current OTA symbol to the last symbol at which UL Control-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_min_cp_ul parameter.
  /// Offset from the current OTA symbol to the last symbol at which UL Control-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_min_cp_ul parameter.
  unsigned sym_cp_ul_end;
  /// Offset from the current OTA symbol to the first symbol at which DL User-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_max_up parameter.
  /// Offset from the current OTA symbol to the first symbol at which DL User-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_max_up parameter.
  unsigned sym_up_dl_start;
  /// Offset from the current OTA symbol to the last symbol at which DL User-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_min_up parameter.
  /// Offset from the current OTA symbol to the last symbol at which DL User-Plane message can be sent within its
  /// transmission window. Must be calculated based on \c T1a_min_up parameter.
  unsigned sym_up_dl_end;
};


} // namespace ofh
} // namespace ocudu
