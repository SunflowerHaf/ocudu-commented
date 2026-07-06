// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/prach_context_repository.h  (316 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#pragma once


#include "context_repository_helpers.h"
#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/adt/expected.h"
#include "ocudu/adt/mpmc_queue.h"
#include "ocudu/adt/unique_function.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ocuduvec/copy.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/phy/support/prach_buffer.h"
#include "ocudu/phy/support/prach_buffer_context.h"
#include "ocudu/phy/support/shared_prach_buffer.h"
#include "ocudu/ran/prach/prach_constants.h"
#include "ocudu/ran/prach/prach_frequency_mapping.h"
#include "ocudu/ran/prach/prach_preamble_information.h"
#include <mutex>
#include <numeric>
#include <optional>


namespace ocudu {
namespace ofh {

///  PRACH context.

///  PRACH context.
class prach_context
{
  /// PRACH buffer writer statistics.
  /// PRACH buffer writer statistics.
  struct prach_buffer_writer_stats {
    prach_buffer_writer_stats(unsigned nof_ports, size_t nof_res) :
      re_written(nof_ports, bounded_bitset<prach_constants::LONG_SEQUENCE_LENGTH>(nof_res))
    {
    }

    /// Number of REs written indexed by port.

    /// Number of REs written indexed by port.
    static_vector<bounded_bitset<prach_constants::LONG_SEQUENCE_LENGTH>, MAX_NOF_SUPPORTED_EAXC> re_written;

    /// Returns true when all the REs for the current symbol have been written.

    /// Returns true when all the REs for the current symbol have been written.
    bool have_all_res_been_written() const
    {
      return std::all_of(re_written.begin(), re_written.end(), [&](const auto& port) { return port.all(); });
    }
  };


public:
  struct prach_context_information {
    /// PRACH buffer context.
    /// PRACH buffer context.
    prach_buffer_context context;
    /// PRACH buffer.
    /// PRACH buffer.
    shared_prach_buffer buffer;
  };

  /// Default constructor.

  /// Default constructor.
  prach_context() = default;

  /// Constructs an uplink PRACH context with the given PRACH buffer and PRACH buffer context.

  /// Constructs an uplink PRACH context with the given PRACH buffer and PRACH buffer context.
  prach_context(const prach_buffer_context& context,
                shared_prach_buffer         buffer,
                std::optional<unsigned>     start_symbol_) :
    context_info({.context = context, .buffer = std::move(buffer)})
  {
    ocudu_assert(context.nof_fd_occasions == 1, "Only supporting one frequency domain occasion");
    ocudu_assert(is_short_preamble(context.format) ||
                     (is_long_preamble(context.format) && context.nof_td_occasions == 1),
                 "Only supporting one time domain occasion for long preamble format");

    // Get preamble information.

    // Get preamble information.
    preamble_info =
        is_long_preamble(context.format)
            ? get_prach_preamble_long_info(context.format)
            : get_prach_preamble_short_info(context.format, to_ra_subcarrier_spacing(context.pusch_scs), true);


    freq_mapping_info = prach_frequency_mapping_get(preamble_info.scs, context.pusch_scs);


    nof_symbols  = preamble_info.nof_symbols;
    start_symbol = start_symbol_.value_or(context_info.context.start_symbol);

    // Initialize statistics.

    // Initialize statistics.
    for (unsigned i = 0; i != nof_symbols; ++i) {
      buffer_stats.emplace_back(context_info.buffer->get_max_nof_ports(), preamble_info.sequence_length);
    }
  }


  prach_context(const prach_context& other)
  {
    context_info.context = other.context_info.context;
    context_info.buffer  = other.context_info.buffer.clone();
    buffer_stats         = other.buffer_stats;
    preamble_info        = other.preamble_info;
    freq_mapping_info    = other.freq_mapping_info;
    nof_symbols          = other.nof_symbols;
    start_symbol         = other.start_symbol;
  }


  prach_context& operator=(const prach_context& other)
  {
    context_info.context = other.context_info.context;
    context_info.buffer  = other.context_info.buffer.clone();
    buffer_stats         = other.buffer_stats;
    preamble_info        = other.preamble_info;
    freq_mapping_info    = other.freq_mapping_info;
    nof_symbols          = other.nof_symbols;
    start_symbol         = other.start_symbol;


    return *this;
  }

  /// Returns true if this context is empty, otherwise false.

  /// Returns true if this context is empty, otherwise false.
  bool empty() const { return context_info.buffer == nullptr; }

  /// Returns the PRACH buffer context.

