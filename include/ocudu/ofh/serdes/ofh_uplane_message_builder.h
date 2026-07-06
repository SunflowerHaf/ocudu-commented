// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/serdes/ofh_uplane_message_builder.h  (37 lines)
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


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_properties.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace ofh {

/// \brief Open Fronthaul User-Plane message builder interface.
///
/// Builds a User Plane message following the O-RAN Open Fronthaul specification.

/// \brief Open Fronthaul User-Plane message builder interface.
///
/// Builds a User Plane message following the O-RAN Open Fronthaul specification.
class uplane_message_builder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplane_message_builder() = default;

  /// Returns the Open Fronthaul User-Plane header size in bytes.

  /// Returns the Open Fronthaul User-Plane header size in bytes.
  virtual units::bytes get_header_size(const ru_compression_params& params) const = 0;

  /// \brief Builds a User Plane message given the \c config parameters, places result in \c buffer.
  ///
  /// \param[out] buffer Buffer where the message will be built.
  /// \param[in] iq_data IQ samples.
  /// \param[in] config  User plane message parameters.
  /// \return Number of bytes serialized in the buffer.

  /// \brief Builds a User Plane message given the \c config parameters, places result in \c buffer.
  ///
  /// \param[out] buffer Buffer where the message will be built.
  /// \param[in] iq_data IQ samples.
  /// \param[in] config  User plane message parameters.
  /// \return Number of bytes serialized in the buffer.
  virtual unsigned
  build_message(span<uint8_t> buffer, span<const cbf16_t> iq_data, const uplane_message_params& params) = 0;
};


} // namespace ofh
} // namespace ocudu
