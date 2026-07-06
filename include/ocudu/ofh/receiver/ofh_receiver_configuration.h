// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/receiver/ofh_receiver_configuration.h  (63 lines)
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


#include "ocudu/ofh/compression/iq_decompressor.h"
#include "ocudu/ofh/ethernet/vlan_ethernet_frame_decoder.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/receiver/ofh_receiver_timing_parameters.h"
#include "ocudu/ofh/receiver/ofh_receiver_warn_unreceived_frames_parameters.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder.h"
#include "ocudu/ran/bs_channel_bandwidth.h"
#include "ocudu/ran/cyclic_prefix.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul receiver configuration.

/// Open Fronthaul receiver configuration.
struct receiver_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// Subcarrier spacing.
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// PRACH eAxC.
  /// PRACH eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> prach_eaxc;
  /// Uplink eAxC.
  /// Uplink eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_eaxc;
  /// Destination MAC address.
  /// Destination MAC address.
  ether::mac_address mac_dst_address;
  /// Source MAC address.
  /// Source MAC address.
  ether::mac_address mac_src_address;
  /// Reception window timing parameters.
  /// Reception window timing parameters.
  rx_window_timing_parameters rx_timing_params;
  /// \brief RU operating bandwidth.
  ///
  /// Set this option when the operating bandwidth of the RU is larger than the configured bandwidth of the cell.
  /// \brief RU operating bandwidth.
  ///
  /// Set this option when the operating bandwidth of the RU is larger than the configured bandwidth of the cell.
  bs_channel_bandwidth ru_operating_bw;
  /// Uplink compression parameters.
  /// Uplink compression parameters.
  ru_compression_params ul_compression_params;
  /// PRACH compression parameters.
  /// PRACH compression parameters.
  ru_compression_params prach_compression_params;
  /// Uplink static compression header flag.
  /// Uplink static compression header flag.
  bool is_uplink_static_compr_hdr_enabled = true;
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
  /// If set to true, metrics are enabled in the receiver.
  /// If set to true, metrics are enabled in the receiver.
  bool are_metrics_enabled = false;
  /// Warn of unreceived Radio Unit frames status.
  /// Warn of unreceived Radio Unit frames status.
  warn_unreceived_ru_frames log_unreceived_ru_frames = warn_unreceived_ru_frames::after_traffic_detection;
  /// If set to true, logs late events as warnings, otherwise as info.
  /// If set to true, logs late events as warnings, otherwise as info.
  bool enable_log_warnings_for_lates = true;
};


} // namespace ofh
} // namespace ocudu
