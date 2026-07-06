// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_low/o_du_low_metrics_collector_impl.cpp  (20 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "o_du_low_metrics_collector_impl.h"
#include "ocudu/du/du_low/du_low_metrics_collector.h"
#include "ocudu/du/du_low/o_du_low_metrics.h"


using namespace ocudu;
using namespace odu;


void o_du_low_metrics_collector_impl::collect_metrics(o_du_low_metrics& metrics)
{
  if (collector == nullptr) {
    return;
  }

  // Collect DU low metrics.

  // Collect DU low metrics.
  collector->collect_metrics(metrics.du_lo_metrics);
}
