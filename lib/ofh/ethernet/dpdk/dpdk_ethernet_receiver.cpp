// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/dpdk/dpdk_ethernet_receiver.cpp  (118 lines)
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

#include "dpdk_ethernet_receiver.h"
#include "ocudu/instrumentation/traces/ofh_traces.h"
#include "ocudu/ofh/ethernet/dpdk/dpdk_ethernet_rx_buffer.h"
#include "ocudu/ofh/ethernet/ethernet_frame_notifier.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/synchronization/sync_event.h"
#include <rte_ethdev.h>
#include <thread>


using namespace ocudu;
using namespace ether;


namespace {


class dummy_frame_notifier : public frame_notifier
{
  // See interface for documentation.
  // See interface for documentation.
  void on_new_frame(ether::unique_rx_buffer buffer) override {}
};


} // namespace

/// This dummy object is passed to the constructor of the DPDK Ethernet receiver implementation as a placeholder for the
/// actual frame notifier, which will be later set up through the \ref start() method.

/// This dummy object is passed to the constructor of the DPDK Ethernet receiver implementation as a placeholder for the
/// actual frame notifier, which will be later set up through the \ref start() method.
static dummy_frame_notifier dummy_notifier;


dpdk_receiver_impl::dpdk_receiver_impl(task_executor&                     executor_,
                                       std::shared_ptr<dpdk_port_context> port_ctx_,
                                       ocudulog::basic_logger&            logger_,
                                       bool                               are_metrics_enabled) :
  logger(logger_),
  executor(executor_),
  notifier(&dummy_notifier),
  port_ctx(std::move(port_ctx_)),
  metrics_collector(are_metrics_enabled)
{
  ocudu_assert(port_ctx, "Invalid port context");
}


void dpdk_receiver_impl::start(frame_notifier& notifier_)
{
  logger.info("Starting the DPDK ethernet frame receiver");


  stop_manager.reset();


  notifier = &notifier_;


  sync_event wait_event;
  if (!executor.defer([this, token = wait_event.get_token()]() { receive_loop(); })) {
    report_error("Unable to start the DPDK ethernet frame receiver on port '{}'", port_ctx->get_port_id());
  }

  // Block waiting for receiver executor to start.

  // Block waiting for receiver executor to start.
  wait_event.wait();


  logger.info("Started the DPDK ethernet frame receiver on port '{}'", port_ctx->get_port_id());
}


void dpdk_receiver_impl::stop()
{
  logger.info("Requesting stop of the DPDK ethernet frame receiver on port '{}'", port_ctx->get_port_id());
  stop_manager.stop();
  logger.info("Stopped the DPDK ethernet frame receiver on port '{}'", port_ctx->get_port_id());
}


void dpdk_receiver_impl::receive_loop()
{
  auto token = stop_manager.get_token();
  if (OCUDU_UNLIKELY(token.is_stop_requested())) {
    return;
  }


  receive();

  // Retry the task deferring when it fails.

  // Retry the task deferring when it fails.
  while (!executor.defer([this, tk = std::move(token)]() { receive_loop(); })) {
    std::this_thread::sleep_for(std::chrono::microseconds(10));
  }
}


void dpdk_receiver_impl::receive()
{
  std::array<::rte_mbuf*, MAX_BURST_SIZE> mbufs;


  auto        meas       = metrics_collector.create_time_execution_measurer();
  trace_point dpdk_rx_tp = ofh_tracer.now();


  unsigned num_frames = ::rte_eth_rx_burst(port_ctx->get_dpdk_port_id(), 0, mbufs.data(), MAX_BURST_SIZE);
  if (num_frames == 0) {
    ofh_tracer << instant_trace_event("ofh_receiver_wait_data", instant_trace_event::cpu_scope::thread);
    metrics_collector.update_stats(meas.stop());


    std::this_thread::sleep_for(std::chrono::microseconds(5));
    return;
  }


  if (!metrics_collector.disabled()) {
    uint64_t nof_bytes_received = 0;
    for (auto* mbuf : span<::rte_mbuf*>(mbufs.data(), num_frames)) {
      nof_bytes_received += mbuf->data_len;
    }
    metrics_collector.update_stats(meas.stop(), nof_bytes_received, num_frames);
  }


  for (auto* mbuf : span<::rte_mbuf*>(mbufs.data(), num_frames)) {
    ::rte_vlan_strip(mbuf);
    notifier->on_new_frame(unique_rx_buffer(dpdk_rx_buffer_impl(mbuf)));
  }
  ofh_tracer << trace_event("ofh_dpdk_rx", dpdk_rx_tp);
}


receiver_metrics_collector* dpdk_receiver_impl::get_metrics_collector()
{
  return metrics_collector.disabled() ? nullptr : &metrics_collector;
}
