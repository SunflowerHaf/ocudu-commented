// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_transmitter_impl.cpp  (99 lines)
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

#include "ethernet_transmitter_impl.h"
#include "ocudu/support/error_handling.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <net/if.h>
#include <netinet/ether.h>
#include <sys/ioctl.h>
#include <unistd.h>


using namespace ocudu;
using namespace ether;


transmitter_impl::transmitter_impl(const transmitter_config& config, ocudulog::basic_logger& logger_) :
  logger(logger_), metrics_collector(config.are_metrics_enabled)
{
  socket_fd = ::socket(AF_PACKET, SOCK_RAW | SOCK_NONBLOCK, IPPROTO_RAW);
  if (socket_fd < 0) {
    report_error("Unable to open raw socket for Ethernet transmitter: {}", ::strerror(errno));
  }


  if (config.interface.size() > (IFNAMSIZ - 1)) {
    report_error("The Ethernet transmitter interface name '{}' exceeds the maximum allowed length");
  }


  ::ifreq if_idx = {};
  ::strncpy(if_idx.ifr_name, config.interface.c_str(), IFNAMSIZ - 1);

  // Set requested MTU size.

  // Set requested MTU size.
  if_idx.ifr_mtu = config.mtu_size.value();
  if (::ioctl(socket_fd, SIOCSIFMTU, &if_idx) < 0) {
    // Get the MTU size of the NIC.
    // Get the MTU size of the NIC.
    int current_mtu = -1;
    if (::ioctl(socket_fd, SIOCGIFMTU, &if_idx) < 0) {
      logger.warning("Could not check MTU of the NIC interface '{}' in the Ethernet transmitter", config.interface);
    } else {
      current_mtu = if_idx.ifr_mtu;
    }
    report_error(
        "Unable to set MTU size to '{}' bytes for NIC interface '{}' in the Ethernet transmitter, current MTU size "
        "set to '{}' bytes",
        config.mtu_size,
        config.interface,
        current_mtu);
  }

  // Get the index of the NIC.

  // Get the index of the NIC.
  if (::ioctl(socket_fd, SIOCGIFINDEX, &if_idx) < 0) {
    report_error("Unable to get index for NIC interface in the Ethernet transmitter");
  }

  // Prepare the socket address used by sendto.

  // Prepare the socket address used by sendto.
  socket_address             = {};
  socket_address.sll_ifindex = if_idx.ifr_ifindex;
  socket_address.sll_halen   = ETH_ALEN;
  std::copy(std::begin(config.mac_dst_address), std::end(config.mac_dst_address), std::begin(socket_address.sll_addr));


  logger.info("Opened successfully the NIC interface '{}' (fd = '{}') used by the Ethernet transmitter",
              config.interface,
              socket_fd);
}


transmitter_impl::~transmitter_impl()
{
  ::close(socket_fd);
}


void transmitter_impl::send(span<span<const uint8_t>> frames)
{
  for (auto frame : frames) {
    auto meas = metrics_collector.create_time_execution_measurer();


    int ret = ::sendto(socket_fd,
                       frame.data(),
                       frame.size(),
                       0,
                       reinterpret_cast<::sockaddr*>(&socket_address),
                       sizeof(socket_address));


    if (ret < 0) {
      logger.warning("Ethernet transmitter with fd = '{}' could not transmit '{}' bytes, consider tuning "
                     "the NIC system settings to obtain higher performance or use DPDK",
                     socket_fd,
                     frame.size());


      metrics_collector.update_stats(meas.stop());
      continue;
    }
    metrics_collector.update_stats(meas.stop(), frame.size());
  }
}


transmitter_metrics_collector* transmitter_impl::get_metrics_collector()
{
  return metrics_collector.disabled() ? nullptr : &metrics_collector;
}
