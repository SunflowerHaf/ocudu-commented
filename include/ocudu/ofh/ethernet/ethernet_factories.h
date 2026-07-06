// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/ethernet_factories.h  (40 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/ofh
// Open Fronthaul public interface headers. CONDITIONAL: linked into the binary via a temporary dependency (see lib/ofh note) but not used at runtime in split-8. These headers define the OFH contract between the lib/ofh library and its callers (primarily lib/ru/ofh).
//
// Contents:
//   ofh/compression/      — IQ compressor/decompressor abstract interfaces and compression parameter types (scheme, data width, BFP exponent).
//   ofh/ecpri/            — eCPRI packet builder, decoder, and property types.
//   ofh/ethernet/         — Ethernet frame builder/receiver interfaces, VLAN tag types, and port configuration.
//   ofh/ofh_factories.h   — Top-level OFH sector factory.
//   ofh/ofh_sector.h      — OFH sector interface (one per radio sector/cell).
//   ofh/receiver/         — OFH uplink receiver interface (delivers received IQ).
//   ofh/serdes/           — C-plane and U-plane message serialiser interfaces.
//   ofh/timing/           — OFH timing controller interface (slot indication source).
//   ofh/transmitter/      — OFH downlink transmitter interface.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ethernet/ethernet_frame_builder.h"
#include "ocudu/ofh/ethernet/ethernet_receiver.h"
#include "ocudu/ofh/ethernet/ethernet_receiver_config.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter_config.h"
#include "ocudu/ofh/ethernet/vlan_ethernet_frame_decoder.h"
#include <memory>


namespace ocudu {


class task_executor;


namespace ether {


class frame_notifier;

/// Creates an Ethernet transmitter.

/// Creates an Ethernet transmitter.
std::unique_ptr<transmitter> create_transmitter(const transmitter_config& config, ocudulog::basic_logger& logger);

/// Creates an Ethernet receiver.

/// Creates an Ethernet receiver.
std::unique_ptr<receiver>
create_receiver(const receiver_config& config, task_executor& executor, ocudulog::basic_logger& logger);

/// Creates an Ethernet frame builder with VLAN tag insertion.

/// Creates an Ethernet frame builder with VLAN tag insertion.
std::unique_ptr<frame_builder> create_vlan_frame_builder(const vlan_frame_params& eth_params);

/// Creates an Ethernet frame builder without VLAN tag insertion.

/// Creates an Ethernet frame builder without VLAN tag insertion.
std::unique_ptr<frame_builder> create_frame_builder(const vlan_frame_params& eth_params);

/// Creates an Ethernet VLAN frame decoder.

/// Creates an Ethernet VLAN frame decoder.
std::unique_ptr<vlan_frame_decoder> create_vlan_frame_decoder(ocudulog::basic_logger& logger, unsigned sector_id);


} // namespace ether
} // namespace ocudu
