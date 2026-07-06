// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/uplane_bound_check_helpers.h  (83 lines)
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


#include "../support/uplink_cplane_context_repository.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/serdes/ofh_message_decoder_properties.h"
#include <algorithm>


namespace ocudu {
namespace ofh {

/// Returns true if an OFDM symbol index is valid for the given uplink Control-Plane context.

/// Returns true if an OFDM symbol index is valid for the given uplink Control-Plane context.
constexpr bool is_symbol_index_in_cplane_valid(const ul_cplane_context& cp_context, unsigned start_symbol)
{
  return (start_symbol >= cp_context.start_symbol) &&
         (start_symbol < (cp_context.start_symbol + cp_context.nof_symbols));
}

/// Returns true if all of the Open Fronthaul User-Plane per section PRB fields are valid, otherwise returns false.

/// Returns true if all of the Open Fronthaul User-Plane per section PRB fields are valid, otherwise returns false.
inline bool are_uplane_prb_fields_valid(const uplane_message_decoder_results& results,
                                        const ul_cplane_context&              cp_context,
                                        unsigned                              sector_id,
                                        ocudulog::basic_logger&               logger)
{
  return std::none_of(
      results.sections.begin(),
      results.sections.end(),
      [cp_context, sector_id, &logger](const uplane_section_params& up_section) {
        if (OCUDU_UNLIKELY(up_section.start_prb > MAX_NOF_PRBS - 1)) {
          logger.info(
              "Sector#{}: dropped received Open Fronthaul User-Plane packet as the first PRB index '{}' is not valid",
              sector_id,
              up_section.start_prb);


          return true;
        }


        if (OCUDU_UNLIKELY(up_section.start_prb + up_section.nof_prbs > MAX_NOF_PRBS)) {
          logger.info(
              "Sector#{}: dropped received Open Fronthaul User-Plane packet as the last PRB index '{}' is not valid",
              sector_id,
              up_section.start_prb + up_section.nof_prbs);


          return true;
        }


        if (OCUDU_UNLIKELY(!up_section.is_every_rb_used)) {
          logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as 'every other resource block is "
                      "used' mode is not supported",
                      sector_id);


          return true;
        }


        if (OCUDU_UNLIKELY(!up_section.use_current_symbol_number)) {
          logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as 'increment the current symbol "
                      "number and use that' mode is not supported",
                      sector_id);


          return true;
        }


        bool is_up_section_not_found_in_cp_section =
            up_section.start_prb < cp_context.prb_start ||
            (up_section.start_prb + up_section.nof_prbs) > (cp_context.prb_start + cp_context.nof_prb);


        if (OCUDU_UNLIKELY(is_up_section_not_found_in_cp_section)) {
          logger.info("Sector#{}: dropped received Open Fronthaul User-Plane packet as PRB index range '{}:{}' does "
                      "not match the expected range '{}:{}'",
                      sector_id,
                      up_section.start_prb,
                      up_section.nof_prbs,
                      cp_context.prb_start,
                      cp_context.nof_prb);
        }
        return is_up_section_not_found_in_cp_section;
      });
}


} // namespace ofh
} // namespace ocudu
