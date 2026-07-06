// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/serdes/ofh_message_properties.h  (104 lines)
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


#include <cstdint>


namespace ocudu {
namespace ofh {

/// Open Fronthaul data direction.

/// Open Fronthaul data direction.
enum class data_direction : uint8_t { uplink, downlink };

/// Converts and returns the given data direction into an integer.

/// Converts and returns the given data direction into an integer.
constexpr unsigned to_value(data_direction dir)
{
  return static_cast<unsigned>(dir);
}

/// Resource block type.

/// Resource block type.
enum class rb_id_type : uint8_t { every_rb_used, every_other_rb_used };

/// Converts and returns the given resource block type into an integer.

/// Converts and returns the given resource block type into an integer.
constexpr unsigned to_value(rb_id_type rb)
{
  return static_cast<unsigned>(rb);
}

/// Symbol increment type.

/// Symbol increment type.
enum class symbol_incr_type : uint8_t { current_symbol_number, increment_current_symbol_number };

/// Converts and returns the given symbol increment type into an integer.

/// Converts and returns the given symbol increment type into an integer.
constexpr unsigned to_value(symbol_incr_type s)
{
  return static_cast<unsigned>(s);
}

/// Filter index type.

/// Filter index type.
enum class filter_index_type : uint8_t {
  standard_channel_filter       = 0,
  ul_prach_preamble_1p25khz     = 1,
  ul_prach_preamble_5kHz        = 2,
  ul_prach_preamble_short       = 3,
  ul_prach_preamble_short_15kHz = 6,
  ul_prach_preamble_short_30kHz = 7,
  ul_nprach_preamble            = 4,
  ul_prach_preamble_7p5kHz      = 5,
  reserved                      = 8
};

/// Converts and returns the given filter type into an integer.

/// Converts and returns the given filter type into an integer.
constexpr unsigned to_value(filter_index_type filter_type)
{
  return static_cast<unsigned>(filter_type);
}

/// Converts and returns the given index to a filter index type.

/// Converts and returns the given index to a filter index type.
constexpr filter_index_type to_filter_index_type(unsigned index)
{
  switch (index) {
    case 0:
      return filter_index_type::standard_channel_filter;
    case 1:
      return filter_index_type::ul_prach_preamble_1p25khz;
    case 2:
      return filter_index_type::ul_prach_preamble_5kHz;
    case 3:
      return filter_index_type::ul_prach_preamble_short;
    case 4:
      return filter_index_type::ul_nprach_preamble;
    case 5:
      return filter_index_type::ul_prach_preamble_7p5kHz;
    case 6:
      return filter_index_type::ul_prach_preamble_short_15kHz;
    case 7:
      return filter_index_type::ul_prach_preamble_short_30kHz;
    default:
      return filter_index_type::reserved;
  }
}

/// Returns true is passed filter index corresponds to a PRACH filter, otherwise returns false.

/// Returns true is passed filter index corresponds to a PRACH filter, otherwise returns false.
constexpr bool is_a_prach_message(filter_index_type filter_index)
{
  return ((filter_index >= filter_index_type::ul_prach_preamble_1p25khz) &&
          (filter_index <= filter_index_type::ul_prach_preamble_short_30kHz));
}

/// Open Fronthaul section types.

/// Open Fronthaul section types.
enum class section_type {
  /// Used for indicating idle or guard periods from O-DU to O-RU.
  /// Used for indicating idle or guard periods from O-DU to O-RU.
  type_0,
  /// Used for most Downlink and Uplink physical radio channels.
  /// Used for most Downlink and Uplink physical radio channels.
  type_1,
  /// Used for PRACH and mixed-numerology channels.
  /// Used for PRACH and mixed-numerology channels.
  type_3,
  /// Used for UE scheduling information.
  /// Used for UE scheduling information.
  type_5,
  /// Used for sending channel information for a specific UE ID.
  /// Used for sending channel information for a specific UE ID.
  type_6
};


} // namespace ofh
} // namespace ocudu
