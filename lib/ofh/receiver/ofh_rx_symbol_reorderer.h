// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_rx_symbol_reorderer.h  (42 lines)
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


#include "../support/uplink_notified_grid_symbol_repository.h"
#include "ocudu/ofh/ofh_uplane_rx_symbol_notifier.h"
#include <memory>


namespace ocudu {
namespace ofh {

/// \brief Received symbol reorderer.
///
/// This object is a decorator that receives symbols out of order and notifies them to the configured notifier in
/// ascending order.

/// \brief Received symbol reorderer.
///
/// This object is a decorator that receives symbols out of order and notifies them to the configured notifier in
/// ascending order.
class rx_symbol_reorderer : public uplane_rx_symbol_notifier
{
  uplane_rx_symbol_notifier&                              notifier;
  std::shared_ptr<uplink_notified_grid_symbol_repository> uplink_symbol_repo;


public:
  rx_symbol_reorderer(uplane_rx_symbol_notifier&                              notifier_,
                      std::shared_ptr<uplink_notified_grid_symbol_repository> uplink_symbol_repo_) :
    notifier(notifier_), uplink_symbol_repo(uplink_symbol_repo_)
  {
    ocudu_assert(uplink_symbol_repo, "Invalid notified uplink grid symbol repository");
  }

  // See interface for documentation.

  // See interface for documentation.
  void on_new_uplink_symbol(const uplane_rx_symbol_context& context, shared_resource_grid grid, bool is_valid) override;

  // See interface for documentation.

  // See interface for documentation.
  void on_new_prach_window_data(const prach_buffer_context& context, shared_prach_buffer buffer) override
  {
    // PRACH notifies all symbols at once, no need to reorder.
    // PRACH notifies all symbols at once, no need to reorder.
    notifier.on_new_prach_window_data(context, std::move(buffer));
  }
};


} // namespace ofh
} // namespace ocudu
