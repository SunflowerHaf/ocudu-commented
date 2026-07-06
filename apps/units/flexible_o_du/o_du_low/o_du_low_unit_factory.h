// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_low_unit_factory.h
//
// Purpose (plain English):
//   Public interface for building an O-DU Low unit. The O-DU Low is the
//   upper physical layer — the bit that turns MAC transport blocks into a
//   frequency-domain resource grid (and vice versa on the uplink).
//
//   Declares two things:
//     * o_du_low_unit — the returned struct: owns the running O-DU Low
//       object plus its metric configs.
//     * o_du_low_unit_factory — a small factory class that captures the
//       optional HAL (hardware-accelerator) dependencies at construction
//       time (so the accelerator is initialised only once even if multiple
//       DU-Lows are created), then hands out ready-to-use O-DU Low units
//       via its create() method.
// =============================================================================

#pragma once


#include "apps/services/metrics/metrics_config.h"
#include "o_du_low_unit_factory_config.h"
#include "ocudu/du/du_low/o_du_low.h"


namespace ocudu {

/// O-RAN DU low unit.

/// \brief Everything produced by o_du_low_unit_factory::create().
struct o_du_low_unit {
  std::unique_ptr<odu::o_du_low>            o_du_lo; ///< The running O-DU Low object.
  std::vector<app_services::metrics_config> metrics; ///< Its metric feed configs.
};

/// O-RAN DU low unit factory.

/// \brief Factory for O-DU Low units.
///
/// Instances are cheap; the constructor's job is to initialise the HAL
/// (hardware-accelerator) dependencies exactly once — those live in the
/// factory instance and are shared across every unit it creates.
class o_du_low_unit_factory
{
  /// HAL factories (PDSCH encoder, PUSCH decoder). Both are nullptr unless
  /// the build was configured with DPDK and the user enabled BBDEV.
  o_du_low_hal_dependencies hal_dependencies;


public:
  /// Constructor: initialises HAL dependencies from the (optional) HAL config.
  o_du_low_unit_factory(const std::optional<du_low_unit_hal_config>& hal_config);

  /// Creates an O-RAN DU low unit with the given parameters.

  /// \brief Creates and returns a fully-wired O-DU Low unit.
  /// \param params        The full DU-Low config + per-cell PHY parameters.
  /// \param dependencies  External resources (RG gateway, symbol notifier,
  ///                      executors, FAPI P5 executor).
  o_du_low_unit create(const o_du_low_unit_config& params, const o_du_low_unit_dependencies& dependencies);
};


} // namespace ocudu
