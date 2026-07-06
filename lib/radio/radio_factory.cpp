// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_factory.cpp
 * @brief Top-level radio backend selector — chooses which radio driver to instantiate.
 *
 * This is the entry point ru_factory_sdr_impl.cpp calls (via
 * create_radio_factory()) to obtain the correct radio_factory implementation
 * based on the device_driver string from the YAML config ("uhd" in this
 * deployment). It supports several backends, each conditionally compiled in
 * based on build-time feature flags:
 *
 *   sidekiq:            Epiq Solutions Sidekiq SDR hardware (ENABLE_SIDEKIQ).
 *   uhd:                Ettus Research USRP hardware via UHD (ENABLE_UHD) —
 *                       this is the active backend for this deployment.
 *   zmq:                ZeroMQ software loopback, for testing without real
 *                       hardware (ENABLE_ZMQ).
 *   realtime_loopback:  Always available — an in-process loopback for
 *                       testing the radio interface without any external
 *                       dependency.
 *
 * If the requested driver name doesn't match any built-in backend, it
 * attempts to load a dynamically-linked plugin (via plugin_radio_factory.h),
 * allowing third-party radio drivers to be added without recompiling OCUDU.
 */

#include "ocudu/radio/radio_factory.h"


#ifdef ENABLE_SIDEKIQ
#include "sidekiq/radio_factory_sidekiq_impl.h"
#endif // ENABLE_SIDEKIQ


#ifdef ENABLE_UHD
#include "uhd/radio_uhd_impl.h"
#endif // ENABLE_UHD


#ifdef ENABLE_ZMQ
#include "zmq/radio_factory_zmq_impl.h"
#endif // ENABLE_ZMQ


#include "plugin_radio_factory.h"
#include "realtime_loopback/radio_factory_realtime_loopback_impl.h"


using namespace ocudu;


namespace {


/**
 * @brief One entry in the table of built-in radio backends.
 */
struct radio_factory_entry {
  /// The driver name as it appears in the device_driver config field.
  std::string                                     name;
  /// Constructs an instance of this backend's factory.
  std::function<std::unique_ptr<radio_factory>()> make;
};


} // namespace


/**
 * @brief The table of built-in radio backends, compiled in based on feature flags.
 *
 * Only backends enabled at compile time appear here; for this deployment,
 * ENABLE_UHD is set, so "uhd" is present (along with "realtime_loopback",
 * which is always compiled in for testing purposes).
 */
static const std::vector<radio_factory_entry> radio_factory_available_factories = {
#ifdef ENABLE_SIDEKIQ
    {"sidekiq", []() { return std::make_unique<radio_factory_sidekiq_impl>(); }},
#endif // ENABLE_SIDEKIQ
#ifdef ENABLE_UHD
    {"uhd", []() { return std::make_unique<radio_factory_uhd_impl>(); }},
#endif // ENABLE_UHD
#ifdef ENABLE_ZMQ
    {"zmq", []() { return std::make_unique<radio_factory_zmq_impl>(); }},
#endif // ENABLE_ZMQ
    {"realtime_loopback", []() { return std::make_unique<radio_factory_realtime_loopback_impl>(); }}};


/**
 * @brief Prints the list of available radio backend names to stdout.
 *
 * Called by ru_factory_sdr_impl.cpp during startup, mainly to help diagnose
 * configuration issues — if the requested driver name doesn't appear in this
 * list, the user knows immediately their build doesn't include that backend.
 */
void ocudu::print_available_radio_factories()
{
  if (radio_factory_available_factories.empty()) {
    return;
  }

  // Print available factories.

  fmt::print("Available radio types: ");
  for (unsigned i = 0, e = radio_factory_available_factories.size(); i != e; ++i) {
    if (i > 0) {
      if (i == radio_factory_available_factories.size() - 1) {
        fmt::print(" and ");
      } else {
        fmt::print(", ");
      }
    }
    fmt::print("{}", radio_factory_available_factories[i].name);
  }
  fmt::print(".\n");
}


/**
 * @brief Creates a radio factory instance for the named backend.
 *
 * First checks the built-in backend table (case-insensitive match).
 * If no built-in backend matches, attempts to load a dynamic plugin with
 * that name. If neither succeeds, prints an error and returns nullptr.
 *
 * @param driver_name  The requested backend name (e.g. "uhd"). Converted to
 *                     lowercase before matching, so the config value is
 *                     effectively case-insensitive.
 * @return The constructed radio_factory, or nullptr if no matching backend
 *         was found.
 */
std::unique_ptr<radio_factory> ocudu::create_radio_factory(std::string driver_name)
{
  // Convert driver name to lower case.
  for (char& c : driver_name) {
    c = std::tolower(c);
  }

  // Iterate all available driver names.

  // Check the built-in backend table first.
  for (const radio_factory_entry& entry : radio_factory_available_factories) {
    if (entry.name == driver_name) {
      return entry.make();
    }
  }

  // Try creating a plugin radio factory.

  // Not a built-in backend — try loading it as a dynamic plugin.
  auto factory = create_plugin_radio_factory(driver_name);
  if (factory) {
    return factory;
  }

  // No match, print available factories.

  // No match found anywhere.
  fmt::print("Factory for radio type {} not found. Make sure to select a valid type.\n", driver_name);


  return nullptr;
}
