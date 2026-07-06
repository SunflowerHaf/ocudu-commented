// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file plugin_radio_factory.cpp
 * @brief Implementation of dynamic (runtime-loaded) radio driver plugin support.
 *
 * This file uses the POSIX dlopen/dlsym API to load a shared library at
 * runtime and locate a specific exported C++ symbol (the mangled name of
 * a function called create_dynamic_radio_factory()). If found, it wraps
 * both the resulting radio_factory and the loaded library handle together,
 * ensuring the library is not unloaded (via dlclose) while any radio
 * session or factory object created from it is still alive — unloading
 * the library prematurely would invalidate the function pointers inside
 * any objects it created, causing crashes.
 *
 * Not used in this Split-8 + UHD deployment (UHD is a built-in backend,
 * not a plugin), but documented here for completeness since the build
 * includes it as part of the shared radio factory infrastructure.
 */

#include "plugin_radio_factory.h"
#include "ocudu/radio/radio_factory.h"
#include "ocudu/radio/radio_session.h"
#include <dlfcn.h>
#include <memory>


using namespace ocudu;


namespace {

/// Dynamic library handler deleter - closes the dynamic library upon destruction.

/**
 * @brief Custom deleter that closes a dynamically-loaded library handle.
 */
struct dynamic_library_deleter {
  void operator()(void* handler) const
  {
    if (handler != nullptr) {
      ::dlclose(handler);
    }
  }
};


/// A shared_ptr type for the dynamic library handle, using the custom deleter above.
using handler_ptr = std::shared_ptr<void>;

/// Wraps a radio session with the dynamic library handle.

/**
 * @brief Wraps a radio_session together with the dynamic library handle that created it.
 *
 * Holding the handler alongside the session ensures the shared library stays
 * loaded for as long as the session object is alive. The destructor order
 * matters: session must be destroyed (calling into the plugin's code one
 * last time) BEFORE the library handle is released — destroying them in the
 * other order would mean the session's destructor runs after the library
 * code has been unloaded, causing a crash.
 */
class radio_dynamic_wrapper : public radio_session
{
public:
  /// Constructs a wrapper from the dynamic library handler and an open radio session.
  /**
   * @param handler_  The dynamic library handle (kept alive for as long as session lives).
   * @param session_  The radio session created from the plugin's factory.
   */
  explicit radio_dynamic_wrapper(handler_ptr handler_, std::unique_ptr<radio_session> session_) noexcept :
    handler(std::move(handler_)), session(std::move(session_))
  {
  }

  /// Default destructor - deletes the session first then the dynamic library handler.

  /// Destroys the session first, then releases the library handle — critical ordering.
  ~radio_dynamic_wrapper() override
  {
    session.reset();
    handler.reset();
  }


  // All radio_session interface methods simply forward to the wrapped plugin session.
  radio_management_plane& get_management_plane() override { return session->get_management_plane(); }
  baseband_gateway&       get_baseband_gateway(unsigned stream_id) override
  {
    return session->get_baseband_gateway(stream_id);
  }
  baseband_gateway_timestamp read_current_time() override { return session->read_current_time(); }
  void                       start(baseband_gateway_timestamp init_time) override { session->start(init_time); }
  void                       stop() override { session->stop(); }


private:
  /// Kept alive to prevent the plugin library from being unloaded prematurely.
  handler_ptr                    handler;
  /// The actual radio session implementation from the plugin.
  std::unique_ptr<radio_session> session;
};

/// Wraps a radio factory and a dynamic library handler.

/**
 * @brief Wraps a radio_factory together with the dynamic library handle that created it.
 *
 * Same lifetime-management purpose as radio_dynamic_wrapper, but for the
 * factory object instead of individual sessions.
 */
class radio_factory_dynamic_wrapper : public radio_factory
{
public:
  /// Constructs from handler and factory.
  /**
   * @param handle_   The dynamic library handle.
   * @param factory_  The factory loaded from the plugin.
   */
  radio_factory_dynamic_wrapper(handler_ptr handle_, std::unique_ptr<radio_factory> factory_) :
    handle(std::move(handle_)), factory(std::move(factory_))
  {
  }

  /// Default destructor - deletes the factory first then the dynamic library handler.

