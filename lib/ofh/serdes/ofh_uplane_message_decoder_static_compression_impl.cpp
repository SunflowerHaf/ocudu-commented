// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_uplane_message_decoder_static_compression_impl.cpp  (32 lines)
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

#include "ofh_uplane_message_decoder_static_compression_impl.h"
#include "../support/network_order_binary_deserializer.h"


using namespace ocudu;
using namespace ofh;


uplane_message_decoder_impl::decoded_section_status
uplane_message_decoder_static_compression_impl::decode_compression_header(
    decoder_uplane_section_params&     results,
    network_order_binary_deserializer& deserializer)
{
  // Copy the compression header to the results.
  // Copy the compression header to the results.
  results.ud_comp_hdr = compression_params;


  return uplane_message_decoder_impl::decoded_section_status::ok;
}


uplane_message_decoder_static_compression_impl::uplane_message_decoder_static_compression_impl(
    ocudulog::basic_logger&          logger_,
    subcarrier_spacing               scs_,
    unsigned                         nof_symbols_,
    unsigned                         ru_nof_prbs_,
    unsigned                         sector_id_,
    std::unique_ptr<iq_decompressor> decompressor_,
    const ru_compression_params&     compression_params_) :
  uplane_message_decoder_impl(logger_, scs_, nof_symbols_, ru_nof_prbs_, sector_id_, std::move(decompressor_)),
  compression_params(compression_params_)
{
}
