// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ecpri/ecpri_factories.cpp  (26 lines)
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

#include "ocudu/ofh/ecpri/ecpri_factories.h"
#include "ecpri_packet_builder_impl.h"
#include "ecpri_packet_decoder_impl.h"


using namespace ocudu;
using namespace ecpri;


std::unique_ptr<packet_builder> ocudu::ecpri::create_ecpri_packet_builder()
{
  return std::make_unique<packet_builder_impl>();
}


std::unique_ptr<packet_decoder>
ocudu::ecpri::create_ecpri_packet_decoder_using_payload_size(ocudulog::basic_logger& logger, unsigned sector)
{
  return std::make_unique<packet_decoder_use_header_payload_size>(logger, sector);
}


std::unique_ptr<packet_decoder>
ocudu::ecpri::create_ecpri_packet_decoder_ignoring_payload_size(ocudulog::basic_logger& logger, unsigned sector)
{
  return std::make_unique<packet_decoder_ignore_header_payload_size>(logger, sector);
}
