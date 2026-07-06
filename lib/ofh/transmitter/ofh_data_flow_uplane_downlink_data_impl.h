// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_data_flow_uplane_downlink_data_impl.h  (128 lines)
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
#include "ofh_data_flow_uplane_downlink_data.h"
#include "sequence_identifier_generator.h"
#include "ocudu/instrumentation/traces/ofh_traces.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/ofh/compression/iq_compressor.h"
#include "ocudu/ofh/ecpri/ecpri_packet_builder.h"
#include "ocudu/ofh/ethernet/ethernet_frame_builder.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_builder.h"
#include "ocudu/ran/cyclic_prefix.h"


namespace ocudu {
struct resource_grid_context;


namespace ether {
class eth_frame_pool;
}


namespace ofh {

/// Open Fronthaul User-Plane downlink data flow implementation configuration.

/// Open Fronthaul User-Plane downlink data flow implementation configuration.
struct data_flow_uplane_downlink_data_impl_config {
  /// Radio sector identifier.
  /// Radio sector identifier.
  unsigned sector;
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// RU bandwidth in PRBs.
  /// RU bandwidth in PRBs.
  unsigned ru_nof_prbs;
  /// Downlink eAxCs.
  /// Downlink eAxCs.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> dl_eaxc;
  /// Compression parameters.
  /// Compression parameters.
  ru_compression_params compr_params;
};

/// Open Fronthaul User-Plane downlink data flow implementation dependencies.

/// Open Fronthaul User-Plane downlink data flow implementation dependencies.
struct data_flow_uplane_downlink_data_impl_dependencies {
  /// Logger
  /// Logger
  ocudulog::basic_logger* logger = nullptr;
  /// Ethernet frame pool.
  /// Ethernet frame pool.
  std::shared_ptr<ether::eth_frame_pool> frame_pool;
  /// VLAN frame builder.
  /// VLAN frame builder.
  std::unique_ptr<ether::frame_builder> eth_builder;
  /// eCPRI packet builder.
  /// eCPRI packet builder.
  std::unique_ptr<ecpri::packet_builder> ecpri_builder;
  /// IQ compressor.
  /// IQ compressor.
  std::unique_ptr<iq_compressor> compressor_sel;
  /// User-Plane message builder.
  /// User-Plane message builder.
  std::unique_ptr<uplane_message_builder> up_builder;
};

/// Stores trace names used by the \c data_flow_uplane_downlink_data_impl class when OFH tracing is enabled.

/// Stores trace names used by the \c data_flow_uplane_downlink_data_impl class when OFH tracing is enabled.
template <bool Enabled = true>
class ofh_uplane_trace_names
{
  std::array<std::string, MAX_SUPPORTED_EAXC_ID_VALUE> trace_names;


public:
  explicit ofh_uplane_trace_names(span<const unsigned> dl_eaxc)
  {
    for (unsigned eaxc : dl_eaxc) {
      trace_names[eaxc] = fmt::format("ofh_uplane_eaxc_{}", eaxc);
    }
  }


  const std::string& operator[](std::size_t eaxc) const { return trace_names[eaxc]; }
};

/// Specialization of ofh_uplane_trace_names used when OFH event tracing is disabled.

/// Specialization of ofh_uplane_trace_names used when OFH event tracing is disabled.
template <>
class ofh_uplane_trace_names<false>
{
public:
  explicit ofh_uplane_trace_names(span<const unsigned> dl_eaxc) {}


  const std::string operator[](std::size_t eaxc) const { return ""; }
};

/// Open Fronthaul User-Plane downlink data flow implementation.

/// Open Fronthaul User-Plane downlink data flow implementation.
class data_flow_uplane_downlink_data_impl : public data_flow_uplane_downlink_data
{
public:
  explicit data_flow_uplane_downlink_data_impl(const data_flow_uplane_downlink_data_impl_config&  config,
                                               data_flow_uplane_downlink_data_impl_dependencies&& dependencies);

  // See interface for documentation.

  // See interface for documentation.
  void enqueue_section_type_1_message(const data_flow_uplane_resource_grid_context& context,
                                      const shared_resource_grid&                   grid) override;

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override { return controller; }


private:
  /// Enqueues an User-Plane message burst.
  /// Enqueues an User-Plane message burst.
  void enqueue_section_type_1_message_symbol_burst(const data_flow_uplane_resource_grid_context& context,
                                                   const shared_resource_grid&                   grid);

  /// Enqueues an User-Plane message symbol with the given context and grid.

  /// Enqueues an User-Plane message symbol with the given context and grid.
  unsigned enqueue_section_type_1_message_symbol(span<const cbf16_t>          iq_symbol_data,
                                                 const uplane_message_params& params,
                                                 unsigned                     eaxc,
                                                 span<uint8_t>                buffer);

  // See interface for documentation.

  // See interface for documentation.
  data_flow_message_encoding_metrics_collector* get_metrics_collector() override;


private:
  ocudulog::basic_logger&                   logger;
  const unsigned                            nof_symbols_per_slot;
  const unsigned                            ru_nof_prbs;
  const unsigned                            sector_id;
  const ru_compression_params               compr_params;
  operation_controller_dummy                controller;
  sequence_identifier_generator             up_seq_gen;
  std::shared_ptr<ether::eth_frame_pool>    frame_pool;
  std::unique_ptr<iq_compressor>            compressor_sel;
  std::unique_ptr<ether::frame_builder>     eth_builder;
  std::unique_ptr<ecpri::packet_builder>    ecpri_builder;
  std::unique_ptr<uplane_message_builder>   up_builder;
  ofh_uplane_trace_names<OFH_TRACE_ENABLED> formatted_trace_names;
};


} // namespace ofh
} // namespace ocudu