  /// Returns the PRACH buffer context.
  const prach_buffer_context& get_context() const { return context_info.context; }

  /// Returns the number of REs of one PRACH repetition or zero if no PRACH buffer is associated with this context.

  /// Returns the number of REs of one PRACH repetition or zero if no PRACH buffer is associated with this context.
  unsigned get_prach_nof_re() const { return empty() ? 0U : preamble_info.sequence_length; }

  /// Returns the offset to the first resource element.

  /// Returns the offset to the first resource element.
  unsigned get_prach_offset_to_first_re() const { return freq_mapping_info.k_bar; }

  /// Gets the maximum number of ports supported in PRACH buffer.

  /// Gets the maximum number of ports supported in PRACH buffer.
  unsigned get_max_nof_ports() const { return empty() ? 0U : context_info.buffer->get_max_nof_ports(); }

  /// Returns a span of bitmaps that indicate the REs that have been written for the given symbol. Each element of the
  /// span corresponds to a port.

  /// Returns a span of bitmaps that indicate the REs that have been written for the given symbol. Each element of the
  /// span corresponds to a port.
  span<const bounded_bitset<prach_constants::LONG_SEQUENCE_LENGTH>> get_symbol_re_written(unsigned symbol) const
  {
    ocudu_assert(symbol < nof_symbols, "Invalid symbol index");
    return buffer_stats[symbol].re_written;
  }

  /// Writes the given IQ buffer corresponding to the given symbol and port.

  /// Writes the given IQ buffer corresponding to the given symbol and port.
  void write_iq(unsigned port, unsigned symbol, unsigned re_start, span<const cbf16_t> iq_buffer)
  {
    if (is_long_preamble(context_info.context.format)) {
      // Some RUs always set PRACH symbolId to 0 when long format is used ignoring the value indicated in C-Plane.
      // Some RUs always set PRACH symbolId to 0 when long format is used ignoring the value indicated in C-Plane.
      if (symbol >= start_symbol) {
        symbol -= start_symbol;
      }
    } else {
      symbol -= start_symbol;
    }


    ocudu_assert(context_info.buffer, "No valid PRACH buffer in the context");
    ocudu_assert(symbol < nof_symbols, "Invalid symbol index");

    // Skip writing if the given port does not fit in the PRACH buffer.

    // Skip writing if the given port does not fit in the PRACH buffer.
    if (port >= context_info.buffer->get_max_nof_ports()) {
      return;
    }

    // Update the buffer.

    // Update the buffer.
    span<cbf16_t> prach_out_buffer = context_info.buffer->get_symbol(
        port, context_info.context.nof_fd_occasions - 1, context_info.context.nof_td_occasions - 1, symbol);


    ocudu_assert(prach_out_buffer.last(prach_out_buffer.size() - re_start).size() >= iq_buffer.size(),
                 "Invalid IQ data buffer size to copy as it does not fit into the PRACH buffer");


    ocuduvec::copy(prach_out_buffer.subspan(re_start, iq_buffer.size()), iq_buffer);

    // Update statistics.

    // Update statistics.
    buffer_stats[symbol].re_written[port].fill(re_start, re_start + iq_buffer.size());
  }

  /// Tries to get a complete PRACH buffer. A PRACH buffer is considered completed when all the PRBs for all the ports
  /// have been written.

  /// Tries to get a complete PRACH buffer. A PRACH buffer is considered completed when all the PRBs for all the ports
  /// have been written.
  expected<prach_context_information> try_getting_complete_prach_buffer()
  {
    if (!context_info.buffer) {
      return make_unexpected(default_error_t{});
    }


    if (!std::all_of(buffer_stats.begin(), buffer_stats.end(), [&](const auto& symbol) {
          return symbol.have_all_res_been_written();
        })) {
      return make_unexpected(default_error_t{});
    }


    return {{context_info.context, std::move(context_info.buffer)}};
  }

  /// Returns the information of this PRACH context.

  /// Returns the information of this PRACH context.
  prach_context_information pop_context_information() { return {context_info.context, std::move(context_info.buffer)}; }


private:
  /// PRACH context information
  /// PRACH context information
  prach_context_information context_info;
  /// Statistic of written data.
  /// Statistic of written data.
  static_vector<prach_buffer_writer_stats, prach_constants::SHORT_SEQUENCE_MAX_NOF_SYMBOLS> buffer_stats;
  /// Preamble info of the PRACH associated with the stored context.
  /// Preamble info of the PRACH associated with the stored context.
  prach_preamble_information preamble_info;
  /// Stored PRACH frequency mapping.
  /// Stored PRACH frequency mapping.
  prach_frequency_mapping_information freq_mapping_info;
  /// Number of OFDM symbols used by the stored PRACH.
  /// Number of OFDM symbols used by the stored PRACH.
  unsigned nof_symbols;
  /// OFDM symbol index within the slot marking the start of PRACH preamble after the cyclic prefix.
  /// OFDM symbol index within the slot marking the start of PRACH preamble after the cyclic prefix.
  unsigned start_symbol;
};

/// PRACH context repository.

/// PRACH context repository.
class prach_context_repository
{
  using queue_type =
      concurrent_queue<unique_task, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;


