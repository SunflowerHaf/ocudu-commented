// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_serdes_factories.cpp  (62 lines)
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

#include "ocudu/ofh/serdes/ofh_serdes_factories.h"
#include "ofh_cplane_message_builder_dynamic_compression_impl.h"
#include "ofh_cplane_message_builder_static_compression_impl.h"
#include "ofh_uplane_message_builder_dynamic_compression_impl.h"
#include "ofh_uplane_message_builder_static_compression_impl.h"
#include "ofh_uplane_message_decoder_dynamic_compression_impl.h"
#include "ofh_uplane_message_decoder_static_compression_impl.h"


using namespace ocudu;
using namespace ofh;


std::unique_ptr<cplane_message_builder> ocudu::ofh::create_ofh_control_plane_static_compression_message_builder()
{
  return std::make_unique<cplane_message_builder_static_compression_impl>();
}


std::unique_ptr<cplane_message_builder> ocudu::ofh::create_ofh_control_plane_dynamic_compression_message_builder()
{
  return std::make_unique<cplane_message_builder_dynamic_compression_impl>();
}


std::unique_ptr<uplane_message_builder>
ocudu::ofh::create_static_compr_method_ofh_user_plane_packet_builder(ocudulog::basic_logger& logger,
                                                                     iq_compressor&          compressor)
{
  return std::make_unique<ofh_uplane_message_builder_static_compression_impl>(logger, compressor);
}


std::unique_ptr<uplane_message_builder>
ocudu::ofh::create_dynamic_compr_method_ofh_user_plane_packet_builder(ocudulog::basic_logger& logger,
                                                                      iq_compressor&          compressor)
{
  return std::make_unique<ofh_uplane_message_builder_dynamic_compression_impl>(logger, compressor);
}


std::unique_ptr<uplane_message_decoder>
ocudu::ofh::create_static_compr_method_ofh_user_plane_packet_decoder(ocudulog::basic_logger&          logger,
                                                                     subcarrier_spacing               scs,
                                                                     cyclic_prefix                    cp,
                                                                     unsigned                         ru_nof_prbs,
                                                                     unsigned                         sector_id_,
                                                                     std::unique_ptr<iq_decompressor> decompressor,
                                                                     const ru_compression_params&     compr_params)
{
  return std::make_unique<uplane_message_decoder_static_compression_impl>(
      logger, scs, get_nsymb_per_slot(cp), ru_nof_prbs, sector_id_, std::move(decompressor), compr_params);
}


std::unique_ptr<uplane_message_decoder>
ocudu::ofh::create_dynamic_compr_method_ofh_user_plane_packet_decoder(ocudulog::basic_logger&          logger,
                                                                      subcarrier_spacing               scs,
                                                                      cyclic_prefix                    cp,
                                                                      unsigned                         ru_nof_prbs,
                                                                      unsigned                         sector_id_,
                                                                      std::unique_ptr<iq_decompressor> decompressor)
{
  return std::make_unique<uplane_message_decoder_dynamic_compression_impl>(
      logger, scs, get_nsymb_per_slot(cp), ru_nof_prbs, sector_id_, std::move(decompressor));
}
