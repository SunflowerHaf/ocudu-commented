// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ecpri/ecpri_packet_builder_impl.cpp  (83 lines)
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

#include "ecpri_packet_builder_impl.h"
#include "../support/network_order_binary_serializer.h"
#include "ocudu/ofh/ecpri/ecpri_constants.h"
#include "ocudu/ofh/ecpri/ecpri_packet_properties.h"


using namespace ocudu;
using namespace ecpri;


units::bytes packet_builder_impl::get_header_size(message_type msg_type) const
{
  switch (msg_type) {
    case message_type::rt_control_data:
      return ECPRI_COMMON_HEADER_SIZE + ECPRI_REALTIME_CONTROL_PACKET_FIELDS_SIZE;
    case message_type::iq_data:
      return ECPRI_COMMON_HEADER_SIZE + ECPRI_IQ_DATA_PACKET_FIELDS_SIZE;
  }


  return ECPRI_COMMON_HEADER_SIZE;
}

/// Returns the first byte in the eCPRI Common Header.

/// Returns the first byte in the eCPRI Common Header.
static uint8_t get_first_byte_in_common_header(bool concatenate = false)
{
  ocudu_assert(!concatenate, "eCPRI concatenation is currently not supported");


  uint8_t header = 0;
  // Protocol revision (4 highest bits).
  // Protocol revision (4 highest bits).
  header |= uint8_t(ECPRI_PROTOCOL_REVISION) << 4;
  // Reserved 3 bits.
  // Concatenation field (last bit).
  // Reserved 3 bits.
  // Concatenation field (last bit).
  header |= uint8_t(concatenate ? 1U : 0U);


  return header;
}


void packet_builder_impl::build_control_packet(span<uint8_t> buffer, const realtime_control_parameters& msg_params)
{
  // The payload is already appended in the buffer, so payload size equals buffer size - eCPRI header size.
  // The payload is already appended in the buffer, so payload size equals buffer size - eCPRI header size.
  units::bytes payload_size(buffer.size());
  payload_size -= ECPRI_COMMON_HEADER_SIZE;
  ofh::network_order_binary_serializer serializer(buffer.data());

  // Write eCPRI version and concatenation fields (1 Byte).

  // Write eCPRI version and concatenation fields (1 Byte).
  serializer.write(get_first_byte_in_common_header());

  // Write eCPRI message type (1 Byte).

  // Write eCPRI message type (1 Byte).
  serializer.write(static_cast<uint8_t>(message_type::rt_control_data));

  // Write the payload size (2 Bytes).

  // Write the payload size (2 Bytes).
  serializer.write(static_cast<uint16_t>(payload_size.value()));

  // Write RTC_ID (2 Bytes).

  // Write RTC_ID (2 Bytes).
  serializer.write(msg_params.rtc_id);

  // Write SEQ_ID (2 Byte).

  // Write SEQ_ID (2 Byte).
  serializer.write(msg_params.seq_id);
}


void packet_builder_impl::build_data_packet(span<uint8_t> buffer, const iq_data_parameters& msg_params)
{
  // The payload is already appended in the buffer, so payload size equals buffer size - eCPRI header size.
  // The payload is already appended in the buffer, so payload size equals buffer size - eCPRI header size.
  units::bytes payload_size(buffer.size());
  payload_size -= ECPRI_COMMON_HEADER_SIZE;
  ofh::network_order_binary_serializer serializer(buffer.data());

  // Write eCPRI version and concatenation fields (1 Byte).

  // Write eCPRI version and concatenation fields (1 Byte).
  serializer.write(get_first_byte_in_common_header());

  // Write eCPRI message type (1 Byte).

  // Write eCPRI message type (1 Byte).
  serializer.write(static_cast<uint8_t>(message_type::iq_data));

  // Write the payload size (2 Bytes).

  // Write the payload size (2 Bytes).
  serializer.write(static_cast<uint16_t>(payload_size.value()));

  // Write PC_ID (2 Bytes).

  // Write PC_ID (2 Bytes).
  serializer.write(msg_params.pc_id);

  // Write SEQ_ID (2 Bytes).

  // Write SEQ_ID (2 Bytes).
  serializer.write(msg_params.seq_id);
}
