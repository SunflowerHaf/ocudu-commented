// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_high/du_manager/du_f1_setup_notifier.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/ran/gnb_du_id.h"


namespace ocudu {
namespace odu {

/// Notifier invoked once after a successful F1 Setup, delivering the packed F1SetupRequest and
/// F1SetupResponse bytes together with the gNB-DU-ID. Intended for use by out-of-band consumers
/// that need the raw PDU bytes without being coupled to the F1AP or DU-manager internals.

/// Notifier invoked once after a successful F1 Setup, delivering the packed F1SetupRequest and
/// F1SetupResponse bytes together with the gNB-DU-ID. Intended for use by out-of-band consumers
/// that need the raw PDU bytes without being coupled to the F1AP or DU-manager internals.
class du_f1_setup_complete_notifier
{
public:
  virtual ~du_f1_setup_complete_notifier() = default;

  /// \brief Invoked once after a successful F1 Setup exchange.
  /// \param req  Packed F1SetupRequest PDU bytes.
  /// \param resp Packed F1SetupResponse PDU bytes.
  /// \param gnb_du_id gNB-DU identifier.

  /// \brief Invoked once after a successful F1 Setup exchange.
  /// \param req  Packed F1SetupRequest PDU bytes.
  /// \param resp Packed F1SetupResponse PDU bytes.
  /// \param gnb_du_id gNB-DU identifier.
  virtual void on_f1_setup_complete(byte_buffer req, byte_buffer resp, gnb_du_id_t gnb_du_id) = 0;
};


} // namespace odu
} // namespace ocudu
