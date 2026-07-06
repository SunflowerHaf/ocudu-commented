// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_low/o_du_low_metrics_collector_impl.h  (30 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/du/du_low/o_du_low_metrics_collector.h"


namespace ocudu {
namespace odu {


class du_low_metrics_collector;

/// O-DU low metrics collector implementation.

/// O-DU low metrics collector implementation.
class o_du_low_metrics_collector_impl : public o_du_low_metrics_collector
{
  du_low_metrics_collector* collector = nullptr;


public:
  explicit o_du_low_metrics_collector_impl(du_low_metrics_collector* collector_) : collector(collector_) {}

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(o_du_low_metrics& metrics) override;

  /// Returns true if the metrics are enabled, otherwise false.

  /// Returns true if the metrics are enabled, otherwise false.
  bool enabled() const { return collector != nullptr; }
};


} // namespace odu
} // namespace ocudu
