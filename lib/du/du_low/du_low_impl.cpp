// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_low/du_low_impl.cpp  (41 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "du_low_impl.h"
#include "ocudu/adt/span.h"
#include "ocudu/support/ocudu_assert.h"


using namespace ocudu;
using namespace odu;


du_low_impl::du_low_impl(std::vector<std::unique_ptr<upper_phy>> upper_) : upper(std::move(upper_))
{
  ocudu_assert(!upper.empty(), "Invalid upper PHY");
  // All the upper PHYs share the same metrics collector. Use the first one to configure the DU low metrics collector.
  // All the upper PHYs share the same metrics collector. Use the first one to configure the DU low metrics collector.
  metrics_collector = du_low_metrics_collector_impl(upper.front()->get_metrics_collector());
}


upper_phy& du_low_impl::get_upper_phy(unsigned cell_id)
{
  ocudu_assert(cell_id < upper.size(), "Invalid cell index '{}'. Valid cell indexes [0-{})", cell_id, upper.size());


  return *upper[cell_id];
}


odu::du_low_metrics_collector* du_low_impl::get_metrics_collector()
{
  return metrics_collector.enabled() ? &metrics_collector : nullptr;
}


void du_low_impl::start()
{
  // Nothing to do as the Upper PHY is stateless.
  // Nothing to do as the Upper PHY is stateless.
}


void du_low_impl::stop()
{
  for (auto& cell : upper) {
    cell->stop();
  }
}
