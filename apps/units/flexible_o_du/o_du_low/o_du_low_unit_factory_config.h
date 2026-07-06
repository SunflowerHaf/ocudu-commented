// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_low_unit_factory_config.h
//
// Purpose (plain English):
//   Defines the "call arguments" for o_du_low_unit_factory::create():
//     * o_du_low_unit_config       — the config (unit config + per-cell PHY
//                                    parameters + FAPI adaptor config).
//     * o_du_low_unit_dependencies — the external resources the unit needs
//                                    references to (resource-grid gateway,
//                                    Rx symbol notifier, executor mapper,
//                                    FAPI P5 executor).
//
//   The nested du_low_config struct inside o_du_low_unit_config carries the
//   per-cell parameters the upper PHY needs to size buffers and pick
//   algorithms: bandwidth, subcarrier spacing, TDD pattern, PRACH config
//   index, number of antennas, NTN K-offset, etc.
// =============================================================================

#pragma once


#include "du_low_hal_factory.h"
#include "ocudu/du/du_low/du_low_executor_mapper.h"
#include "ocudu/du/du_low/o_du_low_config.h"
#include "ocudu/ran/tdd/tdd_ul_dl_config.h"
#include <chrono>


namespace ocudu {


struct du_low_unit_config;

/// O-RAN DU low unit configuration.

/// \brief Full configuration passed into o_du_low_unit_factory::create().
struct o_du_low_unit_config {
  /// \brief Per-cell PHY parameters needed to build the upper PHY.
  ///
  /// These are all values the DU High needed anyway — they're passed through
  /// so the DU Low can size its buffers and pick optimised code paths.
  struct du_low_config {
    odu::cell_prach_ports_entry            prach_ports; ///< Which Rx ports carry PRACH.
    unsigned                               max_puschs_per_slot; ///< Sizing hint for PUSCH pipelines.
    frequency_range                        freq_range; ///< FR1 or FR2.
    duplex_mode                            duplex; ///< FDD or TDD.
    subcarrier_spacing                     scs_common; ///< 15/30/60 kHz etc.
    unsigned                               bw_rb; ///< Cell bandwidth in resource blocks.
    std::optional<tdd_ul_dl_config_common> tdd_pattern; ///< TDD slot pattern (nullopt for FDD).
    unsigned                               prach_config_index; ///< TS38.211 PRACH config table index.
    unsigned                               pusch_max_nof_layers; ///< Max MIMO layers on PUSCH.
    unsigned                               nof_rx_antennas; ///< Uplink antennas.
    unsigned                               nof_tx_antennas; ///< Downlink antennas.
    /// NTN cell-specific K-offset. Empty for terrestrial cells.
    /// NTN cell-specific K-offset (satellite propagation delay compensation).
    /// Empty for terrestrial cells.
    std::optional<std::chrono::milliseconds> ntn_cs_koffset;
  };


  /// Reference to the whole DU-Low unit config (loggers, threads, expert PHY).
  const du_low_unit_config&                      du_low_unit_cfg;
  /// One du_low_config entry per cell managed by this DU Low.
  std::vector<du_low_config>                     cells;
  /// FAPI fastpath adaptor config (MAC↔PHY message-passing customisation).
  fapi_adaptor::phy_fapi_fastpath_adaptor_config fapi_cfg;
};

/// O-RAN DU low unit dependencies.

/// \brief External resources the O-DU Low needs to run.
struct o_du_low_unit_dependencies {
  /// Where the DL resource grids are written to (consumed by the RU below).
  upper_phy_rg_gateway&                 rg_gateway;
  /// Callback the upper PHY uses to request UL symbols from the RU.
  upper_phy_rx_symbol_request_notifier& rx_symbol_request_notifier;
  /// Executor mapper: gives the DU Low its PDSCH/PUSCH/PUCCH thread pools.
  odu::du_low_executor_mapper&          workers;
  /// The task executor used for FAPI P5 (config) messages.
  task_executor&                        fapi_p5_executor;
};


} // namespace ocudu
