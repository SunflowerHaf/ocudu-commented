// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/mac/mac_ctrl/mac_scheduler_configurator.h  (60 lines)
//
// LIBRARY: lib/mac
// Medium Access Control (MAC, TS 38.321): scheduler interface adaptor, HARQ process management, multiplexing/demultiplexing of logical channels into transport blocks, random-access (RACH) handling, and timing-advance control. Interfaces: MAC SDU to/from RLC, MAC PDU to/from the lower PHY via FAPI.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/mac_ue_configurator.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {


struct mac_cell_creation_request;
class scheduler_cell_metrics_notifier;


struct mac_scheduler_cell_creation_request {
  const mac_cell_creation_request& cell_params;
  scheduler_cell_metrics_notifier* metric_notifier;
  /// Whether per-UE scheduler metrics should be reported.
  /// Whether per-UE scheduler metrics should be reported.
  bool report_ue_metrics = true;
};

/// \brief Adapter interface between MAC and scheduler that allows the OCUDU gNB MAC to configure different scheduler
/// implementations.
/// Note: This adapter interface makes scheduler configuration methods awaitable.

/// \brief Adapter interface between MAC and scheduler that allows the OCUDU gNB MAC to configure different scheduler
/// implementations.
/// Note: This adapter interface makes scheduler configuration methods awaitable.
class mac_scheduler_configurator
{
public:
  virtual ~mac_scheduler_configurator() = default;

  /// \brief Adds a new cell configuration to the scheduler and activates it.
  ///
  /// \param msg New cell configuration.

  /// \brief Adds a new cell configuration to the scheduler and activates it.
  ///
  /// \param msg New cell configuration.
  virtual void add_cell(const mac_scheduler_cell_creation_request& msg) = 0;

  /// \brief Removes an existing cell from the scheduler.
  ///
  /// \param cell_index DU-specific index of the cell to remove.

  /// \brief Removes an existing cell from the scheduler.
  ///
  /// \param cell_index DU-specific index of the cell to remove.
  virtual void remove_cell(du_cell_index_t cell_index) = 0;

  /// \brief Adds a new UE configuration to the scheduler.
  ///
  /// \param msg new UE configuration.
  /// \return Asynchronous task handle that represents the state and outcome of the UE reconfiguration task.

  /// \brief Adds a new UE configuration to the scheduler.
  ///
  /// \param msg new UE configuration.
  /// \return Asynchronous task handle that represents the state and outcome of the UE reconfiguration task.
  virtual async_task<bool> handle_ue_creation_request(const mac_ue_create_request& msg) = 0;

  /// \brief Reconfigures an existing UE configuration in the scheduler.
  ///
  /// \param msg new configuration for existing UE.
  /// \return Asynchronous task handle that represents the state and outcome of the UE reconfiguration task.

  /// \brief Reconfigures an existing UE configuration in the scheduler.
  ///
  /// \param msg new configuration for existing UE.
  /// \return Asynchronous task handle that represents the state and outcome of the UE reconfiguration task.
  virtual async_task<bool> handle_ue_reconfiguration_request(const mac_ue_reconfiguration_request& msg) = 0;

  /// \brief Removes UE from MAC scheduler in an asynchronous manner.
  /// The scheduler shouldn't allocate more grants directed at the UE being removed after this procedure is complete.

  /// \brief Removes UE from MAC scheduler in an asynchronous manner.
  /// The scheduler shouldn't allocate more grants directed at the UE being removed after this procedure is complete.
  virtual async_task<void> handle_ue_removal_request(const mac_ue_delete_request& msg) = 0;

  /// Handle the confirmation that the UE received and applied the last sent RRC configuration.

  /// Handle the confirmation that the UE received and applied the last sent RRC configuration.
  virtual void handle_ue_config_applied(du_ue_index_t ue_index) = 0;
};


} // namespace ocudu
