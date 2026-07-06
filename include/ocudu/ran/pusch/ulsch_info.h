// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/ulsch_info.h  (146 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/sch/sch_mcs.h"
#include "ocudu/ran/sch/sch_segmentation.h"
#include "ocudu/support/units.h"
#include <optional>


namespace ocudu {

/// \brief Collects the necessary parameters to calculate the Uplink Shared Channel (UL-SCH) information.
///
/// The parameters are described in TS38.212 Section 6.3.2.4.1.

/// \brief Collects the necessary parameters to calculate the Uplink Shared Channel (UL-SCH) information.
///
/// The parameters are described in TS38.212 Section 6.3.2.4.1.
struct ulsch_configuration {
  /// Transport block size. Set to zero if no shared channel is multiplexed.
  /// Transport block size. Set to zero if no shared channel is multiplexed.
  units::bits tbs;
  /// Modulation and coding scheme.
  /// Modulation and coding scheme.
  sch_mcs_description mcs_descr;
  /// Number of HARQ-ACK bits to multiplex in the transmission. Parameter \f$O_\textup{ACK}\f$.
  /// Number of HARQ-ACK bits to multiplex in the transmission. Parameter \f$O_\textup{ACK}\f$.
  units::bits nof_harq_ack_bits;
  /// Number of CSI Part 1 bits to multiplex in the transmission. Parameter \f$O_\textup{CSI-1}\f$.
  /// Number of CSI Part 1 bits to multiplex in the transmission. Parameter \f$O_\textup{CSI-1}\f$.
  units::bits nof_csi_part1_bits;
  /// Number of CSI Part 2 bits to multiplex in the transmission. Parameter \f$O_\textup{CSI-2}\f$.
  /// Number of CSI Part 2 bits to multiplex in the transmission. Parameter \f$O_\textup{CSI-2}\f$.
  units::bits nof_csi_part2_bits;
  /// \brief Parameter \f$\alpha\f$ as per TS38.212 Section 6.3.2.4.
  ///
  /// Provided by the higher layer parameter \e scaling in TS38.331 Section 6.3.2, Information Element \e UCI-OnPUSCH.
  /// \brief Parameter \f$\alpha\f$ as per TS38.212 Section 6.3.2.4.
  ///
  /// Provided by the higher layer parameter \e scaling in TS38.331 Section 6.3.2, Information Element \e UCI-OnPUSCH.
  float alpha_scaling;
  /// Parameter \f$\beta _\textup{offset} ^\textup{HARQ-ACK}\f$.
  /// Parameter \f$\beta _\textup{offset} ^\textup{HARQ-ACK}\f$.
  float beta_offset_harq_ack;
  /// Parameter \f$\beta _\textup{offset} ^\textup{CSI-1}\f$.
  /// Parameter \f$\beta _\textup{offset} ^\textup{CSI-1}\f$.
  float beta_offset_csi_part1;
  /// Parameter \f$\beta _\textup{offset} ^\textup{CSI-2}\f$.
  /// Parameter \f$\beta _\textup{offset} ^\textup{CSI-2}\f$.
  float beta_offset_csi_part2;
  /// Transmission bandwidth in resource blocks.
  /// Transmission bandwidth in resource blocks.
  unsigned nof_rb;
  /// First OFDM index for the transmission within the slot.
  /// First OFDM index for the transmission within the slot.
  unsigned start_symbol_index;
  /// Number of OFDM symbols used for the transmission.
  /// Number of OFDM symbols used for the transmission.
  unsigned nof_symbols;
  /// DM-RS Type.
  /// DM-RS Type.
  dmrs_config_type dmrs_type;
  /// Boolean mask indicating which OFDM symbols in the slot contain DM-RS.
  /// Boolean mask indicating which OFDM symbols in the slot contain DM-RS.
  bounded_bitset<MAX_NSYMB_PER_SLOT> dmrs_symbol_mask;
  /// Number of CDM groups without data.
  /// Number of CDM groups without data.
  unsigned nof_cdm_groups_without_data;
  /// Number of transmission layers.
  /// Number of transmission layers.
  unsigned nof_layers;
  /// Set to true if the transmission overlaps with the Direct Current (DC).
  /// Set to true if the transmission overlaps with the Direct Current (DC).
  bool contains_dc;
};

/// \brief Collects Uplink Shared Channel (UL-SCH) derived parameters.
///
/// The parameters are described in TS38.212 Section 6.3.2.4.1.

/// \brief Collects Uplink Shared Channel (UL-SCH) derived parameters.
///
/// The parameters are described in TS38.212 Section 6.3.2.4.1.
struct ulsch_information {
  /// Shared channel (SCH) parameters.
  /// Shared channel (SCH) parameters.
  std::optional<sch_information> sch;
  /// Number of encoded and rate-matched UL-SCH data bits. Parameter \f$G^\textup{UL-SCH}\f$.
  /// Number of encoded and rate-matched UL-SCH data bits. Parameter \f$G^\textup{UL-SCH}\f$.
  units::bits nof_ul_sch_bits;
  /// Number of encoded and rate-matched HARQ-ACK data bits. Parameter \f$G^\textup{HARQ-ACK}\f$.
  /// Number of encoded and rate-matched HARQ-ACK data bits. Parameter \f$G^\textup{HARQ-ACK}\f$.
  units::bits nof_harq_ack_bits;
  /// Number of reserved bits for HARQ-ACK. Parameter \f$G^\textup{HARQ-ACK}_\textup{rvd}\f$.
  /// Number of reserved bits for HARQ-ACK. Parameter \f$G^\textup{HARQ-ACK}_\textup{rvd}\f$.
  units::bits nof_harq_ack_rvd;
  /// Number of encoded and rate-matched CSI Part 1 data bits. Parameter \f$G^\textup{CSI-part1}\f$.
  /// Number of encoded and rate-matched CSI Part 1 data bits. Parameter \f$G^\textup{CSI-part1}\f$.
  units::bits nof_csi_part1_bits;
  /// Number of encoded and rate-matched CSI Part 2 data bits. Parameter \f$G^\textup{CSI-part2}\f$.
  /// Number of encoded and rate-matched CSI Part 2 data bits. Parameter \f$G^\textup{CSI-part2}\f$.
  units::bits nof_csi_part2_bits;
  /// Number of resource elements occupied by HARQ-ACK information. Parameter \f$Q'_\textup{ACK}\f$.
  /// Number of resource elements occupied by HARQ-ACK information. Parameter \f$Q'_\textup{ACK}\f$.
  unsigned nof_harq_ack_re;
  /// Number of resource elements occupied by CSI Part 1 information. Parameter \f$Q'_\textup{CSI-1}\f$.
  /// Number of resource elements occupied by CSI Part 1 information. Parameter \f$Q'_\textup{CSI-1}\f$.
  unsigned nof_csi_part1_re;
  /// Number of resource elements occupied by CSI Part 1 information. Parameter \f$Q'_\textup{CSI-2}\f$.
  /// Number of resource elements occupied by CSI Part 1 information. Parameter \f$Q'_\textup{CSI-2}\f$.
  unsigned nof_csi_part2_re;
  /// Number of bits that are affected by overlapping with the direct current.
  /// Number of bits that are affected by overlapping with the direct current.
  units::bits nof_dc_overlap_bits;

