// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_rx_symbol_reorderer.cpp  (27 lines)
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

#include "ofh_rx_symbol_reorderer.h"
#include "ocudu/phy/support/shared_resource_grid.h"


using namespace ocudu;
using namespace ofh;


void rx_symbol_reorderer::on_new_uplink_symbol(const uplane_rx_symbol_context& context,
                                               shared_resource_grid            grid,
                                               bool                            is_valid)
{
  std::optional<uplink_notified_grid_symbol_repository::results> symbols =
      uplink_symbol_repo->update_rx_symbol_and_compute_symbols_to_notify(context.slot, context.symbol, is_valid);

  // No symbols to notify.

  // No symbols to notify.
  if (!symbols) {
    return;
  }


  for (unsigned i = symbols->symbols.start(), e = symbols->symbols.stop(); i != e; ++i) {
    uplane_rx_symbol_context new_context = context;
    new_context.symbol                   = i;
    notifier.on_new_uplink_symbol(new_context, grid.copy(), symbols->valid_symbols.test(i));
  }
}
