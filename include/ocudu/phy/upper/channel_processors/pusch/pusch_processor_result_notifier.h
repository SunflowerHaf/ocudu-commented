// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pusch/pusch_processor_result_notifier.h  (76 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/upper/channel_processors/pusch/pusch_decoder_result.h"
#include "ocudu/phy/upper/channel_processors/uci/uci_status.h"
#include "ocudu/phy/upper/channel_state_information.h"
#include "ocudu/ran/uci/uci_payload_type.h"


namespace ocudu {

/// Collects the results of UCI field decoding.

/// Collects the results of UCI field decoding.
struct pusch_uci_field {
  uci_payload_type payload;
  uci_status       status;

  /// Clears the contents of the field.

  /// Clears the contents of the field.
  void clear()
  {
    payload.resize(0);
    status = uci_status::unknown;
  }
};

/// Groups the PUSCH processor UL-SCH data decode results.

/// Groups the PUSCH processor UL-SCH data decode results.
struct pusch_processor_result_data {
  /// SCH decoding information.
  /// SCH decoding information.
  pusch_decoder_result data;
  /// Channel state information.
  /// Channel state information.
  channel_state_information csi;
};

/// Groups the PUSCH processor UL-SCH control decode results.

/// Groups the PUSCH processor UL-SCH control decode results.
struct pusch_processor_result_control {
  /// \brief Decoded HARQ-ACK information bits.
  /// \remark Leave empty if no HARQ-ACK information bits are multiplexed with the UL-SCH.
  /// \brief Decoded HARQ-ACK information bits.
  /// \remark Leave empty if no HARQ-ACK information bits are multiplexed with the UL-SCH.
  pusch_uci_field harq_ack;
  /// \brief Decoded CSI Part 1 information bits.
  /// \remark Leave empty if no CSI Part 1 information bits are multiplexed with the UL-SCH.
  /// \brief Decoded CSI Part 1 information bits.
  /// \remark Leave empty if no CSI Part 1 information bits are multiplexed with the UL-SCH.
  pusch_uci_field csi_part1;
  /// \brief Decoded CSI Part 2 information bits.
  /// \remark Leave empty if no CSI Part 2 information bits are multiplexed with the UL-SCH.
  /// \brief Decoded CSI Part 2 information bits.
  /// \remark Leave empty if no CSI Part 2 information bits are multiplexed with the UL-SCH.
  pusch_uci_field csi_part2;
  /// Channel state information.
  /// Channel state information.
  channel_state_information csi;
};

/// \brief PUSCH processor result notifier.
///
/// The PUSCH processor uses this interface for notifying results.

/// \brief PUSCH processor result notifier.
///
/// The PUSCH processor uses this interface for notifying results.
class pusch_processor_result_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~pusch_processor_result_notifier() = default;

  /// \brief Notifies the detection of Uplink Control Information (UCI) on PUSCH.
  ///
  /// The UCI result is always notified after on_csi(), if the \ref pusch_processor::uci_description contains any
  /// payload bits. Otherwise, it is not notified.
  ///
  /// \param[in] uci Actual UCI decoding results.

  /// \brief Notifies the detection of Uplink Control Information (UCI) on PUSCH.
  ///
  /// The UCI result is always notified after on_csi(), if the \ref pusch_processor::uci_description contains any
  /// payload bits. Otherwise, it is not notified.
  ///
  /// \param[in] uci Actual UCI decoding results.
  virtual void on_uci(const pusch_processor_result_control& uci) = 0;

  /// \brief Notifies the shared channel decoding.
  ///
  /// The SCH result is always notified after on_csi(), if the \ref pusch_processor::pdu_t::codeword is
  /// available.
  ///
  /// \param[in] sch Actual SCH decoding results.

  /// \brief Notifies the shared channel decoding.
  ///
  /// The SCH result is always notified after on_csi(), if the \ref pusch_processor::pdu_t::codeword is
  /// available.
  ///
  /// \param[in] sch Actual SCH decoding results.
  virtual void on_sch(const pusch_processor_result_data& sch) = 0;
};


} // namespace ocudu
