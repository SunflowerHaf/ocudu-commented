// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_receiver_factories.h  (34 lines)
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


#include "../support/prach_context_repository.h"
#include "../support/uplink_context_repository.h"
#include "../support/uplink_cplane_context_repository.h"
#include "../support/uplink_notified_grid_symbol_repository.h"
#include "ofh_receiver_impl.h"
#include "ocudu/ofh/receiver/ofh_receiver.h"
#include "ocudu/ofh/receiver/ofh_receiver_configuration.h"
#include <memory>


namespace ocudu {


class task_executor;


namespace ofh {

/// Creates a receiver with the given configuration and dependencies.

/// Creates a receiver with the given configuration and dependencies.
std::unique_ptr<receiver> create_receiver(const receiver_config&                                  receiver_cfg,
                                          ocudulog::basic_logger&                                 logger,
                                          task_executor&                                          uplink_executor,
                                          std::unique_ptr<ether::receiver>                        eth_receiver,
                                          uplane_rx_symbol_notifier*                              notifier,
                                          std::shared_ptr<prach_context_repository>               prach_context_repo,
                                          std::shared_ptr<uplink_context_repository>              ul_slot_context_repo,
                                          std::shared_ptr<uplink_cplane_context_repository>       ul_cp_context_repo,
                                          std::shared_ptr<uplink_cplane_context_repository>       prach_cp_context_repo,
                                          std::shared_ptr<uplink_notified_grid_symbol_repository> notifier_symbol_repo);


} // namespace ofh
} // namespace ocudu
