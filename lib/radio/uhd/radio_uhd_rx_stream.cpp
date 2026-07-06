// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_rx_stream.cpp
 * @brief Implementation of UHD receive streaming: stream creation, packet assembly, and error reporting.
 */

#include "radio_uhd_rx_stream.h"
#include "ocudu/ocuduvec/zero.h"


using namespace ocudu;

/// Receive timeout in seconds.

/// Timeout for a single UHD recv() call.
static constexpr double RECEIVE_TIMEOUT_S = 0.2f;
/// Set to true for receiving data in a single packet.
/// If true, receive() returns after a single UHD packet rather than filling
/// the requested buffer fully in one internal call (set false here — multi-
/// packet assembly is handled explicitly in the receive() loop below).
static constexpr bool ONE_PACKET = false;


/**
 * @brief Receives a single block of samples from UHD.
 *
 * @param nof_rxd_samples  Output: number of samples received in this call.
 * @param data             Destination buffer.
 * @param offset           Sample offset within data to write at.
 * @param md               Output: UHD receive metadata for this block.
 * @return true if no exception was caught.
 */
bool radio_uhd_rx_stream::receive_block(unsigned&                       nof_rxd_samples,
                                        baseband_gateway_buffer_writer& data,
                                        unsigned                        offset,
                                        uhd::rx_metadata_t&             md)
{
  // Extract number of samples.
  unsigned num_samples = data.get_nof_samples() - offset;

  // Make sure the number of channels is equal.

  ocudu_assert(data.get_nof_channels() == nof_channels, "Number of channels does not match.");

  // Flatten buffers.

  // UHD's API expects an array of raw void* pointers, one per channel.
  static_vector<void*, RADIO_MAX_NOF_CHANNELS> buffs_flat_ptr;
  for (unsigned channel = 0; channel != nof_channels; ++channel) {
    buffs_flat_ptr.emplace_back(reinterpret_cast<void*>(data[channel].subspan(offset, num_samples).data()));
  }


  uhd::rx_streamer::buffs_type buffs_cpp(buffs_flat_ptr.data(), nof_channels);


  return safe_execution([this, buffs_cpp, num_samples, &md, &nof_rxd_samples]() {
    nof_rxd_samples = stream->recv(buffs_cpp, num_samples, md, RECEIVE_TIMEOUT_S, ONE_PACKET);
  });
}


/**
 * @brief Constructor. Opens the UHD rx_streamer for this stream's configured channels.
 *
 * @param usrp        The USRP context.
 * @param description Stream configuration parameters.
 * @param notifier_   Receives radio event notifications.
 */
radio_uhd_rx_stream::radio_uhd_rx_stream(uhd::usrp::multi_usrp::sptr& usrp,
                                         const stream_description&    description,
                                         radio_event_notifier&        notifier_) :
  id(description.id), srate_Hz(description.srate_Hz), notifier(notifier_)
{
  ocudu_assert(std::isnormal(srate_Hz) && (srate_Hz > 0.0), "Invalid sampling rate {}.", srate_Hz);

  // Build stream arguments.

  // CPU-side format is always sc16 (16-bit signed complex); the
  // over-the-wire format may differ for bandwidth/precision trade-offs.
  uhd::stream_args_t stream_args = {};
  stream_args.cpu_format         = "sc16";
  switch (description.otw_format) {
    case radio_configuration::over_the_wire_format::DEFAULT:
    case radio_configuration::over_the_wire_format::SC16:
      stream_args.otw_format = "sc16";
      break;
    case radio_configuration::over_the_wire_format::SC12:
      stream_args.otw_format = "sc12";
      break;
    case radio_configuration::over_the_wire_format::SC8:
      stream_args.otw_format = "sc8";
      break;
  }
  stream_args.args     = description.args;
  stream_args.channels = description.ports;


  if (!safe_execution([this, usrp, &stream_args]() {
        stream          = usrp->get_rx_stream(stream_args);
        max_packet_size = stream->get_max_num_samps();
        nof_channels    = stream->get_num_channels();
      })) {
    return;
  }


  is_init_successful = true;
}


/**
 * @brief Issues a UHD command to begin continuous streaming, at the given time.
 *
 * Uses UHD's STREAM_MODE_START_CONTINUOUS — once started, the USRP
 * continuously delivers samples until explicitly stopped (rather than a
 * one-shot capture of a fixed sample count).
 *
 * @param time_spec  The intended start time. If it equals the zero time spec
 *                   (uhd::time_spec_t() default), streaming begins immediately
 *                   ("stream_now") rather than at a scheduled future timestamp.
 * @return true if successfully started (false if construction had already
 *         failed, or an exception occurred issuing the command).
 */
bool radio_uhd_rx_stream::start(const uhd::time_spec_t& time_spec)
{
  if (!is_init_successful) {
    return false;
  }


  stop_control.reset();


  if (!safe_execution([this, &time_spec]() {
        uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
        stream_cmd.time_spec  = time_spec;
        stream_cmd.stream_now = (time_spec.get_real_secs() == uhd::time_spec_t());


        stream->issue_stream_cmd(stream_cmd);
      })) {
    fmt::println("Error: failed to start receive stream {}. {}.", id, get_error_message().c_str());
  }


  return true;
}


