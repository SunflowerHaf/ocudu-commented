// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ofh_sector_config.h  (139 lines)
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


#include "ocudu/adt/static_vector.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/ofh/compression/compression_params.h"
#include "ocudu/ofh/ethernet/ethernet_mac_address.h"
#include "ocudu/ofh/ethernet/ethernet_receiver.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter.h"
#include "ocudu/ofh/ethernet/ethernet_vlan_params.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/ofh_uplane_rx_symbol_notifier.h"
#include "ocudu/ofh/receiver/ofh_receiver_configuration.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_configuration.h"
#include "ocudu/ran/bs_channel_bandwidth.h"
#include "ocudu/ran/cyclic_prefix.h"
#include <string>


namespace ocudu {


class task_executor;


namespace ofh {


class error_notifier;

/// Open Fronthaul sector configuration.

/// Open Fronthaul sector configuration.
struct sector_configuration {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector_id;
  /// Ethernet interface name or identifier.
  /// Ethernet interface name or identifier.
  std::string interface;
  /// Promiscuous mode flag.
  /// Promiscuous mode flag.
  bool is_promiscuous_mode_enabled;
  /// Ethernet link status checking flag.
  /// Ethernet link status checking flag.
  bool is_link_status_check_enabled;
  /// MTU size.
  /// MTU size.
  units::bytes mtu_size;
  /// Destination MAC address, corresponds to the Radio Unit MAC address.
  /// Destination MAC address, corresponds to the Radio Unit MAC address.
  ether::mac_address mac_dst_address;
  /// Source MAC address, corresponds to the Distributed Unit MAC address.
  /// Source MAC address, corresponds to the Distributed Unit MAC address.
  ether::mac_address mac_src_address;
  /// VLAN configuration for C-Plane.
  /// VLAN configuration for C-Plane.
  std::optional<ether::vlan_parameters> vlan_cfg_cp;
  /// VLAN configuration for U-Plane.
  /// VLAN configuration for U-Plane.
  std::optional<ether::vlan_parameters> vlan_cfg_up;

  /// DU transmission window timing parameters.

  /// DU transmission window timing parameters.
  tx_window_timing_parameters tx_window_timing_params;
  /// Reception window timing parameters.
  /// Reception window timing parameters.
  rx_window_timing_parameters rx_window_timing_params;

  /// Cyclic prefix.

  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Highest subcarrier spacing.
  /// Highest subcarrier spacing.
  subcarrier_spacing scs;
  /// Cell channel bandwidth.
  /// Cell channel bandwidth.
  bs_channel_bandwidth bw;
  /// \brief RU operating bandwidth.
  ///
  /// Set this option when the operating bandwidth of the RU is larger than the configured bandwidth of the cell.
  /// \brief RU operating bandwidth.
  ///
  /// Set this option when the operating bandwidth of the RU is larger than the configured bandwidth of the cell.
  bs_channel_bandwidth ru_operating_bw;

  /// PRACH eAxC.

  /// PRACH eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> prach_eaxc;
  /// Downlink eAxC.
  /// Downlink eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> dl_eaxc;
  /// Uplink eAxC.
  /// Uplink eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_eaxc;

  /// Enables the Control-Plane PRACH message signalling.

  /// Enables the Control-Plane PRACH message signalling.
  bool is_prach_control_plane_enabled = false;
  /// Ignore the start symbol value received in the PRACH U-Plane packets.
  /// Ignore the start symbol value received in the PRACH U-Plane packets.
  bool ignore_prach_start_symbol = false;
  /// If set to true, the payload size encoded in a eCPRI header is ignored.
  /// If set to true, the payload size encoded in a eCPRI header is ignored.
  bool ignore_ecpri_payload_size_field = false;
  /// If set to true, the sequence id encoded in a eCPRI packet is ignored.
  /// If set to true, the sequence id encoded in a eCPRI packet is ignored.
  bool ignore_ecpri_seq_id_field = false;
  /// If set to true, metrics are enabled in the sector.
  /// If set to true, metrics are enabled in the sector.
  bool are_metrics_enabled = false;
  /// If set to true, logs late events as warnings, otherwise as info.
  /// If set to true, logs late events as warnings, otherwise as info.
  bool enable_log_warnings_for_lates = true;
  /// Warn of unreceived Radio Unit frames status.
  /// Warn of unreceived Radio Unit frames status.
  warn_unreceived_ru_frames log_unreceived_ru_frames = warn_unreceived_ru_frames::after_traffic_detection;
  /// Uplink compression parameters.
  /// Uplink compression parameters.
  ru_compression_params ul_compression_params;
  /// Downlink compression parameters.
  /// Downlink compression parameters.
  ru_compression_params dl_compression_params;
  /// PRACH compression parameters.
  /// PRACH compression parameters.
  ru_compression_params prach_compression_params;
  /// Downlink static compression header flag.
  /// Downlink static compression header flag.
  bool is_downlink_static_compr_hdr_enabled = true;
  /// Uplink static compression header flag.
  /// Uplink static compression header flag.
  bool is_uplink_static_compr_hdr_enabled = true;
  /// IQ data scaling to be applied prior to Downlink data compression.
  /// IQ data scaling to be applied prior to Downlink data compression.
  float iq_scaling;
  /// C-Plane PRACH FFT size (to be used in Type 3 messages).
  /// C-Plane PRACH FFT size (to be used in Type 3 messages).
  ofh::cplane_fft_size c_plane_prach_fft_len = ofh::cplane_fft_size::fft_4096;
  /// \brief Number of slots the timing handler is notified in advance of the transmission time.
  ///
  /// Sets the maximum allowed processing delay in slots.
  /// \brief Number of slots the timing handler is notified in advance of the transmission time.
  ///
  /// Sets the maximum allowed processing delay in slots.
  unsigned max_processing_delay_slots;
  /// Downlink processing time in microseconds.
  /// Downlink processing time in microseconds.
  std::chrono::microseconds dl_processing_time;
  /// Uplink request processing time in microseconds.
  /// Uplink request processing time in microseconds.
  std::chrono::microseconds ul_processing_time;
  /// Number of reception antennas.
  /// Number of reception antennas.
  unsigned nof_antennas_ul;

  /// Indicates if DPDK should be used by the underlying implementation.

  /// Indicates if DPDK should be used by the underlying implementation.
  bool uses_dpdk;
  /// Optional TDD configuration.
  /// Optional TDD configuration.
  std::optional<tdd_ul_dl_config_common> tdd_config;
};

/// Open Fronthaul sector dependencies.

/// Open Fronthaul sector dependencies.
struct sector_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger* logger = nullptr;
  /// Error notifier.
  /// Error notifier.
  error_notifier* err_notifier = nullptr;
  /// Downlink task executor.
  /// Downlink task executor.
  task_executor* downlink_executor = nullptr;
  /// Message transmitter and receiver task executor.
  /// Message transmitter and receiver task executor.
  task_executor* txrx_executor = nullptr;
  /// Uplink task executor.
  /// Uplink task executor.
  task_executor* uplink_executor = nullptr;
  /// User-Plane received symbol notifier.
  /// User-Plane received symbol notifier.
  uplane_rx_symbol_notifier* notifier = nullptr;
  /// Optional Ethernet transmitter.
  /// Optional Ethernet transmitter.
  std::optional<std::unique_ptr<ether::transmitter>> eth_transmitter;
  /// Optional Ethernet receiver.
  /// Optional Ethernet receiver.
  std::optional<std::unique_ptr<ether::receiver>> eth_receiver;
};


} // namespace ofh
} // namespace ocudu
