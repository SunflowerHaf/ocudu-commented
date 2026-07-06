// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_tx_stream_fsm.h
 * @brief State machine governing the transmit stream's burst lifecycle.
 *
 * USRPs transmit in "bursts" — UHD requires each contiguous block of samples
 * to be explicitly bracketed with start-of-burst and end-of-burst flags.
 * This matters because:
 *
 *   - When using discontinuous transmission mode (the Tx chain powers
 *     off between transmissions to save power and reduce interference),
 *     each transmission must be a distinct burst.
 *   - When a real-time failure occurs (a late sample or Tx underflow), the
 *     current burst must be properly closed before a new one can begin —
 *     simply continuing to send samples without acknowledging the error
 *     would leave the USRP's internal state inconsistent.
 *
 * This finite state machine tracks exactly where in the burst lifecycle the
 * stream currently is, and decides — for each call to transmit() — what
 * metadata flags (start_of_burst, end_of_burst, time_spec) should be set,
 * and whether the block should even be sent to UHD at all.
 */

#pragma once


#include <condition_variable>
#include <mutex>


#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wall"
#else // __clang__
#pragma GCC diagnostic ignored "-Wsuggest-override"
#endif // __clang__
#pragma GCC diagnostic ignored "-Wextra-semi"
#include <uhd/types/metadata.hpp>
#include <uhd/types/time_spec.hpp>
#pragma GCC diagnostic pop


namespace ocudu {

/// Radio UHD transmit stream finite state machine.

/**
 * @brief State machine for managing UHD transmit burst start/end signalling.
 *
 * Thread-safe: protected internally by a mutex since transmit() can be
 * called from the Tx processing thread while async events (burst ACKs,
 * underflow notifications) arrive from the UHD async message thread.
 */
class radio_uhd_tx_stream_fsm
{
  /// Wait for end-of-burst acknowledgement timeout in seconds.
  /// Maximum time to wait for UHD's end-of-burst acknowledgement before giving up.
  static constexpr double WAIT_EOB_ACK_TIMEOUT_S = 0.01;

  /// Defines the Tx stream internal states.

  /**
   * @brief The possible states of the Tx burst lifecycle.
   */
  enum class states {
    /// Indicates the stream was not initialized successfully.
    /// Stream construction failed or has not yet been initialised.
    UNINITIALIZED = 0,
    /// Indicates the stream is ready to start burst.
    /// Ready to begin a new burst on the next transmit() call.
    START_BURST,
    /// Indicates the stream is transmitting a burst.
    /// Currently mid-burst — samples are flowing continuously.
    IN_BURST,
    /// Indicates an end-of-burst must be transmitted and abort any transmission.
    /// A real-time failure occurred mid-burst; the next transmit() call must
    /// signal end-of-burst to UHD and abort the current transmission.
    END_OF_BURST,
    /// Indicates wait for end-of-burst acknowledgement.
    /// End-of-burst has been signalled to UHD; waiting for UHD's
    /// acknowledgement (EVENT_CODE_BURST_ACK) before starting a new burst.
    WAIT_END_OF_BURST
  };

  /// Indicates the current state.

  /// The current state.
  states state;
  /// Protects the class concurrent access.
  /// Protects concurrent access from the Tx thread and the async event thread.
  mutable std::mutex mutex;
  /// The deadline by which the end-of-burst ACK must arrive, after which the
  /// FSM gives up waiting and proceeds as if it had been acknowledged.
  uhd::time_spec_t   wait_eob_timeout = uhd::time_spec_t();


public:
  /// \brief Notifies that the transmit stream has been initialized successfully.
  /**
   * @brief Called once the Tx stream has been successfully created.
   *
   * Transitions from UNINITIALIZED to START_BURST, allowing transmissions to begin.
   */
  void init_successful()
  {
    std::scoped_lock lock(mutex);
    state = states::START_BURST;
  }

  /// \brief Notifies a late or an underflow event.
  /// \remark Transitions state end of burst if it is in a burst.
  /// \param[in] time_spec Indicates the time the underflow event occurred.

  /**
   * @brief Called when UHD reports a late sample or Tx underflow event.
   *
   * If currently mid-burst, transitions to END_OF_BURST so the next
   * transmit() call will properly close out the burst rather than continuing
   * to send into an already-broken stream state.
   *
   * @param time_spec  The UHD timestamp at which the event occurred — used to
   *                   compute the deadline for the end-of-burst acknowledgement.
   */
  void async_event_late_underflow(const uhd::time_spec_t& time_spec)
  {
    std::scoped_lock lock(mutex);
    if (state == states::IN_BURST) {
      state            = states::END_OF_BURST;
      wait_eob_timeout = time_spec;
      wait_eob_timeout += WAIT_EOB_ACK_TIMEOUT_S;
    }
  }

  /// \brief Notifies an end-of-burst acknowledgement.
  /// \remark Transitions state to start burst if it is waiting for the end-of-burst.

