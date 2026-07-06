// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/sdu_window.h  (68 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/circular_map.h"
#include "ocudu/support/ocudu_assert.h"
#include <cstddef>
#include <cstdint>


namespace ocudu {

/// \brief This class provides a container for the Tx/Rx windows holding SDU info objects that are indexed by Sequence
/// Numbers (SN).
///
/// \tparam T               Storage Type.
/// \tparam PREFIXED_LOGGER An implementation of a prefixed_logger<type> for logging.

/// \brief This class provides a container for the Tx/Rx windows holding SDU info objects that are indexed by Sequence
/// Numbers (SN).
///
/// \tparam T               Storage Type.
/// \tparam PREFIXED_LOGGER An implementation of a prefixed_logger<type> for logging.
template <typename T, typename PREFIXED_LOGGER>
class sdu_window
{
public:
  sdu_window(PREFIXED_LOGGER& logger_, size_t size) : logger(logger_), window(size) {}


  T& add_sn(size_t sn)
  {
    if (has_sn(sn)) {
      logger.log_error("sn={} already present in window, overwriting.", sn);
      ocudu_assertion_failure("sn={} already present in window.", sn);
    } else {
      logger.log_debug("Adding sn={} to window.", sn);
    }


    window.overwrite(sn, T());


    return window[sn];
  }


  void remove_sn(size_t sn)
  {
    if (not has_sn(sn)) {
      logger.log_error("Cannot remove sn={} because not contained in the window.", sn);
      ocudu_assertion_failure("Cannot remove sn={} because not contained in the window.", sn);
      return;
    }


    logger.log_debug("Removing sn={} from window", sn);
    window.erase(sn);
  }


  T&       operator[](size_t sn) { return window[sn]; }
  const T& operator[](size_t sn) const { return window[sn]; }


  size_t size() const { return window.size(); }


  bool full() const { return window.full(); }


  bool empty() const { return window.empty(); }


  void clear() { window.clear(); }


  bool has_sn(uint32_t sn) const { return window.contains(sn); }


private:
  PREFIXED_LOGGER&                logger;
  circular_map<uint32_t, T, true> window;
};


} // namespace ocudu
