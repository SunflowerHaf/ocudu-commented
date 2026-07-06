// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/sidekiq/sidekiq_helper_functions.h  (19 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"


namespace ocudu {

/// \brief Converts packed 12-bit signed integer samples to 16-bit complex integer samples.
/// \remark An assertion is triggered if the input and output sizes are not consistent.

/// \brief Converts packed 12-bit signed integer samples to 16-bit complex integer samples.
/// \remark An assertion is triggered if the input and output sizes are not consistent.
void convert_i12_to_ci16(span<ci16_t> out, span<const uint32_t> in);

/// \brief Converts packed 16-bit signed integer samples to 12-bit complex integer samples.
/// \remark An assertion is triggered if the input and output sizes are not consistent.

/// \brief Converts packed 16-bit signed integer samples to 12-bit complex integer samples.
/// \remark An assertion is triggered if the input and output sizes are not consistent.
void convert_ci16_to_i12(span<uint32_t> out, span<const ci16_t> in);


} // namespace ocudu
