// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_uplane_message_builder_impl.cpp  (142 lines)
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

#include "ofh_uplane_message_builder_impl.h"
#include "../serdes/ofh_cuplane_constants.h"
#include "../support/network_order_binary_serializer.h"
#include "ocudu/ofh/compression/compression_properties.h"
#include "ocudu/ofh/compression/iq_compressor.h"
#include "ocudu/ran/resource_block.h"


using namespace ocudu;
using namespace ofh;

/// Encodes data direction, payload version and filter index.

/// Encodes data direction, payload version and filter index.
static uint8_t encode_data_direction()
{
  uint8_t octet = 0;
  // Data direction (DL); offset: 7, 1 bit long.
  // Data direction (DL); offset: 7, 1 bit long.
  octet |= uint8_t(to_value(data_direction::downlink)) << 7u;
  // Payload version; offset: 4, 3 bits long.
  // Payload version; offset: 4, 3 bits long.
  octet |= uint8_t(OFH_PAYLOAD_VERSION) << 4u;
  // Filter index is fixed to 0, skip it.

  // Filter index is fixed to 0, skip it.

  return octet;
}

/// Encodes subframe index and MSB bits of slot index.

/// Encodes subframe index and MSB bits of slot index.
static uint8_t encode_subframe_and_slot(slot_point slot)
{
  uint8_t octet = 0;
  // Subframe index; offset: 4, 4 bits long.
  // Subframe index; offset: 4, 4 bits long.
  octet |= uint8_t(slot.subframe_index()) << 4u;
  // Four MSBs of the slot index within 1ms subframe; offset: 4, 6 bits long.
  // Four MSBs of the slot index within 1ms subframe; offset: 4, 6 bits long.
  octet |= uint8_t(slot.subframe_slot_index() >> 2u);


  return octet;
}

/// Encodes remaining LSB bits of the slot index and then symbol index.

/// Encodes remaining LSB bits of the slot index and then symbol index.
static uint8_t encode_slot_lsb_and_symbol(const uplane_message_params& params)
{
  uint8_t octet = 0;
  octet |= uint8_t(params.slot.subframe_slot_index() & 0x3) << 6u;
  octet |= uint8_t(params.symbol_id);


  return octet;
}

/// Encodes and returns the 4 LSB bits section id, the rb bit, number of symbols and the 2 MSB bits of start PRB.

/// Encodes and returns the 4 LSB bits section id, the rb bit, number of symbols and the 2 MSB bits of start PRB.
static uint8_t encode_sect_id_rb_symbols(const uplane_message_params& params)
{
  uint8_t octet = 0;
  octet |= uint8_t(rb_id_type::every_rb_used) << 3u;
  octet |= uint8_t(symbol_incr_type::current_symbol_number) << 2u;
  octet |= uint8_t(params.start_prb >> 8u) & 0x3;


  return octet;
}

/// Writes radio application header to the output buffer.

/// Writes radio application header to the output buffer.
static void build_radio_app_header(network_order_binary_serializer& serializer, const uplane_message_params& params)
{
  // Data direction + payload version + filter index (1 Byte).
  // Data direction + payload version + filter index (1 Byte).
  serializer.write(encode_data_direction());

  // Write FrameId (1 Byte) - a counter for 10 ms frames (wrapping period 2.56 seconds), range [0, 256].

  // Write FrameId (1 Byte) - a counter for 10 ms frames (wrapping period 2.56 seconds), range [0, 256].
  serializer.write(uint8_t(params.slot.sfn()));

  // Write subframe and slot index (1 Byte).

  // Write subframe and slot index (1 Byte).
  serializer.write(encode_subframe_and_slot(params.slot));

  // Write 2 LSBs of slot index and symbol index.

  // Write 2 LSBs of slot index and symbol index.
  serializer.write(encode_slot_lsb_and_symbol(params));
}

/// Writes section1 header to the output buffer.

/// Writes section1 header to the output buffer.
static void build_section1_header(network_order_binary_serializer& serializer, const uplane_message_params& params)
{
  // Section ID is fixed to 0.
  // Section ID is fixed to 0.
  serializer.write(uint8_t(0));

  // Write rb, symInc and 2 MSB bits of start PRB.

  // Write rb, symInc and 2 MSB bits of start PRB.
  serializer.write(encode_sect_id_rb_symbols(params));

  // Write remaining LSBs of start PRB.

  // Write remaining LSBs of start PRB.
  serializer.write(uint8_t(params.start_prb));

  // Write number of PRBs.

  // Write number of PRBs.
  serializer.write(uint8_t((params.nof_prb > std::numeric_limits<uint8_t>::max()) ? 0 : params.nof_prb));
}


void uplane_message_builder_impl::serialize_iq_data(network_order_binary_serializer& serializer,
                                                    span<const cbf16_t>              iq_data,
                                                    unsigned                         nof_prbs,
                                                    const ru_compression_params&     compr_params)
{
  if (OCUDU_UNLIKELY(logger.debug.enabled())) {
    logger.debug("Packing '{}' PRBs inside a User-Plane message using compression type '{}' and bitwidth '{}'",
                 nof_prbs,
                 to_string(compr_params.type),
                 compr_params.data_width);
  }

  // Serialize compression header.

  // Serialize compression header.
  serialize_compression_header(serializer, compr_params);


  if (ud_comp_length_support) {
    // The udCompLen field shall only be present for the following compression methods:
    // "BFP + selective RE sending" or "Modulation compression + selective RE sending".
    // The udCompLen field shall only be present for the following compression methods:
    // "BFP + selective RE sending" or "Modulation compression + selective RE sending".
    if (compr_params.type == compression_type::bfp_selective || compr_params.type == compression_type::mod_selective) {
      units::bits prb_iq_data_size_bits(NOF_SUBCARRIERS_PER_RB * 2U * compr_params.data_width);
      uint16_t    udCompLen = prb_iq_data_size_bits.round_up_to_bytes().value();
      serializer.write(udCompLen);
    }
  }

  // Size in bytes of one compressed PRB using the given compression parameters.

  // Size in bytes of one compressed PRB using the given compression parameters.
  units::bytes prb_size           = get_compressed_prb_size(compr_params);
  units::bytes bytes_to_serialize = prb_size * nof_prbs;


  span<uint8_t> compr_prb_view = serializer.get_view_and_advance(bytes_to_serialize.value());
  compressor.compress(compr_prb_view, iq_data, compr_params);
}


unsigned uplane_message_builder_impl::build_message(span<uint8_t>                buffer,
                                                    span<const cbf16_t>          iq_data,
                                                    const uplane_message_params& params)
{
  ocudu_assert(params.sect_type == section_type::type_1, "Unsupported section type");
  ocudu_assert(iq_data.size() == params.nof_prb * NOF_SUBCARRIERS_PER_RB,
               "The number of PRBs derived from the IQ samples is '{}' and requested number of PRBs to pack is '{}'",
               iq_data.size() / NOF_SUBCARRIERS_PER_RB,
               params.nof_prb);


  network_order_binary_serializer serializer(buffer.data());


  build_radio_app_header(serializer, params);
  build_section1_header(serializer, params);
  serialize_iq_data(serializer, iq_data, params.nof_prb, params.compression_params);


  return serializer.get_offset();
}
