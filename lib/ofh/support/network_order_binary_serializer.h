// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/network_order_binary_serializer.h  (92 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/support/ocudu_assert.h"
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>


namespace ocudu {
namespace ofh {

/// This class serializes input data into the configured memory buffer in network order (big-endian).

/// This class serializes input data into the configured memory buffer in network order (big-endian).
class network_order_binary_serializer
{
public:
  explicit network_order_binary_serializer(uint8_t* ptr_) : ptr(ptr_)
  {
    ocudu_assert(ptr, "Invalid pointer to buffer");
  }

  /// Serializes the given value and advances the position by sizeof(x) bytes.

  /// Serializes the given value and advances the position by sizeof(x) bytes.
  void write(uint16_t x)
  {
    // Convert to network order.
    // Convert to network order.
    uint16_t net_x = htons(x);
    std::memcpy(ptr, &net_x, sizeof(net_x));
    advance(sizeof(net_x));
  }

  /// Serializes the given value and advances the position by sizeof(x) bytes.

  /// Serializes the given value and advances the position by sizeof(x) bytes.
  void write(int16_t x)
  {
    // Convert to network order.
    // Convert to network order.
    uint16_t net_x = htons(x);
    std::memcpy(ptr, &net_x, sizeof(net_x));
    advance(sizeof(net_x));
  }

  /// Serializes the given value and advances the position by sizeof(x) bytes.

  /// Serializes the given value and advances the position by sizeof(x) bytes.
  void write(uint8_t x)
  {
    std::memcpy(ptr, &x, sizeof(x));
    advance(sizeof(x));
  }

  /// Serializes the given span and advances the position by sizeof(x) bytes for each element.

  /// Serializes the given span and advances the position by sizeof(x) bytes for each element.
  template <typename T>
  void write(span<T> s)
  {
    for (const auto elem : s) {
      write(elem);
    }
  }

  /// Serializes the given span of bytes and advances the position by the span size.

  /// Serializes the given span of bytes and advances the position by the span size.
  void write(span<const uint8_t> s)
  {
    std::memcpy(ptr, s.data(), s.size() * sizeof(uint8_t));
    advance(s.size() * sizeof(uint8_t));
  }

  /// Serializes the given span of bytes and advances the position by the span size.

  /// Serializes the given span of bytes and advances the position by the span size.
  void write(span<uint8_t> s) { write(span<const uint8_t>(s)); }

  /// Advances the offset by the given amount.

  /// Advances the offset by the given amount.
  void advance(unsigned x)
  {
    ptr += x;
    offset += x;
  }

  /// Returns a view over the given number of bytes and advances the offset by this amount.

  /// Returns a view over the given number of bytes and advances the offset by this amount.
  span<uint8_t> get_view_and_advance(unsigned x)
  {
    span<uint8_t> view(ptr, x);
    advance(x);
    return view;
  }

  /// Returns the current offset.

  /// Returns the current offset.
  unsigned get_offset() const { return offset; }


private:
  uint8_t* ptr;
  unsigned offset = 0;
};


} // namespace ofh
} // namespace ocudu
