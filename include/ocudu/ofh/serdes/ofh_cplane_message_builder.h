// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/serdes/ofh_cplane_message_builder.h  (51 lines)
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
#include "ocudu/ofh/serdes/ofh_cplane_message_properties.h"


namespace ocudu {
namespace ofh {

/// \brief Open Fronthaul Control-Plane message builder interface.
///
/// Builds a Control-Plane message following the O-RAN Open Fronthaul specification.

/// \brief Open Fronthaul Control-Plane message builder interface.
///
/// Builds a Control-Plane message following the O-RAN Open Fronthaul specification.
class cplane_message_builder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~cplane_message_builder() = default;

  /// \brief Builds a DL/UL radio channel Control-Plane message into the given buffer using the given
  /// \c parameters.
  ///
  /// This Control-Plane message is used for most DL/UL radio channels.
  ///
  /// \param[out] buffer Buffer where the message will be built.
  /// \param[in] msg_params Control-Plane parameters.
  /// \return Number of bytes serialized in the buffer.

  /// \brief Builds a DL/UL radio channel Control-Plane message into the given buffer using the given
  /// \c parameters.
  ///
  /// This Control-Plane message is used for most DL/UL radio channels.
  ///
  /// \param[out] buffer Buffer where the message will be built.
  /// \param[in] msg_params Control-Plane parameters.
  /// \return Number of bytes serialized in the buffer.
  virtual unsigned build_dl_ul_radio_channel_message(span<uint8_t>                          buffer,
                                                     const cplane_section_type1_parameters& msg_params) = 0;

  /// \brief Builds Control-Plane message aimed at idle or guard periods indication from O-DU to O-RU.
  ///
  /// \param[out] buffer    Buffer where the message will be built.
  /// \param[in] msg_params Control-Plane parameters.
  /// \return Number of bytes serialized in the buffer.

  /// \brief Builds Control-Plane message aimed at idle or guard periods indication from O-DU to O-RU.
  ///
  /// \param[out] buffer    Buffer where the message will be built.
  /// \param[in] msg_params Control-Plane parameters.
  /// \return Number of bytes serialized in the buffer.
  virtual unsigned build_idle_guard_period_message(span<uint8_t>                          buffer,
                                                   const cplane_section_type0_parameters& msg_params) = 0;

  /// \brief Builds PRACH and mixed-numerology channel Control-Plane message into the given buffer using the given
  /// \c parameters.
  ///
  /// \param[out] buffer    Buffer where the message will be built.
  /// \param[in] msg_params Control-Plane parameters.
  /// \return Number of bytes serialized in the buffer.

  /// \brief Builds PRACH and mixed-numerology channel Control-Plane message into the given buffer using the given
  /// \c parameters.
  ///
  /// \param[out] buffer    Buffer where the message will be built.
  /// \param[in] msg_params Control-Plane parameters.
  /// \return Number of bytes serialized in the buffer.
  virtual unsigned build_prach_mixed_numerology_message(span<uint8_t>                          buffer,
                                                        const cplane_section_type3_parameters& msg_params) = 0;
};


} // namespace ofh
} // namespace ocudu
