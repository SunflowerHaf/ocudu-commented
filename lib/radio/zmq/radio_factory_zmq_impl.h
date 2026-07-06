// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/zmq/radio_factory_zmq_impl.h  (24 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "radio_config_zmq_validator.h"
#include "ocudu/radio/radio_factory.h"


namespace ocudu {

/// Describes a ZeroMQ Radio based factory.

/// Describes a ZeroMQ Radio based factory.
class radio_factory_zmq_impl : public radio_factory
{
public:
  // See interface for documentation.
  // See interface for documentation.
  const radio_configuration::validator& get_configuration_validator() const override;

  // See interface for documentation.

  // See interface for documentation.
  std::unique_ptr<radio_session> create(const radio_configuration::radio& config,
                                        task_executor&                    async_task_executor,
                                        radio_event_notifier&             notifier) override;
};


} // namespace ocudu