  /// \brief Calculates the effective code rate normalized between 0 and 1.
  ///
  /// The effective code rate is determined as the quotient of the number of information bits plus CRCs and the total
  /// number of channel bits.
  ///
  /// An assertion is triggered if:
  /// - UL-SCH is not present;
  /// - the resultant codeblock size is not greater than the number of filler bits; or
  /// - the number of rate matched bits for HARQ-ACK feedback is not smaller than the number of rate matched UL-SCH
  /// bits.

  /// \brief Calculates the effective code rate normalized between 0 and 1.
  ///
  /// The effective code rate is determined as the quotient of the number of information bits plus CRCs and the total
  /// number of channel bits.
  ///
  /// An assertion is triggered if:
  /// - UL-SCH is not present;
  /// - the resultant codeblock size is not greater than the number of filler bits; or
  /// - the number of rate matched bits for HARQ-ACK feedback is not smaller than the number of rate matched UL-SCH
  /// bits.
  float get_effective_code_rate() const
  {
    using namespace units::literals;

    // Ensure UL-SCH is present and the number of bits per CB is greater than filler bits.

    // Ensure UL-SCH is present and the number of bits per CB is greater than filler bits.
    ocudu_assert(sch.has_value(), "SCH information is not present.");
    ocudu_assert(sch.value().nof_bits_per_cb.value() > sch.value().nof_filler_bits_per_cb.value(),
                 "The number of bits per CB must be greater than the number of filler bits.");

    // Return 0 if no UL-SCH bits are present.

    // Return 0 if no UL-SCH bits are present.
    if (nof_ul_sch_bits.value() == 0) {
      return 0;
    }

    // Select the number of effective rate matched bits carrying UL-SCH.

    // Select the number of effective rate matched bits carrying UL-SCH.
    unsigned effective_ul_sch_bits = nof_ul_sch_bits.value();

    // Adjust the effective rate matched UL-SCH bits considering HARQ-ACK feedback bits.

    // Adjust the effective rate matched UL-SCH bits considering HARQ-ACK feedback bits.
    if (nof_harq_ack_rvd > 0_bits) {
      // Ensure the subtraction of HARQ-ACK bits does not result in zero or negative.
      // Ensure the subtraction of HARQ-ACK bits does not result in zero or negative.
      ocudu_assert(nof_ul_sch_bits > nof_harq_ack_bits,
                   "UL-SCH rate match length ({} bits) must be greater than the HARQ-ACK rate match length ({} bits).",
                   nof_ul_sch_bits,
                   nof_harq_ack_bits);


      effective_ul_sch_bits -= nof_harq_ack_bits.value();
    }

    // Adjust the effective rate matched UL-SCH bits considering the bits overlapped with the DC position.

    // Adjust the effective rate matched UL-SCH bits considering the bits overlapped with the DC position.
    if (nof_dc_overlap_bits > 0_bits) {
      // Ensure the subtraction of overlapped DC bits does not result in zero or a negative value.
      // Ensure the subtraction of overlapped DC bits does not result in zero or a negative value.
      ocudu_assert(effective_ul_sch_bits > nof_dc_overlap_bits.value(),
                   "UL-SCH rate match length bits (i.e. {}) must be greater than the bits overlapped with DC position "
                   "(i.e. {}).",
                   effective_ul_sch_bits,
                   nof_dc_overlap_bits);


      effective_ul_sch_bits -= nof_dc_overlap_bits.value();
    }

    // Calculate the exact number of bits to encode, including payload, transport block CRC, and codeblock CRC.

    // Calculate the exact number of bits to encode, including payload, transport block CRC, and codeblock CRC.
    unsigned nof_effective_payload_bits =
        (sch.value().nof_bits_per_cb.value() - sch.value().nof_filler_bits_per_cb.value()) * sch.value().nof_cb;

    // Calculate the effective code rate as the quotient of the effective payload bits to effective rate matched bits.

    // Calculate the effective code rate as the quotient of the effective payload bits to effective rate matched bits.
    return static_cast<float>(nof_effective_payload_bits) / static_cast<float>(effective_ul_sch_bits);
  }
};

/// Gets the UL-SCH information for a given PUSCH configuration.

/// Gets the UL-SCH information for a given PUSCH configuration.
ulsch_information get_ulsch_information(const ulsch_configuration& config);


} // namespace ocudu
