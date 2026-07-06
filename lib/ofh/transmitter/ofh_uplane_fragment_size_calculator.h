// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_uplane_fragment_size_calculator.h  (51 lines)
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


#include "ocudu/ofh/compression/compression_params.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace ofh {

/// \brief Open Fronthaul fragment size calculator.
///
/// This class calculates the fragments of a configured PRB range, based on the given frame size and compression
/// parameters. This class assumes one section per fragment.

/// \brief Open Fronthaul fragment size calculator.
///
/// This class calculates the fragments of a configured PRB range, based on the given frame size and compression
/// parameters. This class assumes one section per fragment.
class ofh_uplane_fragment_size_calculator
{
public:
  ofh_uplane_fragment_size_calculator(unsigned                     start_prb_,
                                      unsigned                     nof_prbs_,
                                      const ru_compression_params& compr_params);

  /// \brief Calculates the fragment size of the configured PRBs that will fit in the given frame size.
  ///
  /// \param[out] fragment_start_prb Start PRB for frame.
  /// \param[out] fragment_nof_prbs Number of PRBs that fit in the frame.
  /// \param[in] frame_size Frame size.
  /// \return True if it is the last fragment, otherwise false.

  /// \brief Calculates the fragment size of the configured PRBs that will fit in the given frame size.
  ///
  /// \param[out] fragment_start_prb Start PRB for frame.
  /// \param[out] fragment_nof_prbs Number of PRBs that fit in the frame.
  /// \param[in] frame_size Frame size.
  /// \return True if it is the last fragment, otherwise false.
  bool calculate_fragment_size(unsigned& fragment_start_prb, unsigned& fragment_nof_prbs, unsigned frame_size);

  /// \brief Calculates number of segments required to codify one resource grid symbol given the frame size.
  ///
  /// \param[in] frame_size   Frame size.
  /// \param[in] nof_prbs     Number of PRBs in a resource grid.
  /// \param[in] compr_params  Compression parameters for the I and Q samples.
  /// \param[in] headers_size Size of the headers stored in a frame alongside the I and Q samples.
  /// \return Number of segments.

  /// \brief Calculates number of segments required to codify one resource grid symbol given the frame size.
  ///
  /// \param[in] frame_size   Frame size.
  /// \param[in] nof_prbs     Number of PRBs in a resource grid.
  /// \param[in] compr_params  Compression parameters for the I and Q samples.
  /// \param[in] headers_size Size of the headers stored in a frame alongside the I and Q samples.
  /// \return Number of segments.
  static unsigned calculate_nof_segments(units::bytes                 frame_size,
                                         unsigned                     nof_prbs,
                                         const ru_compression_params& compr_params,
                                         units::bytes                 headers_size);


private:
  const unsigned     start_prb;
  const unsigned     nof_prbs;
  const units::bytes prb_size;
  unsigned           next_fragment_start_prb_index;
};


} // namespace ofh
} // namespace ocudu
