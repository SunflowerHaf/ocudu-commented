// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h  (35 lines)
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


#include "ocudu/ofh/timing/slot_symbol_point.h"
#include <chrono>


namespace ocudu {
namespace ofh {

/// Slot symbol time point context.

/// Slot symbol time point context.
struct slot_symbol_point_context {
  slot_symbol_point symbol_point;
  /// Hyperframe number.
  /// Hyperframe number.
  unsigned                                           hfn;
  std::chrono::time_point<std::chrono::system_clock> time_point;
};

/// This interface notifies the timing boundary of an OFDM symbol over the air.

/// This interface notifies the timing boundary of an OFDM symbol over the air.
class ota_symbol_boundary_notifier
{
public:
  virtual ~ota_symbol_boundary_notifier() = default;

  /// \brief Notifies a new OTA symbol boundary event.
  ///
  /// Notifies that the beginning of a new OTA symbol has started.
  ///
  /// \param[in] symbol_point_context Current slot and symbol point.

  /// \brief Notifies a new OTA symbol boundary event.
  ///
  /// Notifies that the beginning of a new OTA symbol has started.
  ///
  /// \param[in] symbol_point_context Current slot and symbol point.
  virtual void on_new_symbol(const slot_symbol_point_context& symbol_point_context) = 0;
};


} // namespace ofh
} // namespace ocudu
