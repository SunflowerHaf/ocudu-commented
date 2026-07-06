// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/vlan_ethernet_frame_decoder_impl.cpp  (35 lines)
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

#include "vlan_ethernet_frame_decoder_impl.h"
#include "../support/network_order_binary_deserializer.h"
#include "ethernet_constants.h"


using namespace ocudu;
using namespace ether;


static constexpr unsigned MIN_ETH_LEN = 64;


span<const uint8_t> vlan_frame_decoder_impl::decode(span<const uint8_t> frame, vlan_frame_params& eth_params)
{
  // Ethernet frames should include padding bytes up to the minimum length.
  // Ethernet frames should include padding bytes up to the minimum length.
  if (OCUDU_UNLIKELY(frame.size() < MIN_ETH_LEN)) {
    logger.debug("Sector #{}: Dropped received Ethernet frame of size '{}' bytes as it is below the minimum allowed "
                 "size of '{}' bytes",
                 sector_id,
                 frame.size(),
                 MIN_ETH_LEN);
    return {};
  }


  ofh::network_order_binary_deserializer deserializer(frame);


  deserializer.read(eth_params.mac_dst_address);
  deserializer.read(eth_params.mac_src_address);

  // VLAN parameters are stripped by the NIC.


  // VLAN parameters are stripped by the NIC.

  eth_params.eth_type = deserializer.read<uint16_t>();


  return frame.last(frame.size() - deserializer.get_offset());
}
