// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ecpri/ecpri_packet_decoder_impl.h  (70 lines)
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


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ecpri/ecpri_packet_decoder.h"


namespace ocudu {
namespace ecpri {

/// eCPRI packet decoder implementation.

/// eCPRI packet decoder implementation.
class packet_decoder_impl : public packet_decoder
{
public:
  packet_decoder_impl(ocudulog::basic_logger& logger_, unsigned sector_) : logger(logger_), sector(sector_) {}

  // See interface for documentation.

  // See interface for documentation.
  span<const uint8_t> decode(span<const uint8_t> packet, packet_parameters& params) override;


private:
  /// Decodes an eCPRI common header from the packet.
  ///
  /// \param packet eCPRI packet to decode.
  /// \param params eCPRI decoded parameters.
  /// \return A span to the eCPRI parameters and payload on success, otherwise an empty span.
  /// Decodes an eCPRI common header from the packet.
  ///
  /// \param packet eCPRI packet to decode.
  /// \param params eCPRI decoded parameters.
  /// \return A span to the eCPRI parameters and payload on success, otherwise an empty span.
  span<const uint8_t> decode_header(span<const uint8_t> packet, packet_parameters& params);

  /// Decodes eCPRI parameters and extracts eCPRI payload from the given packet.
  /// \param packet eCPRI parameters and payload to decode.
  /// \param params eCPRI decoded parameters.
  /// \return A span to the eCPRI payload on success, otherwise an empty span.

  /// Decodes eCPRI parameters and extracts eCPRI payload from the given packet.
  /// \param packet eCPRI parameters and payload to decode.
  /// \param params eCPRI decoded parameters.
  /// \return A span to the eCPRI payload on success, otherwise an empty span.
  virtual span<const uint8_t> decode_payload(span<const uint8_t> packet, packet_parameters& params) = 0;


protected:
  ocudulog::basic_logger& logger;
  const unsigned          sector;
};

/// \brief eCPRI packet decoder implementation utilizing payload size encoded in a eCPRI header.

/// \brief eCPRI packet decoder implementation utilizing payload size encoded in a eCPRI header.
class packet_decoder_use_header_payload_size : public packet_decoder_impl
{
public:
  packet_decoder_use_header_payload_size(ocudulog::basic_logger& logger_, unsigned sector_) :
    packet_decoder_impl(logger_, sector_)
  {
  }


private:
  // See interface for documentation.
  // See interface for documentation.
  span<const uint8_t> decode_payload(span<const uint8_t> packet, packet_parameters& params) override;
};

/// \brief eCPRI packet decoder implementation ignoring payload size encoded in a eCPRI header and using remaining
/// packet bytes as a payload.

/// \brief eCPRI packet decoder implementation ignoring payload size encoded in a eCPRI header and using remaining
/// packet bytes as a payload.
class packet_decoder_ignore_header_payload_size : public packet_decoder_impl
{
public:
  packet_decoder_ignore_header_payload_size(ocudulog::basic_logger& logger_, unsigned sector_) :
    packet_decoder_impl(logger_, sector_)
  {
  }


private:
  // See interface for documentation.
  // See interface for documentation.
  span<const uint8_t> decode_payload(span<const uint8_t> packet, packet_parameters& params) override;
};


} // namespace ecpri
} // namespace ocudu
