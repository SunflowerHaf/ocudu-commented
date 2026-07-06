// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/ethernet_unique_buffer.h  (118 lines)
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
#include "ocudu/support/units.h"


namespace ocudu {
namespace ether {


namespace detail {

/// Base vtable for move/destroy operations over the object stored in "unique_rx_buffer".

/// Base vtable for move/destroy operations over the object stored in "unique_rx_buffer".
class storage_helper
{
public:
  constexpr storage_helper()                     = default;
  virtual ~storage_helper()                      = default;
  virtual void move(void* src, void* dest) const = 0;
  virtual void destroy(void* src) const          = 0;
  virtual bool empty() const                     = 0;
};

/// Specialization of move/destroy operations for when the "unique_rx_buffer" stores an object in its internal storage.

/// Specialization of move/destroy operations for when the "unique_rx_buffer" stores an object in its internal storage.
template <typename T>
class storage_helper_impl : public storage_helper
{
public:
  constexpr storage_helper_impl() = default;
  void move(void* src, void* dest) const override
  {
    ::new (dest) T(std::move(*static_cast<T*>(src)));
    static_cast<T*>(src)->~T();
  }
  void destroy(void* src) const override { static_cast<T*>(src)->~T(); }
  bool empty() const override { return false; }
};

/// Specialization of move/destroy operations for when the "unique_rx_buffer" is empty.

/// Specialization of move/destroy operations for when the "unique_rx_buffer" is empty.
class empty_storage : public storage_helper
{
public:
  constexpr empty_storage() = default;
  void move(void* src, void* dest) const override {}
  void destroy(void* src) const override {}
  bool empty() const override { return true; }
};


} // namespace detail

/// Receive buffer interface.

/// Receive buffer interface.
class rx_buffer
{
public:
  virtual ~rx_buffer() = default;

  /// Returns a span of bytes received from the NIC.

  /// Returns a span of bytes received from the NIC.
  virtual span<const uint8_t> data() const = 0;
};

/// Receive buffer wrapper enforcing unique ownership of the stored buffer.

/// Receive buffer wrapper enforcing unique ownership of the stored buffer.
class unique_rx_buffer
{
  static constexpr units::bytes             storage_capacity{32};
  static const inline detail::empty_storage empty_object;


  using storage_t = std::aligned_storage_t<storage_capacity.value(), alignof(std::max_align_t)>;


public:
  /// Default constructor initializes internal storage with an empty object.
  /// Default constructor initializes internal storage with an empty object.
  constexpr unique_rx_buffer() noexcept : storage_ptr(&empty_object), buffer_ptr(nullptr) {}

  /// Default destructor.

  /// Default destructor.
  ~unique_rx_buffer() { storage_ptr->destroy(&buffer); }

  /// Copy constructor and copy assignment are deleted.

  /// Copy constructor and copy assignment are deleted.
  unique_rx_buffer(const unique_rx_buffer& other)      = delete;
  unique_rx_buffer& operator=(unique_rx_buffer& other) = delete;

  /// Constructor receives an R-value reference to an object implementing rx_buffer interface.

  /// Constructor receives an R-value reference to an object implementing rx_buffer interface.
  template <typename T>
  unique_rx_buffer(T&& rx_buffer_wrapper) noexcept(std::is_nothrow_move_constructible_v<T>)
  {
    static_assert(sizeof(rx_buffer_wrapper) <= storage_capacity.value(),
                  "Pre-allocated storage does not have enough space to store passed rx buffer");


    static const detail::storage_helper_impl<T> helper{};
    storage_ptr = &helper;
    ::new (&buffer) T(std::forward<T>(rx_buffer_wrapper));
  }

  /// Move constructor.

  /// Move constructor.
  unique_rx_buffer(unique_rx_buffer&& other) noexcept : storage_ptr(other.storage_ptr)
  {
    other.storage_ptr = &empty_object;
    storage_ptr->move(&other.buffer, &buffer);
  }

  /// Returns the view over stored data buffer.

  /// Returns the view over stored data buffer.
  span<const uint8_t> data() const
  {
    if (storage_ptr->empty()) {
      return {};
    }
    return static_cast<const rx_buffer*>(static_cast<void*>(&buffer))->data();
  }


private:
  const detail::storage_helper* storage_ptr;
  union {
    mutable storage_t buffer;
    void*             buffer_ptr;
  };
};


} // namespace ether
} // namespace ocudu
