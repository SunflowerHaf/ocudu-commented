// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gtpu/gtpu_demux_factory.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/gtpu
// GTP-U interface headers: the gtpu_demux (routes incoming GTP-U packets to the right tunnel endpoint), gtpu_tunnel_rx_upper_layer_notifier and tx_lower_layer interfaces, and the TEID pool. These define how the GTP-U layer interacts with SDAP/PDCP above and UDP sockets below.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gtpu/gtpu_demux.h"
#include "ocudu/gtpu/gtpu_teid_pool.h"
#include "ocudu/pcap/dlt_pcap.h"
#include "ocudu/support/executors/task_executor.h"
#include <memory>


namespace ocudu {


struct gtpu_demux_creation_request {
  gtpu_demux_cfg_t               cfg                 = {};
  gtpu_teid_lingering_interface* teid_linger_checker = nullptr;
  dlt_pcap*                      gtpu_pcap           = nullptr;
};

/// Creates an instance of an GTP-U demux object.

/// Creates an instance of an GTP-U demux object.
std::unique_ptr<gtpu_demux> create_gtpu_demux(const gtpu_demux_creation_request& msg);


} // namespace ocudu
