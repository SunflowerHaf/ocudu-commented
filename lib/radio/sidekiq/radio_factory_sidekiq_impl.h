// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/sidekiq/radio_factory_sidekiq_impl.h  (27 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "radio_config_sidekiq_validator.h"
#include "ocudu/radio/radio_factory.h"


namespace ocudu {

/// Implements a Sidekiq radio factory.

/// Implements a Sidekiq radio factory.
class radio_factory_sidekiq_impl : public radio_factory
{
public:
  // See the radio_factory interface for documentation.
  // See the radio_factory interface for documentation.
  const radio_configuration::validator& get_configuration_validator() const override { return config_validator; }

  // See the radio_factory interface for documentation.

  // See the radio_factory interface for documentation.
  std::unique_ptr<radio_session> create(const radio_configuration::radio& config,
                                        task_executor&                    async_task_executor,
                                        radio_event_notifier&             notifier) override;


private:
  static radio_config_sidekiq_config_validator config_validator;
};


} // namespace ocudu
