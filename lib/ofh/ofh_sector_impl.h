// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ofh_sector_impl.h  (75 lines)
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


#include "ofh_metrics_collector_impl.h"
#include "ofh_sector_controller.h"
#include "support/prach_context_repository.h"
#include "support/uplink_context_repository.h"
#include "support/uplink_cplane_context_repository.h"
#include "ocudu/ofh/ethernet/ethernet_receiver.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter.h"
#include "ocudu/ofh/ofh_sector.h"
#include "ocudu/ofh/receiver/ofh_receiver.h"
#include "ocudu/ofh/transmitter/ofh_transmitter.h"


namespace ocudu {
namespace ofh {

/// Sector implementation configuration.

/// Sector implementation configuration.
struct sector_impl_config {
  unsigned sector_id;
  bool     are_metrics_enabled = false;
};

/// Sector implementation dependencies.

/// Sector implementation dependencies.
struct sector_impl_dependencies {
  std::unique_ptr<receiver>                  ofh_receiver;
  std::unique_ptr<transmitter>               ofh_transmitter;
  std::shared_ptr<uplink_context_repository> ul_data_repo;
  std::shared_ptr<prach_context_repository>  ul_prach_repo;
  ether::transmitter&                        eth_transmitter;
  ether::receiver&                           eth_receiver;
};

/// Open Fronthaul sector implementation.

/// Open Fronthaul sector implementation.
class sector_impl : public sector
{
public:
  sector_impl(const sector_impl_config& config, sector_impl_dependencies&& dependencies) :
    ofh_receiver(std::move(dependencies.ofh_receiver)),
    ofh_transmitter(std::move(dependencies.ofh_transmitter)),
    ofh_sector_controller(*ofh_transmitter,
                          *ofh_receiver,
                          std::move(dependencies.ul_data_repo),
                          std::move(dependencies.ul_prach_repo)),
    ofh_metrics_collector(ofh_receiver->get_metrics_collector(),
                          ofh_transmitter->get_metrics_collector(),
                          config.sector_id)
  {
    ocudu_assert(ofh_receiver, "Invalid Open Fronthaul receiver");
    ocudu_assert(ofh_transmitter, "Invalid Open Fronthaul transmitter");
  }

  // See interface for documentation.

  // See interface for documentation.
  receiver& get_receiver() override;

  // See interface for documentation.

  // See interface for documentation.
  transmitter& get_transmitter() override;

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override;

  // See interface for documentation.

  // See interface for documentation.
  metrics_collector* get_metrics_collector() override;


private:
  std::unique_ptr<receiver>    ofh_receiver;
  std::unique_ptr<transmitter> ofh_transmitter;
  sector_controller            ofh_sector_controller;
  metrics_collector_impl       ofh_metrics_collector;
};


} // namespace ofh
} // namespace ocudu
