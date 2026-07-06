// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_data_flow_cplane_scheduling_commands.h  (77 lines)
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
#include "ocudu/ofh/serdes/ofh_message_properties.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_data_flow_metrics.h"
#include "ocudu/ran/prach/prach_subcarrier_spacing.h"
#include "ocudu/ran/resource_allocation/ofdm_symbol_range.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace ofh {


class operation_controller;

/// Open Fronthaul Control-Plane PRACH context parameters.

/// Open Fronthaul Control-Plane PRACH context parameters.
struct data_flow_cplane_scheduling_prach_context {
  /// Slot point.
  /// Slot point.
  slot_point slot;
  /// eAxC.
  /// eAxC.
  unsigned eaxc;
  /// Filter type.
  /// Filter type.
  filter_index_type filter_type;
  /// This parameter is the last symbol that starts right at or before the PRACH preamble (after cyclic prefix).
  /// This parameter is the last symbol that starts right at or before the PRACH preamble (after cyclic prefix).
  unsigned start_symbol;
  /// Number of PRACH repetitions, used to initialize numSymbol parameter.
  /// Number of PRACH repetitions, used to initialize numSymbol parameter.
  unsigned nof_repetitions;
  /// PUSCH subcarrier spacing.
  /// PUSCH subcarrier spacing.
  subcarrier_spacing scs;
  /// PRACH subcarrier spacing.
  /// PRACH subcarrier spacing.
  prach_subcarrier_spacing prach_scs;
  /// First subcarrier index used by PRACH message.
  /// First subcarrier index used by PRACH message.
  unsigned prach_start_re;
  /// Number of PRBs used by PRACH.
  /// Number of PRBs used by PRACH.
  unsigned prach_nof_rb;
  /// Time offset to the start of PRACH.
  /// Time offset to the start of PRACH.
  unsigned time_offset;
};

/// Open Fronthaul Control-Plane type 1 context parameters.

/// Open Fronthaul Control-Plane type 1 context parameters.
struct data_flow_cplane_type_1_context {
  /// Slot point.
  /// Slot point.
  slot_point slot;
  /// eAxC.
  /// eAxC.
  unsigned eaxc;
  /// Filter type.
  /// Filter type.
  filter_index_type filter_type;
  /// Direction.
  /// Direction.
  data_direction direction;
  /// Symbol range.
  /// Symbol range.
  ofdm_symbol_range symbol_range;
};

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow.

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow.
class data_flow_cplane_scheduling_commands
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~data_flow_cplane_scheduling_commands() = default;

  /// Returns the controller of this Open Fronthaul Control-Plane data flow.

  /// Returns the controller of this Open Fronthaul Control-Plane data flow.
  virtual operation_controller& get_operation_controller() = 0;

  /// Enqueues Open Fronthaul section type 1 message with the given slot and eAxC.

  /// Enqueues Open Fronthaul section type 1 message with the given slot and eAxC.
  virtual void enqueue_section_type_1_message(const data_flow_cplane_type_1_context& context) = 0;

  /// Enqueues Open Fronthaul section type 3 PRACH message with the given parameters.

  /// Enqueues Open Fronthaul section type 3 PRACH message with the given parameters.
  virtual void enqueue_section_type_3_prach_message(const data_flow_cplane_scheduling_prach_context& context) = 0;

  /// Returns the performance metrics collector of this data flow.

  /// Returns the performance metrics collector of this data flow.
  virtual data_flow_message_encoding_metrics_collector* get_metrics_collector() = 0;
};


} // namespace ofh
} // namespace ocudu
