// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ofh_uplane_rx_symbol_notifier.h  (45 lines)
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


#include "ocudu/phy/support/shared_prach_buffer.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {
struct prach_buffer_context;
class shared_resource_grid;


namespace ofh {

/// User-Plane reception symbol context.

/// User-Plane reception symbol context.
struct uplane_rx_symbol_context {
  /// Slot point.
  /// Slot point.
  slot_point slot;
  /// Symbol identifier.
  /// Symbol identifier.
  unsigned symbol;
  /// Sector.
  /// Sector.
  unsigned sector;
};

/// Open Fronthaul User-Plane symbol reception notifier.

/// Open Fronthaul User-Plane symbol reception notifier.
class uplane_rx_symbol_notifier
{
public:
  virtual ~uplane_rx_symbol_notifier() = default;

  /// \brief Notifies the completion of an OFDM symbol for a given context.
  ///
  /// \param[in] context Notification context.
  /// \param[in] grid    Resource grid that belongs to the context.

  /// \brief Notifies the completion of an OFDM symbol for a given context.
  ///
  /// \param[in] context Notification context.
  /// \param[in] grid    Resource grid that belongs to the context.
  virtual void
  on_new_uplink_symbol(const uplane_rx_symbol_context& context, shared_resource_grid grid, bool is_valid) = 0;

  /// \brief Notifies the completion of a PRACH window.
  /// \param[in] context PRACH context.
  /// \param[in] buffer  PRACH buffer.

  /// \brief Notifies the completion of a PRACH window.
  /// \param[in] context PRACH context.
  /// \param[in] buffer  PRACH buffer.
  virtual void on_new_prach_window_data(const prach_buffer_context& context, shared_prach_buffer buffer) = 0;
};


} // namespace ofh
} // namespace ocudu
