// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_low_unit_factory.cpp
//
// Purpose (plain English):
//   Implementation of o_du_low_unit_factory. Three steps in create():
//     1. Copy the FAPI config and metrics flag from the "unit" config into
//        the internal odu::o_du_low_config used by the core factory.
//     2. Call generate_o_du_low_config() (in du_low_config_translator.cpp)
//        to derive every remaining internal parameter from the per-cell
//        parameters (PDSCH/PUSCH sizing, PRACH detector setup, etc.).
//     3. Build the odu::o_du_low_dependencies bag (upper-PHY executors,
//        hardware-accelerator factories if any, per-cell RG gateway pointers)
//        and hand everything to the core odu::make_o_du_low() factory.
//   The result is a running upper-PHY object plus a metrics vector.
// =============================================================================

#include "o_du_low_unit_factory.h"
#include "apps/services/worker_manager/worker_manager.h"
#include "du_low_config.h"
#include "du_low_config_translator.h"
#include "du_low_hal_factory.h"
#include "ocudu/du/du_low/o_du_low_factory.h"
#include "ocudu/ran/slot_pdu_capacity_constants.h"


using namespace ocudu;


// Constructor: initialise HAL deps once. In software builds these are all
// nullptr; in DPDK+BBDEV builds this actually opens the accelerator card.
o_du_low_unit_factory::o_du_low_unit_factory(const std::optional<du_low_unit_hal_config>& hal_config) :
  hal_dependencies(make_du_low_hal_dependencies(hal_config))
{
}


// -----------------------------------------------------------------------------
// generate_du_low_dependencies()
//   Assembles the odu::du_low_dependencies struct that the core factory needs.
//   Contents: a logger handle, a common upper-PHY dependency block (executors +
//   hardware factories), and one per-cell dependency block wiring the RG
//   gateway and Rx-symbol-request notifier.
// -----------------------------------------------------------------------------
static odu::du_low_dependencies generate_du_low_dependencies(const o_du_low_unit_dependencies& dependencies,
                                                             const o_du_low_hal_dependencies&  hal_dependencies,
                                                             unsigned                          nof_cells)
{
  odu::du_low_dependencies out_deps;
  out_deps.logger = &ocudulog::fetch_basic_logger("DU");
  out_deps.cells.reserve(nof_cells);


  // Common upper-PHY dependencies: executors are shared across cells.
  upper_phy_factory_dependencies& upper_phy_common_deps = out_deps.upper_phy_common_deps;
  upper_phy_common_deps.executors                       = dependencies.workers.get_upper_phy_execution_config();


  // If HW accelerators are present, plug them into the common deps.
  if (hal_dependencies.hw_encoder_factory) {
    upper_phy_common_deps.hw_encoder_factory = hal_dependencies.hw_encoder_factory;
  }

  if (hal_dependencies.hw_decoder_factory) {
    upper_phy_common_deps.hw_decoder_factory = hal_dependencies.hw_decoder_factory;
  }


  // Per-cell dependencies: currently just the RG gateway + Rx symbol notifier.
  // Both are shared across cells here (one gateway serves all cells).
  for (unsigned i = 0, e = nof_cells; i != e; ++i) {
    upper_phy_dependencies& upper_phy_cell    = out_deps.cells.emplace_back().upper_phy_deps;
    upper_phy_cell.rg_gateway                 = &dependencies.rg_gateway;
    upper_phy_cell.rx_symbol_request_notifier = &dependencies.rx_symbol_request_notifier;
  }


  return out_deps;
}


// -----------------------------------------------------------------------------
// create() — the factory entry point.
// -----------------------------------------------------------------------------
o_du_low_unit o_du_low_unit_factory::create(const o_du_low_unit_config& params, const o_du_low_unit_dependencies& deps)
{
  odu::o_du_low_config o_du_low_cfg;

  // Copy FAPI configuration.

  // Straight passthrough — the FAPI config is user-facing already.
  o_du_low_cfg.fapi_cfg = params.fapi_cfg;

  // Configure the metrics.

  // Enable the DU-Low metrics feed if the user asked for it.
  o_du_low_cfg.enable_metrics = params.du_low_unit_cfg.metrics_cfg.enable_du_low;

  // Generate O-DU low configuration.

  // Derive every remaining internal parameter (upper PHY sizing, PRACH
  // detector setup, algorithm choices) from the per-cell params.
  generate_o_du_low_config(o_du_low_cfg, params.du_low_unit_cfg, params.cells);

  // Generate O-DU low dependencies.

  // Bundle dependencies + FAPI P5 executor into the core dep struct.
  odu::o_du_low_dependencies o_du_low_deps = {
      .du_low_deps      = generate_du_low_dependencies(deps, hal_dependencies, params.cells.size()),
      .fapi_p5_executor = deps.fapi_p5_executor};


  // Actually construct the upper PHY.
  o_du_low_unit unit;
  unit.o_du_lo = odu::make_o_du_low(o_du_low_cfg, o_du_low_deps);
  report_error_if_not(unit.o_du_lo, "Invalid O-DU low");


  return unit;
}
