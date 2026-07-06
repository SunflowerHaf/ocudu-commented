// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/realtime_loopback/radio_config_realtime_loopback_validator.h  (18 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "ocudu/radio/radio_configuration.h"


namespace ocudu {

/// Radio configuration validator for the loopback realtime radio.

/// Radio configuration validator for the loopback realtime radio.
class radio_config_realtime_loopback_validator : public radio_configuration::validator
{
public:
  // See interface for documentation.
  // See interface for documentation.
  bool is_configuration_valid(const radio_configuration::radio& config) const override;
};


} // namespace ocudu
