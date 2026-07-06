// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ofh_factories.h  (46 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/ofh
// Open Fronthaul public interface headers. CONDITIONAL: linked into the binary via a temporary dependency (see lib/ofh note) but not used at runtime in split-8. These headers define the OFH contract between the lib/ofh library and its callers (primarily lib/ru/ofh).
//
// Contents:
//   ofh/compression/      — IQ compressor/decompressor abstract interfaces and compression parameter types (scheme, data width, BFP exponent).
//   ofh/ecpri/            — eCPRI packet builder, decoder, and property types.
//   ofh/ethernet/         — Ethernet frame builder/receiver interfaces, VLAN tag types, and port configuration.
//   ofh/ofh_factories.h   — Top-level OFH sector factory.
//   ofh/ofh_sector.h      — OFH sector interface (one per radio sector/cell).
//   ofh/receiver/         — OFH uplink receiver interface (delivers received IQ).
//   ofh/serdes/           — C-plane and U-plane message serialiser interfaces.
//   ofh/timing/           — OFH timing controller interface (slot indication source).
//   ofh/transmitter/      — OFH downlink transmitter interface.
// =============================================================================

#pragma once


#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/ofh_sector.h"
#include "ocudu/ofh/ofh_sector_config.h"
#include "ocudu/ofh/ofh_uplane_rx_symbol_notifier.h"
#include "ocudu/ofh/receiver/ofh_sequence_id_checker.h"
#include "ocudu/ofh/timing/ofh_timing_manager.h"
#include <memory>


namespace ocudu {
class task_executor;


namespace ofh {

/// Creates an Open Fronthaul sequence identifier checker.

/// Creates an Open Fronthaul sequence identifier checker.
std::unique_ptr<sequence_id_checker> create_sequence_id_checker();

/// Open Fronthaul controller config.

/// Open Fronthaul controller config.
struct controller_config {
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Highest subcarrier spacing.
  /// Highest subcarrier spacing.
  subcarrier_spacing scs;
  /// GPS Alpha - Valid value range: [0, 1.2288e7].
  /// GPS Alpha - Valid value range: [0, 1.2288e7].
  unsigned gps_Alpha;
  /// GPS Beta - Valid value range: [-32768, 32767].
  /// GPS Beta - Valid value range: [-32768, 32767].
  int gps_Beta;
  /// If set to true, logs late events as warnings, otherwise as info.
  /// If set to true, logs late events as warnings, otherwise as info.
  bool enable_log_warnings_for_lates;
  /// Busy waiting enabled flag.
  /// Busy waiting enabled flag.
  bool enable_busy_waiting;
};

/// Creates an Open Fronthaul timing manager with the given parameters.

/// Creates an Open Fronthaul timing manager with the given parameters.
std::unique_ptr<timing_manager>
create_ofh_timing_manager(const controller_config& config, ocudulog::basic_logger& logger, task_executor& executor);

/// Creates an Open Fronthaul sector.

/// Creates an Open Fronthaul sector.
std::unique_ptr<sector> create_ofh_sector(const sector_configuration& sector_cfg, sector_dependencies&& sector_deps);


} // namespace ofh
} // namespace ocudu
