// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pucch/pucch_demodulator.h  (137 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/upper/channel_estimation.h"
#include "ocudu/phy/upper/log_likelihood_ratio.h"


namespace ocudu {


class resource_grid_reader;

/// PUCCH demodulator interface for Formats 2, 3 and 4.

/// PUCCH demodulator interface for Formats 2, 3 and 4.
class pucch_demodulator
{
public:
  /// Collects PUCCH Format 2 demodulation parameters.
  /// Collects PUCCH Format 2 demodulation parameters.
  struct format2_configuration {
    /// Port indices used for the PUCCH reception.
    /// Port indices used for the PUCCH reception.
    static_vector<uint8_t, MAX_PORTS> rx_ports;
    /// Lowest PRB index used for the PUCCH transmission within the resource grid {0, ..., 274}.
    /// Lowest PRB index used for the PUCCH transmission within the resource grid {0, ..., 274}.
    unsigned first_prb;
    /// \brief Index of the first PRB after frequency hopping as per TS38.213 Section 9.2.1.
    ///
    /// Lowest PRB index used for the PUCCH transmission within the BWP {0, ..., 274} if intra-slot frequency hopping is
    /// enabled, empty otherwise.
    /// \brief Index of the first PRB after frequency hopping as per TS38.213 Section 9.2.1.
    ///
    /// Lowest PRB index used for the PUCCH transmission within the BWP {0, ..., 274} if intra-slot frequency hopping is
    /// enabled, empty otherwise.
    std::optional<unsigned> second_hop_prb;
    /// Number of PRB allocated to PUCCH Format 2 {1, ..., 16}.
    /// Number of PRB allocated to PUCCH Format 2 {1, ..., 16}.
    unsigned nof_prb;
    /// Start symbol index within the slot {0, ..., 13}.
    /// Start symbol index within the slot {0, ..., 13}.
    unsigned start_symbol_index;
    /// Number of symbols for the PUCCH transmission {1, 2}.
    /// Number of symbols for the PUCCH transmission {1, 2}.
    unsigned nof_symbols;
    /// Radio Network Temporary Identifier, see parameter \f$n_{RNTI}\f$ in TS38.211 Section 6.3.2.5.1.
    /// Radio Network Temporary Identifier, see parameter \f$n_{RNTI}\f$ in TS38.211 Section 6.3.2.5.1.
    uint16_t rnti;
    /// Scrambling identifier, see parameter \f$n_{ID}\f$ in TS38.211 Section 6.3.2.5.1. Range is {0, ..., 1023}.
    /// Scrambling identifier, see parameter \f$n_{ID}\f$ in TS38.211 Section 6.3.2.5.1. Range is {0, ..., 1023}.
    unsigned n_id;
  };

  /// Collects PUCCH Format 3 demodulation parameters.

  /// Collects PUCCH Format 3 demodulation parameters.
  struct format3_configuration {
    /// Port indices used for the PUCCH reception.
    /// Port indices used for the PUCCH reception.
    static_vector<uint8_t, MAX_PORTS> rx_ports;
    /// Lowest PRB index used for the PUCCH transmission within the resource grid {0, ..., 274}.
    /// Lowest PRB index used for the PUCCH transmission within the resource grid {0, ..., 274}.
    unsigned first_prb;
    /// \brief Index of the first PRB after frequency hopping as per TS38.213 Section 9.2.1.
    ///
    /// Lowest PRB index used for the PUCCH transmission within the BWP {0, ..., 274} if intra-slot frequency hopping is
    /// enabled, empty otherwise.
    /// \brief Index of the first PRB after frequency hopping as per TS38.213 Section 9.2.1.
    ///
    /// Lowest PRB index used for the PUCCH transmission within the BWP {0, ..., 274} if intra-slot frequency hopping is
    /// enabled, empty otherwise.
    std::optional<unsigned> second_hop_prb;
    /// Number of PRB allocated to PUCCH Format 3 {1, ..., 16}.
    /// Number of PRB allocated to PUCCH Format 3 {1, ..., 16}.
    unsigned nof_prb;
    /// Start symbol index within the slot {0, ..., 13}.
    /// Start symbol index within the slot {0, ..., 13}.
    unsigned start_symbol_index;
    /// Number of symbols for the PUCCH transmission {4, ..., 14}.
    /// Number of symbols for the PUCCH transmission {4, ..., 14}.
    unsigned nof_symbols;
    /// Radio Network Temporary Identifier, see parameter \f$n_{RNTI}\f$ in TS38.211 Section 6.3.2.5.1.
    /// Radio Network Temporary Identifier, see parameter \f$n_{RNTI}\f$ in TS38.211 Section 6.3.2.5.1.
    uint16_t rnti;
    /// Scrambling identifier, see parameter \f$n_{ID}\f$ in TS38.211 Section 6.3.2.5.1. Range is {0, ..., 1023}.
    /// Scrambling identifier, see parameter \f$n_{ID}\f$ in TS38.211 Section 6.3.2.5.1. Range is {0, ..., 1023}.
    unsigned n_id;
    /// Set to higher layer parameter \e additionalDMRS described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    /// Set to higher layer parameter \e additionalDMRS described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    bool additional_dmrs;
    /// Set to higher layer parameter \e pi2BPSK described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    /// Set to higher layer parameter \e pi2BPSK described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    bool pi2_bpsk;
  };

