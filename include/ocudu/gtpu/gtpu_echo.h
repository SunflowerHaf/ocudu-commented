// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gtpu/gtpu_echo.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/gtpu
// GTP-U interface headers: the gtpu_demux (routes incoming GTP-U packets to the right tunnel endpoint), gtpu_tunnel_rx_upper_layer_notifier and tx_lower_layer interfaces, and the TEID pool. These define how the GTP-U layer interacts with SDAP/PDCP above and UDP sockets below.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gtpu/gtpu_tunnel_common_rx.h"


namespace ocudu {

/// Class used to interface with an GTP-U path management entity.
/// It will contain getters for the RX entities interfaces.
/// TX and RX is considered from the perspective of the GTP-U.

/// Class used to interface with an GTP-U path management entity.
/// It will contain getters for the RX entities interfaces.
/// TX and RX is considered from the perspective of the GTP-U.
class gtpu_echo
{
public:
  gtpu_echo()                            = default;
  virtual ~gtpu_echo()                   = default;
  gtpu_echo(const gtpu_echo&)            = delete;
  gtpu_echo& operator=(const gtpu_echo&) = delete;
  gtpu_echo(gtpu_echo&&)                 = delete;
  gtpu_echo& operator=(gtpu_echo&&)      = delete;


  virtual gtpu_tunnel_common_rx_upper_layer_interface* get_rx_upper_layer_interface() = 0;
};


} // namespace ocudu
