// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_receiver_impl.cpp  (135 lines)
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

#include "ofh_receiver_impl.h"
#include "ofh_message_receiver_task_dispatcher.h"
#include "ocudu/ofh/ethernet/ethernet_properties.h"


using namespace ocudu;
using namespace ofh;


static message_receiver_config get_message_receiver_configuration(const receiver_config& rx_config)
{
  message_receiver_config config;


  config.sector                        = rx_config.sector;
  config.nof_symbols                   = get_nsymb_per_slot(rx_config.cp);
  config.scs                           = rx_config.scs;
  config.vlan_params.mac_src_address   = rx_config.mac_src_address;
  config.vlan_params.mac_dst_address   = rx_config.mac_dst_address;
  config.vlan_params.eth_type          = ether::ECPRI_ETH_TYPE;
  config.warn_unreceived_frames        = rx_config.log_unreceived_ru_frames;
  config.are_metrics_enabled           = rx_config.are_metrics_enabled;
  config.enable_log_warnings_for_lates = rx_config.enable_log_warnings_for_lates;


  config.prach_eaxc = rx_config.prach_eaxc;
  config.ul_eaxc    = rx_config.ul_eaxc;


  return config;
}


static message_receiver_dependencies
get_message_receiver_dependencies(receiver_impl_dependencies::message_rx_dependencies rx_dependencies,
                                  rx_window_checker&                                  window_checker,
                                  closed_rx_window_handler&                           window_handler)
{
  message_receiver_dependencies dependencies;
  dependencies.logger         = rx_dependencies.logger;
  dependencies.window_checker = &window_checker;
  dependencies.window_handler = &window_handler;
  dependencies.ecpri_decoder  = std::move(rx_dependencies.ecpri_decoder);
  ocudu_assert(dependencies.ecpri_decoder, "Invalid eCPRI decoder");
  dependencies.eth_frame_decoder = std::move(rx_dependencies.eth_frame_decoder);
  ocudu_assert(dependencies.eth_frame_decoder, "Invalid Ethernet frame decoder");
  dependencies.data_flow_uplink = std::move(rx_dependencies.data_flow_uplink);
  ocudu_assert(dependencies.data_flow_uplink, "Invalid uplink data flow decoder");
  dependencies.data_flow_prach = std::move(rx_dependencies.data_flow_prach);
  ocudu_assert(dependencies.data_flow_prach, "Invalid PRACH data flow decoder");
  dependencies.seq_id_checker = std::move(rx_dependencies.seq_id_checker);
  ocudu_assert(dependencies.seq_id_checker, "Invalid sequence id checker");


  return dependencies;
}


static closed_rx_window_handler_config get_closed_rx_window_handler_config(const receiver_config& config)
{
  closed_rx_window_handler_config out_config;
  out_config.sector                 = config.sector;
  out_config.warn_unreceived_frames = config.log_unreceived_ru_frames;
  out_config.rx_timing_params       = config.rx_timing_params;
  // As it runs in the same executor, do not delay the reception window close.
  // As it runs in the same executor, do not delay the reception window close.
  out_config.nof_symbols_to_process_uplink = 0;


  return out_config;
}


static closed_rx_window_handler_dependencies
generate_closed_rx_window_dependencies(receiver_impl_dependencies::close_rx_window_dependencies&& dependencies,
                                       ocudulog::basic_logger&                                    logger,
                                       task_executor&                                             executor)
{
  closed_rx_window_handler_dependencies out_dependencies;
  out_dependencies.logger      = &logger;
  out_dependencies.executor    = &executor;
  out_dependencies.prach_repo  = std::move(dependencies.prach_repo);
  out_dependencies.uplink_repo = std::move(dependencies.uplink_repo);
  out_dependencies.notifier    = std::move(dependencies.notifier);


  return out_dependencies;
}


void ota_symbol_boundary_dispatcher::on_new_symbol(const slot_symbol_point_context& symbol_point_context)
{
  for (auto& handler : handlers) {
    handler->on_new_symbol(symbol_point_context);
  }
}


receiver_impl::receiver_impl(const receiver_config& config, receiver_impl_dependencies&& dependencies) :
  symbol_reorderer(std::move(dependencies.symbol_reorderer)),
  closed_window_handler(get_closed_rx_window_handler_config(config),
                        generate_closed_rx_window_dependencies(std::move(dependencies.window_handler_dependencies),
                                                               *dependencies.logger,
                                                               *dependencies.executor)),
  window_checker(config.are_metrics_enabled, config.rx_timing_params),
  symbol_boundary_dispatcher([](closed_rx_window_handler& handler, rx_window_checker& checker) {
    std::vector<ota_symbol_boundary_notifier*> handlers;
    if (!checker.disabled()) {
      handlers.push_back(&checker);
    }
    handlers.push_back(&handler);


    return handlers;
  }(closed_window_handler, window_checker)),
  msg_receiver(get_message_receiver_configuration(config),
               get_message_receiver_dependencies(std::move(dependencies.msg_rx_dependencies),
                                                 window_checker,
                                                 closed_window_handler)),
  metrics_collector(config.are_metrics_enabled,
                    closed_window_handler,
                    window_checker,
                    msg_receiver.get_metrics_collector(),
                    dependencies.eth_receiver->get_metrics_collector()),
  rcv_task_dispatcher(*dependencies.logger,
                      msg_receiver,
                      *dependencies.executor,
                      config.sector,
                      std::move(dependencies.eth_receiver)),
  ctrl(rcv_task_dispatcher, closed_window_handler)
{
}


ota_symbol_boundary_notifier* receiver_impl::get_ota_symbol_boundary_notifier()
{
  return &symbol_boundary_dispatcher;
}


operation_controller& receiver_impl::get_operation_controller()
{
  return ctrl;
}


receiver_metrics_collector* receiver_impl::get_metrics_collector()
{
  return metrics_collector.disabled() ? nullptr : &metrics_collector;
}
