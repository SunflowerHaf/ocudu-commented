// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ofh_error_notifier.h  (42 lines)
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


#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul error context.

/// Open Fronthaul error context.
struct error_context {
  /// Slot context.
  /// Slot context.
  slot_point slot;
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
};

/// Open Fronthaul error notifier.

/// Open Fronthaul error notifier.
class error_notifier
{
public:
  virtual ~error_notifier() = default;

  /// \brief Notifies a late downlink message.
  ///
  /// \param[in] context Context of the error.

  /// \brief Notifies a late downlink message.
  ///
  /// \param[in] context Context of the error.
  virtual void on_late_downlink_message(const error_context& context) = 0;

  /// \brief Notifies a late uplink request message.
  ///
  /// \param[in] context Context of the error.

  /// \brief Notifies a late uplink request message.
  ///
  /// \param[in] context Context of the error.
  virtual void on_late_uplink_message(const error_context& context) = 0;

  /// \brief Notifies a late PRACH request message.
  ///
  /// \param[in] context Context of the error.

  /// \brief Notifies a late PRACH request message.
  ///
  /// \param[in] context Context of the error.
  virtual void on_late_prach_message(const error_context& context) = 0;
};


} // namespace ofh
} // namespace ocudu
