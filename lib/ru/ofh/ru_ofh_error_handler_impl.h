// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_error_handler_impl.h  (31 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ofh/ofh_error_notifier.h"
#include "ocudu/ru/ru_error_notifier.h"


namespace ocudu {

/// Radio Unit error handler for the Open Fronthaul interface.

/// Radio Unit error handler for the Open Fronthaul interface.
class ru_ofh_error_handler_impl : public ofh::error_notifier
{
public:
  explicit ru_ofh_error_handler_impl(ru_error_notifier& notifier_) : error_notifier(notifier_) {}

  // See interface for documentation.

  // See interface for documentation.
  void on_late_downlink_message(const ofh::error_context& context) override;

  // See interface for documentation.

  // See interface for documentation.
  void on_late_uplink_message(const ofh::error_context& context) override;

  // See interface for documentation.

  // See interface for documentation.
  void on_late_prach_message(const ofh::error_context& context) override;


private:
  ru_error_notifier& error_notifier;
};


} // namespace ocudu
