// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_receiver_factories.cpp  (178 lines)
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

#include "ofh_receiver_factories.h"
#include "ofh_data_flow_uplane_uplink_data_impl.h"
#include "ofh_data_flow_uplane_uplink_prach_impl.h"
#include "ofh_receiver_impl.h"
#include "ofh_sequence_id_checker_dummy_impl.h"
#include "ofh_sequence_id_checker_impl.h"
#include "ocudu/ofh/compression/compression_factory.h"
#include "ocudu/ofh/ecpri/ecpri_factories.h"
#include "ocudu/ofh/ethernet/ethernet_factories.h"
#include "ocudu/ofh/serdes/ofh_serdes_factories.h"


using namespace ocudu;
using namespace ofh;


static std::unique_ptr<uplane_message_decoder> create_uplane_decoder(const receiver_config&       receiver_cfg,
                                                                     ocudulog::basic_logger&      logger,
                                                                     const ru_compression_params& compr_params)
{
  // Compressors.
  // Compressors.
  std::array<std::unique_ptr<iq_decompressor>, NOF_COMPRESSION_TYPES_SUPPORTED> decompr;
  for (unsigned i = 0; i != NOF_COMPRESSION_TYPES_SUPPORTED; ++i) {
    decompr[i] = create_iq_decompressor(static_cast<compression_type>(i), logger);
  }


  frequency_range freq_range =
      (receiver_cfg.scs > subcarrier_spacing::kHz60) ? frequency_range::FR2 : frequency_range::FR1;


  unsigned nof_prbs_ru = get_max_Nprb(receiver_cfg.ru_operating_bw, receiver_cfg.scs, freq_range);

  // Open FrontHaul decoder.

  // Open FrontHaul decoder.
  return (receiver_cfg.is_uplink_static_compr_hdr_enabled) ? create_static_compr_method_ofh_user_plane_packet_decoder(
                                                                 logger,
                                                                 receiver_cfg.scs,
                                                                 receiver_cfg.cp,
                                                                 nof_prbs_ru,
                                                                 receiver_cfg.sector,
                                                                 create_iq_decompressor_selector(std::move(decompr)),
                                                                 compr_params)
                                                           : create_dynamic_compr_method_ofh_user_plane_packet_decoder(
                                                                 logger,
                                                                 receiver_cfg.scs,
                                                                 receiver_cfg.cp,
                                                                 nof_prbs_ru,
                                                                 receiver_cfg.sector,
                                                                 create_iq_decompressor_selector(std::move(decompr)));
}


static std::unique_ptr<data_flow_uplane_uplink_prach>
create_uplink_prach_data_flow(const receiver_config&                            receiver_cfg,
                              ocudulog::basic_logger&                           logger,
                              std::shared_ptr<uplane_rx_symbol_notifier>        notifier,
                              std::shared_ptr<prach_context_repository>         prach_context_repo,
                              std::shared_ptr<uplink_cplane_context_repository> prach_cp_context_repo)
{
  data_flow_uplane_uplink_prach_impl_config config;
  config.is_prach_cplane_enabled   = receiver_cfg.is_prach_control_plane_enabled;
  config.ignore_prach_start_symbol = receiver_cfg.ignore_prach_start_symbol;
  config.prach_eaxcs               = receiver_cfg.prach_eaxc;
  config.sector                    = receiver_cfg.sector;
  config.are_metrics_enabled       = receiver_cfg.are_metrics_enabled;


  data_flow_uplane_uplink_prach_impl_dependencies dependencies;
  dependencies.logger                    = &logger;
  dependencies.notifier                  = std::move(notifier);
  dependencies.prach_cplane_context_repo = std::move(prach_cp_context_repo);
  dependencies.prach_context_repo        = std::move(prach_context_repo);
  dependencies.uplane_decoder = create_uplane_decoder(receiver_cfg, logger, receiver_cfg.prach_compression_params);


  return std::make_unique<data_flow_uplane_uplink_prach_impl>(config, std::move(dependencies));
}


static std::unique_ptr<data_flow_uplane_uplink_data>
create_uplink_data_flow(const receiver_config&                            receiver_cfg,
                        ocudulog::basic_logger&                           logger,
                        std::shared_ptr<uplane_rx_symbol_notifier>        notifier,
                        std::shared_ptr<uplink_context_repository>        ul_slot_context_repo,
                        std::shared_ptr<uplink_cplane_context_repository> ul_cp_context_repo)
{
  data_flow_uplane_uplink_data_impl_config config;
  config.ul_eaxc             = receiver_cfg.ul_eaxc;
  config.sector              = receiver_cfg.sector;
  config.are_metrics_enabled = receiver_cfg.are_metrics_enabled;


  data_flow_uplane_uplink_data_impl_dependencies dependencies;
  dependencies.logger                 = &logger;
  dependencies.notifier               = std::move(notifier);
  dependencies.ul_cplane_context_repo = std::move(ul_cp_context_repo);
  dependencies.ul_context_repo        = std::move(ul_slot_context_repo);
  dependencies.uplane_decoder         = create_uplane_decoder(receiver_cfg, logger, receiver_cfg.ul_compression_params);


  return std::make_unique<data_flow_uplane_uplink_data_impl>(config, std::move(dependencies));
}


