// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gtpu/gtpu_tunnel_ngu.h  (30 lines)
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
#include "ocudu/gtpu/gtpu_tunnel_ngu_tx.h"


namespace ocudu {

/// Class used to interface with an GTP-U tunnel.
/// It will contain getters for the TX and RX entities interfaces.
/// TX and RX is considered from the perspective of the GTP-U.

/// Class used to interface with an GTP-U tunnel.
/// It will contain getters for the TX and RX entities interfaces.
/// TX and RX is considered from the perspective of the GTP-U.
class gtpu_tunnel_ngu
{
public:
  gtpu_tunnel_ngu()                                  = default;
  virtual ~gtpu_tunnel_ngu()                         = default;
  gtpu_tunnel_ngu(const gtpu_tunnel_ngu&)            = delete;
  gtpu_tunnel_ngu& operator=(const gtpu_tunnel_ngu&) = delete;
  gtpu_tunnel_ngu(gtpu_tunnel_ngu&&)                 = delete;
  gtpu_tunnel_ngu& operator=(gtpu_tunnel_ngu&&)      = delete;


  virtual void                                         stop()                         = 0;
  virtual gtpu_tunnel_common_rx_upper_layer_interface* get_rx_upper_layer_interface() = 0;
  virtual gtpu_tunnel_ngu_tx_lower_layer_interface*    get_tx_lower_layer_interface() = 0;
};


} // namespace ocudu
