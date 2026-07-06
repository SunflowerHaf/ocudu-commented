// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/cell_config.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/pci.h"
#include "ocudu/ran/prach/rach_config_common.h"
#include "ocudu/ran/ssb/ssb_configuration.h"
#include "ocudu/ran/tdd/tdd_ul_dl_config.h"
#include <any>


namespace ocudu {
namespace fapi {

/// Encodes the carrier configuration.

/// Encodes the carrier configuration.
struct carrier_config {
  uint16_t            dl_bandwidth;
  uint32_t            dl_f_ref_arfcn;
  uint16_t            dl_grid_size;
  uint16_t            num_tx_ant;
  uint16_t            ul_bandwidth;
  uint32_t            ul_f_ref_arfcn;
  uint16_t            ul_grid_size;
  uint16_t            num_rx_ant;
  dmrs_typeA_position dmrs_typeA_pos;
};

/// FAPI cell configuration.

/// FAPI cell configuration.
struct cell_configuration {
  subcarrier_spacing                     scs_common;
  cyclic_prefix                          cp;
  pci_t                                  pci;
  duplex_mode                            duplex;
  carrier_config                         carrier_cfg;
  rach_config_common                     prach_cfg;
  ssb_configuration                      ssb_cfg;
  std::optional<tdd_ul_dl_config_common> tdd_ul_dl_cfg_common;
  /// Vendor specific configuration.
  /// Vendor specific configuration.
  std::any vendor_cfg;
};


} // namespace fapi
} // namespace ocudu