/**
 * @brief Fills the given buffer with received samples, calling UHD's recv()
 *        as many times as needed to fill it completely.
 *
 * Handles several edge cases:
 *   - If a stop has been requested, returns immediately with a zero-filled
 *     buffer rather than attempting to receive (avoids blocking shutdown).
 *   - Reports radio events (LATE, OVERFLOW, OTHER) as they're encountered.
 *   - Tracks consecutive timeouts and aborts after 10, to avoid hanging
 *     indefinitely if the radio has stopped responding.
 *
 * @param buffs  The destination buffer to fill, one sub-buffer per channel.
 * @return Metadata containing the timestamp of the first received sample.
 *         An empty (default-constructed) metadata is returned on failure.
 */
baseband_gateway_receiver::metadata radio_uhd_rx_stream::receive(baseband_gateway_buffer_writer& buffs)
{
  baseband_gateway_receiver::metadata ret = {};
  uhd::rx_metadata_t                  md;


  auto token = stop_control.get_token();
  if (OCUDU_UNLIKELY(token.is_stop_requested())) {
    // Stop has been requested — return zero-filled samples rather than
    // attempting to read from a stream that's about to close.
    for (unsigned i = 0, e = buffs.get_nof_channels(); i != e; ++i) {
      ocuduvec::zero(buffs[i]);
    }
    ret.ts = md.time_spec.to_ticks(srate_Hz);
    return ret;
  }


  unsigned nsamples            = buffs[0].size();
  unsigned rxd_samples_total   = 0;
  unsigned timeout_trial_count = 0;

  // Receive stream in multiple blocks.

  // Receive in a loop, issuing multiple UHD packets as needed since each
  // recv() call may deliver fewer samples than requested (limited by
  // max_packet_size).
  while (rxd_samples_total < nsamples) {
    unsigned rxd_samples = 0;
    if (!receive_block(rxd_samples, buffs, rxd_samples_total, md)) {
      fmt::println("Error: failed receiving packet. {}.", get_error_message().c_str());
      return {};
    }

    // Save timespec for first block only if the last timestamp is unknown.

    // Record the timestamp only from the first block — this represents the
    // capture time of the very first sample in the buffer.
    if (rxd_samples_total == 0) {
      ret.ts = md.time_spec.to_ticks(srate_Hz);
    }

    // Increase the total amount of received samples.

    rxd_samples_total += rxd_samples;

    // Prepare notification event.

    radio_event_notifier::event_description event = {.stream_id  = id,
                                                     .channel_id = std::nullopt,
                                                     .source     = radio_event_source::RECEIVE,
                                                     .type       = radio_event_type::UNDEFINED,
                                                     .timestamp  = std::nullopt};

    // Handle error.

    switch (md.error_code) {
      case uhd::rx_metadata_t::ERROR_CODE_TIMEOUT:
        // Count consecutive timeouts; give up after too many in a row
        // (suggests the radio has stopped responding, rather than a
        // transient delay).
        ++timeout_trial_count;
        if (timeout_trial_count >= 10) {
          fmt::println("Error: exceeded maximum number of timed out receive calls.");
          return ret;
        }
        break;
      case uhd::rx_metadata_t::ERROR_CODE_NONE:
        // Ignored.
        // Normal — no error.
        break;
      case uhd::rx_metadata_t::ERROR_CODE_LATE_COMMAND:
        // A previously issued stream command (e.g. start) arrived too late.
        event.type = radio_event_type::LATE;
        break;
      case uhd::rx_metadata_t::ERROR_CODE_OVERFLOW:
        // The USRP's internal Rx buffer overflowed — some samples were lost.
        event.type = radio_event_type::OVERFLOW;
        break;
      case uhd::rx_metadata_t::ERROR_CODE_BROKEN_CHAIN:
      case uhd::rx_metadata_t::ERROR_CODE_ALIGNMENT:
      case uhd::rx_metadata_t::ERROR_CODE_BAD_PACKET:
        // Less common diagnostic errors, reported generically.
        event.type = radio_event_type::OTHER;
        break;
    }

    // Notify if the event type was set.

    if (event.type != radio_event_type::UNDEFINED) {
      notifier.on_radio_rt_event(event);
    }
  }

  // If it reaches here, there is no error.

  // Completed without unrecoverable error.
  return ret;
}


/**
 * @brief Stops the receive stream.
 *
 * Signals stop_control first (so any in-progress receive() returns promptly
 * with zeroed data rather than blocking), then issues UHD's stop command.
 *
 * @return true if successfully stopped; false if a UHD exception occurred.
 */
bool radio_uhd_rx_stream::stop()
{
  stop_control.stop();

  // Try to stop the stream.

  if (!safe_execution([this]() {
        uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS);
        stream_cmd.time_spec  = uhd::time_spec_t();
        stream_cmd.stream_now = true;


        stream->issue_stream_cmd(stream_cmd);
      })) {
    fmt::println("Error: failed to stop stream {}. {}.", id, get_error_message().c_str());
    return false;
  }


  return true;
}
