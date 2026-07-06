// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ecpri/ecpri_packet_builder.h  (43 lines)
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


#include "ocudu/adt/span.h"
#include "ocudu/ofh/ecpri/ecpri_packet_properties.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace ecpri {

/// Describes the eCPRI packet builder.

/// Describes the eCPRI packet builder.
class packet_builder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~packet_builder() = default;

  /// Returns the eCPRI header size in bytes for the given eCPRI message type.

  /// Returns the eCPRI header size in bytes for the given eCPRI message type.
  virtual units::bytes get_header_size(message_type msg_type) const = 0;

  /// Builds a control eCPRI packet using the given control parameters into the given \c buffer.
  ///
  /// This function expects that the buffer already contains the payload of the packet. The builder will write the
  /// header in the first \ref ecpri_packet_builder::get_header_size bytes of the buffer.
  ///
  /// \param[in] buffer Buffer where the packet will be built.
  /// \param[in] msg_params eCPRI message parameters.

  /// Builds a control eCPRI packet using the given control parameters into the given \c buffer.
  ///
  /// This function expects that the buffer already contains the payload of the packet. The builder will write the
  /// header in the first \ref ecpri_packet_builder::get_header_size bytes of the buffer.
  ///
  /// \param[in] buffer Buffer where the packet will be built.
  /// \param[in] msg_params eCPRI message parameters.
  virtual void build_control_packet(span<uint8_t> buffer, const realtime_control_parameters& msg_params) = 0;

  /// Builds a data eCPRI packet using the given data parameters into the given \c buffer.
  ///
  /// This function expects that the buffer already contains the payload of the packet. The builder will write the
  /// header in the first \ref ecpri_packet_builder::get_header_size bytes of the buffer.
  ///
  /// \param[in] buffer Buffer where the packet will be built.
  /// \param[in] msg_params eCPRI message parameters.

  /// Builds a data eCPRI packet using the given data parameters into the given \c buffer.
  ///
  /// This function expects that the buffer already contains the payload of the packet. The builder will write the
  /// header in the first \ref ecpri_packet_builder::get_header_size bytes of the buffer.
  ///
  /// \param[in] buffer Buffer where the packet will be built.
  /// \param[in] msg_params eCPRI message parameters.
  virtual void build_data_packet(span<uint8_t> buffer, const iq_data_parameters& msg_params) = 0;
};


} // namespace ecpri
} // namespace ocudu
