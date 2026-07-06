// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_uplane_prach_symbol_data_flow_writer.h  (43 lines)
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
#include "ocudu/ocudulog/logger.h"


namespace ocudu {
namespace ofh {


struct uplane_message_decoder_results;

/// \brief Open Fronthaul User-Plane PRACH symbol data flow writer.
///
/// Writes IQ data received in an Open Fronthaul message to the corresponding PRACH buffer.

/// \brief Open Fronthaul User-Plane PRACH symbol data flow writer.
///
/// Writes IQ data received in an Open Fronthaul message to the corresponding PRACH buffer.
class uplane_prach_symbol_data_flow_writer
{
public:
  uplane_prach_symbol_data_flow_writer(span<const unsigned>                      prach_eaxc_,
                                       unsigned                                  sector_id_,
                                       ocudulog::basic_logger&                   logger_,
                                       std::shared_ptr<prach_context_repository> prach_context_repo_) :
    prach_eaxc(prach_eaxc_.begin(), prach_eaxc_.end()),
    sector_id(sector_id_),
    logger(logger_),
    prach_context_repo(std::move(prach_context_repo_))
  {
    ocudu_assert(prach_context_repo, "Invalid PRACH context repository");
  }

  /// Writes the given decoder results in the corresponding PRACH buffer. Returns true on success, otherwise false.

  /// Writes the given decoder results in the corresponding PRACH buffer. Returns true on success, otherwise false.
  bool write_to_prach_buffer(unsigned eaxc, const uplane_message_decoder_results& results);


private:
  const static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> prach_eaxc;
  const unsigned                                        sector_id;
  ocudulog::basic_logger&                               logger;
  std::shared_ptr<prach_context_repository>             prach_context_repo;
};


} // namespace ofh
} // namespace ocudu
