// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/o_du_impl.cpp  (80 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "o_du_impl.h"
#include "ocudu/du/du_high/o_du_high.h"
#include "ocudu/du/du_low/o_du_low_metrics_collector.h"
#include "ocudu/du/o_du_metrics.h"
#include "ocudu/du/o_du_metrics_notifier.h"
#include "ocudu/fapi_adaptor/mac/mac_fapi_fastpath_adaptor.h"
#include "ocudu/ocudulog/ocudulog.h"


using namespace ocudu;
using namespace odu;


namespace {

/// O-DU metrics notifier dummy implementation.

/// O-DU metrics notifier dummy implementation.
class o_du_metrics_notifier_dummy : public o_du_metrics_notifier
{
public:
  // See interface for documentation.
  // See interface for documentation.
  void on_new_metrics(const o_du_metrics& metrics) override {}
};


} // namespace

/// Dummy O-DU metrics notifier.

/// Dummy O-DU metrics notifier.
static o_du_metrics_notifier_dummy dummy_notifier;


o_du_impl::o_du_impl(o_du_dependencies&& dependencies) :
  metrics_notifier(dependencies.metrics_notifier ? *dependencies.metrics_notifier : dummy_notifier),
  odu_hi(std::move(dependencies.odu_hi)),
  odu_lo(std::move(dependencies.odu_lo))
{
  ocudu_assert(odu_lo, "Invalid DU low");
  ocudu_assert(odu_hi, "Invalid DU high");

  // Register the O-DU in the O-DU high to listen to O-DU high metrics.

  // Register the O-DU in the O-DU high to listen to O-DU high metrics.
  odu_hi->set_o_du_high_metrics_notifier(*this);
}


void o_du_impl::on_new_metrics(const o_du_high_metrics& metrics)
{
  o_du_metrics du_metrics;

  // Get O-DU low metrics.

  // Get O-DU low metrics.
  if (auto* odu_low_collector = odu_lo->get_metrics_collector()) {
    auto& odu_low_metrics = du_metrics.low.emplace();
    odu_low_collector->collect_metrics(odu_low_metrics);
  }

  // Notify the metrics.

  // Notify the metrics.
  metrics_notifier.on_new_metrics(du_metrics);
}


void o_du_impl::start()
{
  odu_hi->get_operation_controller().start();
  odu_lo->get_operation_controller().start();
}


void o_du_impl::stop()
{
  // Stop the MAC-FAPI adaptor first.
  // Stop the MAC-FAPI adaptor first.
  odu_hi->get_mac_fapi_fastpath_adaptor().stop();


  odu_lo->get_operation_controller().stop();
  odu_hi->get_operation_controller().stop();
}


o_du_high& o_du_impl::get_o_du_high()
{
  return *odu_hi;
}


o_du_low& o_du_impl::get_o_du_low()
{
  return *odu_lo;
}
