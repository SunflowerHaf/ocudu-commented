// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/packing_utils_generic.cpp  (57 lines)
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

#include "packing_utils_generic.h"


using namespace ocudu;
using namespace ofh;


void ocudu::ofh::pack_bytes(bit_buffer& buffer, span<const int16_t> compressed_iq, unsigned iq_width)
{
  static constexpr unsigned NUM_BITS_IN_BYTE = units::bytes(1).to_bits().value();


  unsigned start_pos = 0;
  for (int16_t sample : compressed_iq) {
    unsigned left_to_pack = iq_width;


    while (left_to_pack != 0) {
      unsigned nbits  = std::min(NUM_BITS_IN_BYTE, left_to_pack);
      uint8_t  masked = static_cast<uint8_t>(sample & 0x00ff);
      if (left_to_pack > NUM_BITS_IN_BYTE) {
        masked = sample >> (left_to_pack - NUM_BITS_IN_BYTE);
        sample &= mask_lsb_ones<uint16_t>(left_to_pack - NUM_BITS_IN_BYTE);
      }
      buffer.insert(masked, start_pos, nbits);
      start_pos += nbits;
      left_to_pack -= nbits;
    }
  }

  // Clear tail bits of the last used byte.

  // Clear tail bits of the last used byte.
  if (start_pos % NUM_BITS_IN_BYTE) {
    unsigned nbits = NUM_BITS_IN_BYTE - start_pos % NUM_BITS_IN_BYTE;
    buffer.insert(uint8_t(0), start_pos, nbits);
  }
}


int16_t ocudu::ofh::unpack_bits(const bit_buffer_reader& buffer, unsigned offset, unsigned length)
{
  static constexpr unsigned NUM_BITS_IN_BYTE = units::bytes(1).to_bits().value();


  int16_t  value             = 0;
  unsigned bits_left_to_read = length;


  while (bits_left_to_read) {
    if (bits_left_to_read > NUM_BITS_IN_BYTE) {
      value = buffer.extract(offset, NUM_BITS_IN_BYTE);
      value <<= (bits_left_to_read - NUM_BITS_IN_BYTE);
      bits_left_to_read -= NUM_BITS_IN_BYTE;
      offset += NUM_BITS_IN_BYTE;
      continue;
    }


    value |= buffer.extract(offset, bits_left_to_read);
    bits_left_to_read = 0;
  }
  return value;
}
