// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_controller_impl.h  (52 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ru/ru_controller.h"
#include <memory>


namespace ocudu {

/// \brief RU controller implementation for the Open Fronthaul interface.
///
/// Manages the timing controller that is common to all sectors and the individual controller of each sector.

/// \brief RU controller implementation for the Open Fronthaul interface.
///
/// Manages the timing controller that is common to all sectors and the individual controller of each sector.
class ru_ofh_controller_impl : public ru_controller, public ru_operation_controller
{
public:
  ru_ofh_controller_impl(ocudulog::basic_logger& logger_) : logger(logger_) {}

  // See the ru_operation_controller interface for documentation.

  // See the ru_operation_controller interface for documentation.
  void start() override;

  // See the ru_operation_controller interface for documentation.

  // See the ru_operation_controller interface for documentation.
  void stop() override;

  // See the ru_controller interface for documentation.

  // See the ru_controller interface for documentation.
  ru_operation_controller& get_operation_controller() override { return *this; }

  // See the ru_controller interface for documentation.

  // See the ru_controller interface for documentation.
  ru_gain_controller* get_gain_controller() override { return nullptr; }

  // See the ru_controller interface for documentation.

  // See the ru_controller interface for documentation.
  ru_cfo_controller* get_cfo_controller() override { return nullptr; }

  // See the ru_controller interface for documentation.

  // See the ru_controller interface for documentation.
  ru_center_frequency_controller* get_center_frequency_controller() override { return nullptr; }

  // See the ru_controller interface for documentation.

  // See the ru_controller interface for documentation.
  ru_tx_time_offset_controller* get_tx_time_offset_controller() override { return nullptr; }

  /// Sets the sectors controllers.

  /// Sets the sectors controllers.
  void set_sector_controllers(std::vector<ofh::operation_controller*> controllers);


private:
  ocudulog::basic_logger&                 logger;
  std::vector<ofh::operation_controller*> sector_controllers;
};


} // namespace ocudu
