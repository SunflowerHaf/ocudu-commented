// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_uplane_message_builder_dynamic_compression_impl.cpp  (34 lines)
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

#include "ofh_uplane_message_builder_dynamic_compression_impl.h"
#include "../support/network_order_binary_serializer.h"


using namespace ocudu;
using namespace ofh;


void ofh_uplane_message_builder_dynamic_compression_impl::serialize_compression_header(
    network_order_binary_serializer& serializer,
    const ru_compression_params&     params)
{
  // Serialize compression header.
  // Serialize compression header.
  uint8_t value = 0U;
  // Note that an IQ bitwidth of 16 bits translates to a value of 0.
  // Note that an IQ bitwidth of 16 bits translates to a value of 0.
  value |= uint8_t(params.data_width == 16 ? 0 : params.data_width) << 4U;
  value |= uint8_t(to_value(params.type));
  serializer.write(value);

  // Serialize reserved byte.

  // Serialize reserved byte.
  serializer.write(uint8_t(0));
}


units::bytes
ofh_uplane_message_builder_dynamic_compression_impl::get_header_size(const ru_compression_params& params) const
{
  units::bytes hdr_size(10);
  if (params.type == compression_type::bfp_selective || params.type == compression_type::mod_selective) {
    hdr_size += units::bytes(2);
  }


  return hdr_size;
}
