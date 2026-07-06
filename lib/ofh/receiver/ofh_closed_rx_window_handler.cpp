// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_closed_rx_window_handler.cpp  (123 lines)
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

#include "ofh_closed_rx_window_handler.h"
#include "ocudu/support/executors/task_executor.h"


using namespace ocudu;
using namespace ofh;


closed_rx_window_handler::closed_rx_window_handler(const closed_rx_window_handler_config&  config,
                                                   closed_rx_window_handler_dependencies&& dependencies) :
  notification_delay_in_symbols(config.nof_symbols_to_process_uplink + config.rx_timing_params.sym_end + 1),
  sector_id(config.sector),
  warn_unreceived_frames(config.warn_unreceived_frames),
  log_unreceived_messages(config.warn_unreceived_frames == warn_unreceived_ru_frames::always),
  logger(*dependencies.logger),
  executor(*dependencies.executor),
  prach_repo(std::move(dependencies.prach_repo)),
  uplink_repo(std::move(dependencies.uplink_repo)),
  notifier(std::move(dependencies.notifier))
{
  ocudu_assert(prach_repo, "Invalid PRACH context repository");
  ocudu_assert(uplink_repo, "Invalid uplink context repository");
  ocudu_assert(notifier, "Invalid U-Plane received symbol notifier");
}


void closed_rx_window_handler::on_new_symbol(const slot_symbol_point_context& symbol_point_context)
{
  auto token = stop_manager.get_token();
  if (OCUDU_UNLIKELY(token.is_stop_requested())) {
    return;
  }


  if (!executor.defer([internal_slot = symbol_point_context.symbol_point - notification_delay_in_symbols,
                       this,
                       tk = std::move(token)]() {
        // Add pending contexts to the repository.
        // Add pending contexts to the repository.
        uplink_repo->process_pending_contexts();
        prach_repo->process_pending_contexts();

        // Check the repositories for unhandled contexts.

        // Check the repositories for unhandled contexts.
        handle_uplink_context(internal_slot);
        handle_prach_context(internal_slot);
      })) {
    logger.warning(
        "Sector#{}: failed to dispatch task for checking for lost messages in reception for slot '{}' and symbol '{}'",
        sector_id,
        symbol_point_context.symbol_point.get_slot(),
        symbol_point_context.symbol_point.get_symbol_index());
  }
}


void closed_rx_window_handler::collect_metrics(closed_rx_window_metrics& metrics)
{
  // Fill the metrics and reset internal counters.
  // Fill the metrics and reset internal counters.
  metrics.nof_missing_prach_contexts = nof_missed_prach_contexts.exchange(0, std::memory_order_relaxed);
  metrics.nof_missing_uplink_symbols = nof_missed_uplink_symbols.exchange(0, std::memory_order_relaxed);
}


void closed_rx_window_handler::handle_uplink_context(slot_symbol_point symbol_point)
{
  expected<uplink_context::uplink_context_resource_grid_info> context =
      uplink_repo->pop_resource_grid_symbol(symbol_point.get_slot(), symbol_point.get_symbol_index());


  if (!context) {
    return;
  }


  uplink_context::uplink_context_resource_grid_info& ctx_value = *context;


  uplane_rx_symbol_context notification_context = {
      ctx_value.context.slot, symbol_point.get_symbol_index(), ctx_value.context.sector};
  notifier->on_new_uplink_symbol(notification_context, std::move(ctx_value.grid), false);

  // Increase the metrics counter.

  // Increase the metrics counter.
  nof_missed_uplink_symbols.fetch_add(1, std::memory_order_relaxed);


  if (log_unreceived_messages) {
    logger.warning("Sector#{}: missed incoming User-Plane uplink messages for slot '{}', symbol '{}'",
                   ctx_value.context.sector,
                   ctx_value.context.slot,
                   symbol_point.get_symbol_index());
  }


  if (OCUDU_UNLIKELY(logger.debug.enabled())) {
    logger.debug("Sector#{}: notifying incomplete UL symbol in slot '{}', symbol '{}'",
                 notification_context.sector,
                 notification_context.slot,
                 notification_context.symbol);
  }
}


void closed_rx_window_handler::handle_prach_context(slot_symbol_point symbol_point)
{
  // As the PRACH is sent when all the symbols are received, wait until new slot to notify it PRACH buffer.
  // As the PRACH is sent when all the symbols are received, wait until new slot to notify it PRACH buffer.
  if (symbol_point.get_symbol_index() != 0) {
    return;
  }


  slot_point slot    = symbol_point.get_slot() - 1;
  auto       context = prach_repo->pop_prach_buffer(slot);

  // Nothing to do.

  // Nothing to do.
  if (!context) {
    return;
  }


  const auto& ctx_value = context->context;


  notifier->on_new_prach_window_data(ctx_value, std::move(context->buffer));

  // Increase the metrics counter.

  // Increase the metrics counter.
  nof_missed_prach_contexts.fetch_add(1, std::memory_order_relaxed);


  if (log_unreceived_messages) {
    logger.warning(
        "Sector#{}: missed incoming User-Plane PRACH messages for slot '{}'", ctx_value.sector, ctx_value.slot);
  }


  if (OCUDU_UNLIKELY(logger.debug.enabled())) {
    logger.debug("Sector#{}: notifying incomplete PRACH in slot '{}'", ctx_value.sector, ctx_value.slot);
  }
}
