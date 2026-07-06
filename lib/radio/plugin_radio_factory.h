// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file plugin_radio_factory.h
 * @brief Declares the function for dynamically loading a third-party radio driver plugin.
 *
 * This allows radio backends that aren't compiled directly into OCUDU to be
 * loaded at runtime from a shared library (.so file), provided that library
 * exports the expected factory-creation symbol. This deployment doesn't use
 * a plugin radio (it uses the built-in UHD backend), but this mechanism
 * exists as a fallback whenever the device_driver name doesn't match a
 * built-in backend.
 */

#pragma once


#include "ocudu/radio/radio_factory.h"
#include <memory>
#include <string>


namespace ocudu {


/**
 * @brief Attempts to load a radio driver plugin by name and create its factory.
 *
 * @param driver_name  The driver name; the expected shared library filename
 *                     is constructed as "libocudu_radio_<driver_name>.so".
 * @return The constructed radio_factory, or nullptr if the plugin library
 *         could not be loaded or didn't export the expected symbol.
 */
std::unique_ptr<radio_factory> create_plugin_radio_factory(std::string driver_name);


} // namespace ocudu
