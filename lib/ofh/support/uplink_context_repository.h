// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/uplink_context_repository.h  (252 lines)
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
#include "ocudu/adt/expected.h"
#include "ocudu/adt/mpmc_queue.h"
#include "ocudu/adt/unique_function.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ocuduvec/copy.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/phy/support/resource_grid.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/phy/support/resource_grid_reader.h"
#include "ocudu/phy/support/resource_grid_writer.h"
#include "ocudu/phy/support/shared_resource_grid.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/resource_allocation/ofdm_symbol_range.h"
#include "ocudu/ran/resource_block.h"
#include <mutex>


namespace ocudu {
namespace ofh {

/// Uplink context.

/// Uplink context.
class uplink_context
{
public:
  /// Information related to the resource grid stored in the uplink context.
  /// Information related to the resource grid stored in the uplink context.
  struct uplink_context_resource_grid_info {
    resource_grid_context context;
    shared_resource_grid  grid;
  };

  /// Default constructor.

  /// Default constructor.
  uplink_context() = default;


  uplink_context copy() const
  {
    uplink_context context;
    context.symbol       = symbol;
    context.grid.context = grid.context;
    context.grid.grid    = grid.grid.copy();
    context.re_written   = re_written;
    return context;
  }

  /// Constructs an uplink slot context with the given resource grid and resource grid context.

  /// Constructs an uplink slot context with the given resource grid and resource grid context.
  uplink_context(unsigned symbol_, const resource_grid_context& context_, const shared_resource_grid& grid_) :
    symbol(symbol_), grid({context_, grid_.copy()})
  {
    const resource_grid_reader& reader = grid.grid->get_reader();


    re_written = static_vector<bounded_bitset<MAX_NOF_SUBCARRIERS>, MAX_NOF_SUPPORTED_EAXC>(
        reader.get_nof_ports(), bounded_bitset<MAX_NOF_SUBCARRIERS>(size_t(reader.get_nof_subc())));
  }

  /// Returns true if this context is empty, otherwise false.

  /// Returns true if this context is empty, otherwise false.
  bool empty() const { return !grid.grid.is_valid(); }

  /// Returns the number of PRBs of the context grid or zero if no grid was configured for this context.

  /// Returns the number of PRBs of the context grid or zero if no grid was configured for this context.
  unsigned get_grid_nof_prbs() const
  {
    return (grid.grid) ? (grid.grid.get_reader().get_nof_subc() / NOF_SUBCARRIERS_PER_RB) : 0U;
  }

  /// Returns the resource grid context.

  /// Returns the resource grid context.
  const resource_grid_context& get_grid_context() const { return grid.context; }

  /// Returns a span of bitmaps that indicate the REs that have been written for the given symbol. Each element of the
  /// span corresponds to a port.

  /// Returns a span of bitmaps that indicate the REs that have been written for the given symbol. Each element of the
  /// span corresponds to a port.
  span<const bounded_bitset<MAX_NOF_SUBCARRIERS>> get_re_written_mask() const { return re_written; }

  /// Writes the given RE IQ buffer into the port and start RE.

  /// Writes the given RE IQ buffer into the port and start RE.
  void write_grid(unsigned port, unsigned start_re, span<const cbf16_t> re_iq_buffer)
  {
    ocudu_assert(grid.grid, "Invalid resource grid");
    resource_grid_writer& writer = grid.grid->get_writer();

    // Skip writing if the given port does not fit in the grid.

    // Skip writing if the given port does not fit in the grid.
    if (port >= writer.get_nof_ports()) {
      return;
    }
    span<cbf16_t> grid_view = grid.grid->get_writer().get_view(port, symbol).subspan(start_re, re_iq_buffer.size());
    ocuduvec::copy(grid_view, re_iq_buffer);
    re_written[port].fill(start_re, start_re + re_iq_buffer.size());
  }

  /// Tries to get a complete resource grid. A resource grid is considered completed when all the PRBs for all the ports
  /// have been written.

  /// Tries to get a complete resource grid. A resource grid is considered completed when all the PRBs for all the ports
  /// have been written.
  expected<uplink_context_resource_grid_info> try_getting_complete_resource_grid() const
  {
    if (!grid.grid) {
      return make_unexpected(default_error_t{});
    }


    if (!have_all_prbs_been_written()) {
      return make_unexpected(default_error_t{});
    }


    return uplink_context_resource_grid_info{grid.context, grid.grid.copy()};
  }

  /// Returns the context grid information.

  /// Returns the context grid information.
  const uplink_context_resource_grid_info& get_uplink_context_resource_grid_info() const { return grid; }

  /// Gets the context grid information and clears it.

  /// Gets the context grid information and clears it.
  uplink_context_resource_grid_info pop_uplink_context_resource_grid_info() { return std::move(grid); }


private:
  /// Returns true when all the REs for the current symbol have been written.
  /// Returns true when all the REs for the current symbol have been written.
  bool have_all_prbs_been_written() const
  {
    return std::all_of(
        re_written.begin(), re_written.end(), [](const auto& port_re_written) { return port_re_written.all(); });
  }


private:
  unsigned                                                                   symbol;
  uplink_context_resource_grid_info                                          grid;
  static_vector<bounded_bitset<MAX_NOF_SUBCARRIERS>, MAX_NOF_SUPPORTED_EAXC> re_written;
};

/// Uplink context repository.

/// Uplink context repository.
class uplink_context_repository
{
  using queue_type =
      concurrent_queue<unique_task, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;


