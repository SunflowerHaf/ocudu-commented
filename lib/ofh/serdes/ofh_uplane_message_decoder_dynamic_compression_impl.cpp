// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_uplane_message_decoder_dynamic_compression_impl.cpp  (43 lines)
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

#include "ofh_uplane_message_decoder_dynamic_compression_impl.h"
#include "../support/network_order_binary_deserializer.h"


using namespace ocudu;
using namespace ofh;


uplane_message_decoder_impl::decoded_section_status
uplane_message_decoder_dynamic_compression_impl::decode_compression_header(
    decoder_uplane_section_params&     results,
    network_order_binary_deserializer& deserializer)
{
  if (OCUDU_UNLIKELY(deserializer.remaining_bytes() < 2 * sizeof(uint8_t))) {
    logger.info("Sector#{}: received an Open Fronthaul packet with size of '{}' bytes that is smaller than the user "
                "data compression header length",
                sector_id,
                deserializer.remaining_bytes());


    return uplane_message_decoder_impl::decoded_section_status::incomplete;
  }


  uint8_t value            = deserializer.read<uint8_t>();
  results.ud_comp_hdr.type = to_compression_type(value & 0x0f);

  // Consider a reserved value as malformed message.

  // Consider a reserved value as malformed message.
  if (OCUDU_UNLIKELY(results.ud_comp_hdr.type == compression_type::reserved)) {
    logger.info("Sector#{}: detected malformed Open Fronthaul message as the decoded compression type '{}' is invalid",
                sector_id,
                value & 0x0f);


    return uplane_message_decoder_impl::decoded_section_status::malformed;
  }


  unsigned data_width            = value >> 4U;
  results.ud_comp_hdr.data_width = (data_width == 0) ? MAX_IQ_WIDTH : data_width;

  // Advance the reserved byte.

  // Advance the reserved byte.
  deserializer.advance(1U);


  return uplane_message_decoder_impl::decoded_section_status::ok;
}
