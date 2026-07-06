// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_uplane_message_decoder_dynamic_compression_impl.h  (36 lines)
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


#include "ofh_uplane_message_decoder_impl.h"
#include "ocudu/ocudulog/logger.h"


namespace ocudu {
namespace ofh {


class iq_decompressor;
class network_order_binary_deserializer;

/// Open Fronthaul User-Plane message decoder implementation with dynamic IQ compression.

/// Open Fronthaul User-Plane message decoder implementation with dynamic IQ compression.
class uplane_message_decoder_dynamic_compression_impl : public uplane_message_decoder_impl
{
public:
  uplane_message_decoder_dynamic_compression_impl(ocudulog::basic_logger&          logger_,
                                                  subcarrier_spacing               scs_,
                                                  unsigned                         nof_symbols_,
                                                  unsigned                         ru_nof_prbs_,
                                                  unsigned                         sector_id_,
                                                  std::unique_ptr<iq_decompressor> decompressor_) :
    uplane_message_decoder_impl(logger_, scs_, nof_symbols_, ru_nof_prbs_, sector_id_, std::move(decompressor_))
  {
  }


private:
  // See parent for documentation.
  // See parent for documentation.
  decoded_section_status decode_compression_header(decoder_uplane_section_params&     results,
                                                   network_order_binary_deserializer& deserializer) override;
};


} // namespace ofh
} // namespace ocudu
