// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/network_order_binary_deserializer.h  (121 lines)
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


namespace ocudu {
namespace ofh {

/// This class deserializes data from the configured memory buffer in network order and returns it in host endianness.

/// This class deserializes data from the configured memory buffer in network order and returns it in host endianness.
class network_order_binary_deserializer
{
public:
  explicit network_order_binary_deserializer(span<const uint8_t> buffer) : ptr(buffer.data()), size(buffer.size())
  {
    ocudu_assert(ptr, "Invalid pointer to buffer");
  }

  /// \brief Deserializes a T from the buffer and advances the position by sizeof(T) bytes.
  ///
  /// \note This function only accepts POD types.

  /// \brief Deserializes a T from the buffer and advances the position by sizeof(T) bytes.
  ///
  /// \note This function only accepts POD types.
  template <typename T>
  T read()
  {
    static_assert(std::is_pod<T>::value, "Unsupported data type");


    switch (sizeof(T)) {
      case 1:
        return read_one_byte();
      case 2:
        return read_two_bytes();
      case 4:
        return read_four_bytes();
      default:
        ocudu_assert(0, "Deserializer does not support this data");
    }
    return T();
  }

  /// Deserializes a fixed amount of elements given by the size of the input span and advances the position by sizeof(T)
  /// bytes for each element.

  /// Deserializes a fixed amount of elements given by the size of the input span and advances the position by sizeof(T)
  /// bytes for each element.
  template <typename T>
  void read(span<T> s)
  {
    for (auto& element : s) {
      element = read<T>();
    }
  }

  /// Deserializes a fixed amount of bytes given by the size of the input span and advances the position by the span
  /// size.

  /// Deserializes a fixed amount of bytes given by the size of the input span and advances the position by the span
  /// size.
  void read(span<uint8_t> s)
  {
    std::memcpy(s.data(), ptr, s.size() * sizeof(uint8_t));
    advance(s.size() * sizeof(uint8_t));
  }

  /// Advances the offset by the given amount.

  /// Advances the offset by the given amount.
  void advance(unsigned x)
  {
    ptr += x;
    offset += x;
  }

  /// Returns a view over the given number of bytes and advances the offset by this amount.

  /// Returns a view over the given number of bytes and advances the offset by this amount.
  span<const uint8_t> get_view_and_advance(unsigned x)
  {
    span<const uint8_t> view(ptr, x);
    advance(x);
    return view;
  }

  /// Returns the current offset.

  /// Returns the current offset.
  unsigned get_offset() const { return offset; }

  /// Returns the number of unconsumed bytes of the buffer.

  /// Returns the number of unconsumed bytes of the buffer.
  unsigned remaining_bytes() const { return size - offset; }


private:
  /// Deserializes one byte and advances the position by one byte.
  /// Deserializes one byte and advances the position by one byte.
  uint8_t read_one_byte()
  {
    uint8_t value;
    std::memcpy(&value, ptr, sizeof(value));
    advance(sizeof(value));


    return value;
  }

  /// Deserializes two bytes and advances the position by two bytes.

  /// Deserializes two bytes and advances the position by two bytes.
  uint16_t read_two_bytes()
  {
    uint16_t value;
    std::memcpy(&value, ptr, sizeof(value));
    advance(sizeof(value));


    return ntohs(value);
  }

  /// Deserializes four bytes and advances the position by four bytes.

  /// Deserializes four bytes and advances the position by four bytes.
  uint32_t read_four_bytes()
  {
    uint32_t value;
    std::memcpy(&value, ptr, sizeof(value));
    advance(sizeof(value));


    return ntohl(value);
  }


private:
  const uint8_t* ptr;
  const unsigned size;
  unsigned       offset = 0;
};


} // namespace ofh
} // namespace ocudu
