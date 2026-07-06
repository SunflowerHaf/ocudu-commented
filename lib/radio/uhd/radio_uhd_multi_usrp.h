// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_multi_usrp.h
 * @brief Isolated include of the UHD multi_usrp header with warnings suppressed.
 *
 * This file exists purely to centralise the warning-suppression boilerplate
 * needed when including UHD's multi_usrp.hpp header. The UHD headers were
 * written against an older C++ standard and trigger several modern compiler
 * warnings (missing 'override' keywords, extra semicolons) that aren't
 * actionable since they're in third-party code. Wrapping the include here
 * means every file that needs UHD's multi_usrp type can simply
 * #include "radio_uhd_multi_usrp.h" without repeating the pragma boilerplate.
 *
 * uhd::usrp::multi_usrp is UHD's main class for controlling a USRP device —
 * it exposes all the functions used throughout this driver: setting gain,
 * frequency, sample rate, sync source, and opening Tx/Rx streams.
 */

#pragma once


// Suppress warnings originating from the UHD header itself (third-party code,
// not actionable from this project).
#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wall"
#else // __clang__
#pragma GCC diagnostic ignored "-Wsuggest-override"
#endif // __clang__
#pragma GCC diagnostic ignored "-Wextra-semi"
#include <uhd/usrp/multi_usrp.hpp>
#pragma GCC diagnostic pop
