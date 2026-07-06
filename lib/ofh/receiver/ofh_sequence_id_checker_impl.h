// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_sequence_id_checker_impl.h  (90 lines)
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


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/adt/circular_map.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/receiver/ofh_sequence_id_checker.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul sequence identifier checker implementation.

/// Open Fronthaul sequence identifier checker implementation.
class sequence_id_checker_impl : public sequence_id_checker
{
  static constexpr int NOF_SEQUENCES_IDENTIFIERS      = 1u << 8;
  static constexpr int HALF_NOF_SEQUENCES_IDENTIFIERS = NOF_SEQUENCES_IDENTIFIERS / 2;


  bounded_bitset<MAX_SUPPORTED_EAXC_ID_VALUE>                        initialized;
  static_circular_map<uint8_t, uint8_t, MAX_SUPPORTED_EAXC_ID_VALUE> counters;


public:
  /// Default constructor.
  /// Default constructor.
  sequence_id_checker_impl() : initialized(MAX_SUPPORTED_EAXC_ID_VALUE)
  {
    for (unsigned K = 0; K != MAX_SUPPORTED_EAXC_ID_VALUE; ++K) {
      counters.emplace(K, 0);
    }
  }

  // See interface for documentation.

  // See interface for documentation.
  int update_and_compare_seq_id(unsigned eaxc, uint8_t seq_id) override
  {
    ocudu_assert(eaxc < MAX_SUPPORTED_EAXC_ID_VALUE,
                 "Invalid eAxC value '{}'. Maximum eAxC value is '{}'",
                 eaxc,
                 MAX_SUPPORTED_EAXC_ID_VALUE);


    auto& counter = counters[eaxc];

    // First packet is always valid.

    // First packet is always valid.
    if (!initialized.test(eaxc)) {
      initialized.set(eaxc);
      counter = seq_id;


      return 0;
    }

    // Get the expected sequence identifier and update its value.

    // Get the expected sequence identifier and update its value.
    uint8_t expected_seq_id = counter + 1;


    if (seq_id == expected_seq_id) {
      ++counter;


      return 0;
    }


    int nof_skipped_seq_id = get_nof_skipped_sequence_id(seq_id, expected_seq_id);

    // Update the expected sequence identifier when the sequence identifier is from the future.

    // Update the expected sequence identifier when the sequence identifier is from the future.
    if (nof_skipped_seq_id > 0) {
      counter = seq_id;
    }


    return nof_skipped_seq_id;
  }


private:
  /// \brief Returns the number of skipped sequence identifiers using the given sequence identifier and expected
  /// sequence identifier.
  ///
  /// A negative difference means that the sequence identifier received is from the past.
  /// No difference means that the sequence identifier matches the expected.
  /// A positive difference means that the sequence identifier is from the future.
  /// \brief Returns the number of skipped sequence identifiers using the given sequence identifier and expected
  /// sequence identifier.
  ///
  /// A negative difference means that the sequence identifier received is from the past.
  /// No difference means that the sequence identifier matches the expected.
  /// A positive difference means that the sequence identifier is from the future.
  static int get_nof_skipped_sequence_id(uint8_t seq_id, uint8_t expected_seq_id)
  {
    int a = static_cast<int>(seq_id) - static_cast<int>(expected_seq_id);
    if (a >= HALF_NOF_SEQUENCES_IDENTIFIERS) {
      return a - NOF_SEQUENCES_IDENTIFIERS;
    }
    if (a < -HALF_NOF_SEQUENCES_IDENTIFIERS) {
      return a + NOF_SEQUENCES_IDENTIFIERS;
    }
    return a;
  }
};


} // namespace ofh
} // namespace ocudu
