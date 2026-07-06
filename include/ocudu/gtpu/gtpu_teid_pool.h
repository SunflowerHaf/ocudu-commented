// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gtpu/gtpu_teid_pool.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/gtpu
// GTP-U interface headers: the gtpu_demux (routes incoming GTP-U packets to the right tunnel endpoint), gtpu_tunnel_rx_upper_layer_notifier and tx_lower_layer interfaces, and the TEID pool. These define how the GTP-U layer interacts with SDAP/PDCP above and UDP sockets below.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/ran/gtpu/gtpu_teid.h"
#include "ocudu/support/compiler.h"


namespace ocudu {

/// \brief GTP-U TEID lingering interface.
///
/// This interface is used to check whether an unknown (non-allocated) TEID is still lingering after recent release.
/// When removing a GTP-U tunnel and releasing the TEID, several in-flight PDUs may arrive during/after the procedure
/// for which no GTP-U error indication shall be triggered.

/// \brief GTP-U TEID lingering interface.
///
/// This interface is used to check whether an unknown (non-allocated) TEID is still lingering after recent release.
/// When removing a GTP-U tunnel and releasing the TEID, several in-flight PDUs may arrive during/after the procedure
/// for which no GTP-U error indication shall be triggered.
class gtpu_teid_lingering_interface
{
public:
  virtual ~gtpu_teid_lingering_interface() = default;


  virtual bool is_teid_lingering(gtpu_teid_t teid) = 0;
};

/// \brief GTP-U TEID pool
///
/// This class provides a TEID pool that users can request unused TEIDs.
/// This allows the CU-UP/DU to allocate unused local TEIDs safely even
/// in the event of TEID wrap-around.

/// \brief GTP-U TEID pool
///
/// This class provides a TEID pool that users can request unused TEIDs.
/// This allows the CU-UP/DU to allocate unused local TEIDs safely even
/// in the event of TEID wrap-around.
class gtpu_teid_pool : public gtpu_teid_lingering_interface
{
public:
  virtual ~gtpu_teid_pool() = default;


  [[nodiscard]] virtual expected<gtpu_teid_t> request_teid() = 0;


  [[nodiscard]] virtual bool release_teid(gtpu_teid_t teid) = 0;


  [[nodiscard]] virtual bool full() = 0;


  virtual uint32_t get_max_nof_teids() = 0;
};
} // namespace ocudu
