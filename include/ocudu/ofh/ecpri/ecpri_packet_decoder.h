// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ecpri/ecpri_packet_decoder.h  (39 lines)
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
#include <variant>


namespace ocudu {
namespace ecpri {

/// eCPRI packet parameter.

/// eCPRI packet parameter.
struct packet_parameters {
  /// Common header.
  /// Common header.
  common_header header;
  /// eCPRI type parameters.
  /// eCPRI type parameters.
  std::variant<realtime_control_parameters, iq_data_parameters> type_params;
};

/// eCPRI packet decoder interface.

/// eCPRI packet decoder interface.
class packet_decoder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~packet_decoder() = default;

  /// \brief Decodes the given packet, filling the eCPRI params and returning a span to the eCPRI payload.
  ///
  /// If the decoder detects an unsupported value, it will return an empty span and the params value will be undefined.
  ///
  /// \param[in] packet eCPRI packet to decode.
  /// \param[out] params eCPRI decoded parameters.
  /// \return A span to the eCPRI payload on success, otherwise an empty span in case of error.

  /// \brief Decodes the given packet, filling the eCPRI params and returning a span to the eCPRI payload.
  ///
  /// If the decoder detects an unsupported value, it will return an empty span and the params value will be undefined.
  ///
  /// \param[in] packet eCPRI packet to decode.
  /// \param[out] params eCPRI decoded parameters.
  /// \return A span to the eCPRI payload on success, otherwise an empty span in case of error.
  virtual span<const uint8_t> decode(span<const uint8_t> packet, packet_parameters& params) = 0;
};


} // namespace ecpri
} // namespace ocudu
