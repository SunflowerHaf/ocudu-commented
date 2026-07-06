// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/ethernet_frame_builder.h  (35 lines)
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
#include "ocudu/ofh/ethernet/vlan_ethernet_frame_params.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace ether {

/// \brief Describes the Ethernet frame builder.
///
/// Builds an Ethernet frame following the IEEE 802.3 and IEEE 802.1Q specifications.

/// \brief Describes the Ethernet frame builder.
///
/// Builds an Ethernet frame following the IEEE 802.3 and IEEE 802.1Q specifications.
class frame_builder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~frame_builder() = default;

  /// Returns the Ethernet header size in bytes.

  /// Returns the Ethernet header size in bytes.
  virtual units::bytes get_header_size() const = 0;

  /// \brief Builds an Ethernet frame using the given parameters into \c buffer.
  ///
  /// This function expects that the buffer already contains the payload of the frame. The builder will write the
  /// header in the first \ref frame_builder::get_header_size bytes of the buffer.
  ///
  /// \param[in] buffer Buffer where the frame will be built.

  /// \brief Builds an Ethernet frame using the given parameters into \c buffer.
  ///
  /// This function expects that the buffer already contains the payload of the frame. The builder will write the
  /// header in the first \ref frame_builder::get_header_size bytes of the buffer.
  ///
  /// \param[in] buffer Buffer where the frame will be built.
  virtual void build_frame(span<uint8_t> buffer) = 0;
};


} // namespace ether
} // namespace ocudu
