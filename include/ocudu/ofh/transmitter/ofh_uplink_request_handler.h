// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/transmitter/ofh_uplink_request_handler.h  (46 lines)
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


namespace ocudu {


struct prach_buffer_context;
struct resource_grid_context;
class shared_resource_grid;


namespace ofh {


class error_notifier;

/// \brief Open Fronthaul uplink request handler.
///
/// Handles PRACH and uplink data requests to capture uplink data. The uplink received data will be notified through the
/// \ref ofh_uplane_rx_symbol_notifier notifier.

/// \brief Open Fronthaul uplink request handler.
///
/// Handles PRACH and uplink data requests to capture uplink data. The uplink received data will be notified through the
/// \ref ofh_uplane_rx_symbol_notifier notifier.
class uplink_request_handler
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplink_request_handler() = default;

  /// \brief Requests the Open Fronthaul to capture a PRACH window.
  ///
  /// The Open Fronthaul must capture the window identified by \c context.
  ///
  /// \param[in] context PRACH window context.
  /// \param[in] buffer  PRACH buffer used to write the PRACH window.

  /// \brief Requests the Open Fronthaul to capture a PRACH window.
  ///
  /// The Open Fronthaul must capture the window identified by \c context.
  ///
  /// \param[in] context PRACH window context.
  /// \param[in] buffer  PRACH buffer used to write the PRACH window.
  virtual void handle_prach_occasion(const prach_buffer_context& context, shared_prach_buffer buffer) = 0;

  /// \brief Requests the Open Fronthaul to provide an uplink slot.
  ///
  /// The Open Fronthaul must process the slot described by \c context.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] buffer  Resource grid to store the processed slot.

  /// \brief Requests the Open Fronthaul to provide an uplink slot.
  ///
  /// The Open Fronthaul must process the slot described by \c context.
  ///
  /// \param[in] context Resource grid context.
  /// \param[in] buffer  Resource grid to store the processed slot.
  virtual void handle_new_uplink_slot(const resource_grid_context& context, const shared_resource_grid& grid) = 0;
};


} // namespace ofh
} // namespace ocudu
