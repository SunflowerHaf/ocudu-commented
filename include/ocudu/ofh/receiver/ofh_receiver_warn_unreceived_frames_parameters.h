// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/receiver/ofh_receiver_warn_unreceived_frames_parameters.h  (58 lines)
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


#include "ocudu/adt/expected.h"
#include <string>


namespace ocudu {
namespace ofh {

/// \brief Warn of unreceived Radio Unit frames type.
///
/// never: does not log unreceived frames.
/// always: logs all unreceived frames.
/// after_traffic_detection: logs all the unreceived frames after the first received frame.

/// \brief Warn of unreceived Radio Unit frames type.
///
/// never: does not log unreceived frames.
/// always: logs all unreceived frames.
/// after_traffic_detection: logs all the unreceived frames after the first received frame.
enum class warn_unreceived_ru_frames { never, always, after_traffic_detection };

/// Converts the given warn unreceived RU frames value to string.

/// Converts the given warn unreceived RU frames value to string.
inline const char* to_string(warn_unreceived_ru_frames value)
{
  switch (value) {
    case warn_unreceived_ru_frames::never:
      return "never";
      break;
    case warn_unreceived_ru_frames::always:
      return "always";
      break;
    case warn_unreceived_ru_frames::after_traffic_detection:
      return "after_traffic_detection";
      break;
  }


  return "always";
}

/// Converts the given value to warn unreceived RU frames.

/// Converts the given value to warn unreceived RU frames.
inline expected<warn_unreceived_ru_frames> to_warn_unreceived_ru_frames(std::string value)
{
  std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return std::tolower(c); });


  if (value == "never") {
    return warn_unreceived_ru_frames::never;
  }


  if (value == "always") {
    return warn_unreceived_ru_frames::always;
  }


  if (value == "after_traffic_detection") {
    return warn_unreceived_ru_frames::after_traffic_detection;
  }


  return make_unexpected(default_error_t());
}


} // namespace ofh
} // namespace ocudu