static receiver_impl_dependencies
resolve_receiver_dependencies(const receiver_config&                                  receiver_cfg,
                              ocudulog::basic_logger&                                 logger,
                              task_executor&                                          uplink_executor,
                              std::unique_ptr<ether::receiver>                        eth_receiver,
                              uplane_rx_symbol_notifier*                              notifier,
                              std::shared_ptr<prach_context_repository>               prach_context_repo,
                              std::shared_ptr<uplink_context_repository>              ul_slot_context_repo,
                              std::shared_ptr<uplink_cplane_context_repository>       ul_cp_context_repo,
                              std::shared_ptr<uplink_cplane_context_repository>       prach_cp_context_repo,
                              std::shared_ptr<uplink_notified_grid_symbol_repository> notifier_symbol_repo)
{
  ocudu_assert(notifier, "Invalid received symbol notifier");


  receiver_impl_dependencies dependencies;
  dependencies.logger           = &logger;
  dependencies.executor         = &uplink_executor;
  dependencies.symbol_reorderer = std::make_shared<rx_symbol_reorderer>(*notifier, std::move(notifier_symbol_repo));


  auto& rx_window_handler_dependencies       = dependencies.window_handler_dependencies;
  rx_window_handler_dependencies.prach_repo  = prach_context_repo;
  rx_window_handler_dependencies.uplink_repo = ul_slot_context_repo;
  rx_window_handler_dependencies.notifier    = dependencies.symbol_reorderer;


  auto& msg_rx_dependencies  = dependencies.msg_rx_dependencies;
  msg_rx_dependencies.logger = &logger;


  if (receiver_cfg.ignore_ecpri_payload_size_field) {
    msg_rx_dependencies.ecpri_decoder =
        ecpri::create_ecpri_packet_decoder_ignoring_payload_size(logger, receiver_cfg.sector);
  } else {
    msg_rx_dependencies.ecpri_decoder =
        ecpri::create_ecpri_packet_decoder_using_payload_size(logger, receiver_cfg.sector);
  }
  msg_rx_dependencies.eth_frame_decoder = ether::create_vlan_frame_decoder(logger, receiver_cfg.sector);


  msg_rx_dependencies.data_flow_uplink = create_uplink_data_flow(receiver_cfg,
                                                                 logger,
                                                                 dependencies.symbol_reorderer,
                                                                 std::move(ul_slot_context_repo),
                                                                 std::move(ul_cp_context_repo));
  msg_rx_dependencies.data_flow_prach  = create_uplink_prach_data_flow(receiver_cfg,
                                                                      logger,
                                                                      dependencies.symbol_reorderer,
                                                                      std::move(prach_context_repo),
                                                                      std::move(prach_cp_context_repo));


  msg_rx_dependencies.seq_id_checker =
      (receiver_cfg.ignore_ecpri_seq_id_field)
          ? static_cast<std::unique_ptr<sequence_id_checker>>(std::make_unique<sequence_id_checker_dummy_impl>())
          : static_cast<std::unique_ptr<sequence_id_checker>>(std::make_unique<sequence_id_checker_impl>());


  dependencies.eth_receiver = std::move(eth_receiver);


  return dependencies;
}


std::unique_ptr<receiver>
ocudu::ofh::create_receiver(const receiver_config&                                  receiver_cfg,
                            ocudulog::basic_logger&                                 logger,
                            task_executor&                                          uplink_executor,
                            std::unique_ptr<ether::receiver>                        eth_rx,
                            uplane_rx_symbol_notifier*                              notifier,
                            std::shared_ptr<prach_context_repository>               prach_context_repo,
                            std::shared_ptr<uplink_context_repository>              ul_slot_context_repo,
                            std::shared_ptr<uplink_cplane_context_repository>       ul_cp_context_repo,
                            std::shared_ptr<uplink_cplane_context_repository>       prach_cp_context_repo,
                            std::shared_ptr<uplink_notified_grid_symbol_repository> notifier_symbol_repo)
{
  auto rx_deps = resolve_receiver_dependencies(receiver_cfg,
                                               logger,
                                               uplink_executor,
                                               std::move(eth_rx),
                                               notifier,
                                               std::move(prach_context_repo),
                                               std::move(ul_slot_context_repo),
                                               std::move(ul_cp_context_repo),
                                               std::move(prach_cp_context_repo),
                                               std::move(notifier_symbol_repo));


  return std::make_unique<receiver_impl>(receiver_cfg, std::move(rx_deps));
}
