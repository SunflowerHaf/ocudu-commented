// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/config/config_object_pool.h  (41 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "config_ptr.h"
#include <deque>


namespace ocudu {

/// Pool of configuration objects that ensures uniqueness of the stored objects.

/// Pool of configuration objects that ensures uniqueness of the stored objects.
template <typename T>
class config_object_pool
{
public:
  config_object_pool()                                     = default;
  config_object_pool(config_object_pool&&)                 = default;
  config_object_pool(const config_object_pool&)            = delete;
  config_object_pool& operator=(config_object_pool&&)      = delete;
  config_object_pool& operator=(const config_object_pool&) = delete;

  /// \brief If an object exists in the pool that it is equal to the provided \c obj, then the existing object is
  /// returned. Otherwise, a new entry is added to the pool and returned.

  /// \brief If an object exists in the pool that it is equal to the provided \c obj, then the existing object is
  /// returned. Otherwise, a new entry is added to the pool and returned.
  config_ptr<T> create(const T& obj)
  {
    for (const T& existing_obj : objs) {
      if (existing_obj == obj) {
        return config_ptr<T>{existing_obj};
      }
    }
    objs.push_back(obj);
    return config_ptr<T>{objs.back()};
  }


private:
  // Note: We use a deque to maintain pointer validity.
  // Note: We use a deque to maintain pointer validity.
  std::deque<T> objs;
};


} // namespace ocudu
