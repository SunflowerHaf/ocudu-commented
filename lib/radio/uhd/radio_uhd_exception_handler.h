// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_exception_handler.h
 * @brief Converts UHD/Boost C++ exceptions into simple boolean success/failure results.
 *
 * The UHD library (and the Boost libraries it depends on) report errors by
 * throwing C++ exceptions. This is inconvenient in real-time code paths, where
 * exception handling has unpredictable performance overhead and the rest of
 * this codebase generally prefers explicit boolean return values with a
 * retrievable error message.
 *
 * uhd_exception_handler is the bridge: it provides safe_execution(), which
 * wraps any UHD/Boost call in a try-catch block, captures the exception
 * message if one occurs, and returns a plain bool. Every class that talks
 * directly to UHD (radio_uhd_device, radio_uhd_tx_stream, radio_uhd_rx_stream)
 * inherits from this class to get this capability.
 */

#pragma once


#include "fmt/format.h"
#include <functional>
#include <string>


// Suppress compiler warnings coming from the UHD headers themselves (they
// predate some modern C++ warning checks and would otherwise clutter the
// build output with warnings from code we don't control).
#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wall"
#else // __clang__
#pragma GCC diagnostic ignored "-Wsuggest-override"
#endif // __clang__
#pragma GCC diagnostic ignored "-Wextra-semi"
#include <uhd/error.h>
#include <uhd/exception.hpp>
#pragma GCC diagnostic pop


namespace ocudu {


/**
 * @brief Provides exception-safe execution of UHD calls with captured error messages.
 *
 * Inherited by every class that makes direct UHD library calls.
 */
class uhd_exception_handler
{
public:
  /**
   * @brief Manually sets the error message (used when an error is detected
   *        without an exception being thrown, e.g. a validation failure).
   *
   * @param format_str  A fmt-style format string.
   * @param args        Format arguments.
   */
  template <typename S, typename... Args>
  void on_error(const S& format_str, Args&&... args)
  {
    error_message = fmt::format(format_str, std::forward<Args>(args)...);
  }


  /**
   * @brief Executes the given function, catching any UHD/Boost/std exceptions.
   *
   * Clears any previous error message first, then runs the task. If an
   * exception is thrown, the appropriate error message is captured (UHD
   * exceptions provide a descriptive .what(), Boost exceptions provide
   * diagnostic_information(), and generic std::exception falls back to
   * .what() as well; anything else is caught by the catch-all and given a
   * generic message).
   *
   * @param task  A callable taking no arguments and returning void — typically
   *              a lambda wrapping one or more UHD API calls.
   * @return true if the task completed without throwing; false otherwise
   *         (call get_error_message() for details).
   */
  template <typename F>
  bool safe_execution(F task)
  {
    static_assert(std::is_convertible<F, std::function<void()>>::value, "The function signature must be void()");

    // Clears the error message.

    // Clears the error message from any previous call.
    error_message.clear();

    // Try to execute task and catch exception.

    // Try to execute the task and catch any exception type that could surface
    // from a UHD/Boost call.
    try {
      task();
    } catch (const uhd::exception& e) {
      error_message = e.what();
      return false;
    } catch (const boost::exception& e) {
      error_message = boost::diagnostic_information(e);
      return false;
    } catch (const std::exception& e) {
      error_message = e.what();
      return false;
    } catch (...) {
      error_message = "Unrecognized exception caught.";
      return false;
    }


    return is_successful();
  }


  /// Returns true if the most recent safe_execution() call succeeded (no error message set).
  bool               is_successful() const { return error_message.empty(); }

  /// Returns the most recent error message, or an empty string if successful.
  const std::string& get_error_message() const { return error_message; }


private:
  /// The most recent error message, cleared at the start of each safe_execution() call.
  std::string error_message;
};


} // namespace ocudu
