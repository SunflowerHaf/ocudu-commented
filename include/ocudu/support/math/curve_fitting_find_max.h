// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/math/curve_fitting_find_max.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"


namespace ocudu {

/// \brief Estimates a fractional peak from samples around a maximum.
///
/// It uses a quadratic curve fitting of the input values to estimate the peak position. The result is expressed as a
/// fraction of the sampling time with respect to the center input sample.
///
/// When the peak estimation is not meaningful, the function returns zero, meaning that one should consider the
/// maximum input as the peak and no fractional refinement is possible. This happens if:
///   - the number of input samples is neither three nor five; or
///   - the estimation results in NaN or infinity.
///
/// \param[in] samples Odd number of samples containing a peak maximum in the center.
/// \return The fractional sample estimation where the maximum is located if the result is valid.

/// \brief Estimates a fractional peak from samples around a maximum.
///
/// It uses a quadratic curve fitting of the input values to estimate the peak position. The result is expressed as a
/// fraction of the sampling time with respect to the center input sample.
///
/// When the peak estimation is not meaningful, the function returns zero, meaning that one should consider the
/// maximum input as the peak and no fractional refinement is possible. This happens if:
///   - the number of input samples is neither three nor five; or
///   - the estimation results in NaN or infinity.
///
/// \param[in] samples Odd number of samples containing a peak maximum in the center.
/// \return The fractional sample estimation where the maximum is located if the result is valid.
float curve_fitting_fractional_max(span<const float> samples);


} // namespace ocudu
