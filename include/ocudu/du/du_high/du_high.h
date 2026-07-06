// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_high/du_high.h  (62 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/f1ap/du/f1ap_du.h"
#include "ocudu/mac/mac_cell_control_information_handler.h"
#include "ocudu/mac/mac_cell_rach_handler.h"
#include "ocudu/mac/mac_cell_slot_handler.h"
#include "ocudu/mac/mac_pdu_handler.h"
#include "ocudu/mac/mac_subframe_time_mapper.h"
#include "ocudu/ran/du_types.h"


namespace ocudu {
namespace odu {


class du_configurator;

/// Interface to DU-high class, which owns and manages the interaction between MAC, RLC and F1 layers.

/// Interface to DU-high class, which owns and manages the interaction between MAC, RLC and F1 layers.
class du_high
{
public:
  virtual ~du_high() = default;

  /// Starts this DU, setting it in operational mode. If the DU was already in operational mode, it does nothing.

  /// Starts this DU, setting it in operational mode. If the DU was already in operational mode, it does nothing.
  virtual void start() = 0;

  /// Stops this DU operation.

  /// Stops this DU operation.
  virtual void stop() = 0;

  /// Get handler to received F1AP PDUs.

  /// Get handler to received F1AP PDUs.
  virtual f1ap_message_handler& get_f1ap_pdu_handler() = 0;

  /// Get handler to F1AP ID translator.

  /// Get handler to F1AP ID translator.
  virtual f1ap_ue_id_translator& get_f1ap_ue_id_translator() = 0;

  /// \brief Returns handler of slot indications for a cell with provided cell_index.
  /// \param cell_index Index of cell currently activated in the DU.

  /// \brief Returns handler of slot indications for a cell with provided cell_index.
  /// \param cell_index Index of cell currently activated in the DU.
  virtual mac_cell_slot_handler& get_slot_handler(du_cell_index_t cell_index) = 0;

  /// \brief Returns handler of PRACHs for a given cell.
  /// \param cell_index Index of cell currently activated in the DU.

  /// \brief Returns handler of PRACHs for a given cell.
  /// \param cell_index Index of cell currently activated in the DU.
  virtual mac_cell_rach_handler& get_rach_handler(du_cell_index_t cell_index) = 0;

  /// \brief Returns handler for UL and DL control information for a given cell.
  /// \param cell_index Index of cell currently activated in the DU.

  /// \brief Returns handler for UL and DL control information for a given cell.
  /// \param cell_index Index of cell currently activated in the DU.
  virtual mac_cell_control_information_handler& get_control_info_handler(du_cell_index_t cell_index) = 0;

  /// \brief Returns MAC Rx PDU handler.
  /// The lower layers will use this interface to forward decoded UL PDUs to the MAC.

  /// \brief Returns MAC Rx PDU handler.
  /// The lower layers will use this interface to forward decoded UL PDUs to the MAC.
  virtual mac_pdu_handler& get_pdu_handler() = 0;

  /// Returns handler to configure the operational serving cells and UEs attached to this DU.

  /// Returns handler to configure the operational serving cells and UEs attached to this DU.
  virtual du_configurator& get_du_configurator() = 0;

  /// Returns a mapper of slots to system time.

  /// Returns a mapper of slots to system time.
  virtual mac_subframe_time_mapper& get_subframe_time_mapper() = 0;
};


} // namespace odu
} // namespace ocudu