  queue_type                 pending_context_to_add;
  std::vector<prach_context> buffer;
  //: TODO: make this lock free
  //: TODO: make this lock free
  mutable std::mutex mutex;

  /// Returns the entry of the repository for the given slot.

  /// Returns the entry of the repository for the given slot.
  prach_context& entry(slot_point slot)
  {
    unsigned index = calculate_repository_index(slot, buffer.size());
    return buffer[index];
  }

  /// Returns the entry of the repository for the given slot.

  /// Returns the entry of the repository for the given slot.
  const prach_context& entry(slot_point slot) const
  {
    unsigned index = calculate_repository_index(slot, buffer.size());
    return buffer[index];
  }


public:
  explicit prach_context_repository(unsigned size_) : pending_context_to_add(size_), buffer(size_) {}

  /// Adds the given entry to the repository at slot.

  /// Adds the given entry to the repository at slot.
  void add(const prach_buffer_context& context,
           shared_prach_buffer         buffer_,
           ocudulog::basic_logger&     logger,
           std::optional<unsigned>     start_symbol)
  {
    if (!pending_context_to_add.try_push([context, prach_buff = std::move(buffer_), start_symbol, this]() mutable {
          std::lock_guard<std::mutex> lock(mutex);
          entry(context.slot) = prach_context(context, std::move(prach_buff), start_symbol);
        })) {
      logger.warning("Failed to enqueue task to add the uplink context to the repository");
    }
  }

  /// Process the enqueued contexts to the repository.

  /// Process the enqueued contexts to the repository.
  void process_pending_contexts()
  {
    unique_task task;
    while (pending_context_to_add.try_pop(task)) {
      task();
    }
  }

  /// Function to write the uplink PRACH buffer.

  /// Function to write the uplink PRACH buffer.
  void write_iq(slot_point slot, unsigned port, unsigned symbol, unsigned re_start, span<const cbf16_t> iq_buffer)
  {
    std::lock_guard<std::mutex> lock(mutex);
    entry(slot).write_iq(port, symbol, re_start, iq_buffer);
  }

  /// Returns the entry of the repository for the given slot.

  /// Returns the entry of the repository for the given slot.
  prach_context get(slot_point slot) const
  {
    std::lock_guard<std::mutex> lock(mutex);
    return entry(slot);
  }

  /// \brief Tries to pop a complete PRACH buffer from the repository.
  ///
  /// A PRACH buffer is considered completed when all the PRBs for all the ports have been written. If the pop is
  /// successful it clears the entry of the repository for that slot.

  /// \brief Tries to pop a complete PRACH buffer from the repository.
  ///
  /// A PRACH buffer is considered completed when all the PRBs for all the ports have been written. If the pop is
  /// successful it clears the entry of the repository for that slot.
  expected<prach_context::prach_context_information> try_popping_complete_prach_buffer(slot_point slot)
  {
    std::lock_guard<std::mutex> lock(mutex);
    auto                        result = entry(slot).try_getting_complete_prach_buffer();

    // Clear the entry if the pop was a success.

    // Clear the entry if the pop was a success.
    if (result) {
      entry(slot) = {};
    }


    return result;
  }

  /// Pops a PRACH buffer from the repository.

  /// Pops a PRACH buffer from the repository.
  expected<prach_context::prach_context_information> pop_prach_buffer(slot_point slot)
  {
    std::lock_guard<std::mutex> lock(mutex);
    auto&                       context = entry(slot);


    if (context.empty()) {
      return make_unexpected(default_error_t());
    }


    auto result = context.pop_context_information();
    context     = {};


    return result;
  }

  /// Clears the given slot entry.

  /// Clears the given slot entry.
  void clear(slot_point slot)
  {
    std::lock_guard<std::mutex> lock(mutex);
    entry(slot) = {};
  }

  /// Clears the whole repository.

  /// Clears the whole repository.
  void clear()
  {
    for (auto& entry : buffer) {
      entry = {};
    }
  }
};


} // namespace ofh
} // namespace ocudu