  /**
   * @brief Called when UHD acknowledges the end of a burst.
   *
   * If currently waiting for this acknowledgement, transitions back to
   * START_BURST, ready to begin a fresh transmission.
   */
  void async_event_end_of_burst_ack()
  {
    std::scoped_lock lock(mutex);
    if (state == states::WAIT_END_OF_BURST) {
      state = states::START_BURST;
    }
  }

  /// \brief Handles a new transmission.
  /// \param[out] metadata     Destination of the required metadata.
  /// \param[in]  time_spec    Transmission time of the first sample.
  /// \param[in]  is_empty     Empty buffer flag.
  /// \param[in]  tail_padding Tail padding flag, indicating the last transmission in the burst.
  /// \return True if the block shall be transmitted. False if the block shall be ignored.

  /**
   * @brief Decides what burst metadata to apply for the current transmit() call.
   *
   * This is the core decision function, called once per transmit() invocation.
   * Depending on the current state, it sets the appropriate UHD metadata
   * flags (has_time_spec, start_of_burst, end_of_burst, time_spec) and
   * returns whether the block should actually be sent to UHD at all.
   *
   * State transition summary:
   *   WAIT_END_OF_BURST → if the wait timeout has elapsed, falls through to
   *                        START_BURST handling (gives up waiting for the ACK
   *                        and proceeds anyway, to avoid stalling indefinitely).
   *   START_BURST        → starts a new burst (sets start_of_burst), unless
   *                        the block is empty (skipped entirely).
   *   IN_BURST            → continues the burst; if the block is empty or this
   *                        is tail padding, signals end_of_burst and returns
   *                        to START_BURST without waiting for an ACK (since
   *                        this is a normal/planned end, not an error).
   *   END_OF_BURST        → forced end due to a real-time failure: signals
   *                        end_of_burst and transitions to WAIT_END_OF_BURST.
   *   UNINITIALIZED        → always ignores the transmission.
   *
   * @param metadata      Output: the UHD transmit metadata to populate.
   * @param time_spec     The intended transmission timestamp for this block.
   * @param is_empty      True if the block contains no actual data (e.g. a
   *                      gap between bursts in discontinuous mode).
   * @param tail_padding  True if this is the last block of an intentionally
   *                      ending transmission (planned end, not an error).
   * @return true if the block should be sent to UHD; false if it should be skipped.
   */
  bool on_transmit(uhd::tx_metadata_t& metadata, const uhd::time_spec_t& time_spec, bool is_empty, bool tail_padding)
  {
    std::scoped_lock lock(mutex);


    switch (state) {
      case states::WAIT_END_OF_BURST:
        // Do nothing if the wait for end-of-burst timeout has not expired.
        // Still within the wait window — do nothing, the ACK may still arrive.
        if (wait_eob_timeout.get_real_secs() >= time_spec.get_real_secs()) {
          return false;
        }
        // Otherwise go into start burst state and handle the state.
        // Timeout elapsed — give up waiting and fall through to START_BURST handling.
        state = states::START_BURST;
      case states::START_BURST:
        // Set start of burst flag and time spec.
        if (!is_empty) {
          metadata.has_time_spec  = true;
          metadata.start_of_burst = true;
          metadata.end_of_burst   = tail_padding;
          metadata.time_spec      = time_spec;

          // Transition to in-burst.

          // If this single block isn't already the entire (padded) burst,
          // transition into IN_BURST for subsequent calls.
          if (!tail_padding) {
            state = states::IN_BURST;
          }


          return true;
        }
        // Empty block while waiting to start — nothing to transmit.
        return false;
      case states::IN_BURST:
        if (is_empty || tail_padding) {
          // Signal end of burst to UHD.
          // Planned end of burst (not an error) — signal end_of_burst and
          // go straight back to START_BURST without waiting for an ACK.
          metadata.end_of_burst = true;

          // Transition to start burst without waiting for the EOB ACK.
          state = states::START_BURST;
        }
        break;
      case states::END_OF_BURST:
        // Flag end-of-burst.
        // Forced end due to a real-time failure — signal end_of_burst and
        // wait for UHD's acknowledgement before allowing a new burst.
        metadata.end_of_burst = true;
        state                 = states::WAIT_END_OF_BURST;
        if (wait_eob_timeout == uhd::time_spec_t()) {
          wait_eob_timeout = time_spec;
          wait_eob_timeout += WAIT_EOB_ACK_TIMEOUT_S;
        }
        break;
      case states::UNINITIALIZED:
        // Ignore transmission.
        // Stream isn't ready — always ignore.
        return false;
    }

    // Transmission shall not be ignored.

    return true;
  }

  /// Returns true if an end of burst is required on the event of stopping the UHD radio.

  /**
   * @brief Returns whether an end-of-burst must be sent when stopping the radio.
   *
   * If currently mid-burst when stop() is called, UHD requires an explicit
   * end-of-burst signal to cleanly terminate — otherwise the USRP's internal
   * state may be left inconsistent for the next session.
   *
   * @return true if currently IN_BURST.
   */
  bool on_stop() const { return (state == states::IN_BURST); }
};


} // namespace ocudu