  /// Collects PUCCH Format 4 demodulation parameters.

  /// Collects PUCCH Format 4 demodulation parameters.
  struct format4_configuration {
    /// Port indices used for the PUCCH reception.
    /// Port indices used for the PUCCH reception.
    static_vector<uint8_t, MAX_PORTS> rx_ports;
    /// Lowest PRB index used for the PUCCH transmission within the resource grid {0, ..., 274}.
    /// Lowest PRB index used for the PUCCH transmission within the resource grid {0, ..., 274}.
    unsigned first_prb;
    /// \brief Index of the first PRB after frequency hopping as per TS38.213 Section 9.2.1.
    ///
    /// Lowest PRB index used for the PUCCH transmission within the BWP {0, ..., 274} if intra-slot frequency hopping is
    /// enabled, empty otherwise.
    /// \brief Index of the first PRB after frequency hopping as per TS38.213 Section 9.2.1.
    ///
    /// Lowest PRB index used for the PUCCH transmission within the BWP {0, ..., 274} if intra-slot frequency hopping is
    /// enabled, empty otherwise.
    std::optional<unsigned> second_hop_prb;
    /// Start symbol index within the slot {0, ..., 13}.
    /// Start symbol index within the slot {0, ..., 13}.
    unsigned start_symbol_index;
    /// Number of symbols for the PUCCH transmission {4, ..., 14}.
    /// Number of symbols for the PUCCH transmission {4, ..., 14}.
    unsigned nof_symbols;
    /// Radio Network Temporary Identifier, see parameter \f$n_{RNTI}\f$ in TS38.211 Section 6.3.2.5.1.
    /// Radio Network Temporary Identifier, see parameter \f$n_{RNTI}\f$ in TS38.211 Section 6.3.2.5.1.
    uint16_t rnti;
    /// Scrambling identifier, see parameter \f$n_{ID}\f$ in TS38.211 Section 6.3.2.5.1. Range is {0, ..., 1023}.
    /// Scrambling identifier, see parameter \f$n_{ID}\f$ in TS38.211 Section 6.3.2.5.1. Range is {0, ..., 1023}.
    unsigned n_id;
    /// Set to higher layer parameter \e additionalDMRS described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    /// Set to higher layer parameter \e additionalDMRS described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    bool additional_dmrs;
    /// Set to higher layer parameter \e pi2BPSK described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    /// Set to higher layer parameter \e pi2BPSK described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-FormatConfig.
    bool pi2_bpsk;
    /// Set to higher layer parameter \e occ-Length described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-format4.
    /// Set to higher layer parameter \e occ-Length described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-format4.
    unsigned occ_length;
    /// Set to higher layer parameter \e occ-Index described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-format4.
    /// Set to higher layer parameter \e occ-Index described in TS38.331 Section 6.3.2, Information Element \e
    /// PUCCH-format4.
    unsigned occ_index;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~pucch_demodulator() = default;

  /// \brief Demodulates a PUCCH Format 2 transmission.
  /// \param[out] llr       Destination PUCCH soft-bit buffer.
  /// \param[in]  grid      Input resource grid.
  /// \param[in]  estimates Channel estimates.
  /// \param[in]  config    PUCCH Format 2 configuration parameters.

  /// \brief Demodulates a PUCCH Format 2 transmission.
  /// \param[out] llr       Destination PUCCH soft-bit buffer.
  /// \param[in]  grid      Input resource grid.
  /// \param[in]  estimates Channel estimates.
  /// \param[in]  config    PUCCH Format 2 configuration parameters.
  virtual void demodulate(span<log_likelihood_ratio>   llr,
                          const resource_grid_reader&  grid,
                          const channel_estimate&      estimates,
                          const format2_configuration& config) = 0;

  /// \brief Demodulates a PUCCH Format 3 transmission.
  /// \param[out] llr       Destination PUCCH soft-bit buffer.
  /// \param[in]  grid      Input resource grid.
  /// \param[in]  estimates Channel estimates.
  /// \param[in]  config    PUCCH Format 3 configuration parameters.

  /// \brief Demodulates a PUCCH Format 3 transmission.
  /// \param[out] llr       Destination PUCCH soft-bit buffer.
  /// \param[in]  grid      Input resource grid.
  /// \param[in]  estimates Channel estimates.
  /// \param[in]  config    PUCCH Format 3 configuration parameters.
  virtual void demodulate(span<log_likelihood_ratio>   llr,
                          const resource_grid_reader&  grid,
                          const channel_estimate&      estimates,
                          const format3_configuration& config) = 0;

  /// \brief Demodulates a PUCCH Format 4 transmission.
  /// \param[out] llr       Destination PUCCH soft-bit buffer.
  /// \param[in]  grid      Input resource grid.
  /// \param[in]  estimates Channel estimates.
  /// \param[in]  config    PUCCH Format 4 configuration parameters.

  /// \brief Demodulates a PUCCH Format 4 transmission.
  /// \param[out] llr       Destination PUCCH soft-bit buffer.
  /// \param[in]  grid      Input resource grid.
  /// \param[in]  estimates Channel estimates.
  /// \param[in]  config    PUCCH Format 4 configuration parameters.
  virtual void demodulate(span<log_likelihood_ratio>   llr,
                          const resource_grid_reader&  grid,
                          const channel_estimate&      estimates,
                          const format4_configuration& config) = 0;
};


} // namespace ocudu
