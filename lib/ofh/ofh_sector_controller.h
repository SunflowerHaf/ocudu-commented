// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ofh_sector_controller.h  (42 lines)
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


#include "support/prach_context_repository.h"
#include "support/uplink_context_repository.h"
#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/receiver/ofh_receiver.h"
#include "ocudu/ofh/transmitter/ofh_transmitter.h"
#include <memory>


namespace ocudu {
namespace ofh {

/// Open Fronthaul controller for the sector.

/// Open Fronthaul controller for the sector.
class sector_controller : public operation_controller
{
public:
  sector_controller(transmitter&                               ofh_tx_,
                    receiver&                                  ofh_rx_,
                    std::shared_ptr<uplink_context_repository> slot_repo_,
                    std::shared_ptr<prach_context_repository>  prach_repo_) :
    ofh_tx(ofh_tx_), ofh_rx(ofh_rx_), slot_repo(std::move(slot_repo_)), prach_repo(std::move(prach_repo_))
  {
  }

  // See interface for documentation.

  // See interface for documentation.
  void start() override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;


private:
  transmitter&                               ofh_tx;
  receiver&                                  ofh_rx;
  std::shared_ptr<uplink_context_repository> slot_repo;
  std::shared_ptr<prach_context_repository>  prach_repo;
};


} // namespace ofh
} // namespace ocudu
