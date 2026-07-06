// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/uci/uci_decoder.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/phy/upper/channel_processors/uci/uci_status.h"
#include "ocudu/phy/upper/log_likelihood_ratio.h"
#include "ocudu/ran/sch/modulation_scheme.h"


namespace ocudu {

/// \brief Uplink Control Information decoder.
///
/// Decodes UCI payloads containing SR, HARQ-ACK and/or CSI bits, transmitted on PUCCH, reversing the steps described
/// in TS38.212 Sections 6.3.1.2, 6.3.1.3, 6.3.1.4 and 6.3.1.5.
///
/// Decodes UCI payloads of either HARQ-ACK or CSI bits, transmitted on PUSCH, reversing the steps described in
/// TS38.212 Sections 6.3.2.2, 6.3.2.3 and 6.3.2.4.

/// \brief Uplink Control Information decoder.
///
/// Decodes UCI payloads containing SR, HARQ-ACK and/or CSI bits, transmitted on PUCCH, reversing the steps described
/// in TS38.212 Sections 6.3.1.2, 6.3.1.3, 6.3.1.4 and 6.3.1.5.
///
/// Decodes UCI payloads of either HARQ-ACK or CSI bits, transmitted on PUSCH, reversing the steps described in
/// TS38.212 Sections 6.3.2.2, 6.3.2.3 and 6.3.2.4.
class uci_decoder
{
public:
  /// Collects UCI decoder configuration parameters.
  /// Collects UCI decoder configuration parameters.
  struct configuration {
    /// Transmission modulation.
    /// Transmission modulation.
    modulation_scheme modulation;
    // Add here other parameters.
    // ...
    // Add here other parameters.
    // ...
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~uci_decoder() = default;

  /// \brief Decodes Uplink Control Information carried in either PUCCH or PUSCH.
  /// \param[out] message View of the decoded message.
  /// \param[in]  llr     The received soft bits, as a sequence of log-likelihood ratios.
  /// \param[in]  config  The UCI decoder configuration.
  /// \return The decoding status.

  /// \brief Decodes Uplink Control Information carried in either PUCCH or PUSCH.
  /// \param[out] message View of the decoded message.
  /// \param[in]  llr     The received soft bits, as a sequence of log-likelihood ratios.
  /// \param[in]  config  The UCI decoder configuration.
  /// \return The decoding status.
  virtual uci_status
  decode(span<uint8_t> message, span<const log_likelihood_ratio> llr, const configuration& config) = 0;
};


} // namespace ocudu
