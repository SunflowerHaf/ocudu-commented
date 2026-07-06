// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/dpdk/dpdk_ethernet_factories.cpp  (33 lines)
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

#include "ocudu/ofh/ethernet/dpdk/dpdk_ethernet_factories.h"
#include "dpdk_ethernet_receiver.h"
#include "dpdk_ethernet_transmitter.h"
#include "ocudu/ofh/ethernet/dpdk/dpdk_ethernet_port_context.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter_config.h"


using namespace ocudu;
using namespace ether;


std::shared_ptr<dpdk_port_context> ocudu::ether::create_dpdk_port_context(const transmitter_config& config)
{
  dpdk_port_config port_cfg;
  port_cfg.id                           = config.interface;
  port_cfg.is_promiscuous_mode_enabled  = config.is_promiscuous_mode_enabled;
  port_cfg.is_link_status_check_enabled = config.is_link_status_check_enabled;
  port_cfg.mtu_size                     = config.mtu_size;


  return dpdk_port_context::create(port_cfg);
}


std::pair<std::unique_ptr<transmitter>, std::unique_ptr<receiver>>
ocudu::ether::create_dpdk_txrx(const transmitter_config& config,
                               task_executor&            rx_executor,
                               ocudulog::basic_logger&   logger)
{
  auto ctx = create_dpdk_port_context(config);


  return {std::make_unique<dpdk_transmitter_impl>(ctx, logger, config.are_metrics_enabled),
          std::make_unique<dpdk_receiver_impl>(rx_executor, ctx, logger, config.are_metrics_enabled)};
}
