// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_factories.cpp  (40 lines)
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

#include "ocudu/ofh/ethernet/ethernet_factories.h"
#include "ethernet_frame_builder_impl.h"
#include "ethernet_receiver_impl.h"
#include "ethernet_transmitter_impl.h"
#include "vlan_ethernet_frame_builder_impl.h"
#include "vlan_ethernet_frame_decoder_impl.h"


using namespace ocudu;
using namespace ether;


std::unique_ptr<transmitter> ocudu::ether::create_transmitter(const transmitter_config& config,
                                                              ocudulog::basic_logger&   logger)
{
  return std::make_unique<transmitter_impl>(config, logger);
}


std::unique_ptr<receiver>
ocudu::ether::create_receiver(const receiver_config& config, task_executor& executor, ocudulog::basic_logger& logger)
{
  return std::make_unique<receiver_impl>(config, executor, logger);
}


std::unique_ptr<frame_builder> ocudu::ether::create_vlan_frame_builder(const vlan_frame_params& eth_params)
{
  return std::make_unique<vlan_frame_builder_impl>(eth_params);
}


std::unique_ptr<frame_builder> ocudu::ether::create_frame_builder(const vlan_frame_params& eth_params)
{
  return std::make_unique<frame_builder_impl>(eth_params);
}


std::unique_ptr<vlan_frame_decoder> ocudu::ether::create_vlan_frame_decoder(ocudulog::basic_logger& logger,
                                                                            unsigned                sector_id)
{
  return std::make_unique<vlan_frame_decoder_impl>(logger, sector_id);
}
