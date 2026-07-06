// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/dpdk/dpdk_ethernet_transmitter.cpp  (81 lines)
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

#include "dpdk_ethernet_transmitter.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter_config.h"
#include <rte_ethdev.h>


using namespace ocudu;
using namespace ether;


void dpdk_transmitter_impl::send(span<span<const uint8_t>> frames)
{
  // Receiving a frame burst larger than MAX_BURST_SIZE requires making several Tx bursts.
  // Receiving a frame burst larger than MAX_BURST_SIZE requires making several Tx bursts.
  for (unsigned offset = 0; offset < frames.size();) {
    auto frame_burst = frames.subspan(offset, std::min<unsigned>(MAX_BURST_SIZE, frames.size() - offset));
    offset += frame_burst.size();


    auto meas = metrics_collector.create_time_execution_measurer();


    static_vector<::rte_mbuf*, MAX_BURST_SIZE> mbufs(frame_burst.size());
    if (::rte_pktmbuf_alloc_bulk(port_ctx->get_mempool(), mbufs.data(), frame_burst.size()) < 0) {
      logger.warning("Not enough entries in the mempool to send '{}' frames to the NIC port '{}' in the DPDK Ethernet "
                     "transmitter ",
                     frame_burst.size(),
                     port_ctx->get_port_id());
      metrics_collector.update_stats(meas.stop());
      return;
    }


    uint64_t nof_bytes_in_burst = 0;
    for (unsigned idx = 0, end = frame_burst.size(); idx != end; ++idx) {
      const auto  frame = frame_burst[idx];
      ::rte_mbuf* mbuf  = mbufs[idx];


      if (::rte_pktmbuf_append(mbuf, frame.size()) == nullptr) {
        ::rte_pktmbuf_free(mbuf);
        logger.warning("Unable to append '{}' bytes to the allocated mbuf associated with the NIC port '{}' in the "
                       "DPDK Ethernet transmitter",
                       frame.size(),
                       port_ctx->get_port_id());
        ::rte_pktmbuf_free_bulk(mbufs.data(), mbufs.size());
        metrics_collector.update_stats(meas.stop());
        return;
      }
      mbuf->data_len = frame.size();
      mbuf->pkt_len  = frame.size();
      nof_bytes_in_burst += frame.size();


      uint8_t* data = rte_pktmbuf_mtod(mbuf, uint8_t*);
      std::memcpy(data, frame.data(), frame.size());
    }


    unsigned nof_sent_packets = ::rte_eth_tx_burst(port_ctx->get_dpdk_port_id(), 0, mbufs.data(), mbufs.size());


    if (OCUDU_UNLIKELY(nof_sent_packets < mbufs.size())) {
      logger.warning(
          "DPDK dropped '{}' packets out of a total of '{}' in the tx burst while sending data to the NIC port '{}'",
          mbufs.size() - nof_sent_packets,
          mbufs.size(),
          port_ctx->get_port_id());

      // Recalculate actual number of bytes transmitted.

      // Recalculate actual number of bytes transmitted.
      if (!metrics_collector.disabled()) {
        nof_bytes_in_burst = 0;
        for (unsigned i = 0; i != nof_sent_packets; ++i) {
          nof_bytes_in_burst += frame_burst[i].size();
        }
      }
      for (unsigned buf_idx = nof_sent_packets, last_idx = mbufs.size(); buf_idx != last_idx; ++buf_idx) {
        ::rte_pktmbuf_free(mbufs[buf_idx]);
      }
    }
    metrics_collector.update_stats(meas.stop(), nof_bytes_in_burst, nof_sent_packets);
  }
}


transmitter_metrics_collector* dpdk_transmitter_impl::get_metrics_collector()
{
  return metrics_collector.disabled() ? nullptr : &metrics_collector;
}
