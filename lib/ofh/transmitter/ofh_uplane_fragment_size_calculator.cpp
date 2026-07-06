// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_uplane_fragment_size_calculator.cpp  (96 lines)
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

#include "ofh_uplane_fragment_size_calculator.h"
#include "ocudu/ran/resource_block.h"


using namespace ocudu;
using namespace ofh;

/// Builds and returns an index of the PRB data size lookup table with the given bitwidth.

/// Builds and returns an index of the PRB data size lookup table with the given bitwidth.
static constexpr unsigned build_prb_data_size_lut_index(unsigned bitwidth)
{
  return units::bits(bitwidth * NOF_SUBCARRIERS_PER_RB * 2).round_up_to_bytes().value();
}

/// Returns the PRB data size in bytes for the given compression parameters.

/// Returns the PRB data size in bytes for the given compression parameters.
static units::bytes get_prb_data_size(const ru_compression_params& compr_params)
{
  static constexpr std::array<unsigned, 17> prb_data_size = {build_prb_data_size_lut_index(0),
                                                             build_prb_data_size_lut_index(1),
                                                             build_prb_data_size_lut_index(2),
                                                             build_prb_data_size_lut_index(3),
                                                             build_prb_data_size_lut_index(4),
                                                             build_prb_data_size_lut_index(5),
                                                             build_prb_data_size_lut_index(6),
                                                             build_prb_data_size_lut_index(7),
                                                             build_prb_data_size_lut_index(8),
                                                             build_prb_data_size_lut_index(9),
                                                             build_prb_data_size_lut_index(10),
                                                             build_prb_data_size_lut_index(11),
                                                             build_prb_data_size_lut_index(12),
                                                             build_prb_data_size_lut_index(13),
                                                             build_prb_data_size_lut_index(14),
                                                             build_prb_data_size_lut_index(15),
                                                             build_prb_data_size_lut_index(16)};


  ocudu_assert(compr_params.data_width < prb_data_size.size(), "Invalid data width");


  return units::bytes((compr_params.type == compression_type::none || compr_params.type == compression_type::modulation)
                          ? prb_data_size[compr_params.data_width]
                          : prb_data_size[compr_params.data_width] + 1U);
}


ofh_uplane_fragment_size_calculator::ofh_uplane_fragment_size_calculator(unsigned                     start_prb_,
                                                                         unsigned                     nof_prbs_,
                                                                         const ru_compression_params& compr_params) :
  start_prb(start_prb_),
  nof_prbs(nof_prbs_),
  prb_size(get_prb_data_size(compr_params)),
  next_fragment_start_prb_index(start_prb_)
{
}


bool ofh_uplane_fragment_size_calculator::calculate_fragment_size(unsigned& fragment_start_prb,
                                                                  unsigned& fragment_nof_prbs,
                                                                  unsigned  frame_size)
{
  units::bytes frame_sz(frame_size);


  if (frame_sz.value() < prb_size.value()) {
    fragment_start_prb = next_fragment_start_prb_index;
    fragment_nof_prbs  = 0;


    return false;
  }


  unsigned nof_prbs_fit_in_frame = frame_sz.value() / prb_size.value();


  fragment_start_prb      = next_fragment_start_prb_index;
  unsigned remaining_prbs = nof_prbs - (next_fragment_start_prb_index - start_prb);

  // Last fragment.

  // Last fragment.
  if (nof_prbs_fit_in_frame >= remaining_prbs) {
    fragment_nof_prbs = remaining_prbs;
    next_fragment_start_prb_index += remaining_prbs;


    return true;
  }


  fragment_nof_prbs = nof_prbs_fit_in_frame;
  next_fragment_start_prb_index += nof_prbs_fit_in_frame;


  return false;
}


unsigned ofh_uplane_fragment_size_calculator::calculate_nof_segments(units::bytes                 frame_size,
                                                                     unsigned                     nof_prbs,
                                                                     const ru_compression_params& compr_params,
                                                                     units::bytes                 headers_size)
{
  units::bytes prb_size              = get_prb_data_size(compr_params);
  units::bytes frame_size_data       = frame_size - headers_size;
  unsigned     nof_prbs_fit_in_frame = frame_size_data.value() / prb_size.value();


  return std::ceil(static_cast<float>(nof_prbs) / nof_prbs_fit_in_frame);
}
