// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1u/du/f1u_rx_sdu_notifier.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/f1u
// F1-U interface headers: the DU-side and CU-UP-side F1-U gateway abstractions, the f1u_du_gateway and f1u_cu_up_gateway interfaces, and the TEID (tunnel endpoint) pool interface used to allocate unique tunnel identifiers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"


namespace ocudu {
namespace odu {

/// \brief This interface represents the data exit point of the receiving side of a F1-U bearer of the DU.
/// The F1-U will push NR-U SDUs (e.g. PDCP PDUs/RLC SDUs) to the lower layer (e.g. RLC) using this interface.
/// The F1-U will also inform the lower layer (e.g. RLC) of SDUs (e.g. PDCP PDUs) to be discarded.

/// \brief This interface represents the data exit point of the receiving side of a F1-U bearer of the DU.
/// The F1-U will push NR-U SDUs (e.g. PDCP PDUs/RLC SDUs) to the lower layer (e.g. RLC) using this interface.
/// The F1-U will also inform the lower layer (e.g. RLC) of SDUs (e.g. PDCP PDUs) to be discarded.
class f1u_rx_sdu_notifier
{
public:
  virtual ~f1u_rx_sdu_notifier() = default;


  virtual void on_new_sdu(byte_buffer sdu, bool is_retx) = 0;
  virtual void on_discard_sdu(uint32_t pdcp_sn)          = 0;
};


} // namespace odu
} // namespace ocudu
