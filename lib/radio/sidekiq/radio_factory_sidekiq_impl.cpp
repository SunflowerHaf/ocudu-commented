// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/sidekiq/radio_factory_sidekiq_impl.cpp  (31 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#include "radio_factory_sidekiq_impl.h"
#include "radio_session_sidekiq_impl.h"


using namespace ocudu;


std::unique_ptr<radio_session> radio_factory_sidekiq_impl::create(const radio_configuration::radio& config,
                                                                  task_executor&                    async_task_executor,
                                                                  radio_event_notifier&             notifier)
{
  // Create radio session based on Sidekiq.
  // Create radio session based on Sidekiq.
  std::unique_ptr<radio_session_sidekiq_impl> session =
      std::make_unique<radio_session_sidekiq_impl>(config, async_task_executor, notifier);

  // Check session was created successfully.

  // Check session was created successfully.
  if (!session->is_successful()) {
    return nullptr;
  }

  // Otherwise, return the instance.

  // Otherwise, return the instance.
  return session;
}


radio_config_sidekiq_config_validator radio_factory_sidekiq_impl::config_validator;


std::unique_ptr<radio_factory> ocudu::create_dynamic_radio_factory()
{
  return std::make_unique<radio_factory_sidekiq_impl>();
}
