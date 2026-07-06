// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/sdap/sdap_mapper.h  (20 lines)
//
// INTERFACE HEADER — include/ocudu/sdap
// SDAP interface headers: sdap_rx_pdu (incoming DL PDU from the network) and sdap_tx_sdu (outgoing UL SDU to the network) handler interfaces, the QoS flow mapping interface, and SDAP entity configuration.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

/// DRB to QoS flow mapping.

/// DRB to QoS flow mapping.
class sdap_mapper
{
public:
  virtual ~sdap_mapper() = default;


  virtual bool associate(int mapping_list_number, const void* mapping_list) = 0;


  virtual bool drb_release(int drb) = 0;
};


} // namespace ocudu
