// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_config.h
//
// Purpose (plain English):
//   Groups together the three configuration sub-structures that make up the
//   "upper" half of the O-RAN Distributed Unit (the O-DU High). This is the
//   piece of the gNB that handles the MAC layer, RLC layer, scheduler, F1
//   interface (to the CU), and reporting to the network. The three sub-configs
//   are:
//
//     1. du_high_cfg — the parameters for the DU High itself (cells, PDCCH
//        allocations, PRACH, PUCCH, PDSCH, PUSCH, RLC, PDCP, F1 pcaps, logging,
//        metrics, etc.). This is by far the largest of the three.
//     2. e2_cfg      — the O-RAN E2 interface parameters (the connection to a
//        RAN Intelligent Controller / RIC).
//     3. fapi_cfg    — parameters for the FAPI (Functional API) interface
//        between the MAC (in the DU High) and the PHY (in the DU Low). Since
//        we are running the DU High and DU Low in the same process for split-8,
//        FAPI here is a set of in-memory adaptors, but the config still applies.
//
//   Where this fits in the boot sequence: after the YAML config file has been
//   parsed by the CLI11 schema, an instance of this struct holds the fully
//   populated configuration and is passed into make_o_du_high_unit(...) to
//   actually build the running O-DU High object.
// =============================================================================

#pragma once


// Pull in the three sub-config definitions.
#include "du_high/du_high_config.h" // The big DU High config (cells, layers).
#include "e2/o_du_high_e2_config.h" // O-RAN E2 interface config.
#include "fapi/fapi_config.h" // MAC↔PHY FAPI config.


namespace ocudu {

/// O-DU high unit configuration.

/// \brief Full configuration for the O-DU High half of the flexible O-DU.
///
/// This is just a container that aggregates the three separate config
/// domains. Splitting them this way keeps the code modular: the E2 config,
/// FAPI config, and DU High config each have their own dedicated CLI11
/// registration, YAML writer, validator, and translator functions.
struct o_du_high_unit_config {
  /// DU High parameters (cells, MAC, RLC, PDCP, scheduler, PCAPs, metrics).
  du_high_parsed_config du_high_cfg;
  /// O-RAN E2 interface parameters (RIC address, PCAPs, E2SM modules).
  o_du_high_e2_config   e2_cfg;
  /// FAPI (MAC↔PHY) adaptor parameters.
  fapi_unit_config      fapi_cfg;
};


} // namespace ocudu