  queue_type                                                  pending_context_to_add;
  std::vector<std::array<uplink_context, MAX_NSYMB_PER_SLOT>> buffer;
  //: TODO: make this lock free
  //: TODO: make this lock free
  mutable std::mutex mutex;

  /// Returns the entry of the repository for the given slot and symbol.

  /// Returns the entry of the repository for the given slot and symbol.
  uplink_context& entry(slot_point slot, unsigned symbol)
  {
    ocudu_assert(symbol < MAX_NSYMB_PER_SLOT, "Invalid symbol index '{}'", symbol);


    unsigned index = calculate_repository_index(slot, buffer.size());
    return buffer[index][symbol];
  }

  /// Returns the entry of the repository for the given slot and symbol.

  /// Returns the entry of the repository for the given slot and symbol.
  const uplink_context& entry(slot_point slot, unsigned symbol) const
  {
    ocudu_assert(symbol < MAX_NSYMB_PER_SLOT, "Invalid symbol index '{}'", symbol);


    unsigned index = calculate_repository_index(slot, buffer.size());
    return buffer[index][symbol];
  }


public:
  explicit uplink_context_repository(unsigned size_) : pending_context_to_add(size_), buffer(size_) {}

  /// Adds the given entry to the repository at slot.

  /// Adds the given entry to the repository at slot.
  void add(const resource_grid_context& context,
           const shared_resource_grid&  grid,
           const ofdm_symbol_range&     symbol_range,
           ocudulog::basic_logger&      logger)
  {
    if (!pending_context_to_add.try_push([context, rg = grid.copy(), symbol_range, this]() {
          std::lock_guard<std::mutex> lock(mutex);
          for (unsigned symbol_id = symbol_range.start(), symbol_end = symbol_range.stop(); symbol_id != symbol_end;
               ++symbol_id) {
            entry(context.slot, symbol_id) = uplink_context(symbol_id, context, rg);
          }
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

  /// Writes to the grid at the given slot, port, symbol and start resource element the given IQ buffer.

  /// Writes to the grid at the given slot, port, symbol and start resource element the given IQ buffer.
  void write_grid(slot_point slot, unsigned port, unsigned symbol, unsigned start_re, span<const cbf16_t> re_iq_buffer)
  {
    std::lock_guard<std::mutex> lock(mutex);
    entry(slot, symbol).write_grid(port, start_re, re_iq_buffer);
  }

  /// Returns the entry of the repository for the given slot and symbol.

  /// Returns the entry of the repository for the given slot and symbol.
  uplink_context get(slot_point slot, unsigned symbol) const
  {
    std::lock_guard<std::mutex> lock(mutex);
    return entry(slot, symbol).copy();
  }

  /// \brief Tries to pop a complete resource grid for the given slot and symbol.
  ///
  /// A resource grid is considered completed when all the PRBs for all the ports have been written.

  /// \brief Tries to pop a complete resource grid for the given slot and symbol.
  ///
  /// A resource grid is considered completed when all the PRBs for all the ports have been written.
  expected<uplink_context::uplink_context_resource_grid_info> try_popping_complete_resource_grid_symbol(slot_point slot,
                                                                                                        unsigned symbol)
  {
    std::lock_guard<std::mutex> lock(mutex);
    auto                        result = entry(slot, symbol).try_getting_complete_resource_grid();

    // Symbol is complete or exists. Clear the context.

    // Symbol is complete or exists. Clear the context.
    if (result) {
      entry(slot, symbol) = {};
    }


    return result;
  }

  /// Pops a resource grid for the given slot and symbol.

  /// Pops a resource grid for the given slot and symbol.
  expected<uplink_context::uplink_context_resource_grid_info> pop_resource_grid_symbol(slot_point slot, unsigned symbol)
  {
    std::lock_guard<std::mutex> lock(mutex);


    auto& result = entry(slot, symbol);

    // Symbol does not exist. Do nothing.

    // Symbol does not exist. Do nothing.
    if (result.empty()) {
      return make_unexpected(default_error_t{});
    }

    // Pop and clear the slot/symbol information.

    // Pop and clear the slot/symbol information.
    uplink_context::uplink_context_resource_grid_info info = result.pop_uplink_context_resource_grid_info();
    return info;
  }

  /// Clears the repository entry for the given slot and symbol.

  /// Clears the repository entry for the given slot and symbol.
  void clear(slot_point slot, unsigned symbol)
  {
    std::lock_guard<std::mutex> lock(mutex);
    entry(slot, symbol) = {};
  }

  /// \brief Clears the whole repository, releasing the ownership of pending shared resource grids.

  /// \brief Clears the whole repository, releasing the ownership of pending shared resource grids.
  void clear()
  {
    std::lock_guard<std::mutex> lock(mutex);


    for (auto& elem : buffer) {
      for (auto& symbol : elem) {
        symbol = {};
      }
    }
  }
};


} // namespace ofh
} // namespace ocudu
