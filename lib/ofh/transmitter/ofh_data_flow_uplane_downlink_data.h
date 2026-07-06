// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_data_flow_uplane_downlink_data.h  (52 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#pragma once


#include "ofh_data_flow_cuplane_encoding_metrics_collector.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_data_flow_metrics.h"
#include "ocudu/ran/resource_allocation/ofdm_symbol_range.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {
struct resource_grid_context;
class shared_resource_grid;


namespace ofh {


class operation_controller;

/// Open Fronthaul User-Plane downlink data flow resource grid context.

/// Open Fronthaul User-Plane downlink data flow resource grid context.
struct data_flow_uplane_resource_grid_context {
  /// Provides the slot context within the system frame.
  /// Provides the slot context within the system frame.
  slot_point slot;
  /// Provides the sector identifier.
  /// Provides the sector identifier.
  uint8_t sector;
  /// Provides the port identifier.
  /// Provides the port identifier.
  uint8_t port;
  /// eAxC.
  /// eAxC.
  uint8_t eaxc;
  /// Symbol range.
  /// Symbol range.
  ofdm_symbol_range symbol_range;
};

/// Open Fronthaul User-Plane downlink data flow.

/// Open Fronthaul User-Plane downlink data flow.
class data_flow_uplane_downlink_data
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~data_flow_uplane_downlink_data() = default;

  /// Returns the controller of this Open Fronthaul User-Plane data flow.

  /// Returns the controller of this Open Fronthaul User-Plane data flow.
  virtual operation_controller& get_operation_controller() = 0;

  /// Enqueues the User-Plane downlink data messages with the given context and resource grid.

  /// Enqueues the User-Plane downlink data messages with the given context and resource grid.
  virtual void enqueue_section_type_1_message(const data_flow_uplane_resource_grid_context& context,
                                              const shared_resource_grid&                   grid) = 0;

  /// Returns the performance metrics collector of this data flow.

  /// Returns the performance metrics collector of this data flow.
  virtual data_flow_message_encoding_metrics_collector* get_metrics_collector() = 0;
};


} // namespace ofh
} // namespace ocudu
