// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_uplane_rx_symbol_data_flow_writer.cpp  (80 lines)
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

#include "ofh_uplane_rx_symbol_data_flow_writer.h"
#include "ocudu/instrumentation/traces/ofh_traces.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder_properties.h"


using namespace ocudu;
using namespace ofh;


bool uplane_rx_symbol_data_flow_writer::write_to_resource_grid(unsigned                              eaxc,
                                                               const uplane_message_decoder_results& results)
{
  trace_point access_repo_tp = ofh_tracer.now();


  slot_point     slot       = results.params.slot;
  unsigned       symbol     = results.params.symbol_id;
  uplink_context ul_context = ul_context_repo->get(slot, symbol);
  if (OCUDU_UNLIKELY(ul_context.empty())) {
    logger.info(
        "Sector#{}: dropped received Open Fronthaul message as no uplink slot context was found for slot '{}', symbol "
        "'{}' and eAxC '{}'",
        sector_id,
        results.params.slot,
        results.params.symbol_id,
        eaxc);


    return false;
  }
  ofh_tracer << trace_event("ofh_receiver_access_repo", access_repo_tp);

  // Find resource grid port with eAxC.

  // Find resource grid port with eAxC.
  unsigned rg_port = std::distance(ul_eaxc.begin(), std::find(ul_eaxc.begin(), ul_eaxc.end(), eaxc));
  ocudu_assert(rg_port < ul_eaxc.size(), "Invalid resource grid port value '{}'", rg_port);

  // The DU cell bandwidth may be narrower than the operating bandwidth of the RU.

  // The DU cell bandwidth may be narrower than the operating bandwidth of the RU.
  unsigned du_nof_prbs = ul_context.get_grid_nof_prbs();
  for (const auto& section : results.sections) {
    // Drop the whole section when all PRBs are outside the range of the DU bandwidth and the operating bandwidth of the
    // RU is larger.
    // Drop the whole section when all PRBs are outside the range of the DU bandwidth and the operating bandwidth of the
    // RU is larger.
    if (section.start_prb >= du_nof_prbs) {
      continue;
    }

    // At this point, we have to care about the following cases:
    //   a) The last PRB of the section falls outside the range of the DU cell bandwidth.
    //   b) The last PRB of the section falls inside the range of the DU cell bandwidth.

    // Take care of case (a), takes the first N PRBs inside the section.

    // At this point, we have to care about the following cases:
    //   a) The last PRB of the section falls outside the range of the DU cell bandwidth.
    //   b) The last PRB of the section falls inside the range of the DU cell bandwidth.

    // Take care of case (a), takes the first N PRBs inside the section.
    unsigned nof_prbs_to_write = du_nof_prbs - section.start_prb;
    // Take care of case (b), takes all the PRBs inside the section.
    // Take care of case (b), takes all the PRBs inside the section.
    if (section.start_prb + section.nof_prbs < du_nof_prbs) {
      nof_prbs_to_write = section.nof_prbs;
    }


    trace_point write_rg_tp = ofh_tracer.now();


    ul_context_repo->write_grid(
        slot,
        rg_port,
        symbol,
        section.start_prb * NOF_SUBCARRIERS_PER_RB,
        span<const cbf16_t>(section.iq_samples).first(nof_prbs_to_write * NOF_SUBCARRIERS_PER_RB));


    ofh_tracer << trace_event("ofh_receiver_write_rg", write_rg_tp);


    if (OCUDU_UNLIKELY(logger.debug.enabled())) {
      logger.debug("Sector#{}: written IQ data into UL resource grid PRB range [{},{}), for slot '{}', symbol '{}' and "
                   "port '{}'",
                   sector_id,
                   section.start_prb,
                   section.start_prb + nof_prbs_to_write,
                   slot,
                   symbol,
                   rg_port);
    }
  }


  return true;
}
