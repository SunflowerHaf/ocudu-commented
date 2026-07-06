// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_logger_registrator.h
//
// Purpose (plain English):
//   Registers the two log channels used by the DU-Low ("PHY" and "HWACC")
//   with the central logger service, and applies the user-requested log
//   levels. Called once during startup by the split-8 factory.
//
//     * PHY  — the upper physical layer log channel. Uses "true" so that
//              it is created if it doesn't already exist. Also gets the
//              hex-dump-max-size limit applied (controls how many bytes of
//              a hex-encoded payload are printed before truncation).
//     * HWACC — the hardware-accelerator log channel. Uses "false" so that
//              the fetch fails silently if HWACC wasn't compiled in — the
//              channel is only meaningful in DPDK/BBDEV builds anyway.
// =============================================================================

#pragma once


#include "du_low_config.h"


namespace ocudu {

/// Registers the DU low loggers in the logger service.

/// \brief Registers the DU-Low log channels and sets their levels.
inline void register_du_low_loggers(const du_low_unit_logger_config& log_cfg)
{
  // Set layer-specific logging options.
  // Create-or-fetch the PHY channel and configure it.
  auto& phy_logger = ocudulog::fetch_basic_logger("PHY", true);
  phy_logger.set_level(log_cfg.phy_level);
  phy_logger.set_hex_dump_max_size(log_cfg.hex_max_size);


  // Fetch (do not create) the HWACC channel — set its level if it exists.
  ocudulog::basic_logger& hwacc_logger = ocudulog::fetch_basic_logger("HWACC", false);
  hwacc_logger.set_level(log_cfg.hal_level);
}


} // namespace ocudu