  /// Destroys the factory first, then releases the library handle.
  ~radio_factory_dynamic_wrapper() override
  {
    factory.reset();
    handle.reset();
  }

  // See interface for documentation.

  /// Forwards to the plugin factory's configuration validator.
  const radio_configuration::validator& get_configuration_validator() const override
  {
    return factory->get_configuration_validator();
  }

  // See interface for documentation.

  /**
   * @brief Creates a radio session via the plugin factory and wraps it for safe lifetime management.
   *
   * @param config              The radio configuration.
   * @param async_task_executor Thread executor for asynchronous driver calls.
   * @param notifier            Receives radio event notifications.
   * @return A radio_dynamic_wrapper holding both the session and the library handle.
   */
  std::unique_ptr<radio_session> create(const radio_configuration::radio& config,
                                        task_executor&                    async_task_executor,
                                        radio_event_notifier&             notifier) override
  {
    // Create base radio using the loaded factory.
    std::unique_ptr<radio_session> radio = factory->create(config, async_task_executor, notifier);
    if (radio == nullptr) {
      report_error("Failed to create plugin radio");
    }

    // Wrap the dynamic library handler and the radio instance.

    // Wrap the resulting session together with the (shared) library handle.
    return std::make_unique<radio_dynamic_wrapper>(handle, std::move(radio));
  }


private:
  handler_ptr                    handle;
  std::unique_ptr<radio_factory> factory;
};


} // namespace


/**
 * @brief Loads a radio driver plugin shared library and constructs its factory.
 *
 * Expects the plugin to be named "libocudu_radio_<driver_name>.so" and to
 * export a C++ function with the mangled symbol name corresponding to
 * `ocudu::create_dynamic_radio_factory()` (the mangled name is hardcoded
 * here rather than computed, since the function signature is fixed and known).
 *
 * Loading uses RTLD_NOW (resolve all symbols immediately, catching missing
 * dependencies early), RTLD_DEEPBIND (prefer the plugin's own symbol
 * definitions over the main program's, avoiding symbol collisions with
 * OCUDU's own code), and RTLD_GLOBAL (make the plugin's symbols available to
 * other libraries it may itself load).
 *
 * @param driver_name  The driver name to load (used to construct the
 *                     expected filename).
 * @return The constructed factory wrapped for safe lifetime management, or
 *         nullptr if the library could not be loaded or the expected symbol
 *         was not found.
 */
std::unique_ptr<radio_factory> ocudu::create_plugin_radio_factory(std::string driver_name)
{
  char*       err         = nullptr;
  std::string plugin_name = "libocudu_radio_" + driver_name + ".so";


  void* dl_handle = ::dlopen(plugin_name.c_str(), RTLD_NOW + RTLD_DEEPBIND + RTLD_GLOBAL);
  if (dl_handle == nullptr) {
    err = ::dlerror();
    if (err != nullptr) {
      fmt::print("Failed to load RF plugin {}: {}\n", plugin_name, err);
    }
    return nullptr;
  }

  // Create factory function prototype.

  using create_factory_func = std::unique_ptr<radio_factory>(void);

  // Load symbol.

  // Look up the expected entry-point symbol by its mangled C++ name.
  auto* create_factory =
      reinterpret_cast<create_factory_func*>(::dlsym(dl_handle, "_ZN5ocudu28create_dynamic_radio_factoryEv"));

  // Handle an error loading the symbol.

  if (create_factory == nullptr) {
    err = ::dlerror();
    if (err != nullptr) {
      fmt::print("Error loading symbol {}: {}\n", "create_dynamic_radio_factory", err);
    }
    return nullptr;
  }

  // Create factory.

  // Call the plugin's factory-creation function.
  std::unique_ptr<radio_factory> factory = (*create_factory)();


  if (factory == nullptr) {
    return nullptr;
  }

  // Create shared pointer with deleter.

  // Wrap the dlopen handle in a shared_ptr with a custom deleter (dlclose),
  // so it's released automatically once no longer referenced.
  dynamic_library_deleter deleter;
  handler_ptr             handle(dl_handle, deleter);


  return std::make_unique<radio_factory_dynamic_wrapper>(std::move(handle), std::move(factory));
}
