// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_config_uhd_validator.h
 * @brief Declares the UHD-specific radio configuration validator.
 *
 * This validator checks the radio_configuration::radio struct — the
 * device-agnostic configuration format shared by all radio backends — for
 * values that are structurally valid (non-zero, finite, correctly formatted
 * strings) before the configuration is used to open the actual USRP device.
 *
 * Important distinction: this is a "shape" validator, not a "fit" validator.
 * It does NOT know whether a specific value is supported by the connected
 * hardware (e.g. whether 61.44 MHz is a valid sample rate for a B210). Those
 * hardware-specific limits can only be discovered by querying the actual
 * device once opened (which is what radio_uhd_device.h does when it calls
 * UHD's range-query functions). For checking actual hardware capabilities
 * ahead of time, the UHD command-line tool `uhd_usrp_probe` should be used.
 */

#pragma once


#include "ocudu/radio/radio_configuration.h"


namespace ocudu {

/// \brief Radio configuration validator for uhd based radios.
///
/// This validator validates that parameters values are generally valid, for example frequencies are valid numbers and
/// positive or stream arguments follow a certain pattern. However, it does not validate whether the actual values are
/// supported by the UHD device.
///
/// It is up to the user to select parameters within ranges. These can be consulted using the UHD application \e
/// uhd_usrp_probe.

/**
 * @brief Structural validator for UHD-based radio configurations.
 *
 * Implements the radio_configuration::validator interface used by
 * create_sdr_ru() (in ru_factory_sdr_impl.cpp) before opening the radio
 * session — this catches malformed configuration early with a clear error
 * message, rather than letting it surface as a confusing UHD exception later.
 */
class radio_config_uhd_config_validator : public radio_configuration::validator
{
public:
  // See interface for documentation.
  /**
   * @brief Checks that the configuration values are structurally valid.
   *
   * @param config  The device-agnostic radio configuration to check.
   * @return true if all checks pass; false if any value is malformed
   *         (a descriptive message is printed to stdout before returning false).
   */
  bool is_configuration_valid(const radio_configuration::radio& config) const override;
};


} // namespace ocudu
