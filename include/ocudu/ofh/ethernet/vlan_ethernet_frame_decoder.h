// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/vlan_ethernet_frame_decoder.h  (33 lines)
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


namespace ocudu {
namespace ether {

/// \brief Describes the VLAN Ethernet frame decoder.
///
/// Decodes a VLAN Ethernet frame following the IEEE 802.3 and IEEE 802.1Q specifications.

/// \brief Describes the VLAN Ethernet frame decoder.
///
/// Decodes a VLAN Ethernet frame following the IEEE 802.3 and IEEE 802.1Q specifications.
class vlan_frame_decoder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~vlan_frame_decoder() = default;

  /// \brief Decodes the contents in the given buffer into a VLAN Ethernet frame.
  ///
  /// Decodes the contents of the buffer, filling the fields in the \c eth_params structure. Returns a new span with the
  /// VLAN Ethernet header removed.
  ///
  /// \param[in]  frame Frame to be decoded.
  /// \param[out] eth_params Ethernet message parameters or undefined contents in case of error.
  /// \return A span containing the payload of the VLAN Ethernet frame or an empty span in case of error.

  /// \brief Decodes the contents in the given buffer into a VLAN Ethernet frame.
  ///
  /// Decodes the contents of the buffer, filling the fields in the \c eth_params structure. Returns a new span with the
  /// VLAN Ethernet header removed.
  ///
  /// \param[in]  frame Frame to be decoded.
  /// \param[out] eth_params Ethernet message parameters or undefined contents in case of error.
  /// \return A span containing the payload of the VLAN Ethernet frame or an empty span in case of error.
  virtual span<const uint8_t> decode(span<const uint8_t> frame, vlan_frame_params& eth_params) = 0;
};


} // namespace ether
} // namespace ocudu
