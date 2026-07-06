// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1u/cu_up/f1u_tx_pdu_notifier.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/f1u
// F1-U interface headers: the DU-side and CU-UP-side F1-U gateway abstractions, the f1u_du_gateway and f1u_cu_up_gateway interfaces, and the TEID (tunnel endpoint) pool interface used to allocate unique tunnel identifiers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/nru/nru_message.h"


namespace ocudu {
namespace ocuup {

/// \brief This interface represents the NR-U exit point of the F1-U bearer of the CU-UP
/// through which it passes NR-U PDUs to lower layer (e.g. GTP-U) towards the DU.

/// \brief This interface represents the NR-U exit point of the F1-U bearer of the CU-UP
/// through which it passes NR-U PDUs to lower layer (e.g. GTP-U) towards the DU.
class f1u_tx_pdu_notifier
{
public:
  virtual ~f1u_tx_pdu_notifier() = default;


  virtual void on_new_pdu(nru_dl_message msg) = 0;
};


} // namespace ocuup
} // namespace ocudu
