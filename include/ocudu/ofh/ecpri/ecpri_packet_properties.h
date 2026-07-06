// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ecpri/ecpri_packet_properties.h  (43 lines)
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


#include "ocudu/support/units.h"


namespace ocudu {
namespace ecpri {

/// eCPRI message types.

/// eCPRI message types.
enum class message_type : uint8_t { iq_data = 0x00, rt_control_data = 0x02 };

/// eCPRI common header.

/// eCPRI common header.
struct common_header {
  /// Protocol revision.
  /// Protocol revision.
  unsigned revision;
  /// Last packet flag.
  /// Last packet flag.
  bool is_last_packet;
  /// Message type.
  /// Message type.
  message_type msg_type;
  /// Payload size.
  /// Payload size.
  units::bytes payload_size;
};

/// eCPRI Real-Time control parameters.

/// eCPRI Real-Time control parameters.
struct realtime_control_parameters {
  /// Identifier of a series of Real-Time Control Data messages, as per eCPRI v2 Section 3.2.4.3.
  /// Identifier of a series of Real-Time Control Data messages, as per eCPRI v2 Section 3.2.4.3.
  uint16_t rtc_id;
  /// Identifier of each message in a series of Real-Time Control Data messages, as per eCPRI v2 Section 3.2.4.3.
  /// Identifier of each message in a series of Real-Time Control Data messages, as per eCPRI v2 Section 3.2.4.3.
  uint16_t seq_id;
};

/// eCPRI IQ data parameters.

/// eCPRI IQ data parameters.
struct iq_data_parameters {
  /// Identifier of a series of IQ Data Transfer messages, as per eCPRI v2 Section 3.2.4.1.
  /// Identifier of a series of IQ Data Transfer messages, as per eCPRI v2 Section 3.2.4.1.
  uint16_t pc_id;
  /// Identifier of each message in a series of IQ Data Transfer messages, as per eCPRI v2 Section 3.2.4.1.
  /// Identifier of each message in a series of IQ Data Transfer messages, as per eCPRI v2 Section 3.2.4.1.
  uint16_t seq_id;
};


} // namespace ecpri
} // namespace ocudu
