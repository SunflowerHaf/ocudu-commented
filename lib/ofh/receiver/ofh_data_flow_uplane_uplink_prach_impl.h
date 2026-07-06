// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_data_flow_uplane_uplink_prach_impl.h  (77 lines)
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


#include "../support/prach_context_repository.h"
#include "../support/uplink_cplane_context_repository.h"
#include "ofh_data_flow_uplane_decoding_metrics_collector.h"
#include "ofh_data_flow_uplane_uplink_prach.h"
#include "ofh_uplane_prach_data_flow_notifier.h"
#include "ofh_uplane_prach_symbol_data_flow_writer.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul User-Plane uplink PRACH data flow implementation configuration.

/// Open Fronthaul User-Plane uplink PRACH data flow implementation configuration.
struct data_flow_uplane_uplink_prach_impl_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// PRACH Control-Plane enabled flag.
  /// PRACH Control-Plane enabled flag.
  bool is_prach_cplane_enabled;
  /// Ignore the start symbol value received in the PRACH U-Plane packets.
  /// Ignore the start symbol value received in the PRACH U-Plane packets.
  bool ignore_prach_start_symbol;
  /// Enabled metrics flag.
  /// Enabled metrics flag.
  bool are_metrics_enabled;
  /// Uplink PRACH eAxCs.
  /// Uplink PRACH eAxCs.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> prach_eaxcs;
};

/// Open Fronthaul User-Plane uplink PRACH data flow implementation dependencies.

/// Open Fronthaul User-Plane uplink PRACH data flow implementation dependencies.
struct data_flow_uplane_uplink_prach_impl_dependencies {
  /// Logger.
  /// Logger.
  ocudulog::basic_logger* logger;
  /// User-Plane received symbol notifier.
  /// User-Plane received symbol notifier.
  std::shared_ptr<uplane_rx_symbol_notifier> notifier;
  /// Control-Plane context repository.
  /// Control-Plane context repository.
  std::shared_ptr<uplink_cplane_context_repository> prach_cplane_context_repo;
  /// Uplink PRACH context repository.
  /// Uplink PRACH context repository.
  std::shared_ptr<prach_context_repository> prach_context_repo;
  /// User-Plane message decoder.
  /// User-Plane message decoder.
  std::unique_ptr<uplane_message_decoder> uplane_decoder;
};

/// Open Fronthaul User-Plane uplink PRACH data flow implementation.

/// Open Fronthaul User-Plane uplink PRACH data flow implementation.
class data_flow_uplane_uplink_prach_impl : public data_flow_uplane_uplink_prach
{
public:
  data_flow_uplane_uplink_prach_impl(const data_flow_uplane_uplink_prach_impl_config&  config,
                                     data_flow_uplane_uplink_prach_impl_dependencies&& dependencies);

  // See interface for documentation.

  // See interface for documentation.
  void decode_type1_message(unsigned eaxc, span<const uint8_t> message) override;

  // See interface for documentation.

  // See interface for documentation.
  data_flow_message_decoding_metrics_collector& get_metrics_collector() override { return metrics_collector; }


private:
  /// Returns true if the User-Plane packet represented by the given User-Plane results and eAxC should be filtered,
  /// otherwise false.
  /// Returns true if the User-Plane packet represented by the given User-Plane results and eAxC should be filtered,
  /// otherwise false.
  bool should_uplane_packet_be_filtered(unsigned eaxc, const uplane_message_decoder_results& results) const;


private:
  ocudulog::basic_logger&                           logger;
  const bool                                        is_prach_cplane_enabled;
  std::shared_ptr<uplink_cplane_context_repository> prach_cplane_context_repo;
  std::unique_ptr<uplane_message_decoder>           uplane_decoder;
  uplane_prach_symbol_data_flow_writer              prach_iq_writter;
  uplane_prach_data_flow_notifier                   notification_sender;
  const unsigned                                    sector_id;
  const bool                                        ignore_prach_start_symbol;
  data_flow_message_decoding_metrics_collector      metrics_collector;
};


} // namespace ofh
} // namespace ocudu
