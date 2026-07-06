// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_manager.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


class mac_cell_manager;
class mac_ue_configurator;
class mac_positioning_measurement_handler;
class mac_subframe_time_mapper;

/// Interface used by the management plane of the DU.

/// Interface used by the management plane of the DU.
class mac_manager
{
public:
  virtual ~mac_manager() = default;

  /// Interface to manage the creation, reconfiguration, deletion, activation and deactivation of cells.

  /// Interface to manage the creation, reconfiguration, deletion, activation and deactivation of cells.
  virtual mac_cell_manager& get_cell_manager() = 0;

  /// Interface to manage the creation, reconfiguration and deletion of UEs in the MAC.

  /// Interface to manage the creation, reconfiguration and deletion of UEs in the MAC.
  virtual mac_ue_configurator& get_ue_configurator() = 0;

  /// Fetch positioning measurement handler.

  /// Fetch positioning measurement handler.
  virtual mac_positioning_measurement_handler& get_positioning_handler() = 0;

  /// Get the DU-wide subframe-time mapper that aggregates timing from all cells.
  /// This mapper receives slot indications from all cells but only stores
  /// the first indication for each new subframe.

  /// Get the DU-wide subframe-time mapper that aggregates timing from all cells.
  /// This mapper receives slot indications from all cells but only stores
  /// the first indication for each new subframe.
  virtual mac_subframe_time_mapper& get_subframe_time_mapper() = 0;
};


} // namespace ocudu
