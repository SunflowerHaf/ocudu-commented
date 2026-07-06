// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/detail/slotted_array_detail.h  (18 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"


namespace ocudu {
namespace detail {


template <typename IdType>
struct cast_to_size_operator {
  constexpr std::size_t get_index(const IdType& t) const { return static_cast<std::size_t>(t); }
  constexpr IdType      get_id(std::size_t idx) const { return static_cast<IdType>(idx); }
};


} // namespace detail
} // namespace ocudu
