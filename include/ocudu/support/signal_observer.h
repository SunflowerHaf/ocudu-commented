// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/signal_observer.h  (94 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <functional>
#include <vector>


namespace ocudu {


class signal_observer;

/// This class is a dispatcher for [posix] signals (e.g. SIGTERM,...) to which the signal observer can attach/detach in
/// order to subscribe for signal events.
///
/// The signal dispatcher must outlive all its subscribers, because the signal observer automatically unregister from
/// the signal dispatcher upon destruction.

/// This class is a dispatcher for [posix] signals (e.g. SIGTERM,...) to which the signal observer can attach/detach in
/// order to subscribe for signal events.
///
/// The signal dispatcher must outlive all its subscribers, because the signal observer automatically unregister from
/// the signal dispatcher upon destruction.
class signal_dispatcher
{
public:
  /// \brief Attach a new observer to this signal dispatcher.
  /// \param observer The observer that subscribes for receiving signals.
  /// \brief Attach a new observer to this signal dispatcher.
  /// \param observer The observer that subscribes for receiving signals.
  void attach(signal_observer& observer);
  /// \brief Detach an observer, i.e. end its subscription for receiving signals.
  /// \param observer The observer that unsubscribers from receiving signals.
  /// \brief Detach an observer, i.e. end its subscription for receiving signals.
  /// \param observer The observer that unsubscribers from receiving signals.
  void detach(signal_observer& observer);
  /// \brief Notifies all its attached observers (i.e. subscribers) of the given signal. This function is to be called
  /// from the actual signal source.
  /// \param signal The signal that occured.
  /// \brief Notifies all its attached observers (i.e. subscribers) of the given signal. This function is to be called
  /// from the actual signal source.
  /// \param signal The signal that occured.
  void notify_signal(int signal);


private:
  /// Collection of subscribers attached to this dispatcher.
  /// Collection of subscribers attached to this dispatcher.
  std::vector<signal_observer*> observers;
};


using signal_callback = std::function<void()>;

/// This class is an observer that may be used to subscribe for [posix] signals (e.g. SIGTERM,...) from a signal
/// dispatcher. The dispatcher calls handle_signal to notify the observer of a signal event; the observer then invokes
/// the callback that was set upon construction.
///
/// Upon destruction, the observer automatically unsubscribes from the signal dispatcher.

/// This class is an observer that may be used to subscribe for [posix] signals (e.g. SIGTERM,...) from a signal
/// dispatcher. The dispatcher calls handle_signal to notify the observer of a signal event; the observer then invokes
/// the callback that was set upon construction.
///
/// Upon destruction, the observer automatically unsubscribes from the signal dispatcher.
class signal_observer
{
public:
  /// \brief Creates a signal observer with a given callback and attaches the observer to a signal dispatcher. The
  /// signal dispatcher must outlive the observer due to automatic detach on destruction of the observer.
  /// \param dispatcher_ The signal dispatcher to which this observer shall be attached.
  /// \param callback_ The callback to be invoked on a signal event.
  /// \brief Creates a signal observer with a given callback and attaches the observer to a signal dispatcher. The
  /// signal dispatcher must outlive the observer due to automatic detach on destruction of the observer.
  /// \param dispatcher_ The signal dispatcher to which this observer shall be attached.
  /// \param callback_ The callback to be invoked on a signal event.
  explicit signal_observer(signal_dispatcher& dispatcher_, signal_callback callback_) :
    dispatcher(dispatcher_), callback(std::move(callback_))
  {
    dispatcher.attach(*this);
  }

  /// \brief Automatically unsubscribe from the current_subject (i.e. the signal dispatcher).

  /// \brief Automatically unsubscribe from the current_subject (i.e. the signal dispatcher).
  virtual ~signal_observer() { dispatcher.detach(*this); }

  /// \brief Handles a signal that was dispatched by the signal_dispatcher.
  /// \param signal The signal that occured.

  /// \brief Handles a signal that was dispatched by the signal_dispatcher.
  /// \param signal The signal that occured.
  void handle_signal(int signal) { callback(); }


private:
  /// The signal dispatcher to which this observer is attached.
  /// The signal dispatcher to which this observer is attached.
  signal_dispatcher& dispatcher;
  /// The callback to be invoked on a signal event.
  /// The callback to be invoked on a signal event.
  signal_callback callback;
};


void signal_dispatcher::attach(signal_observer& observer)
{
  observers.push_back(&observer);
}


void signal_dispatcher::detach(signal_observer& observer)
{
  for (auto it = observers.begin(); it != observers.end();) {
    if (*it == &observer) {
      it = observers.erase(it);
      return; // Finish here because observers are unique and attach only once upon their construction
    }
    ++it;
  }
}


void signal_dispatcher::notify_signal(int signal)
{
  for (auto observer : observers) {
    observer->handle_signal(signal);
  }
}


} // namespace ocudu
