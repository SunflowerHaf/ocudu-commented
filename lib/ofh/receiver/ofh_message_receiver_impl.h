// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_message_receiver_impl.h  (122 lines)
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
#include "ofh_closed_rx_window_handler.h"
#include "ofh_data_flow_uplane_uplink_data.h"
#include "ofh_data_flow_uplane_uplink_prach.h"
#include "ofh_message_receiver.h"
#include "ofh_message_receiver_metrics_collector.h"
#include "ofh_sequence_id_checker_impl.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ecpri/ecpri_packet_decoder.h"
#include "ocudu/ofh/ethernet/ethernet_receiver.h"
#include "ocudu/ofh/ethernet/vlan_ethernet_frame_decoder.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/serdes/ofh_message_properties.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder.h"


namespace ocudu {
namespace ofh {


class rx_window_checker;

/// Message receiver configuration.

/// Message receiver configuration.
struct message_receiver_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// Number of symbols
  /// Number of symbols
  unsigned nof_symbols;
  /// Subcarrier spacing.
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// VLAN ethernet frame parameters.
  /// VLAN ethernet frame parameters.
  ether::vlan_frame_params vlan_params;
  /// Uplink PRACH eAxC.
  /// Uplink PRACH eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> prach_eaxc;
  /// Uplink eAxC.
  /// Uplink eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_eaxc;
  /// Warn unreceived Open Fronthaul messages.
  /// Warn unreceived Open Fronthaul messages.
  warn_unreceived_ru_frames warn_unreceived_frames = warn_unreceived_ru_frames::after_traffic_detection;
  /// If set to true, metrics are enabled in the message receiver.
  /// If set to true, metrics are enabled in the message receiver.
  bool are_metrics_enabled = false;
  /// If set to true, logs late events as warnings, otherwise as info.
  /// If set to true, logs late events as warnings, otherwise as info.
  bool enable_log_warnings_for_lates;
};

/// Message receiver dependencies.

/// Message receiver dependencies.
struct message_receiver_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger* logger = nullptr;
  /// Ethernet receiver.
  /// Ethernet receiver.
  std::unique_ptr<ether::receiver> eth_receiver;
  /// Reception window checker.
  /// Reception window checker.
  rx_window_checker* window_checker = nullptr;
  /// Reception window handler.
  /// Reception window handler.
  closed_rx_window_handler* window_handler;
  /// eCPRI packet decoder.
  /// eCPRI packet decoder.
  std::unique_ptr<ecpri::packet_decoder> ecpri_decoder;
  /// Ethernet frame decoder.
  /// Ethernet frame decoder.
  std::unique_ptr<ether::vlan_frame_decoder> eth_frame_decoder;
  /// User-Plane uplink data flow.
  /// User-Plane uplink data flow.
  std::unique_ptr<data_flow_uplane_uplink_data> data_flow_uplink;
  /// User-Plane uplink PRACH data flow.
  /// User-Plane uplink PRACH data flow.
  std::unique_ptr<data_flow_uplane_uplink_prach> data_flow_prach;
  /// Sequence id checker.
  /// Sequence id checker.
  std::unique_ptr<sequence_id_checker> seq_id_checker;
};

/// Open Fronthaul message receiver interface implementation.

/// Open Fronthaul message receiver interface implementation.
class message_receiver_impl : public message_receiver
{
public:
  message_receiver_impl(const message_receiver_config& config, message_receiver_dependencies&& dependencies);

  // See interface for documentation.

  // See interface for documentation.
  void on_new_frame(ether::unique_rx_buffer buffer) override;

  // See interface for the documentation.

  // See interface for the documentation.
  operation_controller& get_operation_controller() override { return controller; }

  // See interface for the documentation.

  // See interface for the documentation.
  message_receiver_metrics_collector* get_metrics_collector() override
  {
    return metrics_collector.enabled() ? &metrics_collector : nullptr;
  }


private:
  /// Processes an Ethernet frame received from the underlying Ethernet link.
  /// Processes an Ethernet frame received from the underlying Ethernet link.
  void process_new_frame(ether::unique_rx_buffer buff);

  /// Returns true if the ethernet frame represented by the given eth parameters should be filtered, otherwise false.

  /// Returns true if the ethernet frame represented by the given eth parameters should be filtered, otherwise false.
  bool should_ethernet_frame_be_filtered(const ether::vlan_frame_params& eth_params) const;

  /// Returns true if the eCPRI packet represented by the given eCPRI parameters should be filtered, otherwise false.

  /// Returns true if the eCPRI packet represented by the given eCPRI parameters should be filtered, otherwise false.
  bool should_ecpri_packet_be_filtered(const ecpri::packet_parameters& ecpri_params) const;


private:
  ocudulog::basic_logger&                               logger;
  const unsigned                                        sector_id;
  const unsigned                                        nof_symbols;
  const subcarrier_spacing                              scs;
  const ether::vlan_frame_params                        vlan_params;
  const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_prach_eaxc;
  const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_eaxc;
  bool                                                  warn_unreceived_frames_on_first_rx_message;
  rx_window_checker&                                    window_checker;
  closed_rx_window_handler&                             window_handler;
  std::unique_ptr<sequence_id_checker>                  seq_id_checker;
  std::unique_ptr<ether::vlan_frame_decoder>            vlan_decoder;
  std::unique_ptr<ecpri::packet_decoder>                ecpri_decoder;
  std::unique_ptr<data_flow_uplane_uplink_data>         data_flow_uplink;
  std::unique_ptr<data_flow_uplane_uplink_prach>        data_flow_prach;
  message_receiver_metrics_collector                    metrics_collector;
  bool                                                  enable_log_warnings_for_lates;
  operation_controller_dummy                            controller;
};


} // namespace ofh
} // namespace ocudu
