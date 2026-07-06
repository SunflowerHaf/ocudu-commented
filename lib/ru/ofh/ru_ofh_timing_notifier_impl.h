// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_timing_notifier_impl.h  (34 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include "ocudu/ru/ru_timing_notifier.h"
#include <chrono>


namespace ocudu {


class ru_timing_notifier;


class ru_ofh_timing_notifier_impl : public ofh::ota_symbol_boundary_notifier
{
public:
  ru_ofh_timing_notifier_impl(unsigned            nof_slot_offset_du_ru_,
                              unsigned            nof_symbols_per_slot,
                              subcarrier_spacing  scs,
                              ru_timing_notifier& timing_notifier_);

  // See interface for documentation.

  // See interface for documentation.
  void on_new_symbol(const ofh::slot_symbol_point_context& symbol_point_context) override;


private:
  const unsigned                 nof_slot_offset_du_ru;
  const std::chrono::nanoseconds nof_slots_offset_du_ru_ns;
  const unsigned                 half_slot_symbol;
  const unsigned                 full_slot_symbol;
  ru_timing_notifier&            timing_notifier;
};


} // namespace ocudu
