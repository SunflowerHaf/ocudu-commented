// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/processors/resource_request_pool.h  (90 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/circular_array.h"
#include "ocudu/ran/slot_point.h"
#include <atomic>
#include <utility>


namespace ocudu {

/// \brief Lock-free resource request pool.
///
/// Stores up to \c requestArraySize requests indexed by slot, each at position
/// <tt>slot.system_slot() % requestArraySize</tt>. A request pairs a slot point with a templated resource.
///
/// Producers push requests and a single consumer pops them. Both operations are implemented by the same \ref exchange
/// method: a producer passes a valid resource, the consumer an empty one. Access to the slot resource is guarded by
/// a non-blocking try-lock wrapper. If two threads reach the same slot at once, one proceeds and the other returns
/// without modifying the stored request.
///
/// To allow reporting the slots that are not processed, \ref exchange always returns a request:
/// - On uncontended access it returns the request previously stored at the slot (empty if there was none). A
///   producer overwriting a non-empty request can thus report the overwritten slot (report a 'late').
/// - In the case of a concurrent collision at the exchange, it returns the request that was passed in, so a producer
///   can report its own dropped slot. The consumer passes an empty request, hence a dropped pop simply yields
///   "no request for this slot".
///
/// \tparam ResourceType     Resource type.
/// \tparam requestArraySize Maximum number of requests contained in the array.

/// \brief Lock-free resource request pool.
///
/// Stores up to \c requestArraySize requests indexed by slot, each at position
/// <tt>slot.system_slot() % requestArraySize</tt>. A request pairs a slot point with a templated resource.
///
/// Producers push requests and a single consumer pops them. Both operations are implemented by the same \ref exchange
/// method: a producer passes a valid resource, the consumer an empty one. Access to the slot resource is guarded by
/// a non-blocking try-lock wrapper. If two threads reach the same slot at once, one proceeds and the other returns
/// without modifying the stored request.
///
/// To allow reporting the slots that are not processed, \ref exchange always returns a request:
/// - On uncontended access it returns the request previously stored at the slot (empty if there was none). A
///   producer overwriting a non-empty request can thus report the overwritten slot (report a 'late').
/// - In the case of a concurrent collision at the exchange, it returns the request that was passed in, so a producer
///   can report its own dropped slot. The consumer passes an empty request, hence a dropped pop simply yields
///   "no request for this slot".
///
/// \tparam ResourceType     Resource type.
/// \tparam requestArraySize Maximum number of requests contained in the array.
template <typename ResourceType, unsigned requestArraySize = 16>
class resource_request_pool
{
public:
  /// Get the maximum number of requests that can be held by the array.
  /// Get the maximum number of requests that can be held by the array.
  static constexpr unsigned get_request_array_size() { return requestArraySize; }

  /// Internal storage type.

  /// Internal storage type.
  struct request_type {
    slot_point   slot;
    ResourceType resource;
  };

  /// \brief Exchanges the request stored at the given request's slot with the given one.
  ///
  /// \param[in] request Request to store, placed at index <tt>request.slot.system_slot() % requestArraySize</tt>.
  /// \return The request previously stored at the calculated index (empty if none), or \c request itself if the slot
  /// is being accessed concurrently and its request is acquired by another thread.

  /// \brief Exchanges the request stored at the given request's slot with the given one.
  ///
  /// \param[in] request Request to store, placed at index <tt>request.slot.system_slot() % requestArraySize</tt>.
  /// \return The request previously stored at the calculated index (empty if none), or \c request itself if the slot
  /// is being accessed concurrently and its request is acquired by another thread.
  request_type exchange(request_type request)
  {
    return requests[request.slot.system_slot()].exchange(std::move(request));
  }


private:
  /// Wraps a request in a lock-free, non-blocking access guard.
  /// Wraps a request in a lock-free, non-blocking access guard.
  class request_wrapper
  {
  public:
    /// \brief Exchanges the stored request with a new one.
    ///
    /// \return The previously stored request, or \c new_request if the slot is accessed concurrently and the exchange
    /// is dropped.
    /// \brief Exchanges the stored request with a new one.
    ///
    /// \return The previously stored request, or \c new_request if the slot is accessed concurrently and the exchange
    /// is dropped.
    request_type exchange(request_type new_request)
    {
      // Acquire access. If the slot is already taken, return the request without storing it.
      // Acquire access. If the slot is already taken, return the request without storing it.
      if (locked.exchange(true, std::memory_order_acquire)) {
        return new_request;
      }

      // Exclusive access acquired.

      // Exclusive access acquired.
      request_type old_request = std::exchange(request, std::move(new_request));


      locked.store(false, std::memory_order_release);
      return old_request;
    }


  private:
    /// Stored request.
    /// Stored request.
    request_type request{};
    /// Non-blocking access guard. Acquire-release semantic is used.
    /// Non-blocking access guard. Acquire-release semantic is used.
    std::atomic<bool> locked{false};
  };

  /// Request storage, indexed by slots.

  /// Request storage, indexed by slots.
  circular_array<request_wrapper, requestArraySize> requests;
};


} // namespace ocudu
