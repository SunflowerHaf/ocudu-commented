// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/zmq/radio_factory_zmq_impl.cpp  (31 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#include "radio_factory_zmq_impl.h"
#include "radio_config_zmq_validator.h"
#include "radio_session_zmq_impl.h"


using namespace ocudu;


std::unique_ptr<radio_session> radio_factory_zmq_impl::create(const radio_configuration::radio& config,
                                                              task_executor&                    async_task_executor,
                                                              radio_event_notifier&             notifier)
{
  // Create radio session based on ZMQ.
  // Create radio session based on ZMQ.
  std::unique_ptr<radio_session_zmq_impl> session =
      std::make_unique<radio_session_zmq_impl>(config, async_task_executor, notifier);

  // Check session was created successfully.

  // Check session was created successfully.
  if (!session->is_successful()) {
    return nullptr;
  }

  // Otherwise, return the instance.

  // Otherwise, return the instance.
  return session;
}


const radio_configuration::validator& radio_factory_zmq_impl::get_configuration_validator() const
{
  static radio_config_zmq_config_validator config_validator;
  return config_validator;
}
