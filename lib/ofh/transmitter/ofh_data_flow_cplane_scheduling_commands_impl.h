// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_data_flow_cplane_scheduling_commands_impl.h  (94 lines)
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


#include "../operation_controller_dummy.h"
#include "../support/uplink_cplane_context_repository.h"
#include "ofh_data_flow_cplane_scheduling_commands.h"
#include "sequence_identifier_generator.h"
#include "ocudu/ofh/ecpri/ecpri_packet_builder.h"
#include "ocudu/ofh/ethernet/ethernet_frame_builder.h"
#include "ocudu/ofh/ethernet/ethernet_frame_pool.h"
#include "ocudu/ofh/serdes/ofh_cplane_message_builder.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow implementation configuration.

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow implementation configuration.
struct data_flow_cplane_scheduling_commands_impl_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// RU bandwidth in PRBs.
  /// RU bandwidth in PRBs.
  unsigned ru_nof_prbs;
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Downlink compression parameters.
  /// Downlink compression parameters.
  ru_compression_params dl_compr_params;
  /// Uplink compression parameters.
  /// Uplink compression parameters.
  ru_compression_params ul_compr_params;
  /// PRACH compression parameters.
  /// PRACH compression parameters.
  ru_compression_params prach_compr_params;
  /// PRACH FFT size (to be used in Type 3 messages).
  /// PRACH FFT size (to be used in Type 3 messages).
  cplane_fft_size c_plane_prach_fft_len;
};

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow implementation dependencies.

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow implementation dependencies.
struct data_flow_cplane_scheduling_commands_impl_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger* logger = nullptr;
  /// Uplink Control-Plane context repository.
  /// Uplink Control-Plane context repository.
  std::shared_ptr<uplink_cplane_context_repository> ul_cplane_context_repo;
  /// PRACH Control-Plane context repository.
  /// PRACH Control-Plane context repository.
  std::shared_ptr<uplink_cplane_context_repository> prach_cplane_context_repo;
  /// Ethernet frame pool.
  /// Ethernet frame pool.
  std::shared_ptr<ether::eth_frame_pool> frame_pool;
  /// VLAN frame builder.
  /// VLAN frame builder.
  std::unique_ptr<ether::frame_builder> eth_builder;
  /// eCPRI packet builder.
  /// eCPRI packet builder.
  std::unique_ptr<ecpri::packet_builder> ecpri_builder;
  /// Control-Plane message builder.
  /// Control-Plane message builder.
  std::unique_ptr<cplane_message_builder> cp_builder;
};

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow implementation.

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow implementation.
class data_flow_cplane_scheduling_commands_impl : public data_flow_cplane_scheduling_commands
{
public:
  data_flow_cplane_scheduling_commands_impl(const data_flow_cplane_scheduling_commands_impl_config&  config,
                                            data_flow_cplane_scheduling_commands_impl_dependencies&& dependencies);

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override { return controller; }

  // See interface for documentation.

  // See interface for documentation.
  void enqueue_section_type_1_message(const data_flow_cplane_type_1_context& context) override;

  // See interface for documentation.

  // See interface for documentation.
  void enqueue_section_type_3_prach_message(const data_flow_cplane_scheduling_prach_context& context) override;

  // See interface for documentation.

  // See interface for documentation.
  data_flow_message_encoding_metrics_collector* get_metrics_collector() override;


private:
  ocudulog::basic_logger&                           logger;
  const unsigned                                    nof_symbols_per_slot;
  const unsigned                                    ru_nof_prbs;
  const unsigned                                    sector_id;
  const cplane_fft_size                             c_plane_prach_fft_len;
  const ru_compression_params                       dl_compr_params;
  const ru_compression_params                       ul_compr_params;
  const ru_compression_params                       prach_compr_params;
  operation_controller_dummy                        controller;
  sequence_identifier_generator                     cp_dl_seq_gen;
  sequence_identifier_generator                     cp_ul_seq_gen;
  std::shared_ptr<uplink_cplane_context_repository> ul_cplane_context_repo;
  std::shared_ptr<uplink_cplane_context_repository> prach_cplane_context_repo;
  std::shared_ptr<ether::eth_frame_pool>            frame_pool;
  std::unique_ptr<ether::frame_builder>             eth_builder;
  std::unique_ptr<ecpri::packet_builder>            ecpri_builder;
  std::unique_ptr<cplane_message_builder>           cp_builder;
};


} // namespace ofh
} // namespace ocudu
