// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/serdes/ofh_uplane_message_decoder.h  (47 lines)
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


#include "ocudu/adt/span.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder_properties.h"
#include "ocudu/ofh/timing/slot_symbol_point.h"
#include <optional>


namespace ocudu {
namespace ofh {
namespace uplane_peeker {

/// Peeks and returns the filter index of the given message.
///
/// \param[in] message Message to peek.
/// \return Message filter index or nullopt if the value cannot be peeked.

/// Peeks and returns the filter index of the given message.
///
/// \param[in] message Message to peek.
/// \return Message filter index or nullopt if the value cannot be peeked.
std::optional<filter_index_type> peek_filter_index(span<const uint8_t> message);

/// Peeks and returns the slot symbol point of the given message.
///
/// \param[in] message Message to peek.
/// \param[in] nof_symbols Number of symbols.
/// \param[in] scs Subcarrier spacing.
/// \return Expected slot symbol point or nullopt if the value cannot be peeked

/// Peeks and returns the slot symbol point of the given message.
///
/// \param[in] message Message to peek.
/// \param[in] nof_symbols Number of symbols.
/// \param[in] scs Subcarrier spacing.
/// \return Expected slot symbol point or nullopt if the value cannot be peeked
std::optional<slot_symbol_point>
peek_slot_symbol_point(span<const uint8_t> message, unsigned nof_symbols, subcarrier_spacing scs);


} // namespace uplane_peeker

/// Open Fronthaul User-Plane message decoder interface.

/// Open Fronthaul User-Plane message decoder interface.
class uplane_message_decoder
{
public:
  virtual ~uplane_message_decoder() = default;

  /// Decodes the given message into results and returns true on success, false otherwise.
  ///
  /// \param[out] results Results of decoding the message. On error, results value is undefined.
  /// \param[in] message Message to be decoded.
  /// \return True on success, false otherwise.

  /// Decodes the given message into results and returns true on success, false otherwise.
  ///
  /// \param[out] results Results of decoding the message. On error, results value is undefined.
  /// \param[in] message Message to be decoded.
  /// \return True on success, false otherwise.
  virtual bool decode(uplane_message_decoder_results& results, span<const uint8_t> message) = 0;
};


} // namespace ofh
} // namespace ocudu
