// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_uplane_prach_symbol_data_flow_writer.cpp  (105 lines)
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

#include "ofh_uplane_prach_symbol_data_flow_writer.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder_properties.h"


using namespace ocudu;
using namespace ofh;


bool uplane_prach_symbol_data_flow_writer::write_to_prach_buffer(unsigned                              eaxc,
                                                                 const uplane_message_decoder_results& results)
{
  slot_point slot = results.params.slot;


  prach_context prach_context = prach_context_repo->get(slot);
  if (OCUDU_UNLIKELY(prach_context.empty())) {
    logger.info("Sector#{}: dropped received Open Fronthaul message as no uplink PRACH context was found for slot '{}' "
                "and eAxC '{}'",
                sector_id,
                slot,
                eaxc);
    return false;
  }

  // Find resource grid port with eAxC.

  // Find resource grid port with eAxC.
  unsigned port = std::distance(prach_eaxc.begin(), std::find(prach_eaxc.begin(), prach_eaxc.end(), eaxc));
  if (OCUDU_UNLIKELY(port >= prach_context.get_max_nof_ports())) {
    logger.info("Sector#{}: skipping eAxC value '{}' as the stored PRACH buffer only supports up to '{}' ports",
                sector_id,
                eaxc,
                prach_context.get_max_nof_ports());

    // This port is not needed for the PRACH, the message is not counted as an error for PRACH. A possible use case is
    // to configure OFH with four ports, two Rx antennas and only one port for PRACH. The eCRPI decoder will filter two
    // of the unused eAxCs (only two Rx antennas), and the other is checked here.

    // This port is not needed for the PRACH, the message is not counted as an error for PRACH. A possible use case is
    // to configure OFH with four ports, two Rx antennas and only one port for PRACH. The eCRPI decoder will filter two
    // of the unused eAxCs (only two Rx antennas), and the other is checked here.
    return true;
  }


  unsigned prach_nof_res           = prach_context.get_prach_nof_re();
  unsigned nof_re_to_prach_data    = prach_context.get_prach_offset_to_first_re();
  unsigned prach_nof_prbs          = std::ceil(float(prach_nof_res + nof_re_to_prach_data) / NOF_SUBCARRIERS_PER_RB);
  unsigned nof_re_after_prach_data = prach_nof_prbs * NOF_SUBCARRIERS_PER_RB - (prach_nof_res + nof_re_to_prach_data);
  unsigned prach_data_start_prb    = nof_re_to_prach_data / NOF_SUBCARRIERS_PER_RB;


  for (const auto& section : results.sections) {
    // Section PRBs are above the last PRB of the PRACH. Do not copy.
    // Section PRBs are above the last PRB of the PRACH. Do not copy.
    if (section.start_prb >= prach_nof_prbs) {
      continue;
    }

    // Section PRBs are below the first PRB of the PRACH. Do not copy.

    // Section PRBs are below the first PRB of the PRACH. Do not copy.
    if (section.start_prb + section.nof_prbs <= prach_data_start_prb) {
      continue;
    }

    // By default, try to copy all the expected PRBs.

    // By default, try to copy all the expected PRBs.
    unsigned nof_prbs_to_write = prach_nof_prbs - section.start_prb;

    // Section contains less PRBs than the PRACH buffer. Copy the whole section.

    // Section contains less PRBs than the PRACH buffer. Copy the whole section.
    if (section.start_prb + section.nof_prbs < prach_nof_prbs) {
      nof_prbs_to_write = section.nof_prbs;
    }

    // Set the start resource element for the PRACH buffer.

    // Set the start resource element for the PRACH buffer.
    unsigned start_re = std::max<int>(0, (section.start_prb * NOF_SUBCARRIERS_PER_RB - nof_re_to_prach_data));

    // Section RE start and number of REs.

    // Section RE start and number of REs.
    unsigned section_start_re = section.start_prb * NOF_SUBCARRIERS_PER_RB;
    unsigned section_nof_re   = nof_prbs_to_write * NOF_SUBCARRIERS_PER_RB;

    // Remove the unused REs from the last PRB.

    // Remove the unused REs from the last PRB.
    if (section.start_prb + section.nof_prbs >= prach_nof_prbs) {
      section_nof_re -= nof_re_after_prach_data;
    }

    // Start RE in the section IQ data.

    // Start RE in the section IQ data.
    unsigned iq_start_re = 0U;
    // If the first RE of the section is smaller than the offset to the first RE that contains data, adjust the first RE
    // that has data in the IQ data.
    // If the first RE of the section is smaller than the offset to the first RE that contains data, adjust the first RE
    // that has data in the IQ data.
    if (section_start_re < nof_re_to_prach_data) {
      iq_start_re = nof_re_to_prach_data - section_start_re;
      // Remove the offset REs from the number of REs of the section.
      // Remove the offset REs from the number of REs of the section.
      section_nof_re -= iq_start_re;
    }

    // Get the number of REs to copy from the IQ data.

    // Get the number of REs to copy from the IQ data.
    unsigned iq_size_re = std::min(section_nof_re, prach_nof_res);

    // Grab the data.

    // Grab the data.
    span<const cbf16_t> prach_in_data = span<const cbf16_t>(section.iq_samples).subspan(iq_start_re, iq_size_re);

    // Copy the data in the buffer.

    // Copy the data in the buffer.
    prach_context_repo->write_iq(slot, port, results.params.symbol_id, start_re, prach_in_data);


    if (OCUDU_UNLIKELY(logger.debug.enabled())) {
      logger.debug("Sector#{}: handling PRACH in slot '{}', symbol '{}' and port '{}'",
                   sector_id,
                   slot,
                   results.params.symbol_id,
                   port);
    }
  }


  return true;
}
