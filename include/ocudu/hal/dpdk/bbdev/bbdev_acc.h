// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/bbdev/bbdev_acc.h  (151 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/hal
// HAL (Hardware Abstraction Layer) public interface headers. CONDITIONAL: only required when building with DPDK_FOUND=ON. In the standard USRP/UHD build these headers are not included by any active code path.
//
// Contents:
//   hal/dpdk/             — DPDK EAL handle, mbuf pool, BBDEV device interfaces.
//   hal/hw_accelerator.h  — Base hardware accelerator interface (submit_op, retrieve_op, get capabilities).
//   hal/phy/upper/        — hw_accelerator_pdsch_enc (offload PDSCH LDPC encoding) and hw_accelerator_pusch_dec (offload PUSCH LDPC decoding) abstract interfaces, plus their factory types and the external HARQ buffer context repository interface.
// =============================================================================

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/adt/mpmc_queue.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/units.h"
#include <rte_bbdev.h>
#include <rte_bbdev_op.h>


namespace ocudu {
namespace dpdk {

/// Maximum number of queues supported by a bbdev-based hardware-accelerator.

/// Maximum number of queues supported by a bbdev-based hardware-accelerator.
constexpr unsigned MAX_NOF_BBDEV_QUEUES = 128;
/// Maximum number of operations that can be stored in a hardware queue at a given time.
/// Maximum number of operations that can be stored in a hardware queue at a given time.
constexpr unsigned MAX_NOF_OP_IN_QUEUE = 16;
/// Maximum number of VF instances supported by a bbdev-based hardware-accelerator.
/// Maximum number of VF instances supported by a bbdev-based hardware-accelerator.
constexpr unsigned MAX_NOF_BBDEV_VF_INSTANCES = 64;

/// Configuration parameters and objects tied to a bbdev-based hardware-accelerator.

/// Configuration parameters and objects tied to a bbdev-based hardware-accelerator.
struct bbdev_acc_configuration {
  /// ID of the bbdev-based hardware-accelerator.
  /// ID of the bbdev-based hardware-accelerator.
  unsigned id;
  /// Number of lcores available to the hardware-accelerated LDPC encoder (disabled if 0).
  /// Number of lcores available to the hardware-accelerated LDPC encoder (disabled if 0).
  unsigned nof_ldpc_enc_lcores = 0;
  /// Number of lcores available to the hardware-accelerated LDPC decoder (disabled if 0).
  /// Number of lcores available to the hardware-accelerated LDPC decoder (disabled if 0).
  unsigned nof_ldpc_dec_lcores = 0;
  /// Number of lcores available to the hardware-accelerated FFT (disabled if 0).
  /// Number of lcores available to the hardware-accelerated FFT (disabled if 0).
  unsigned nof_fft_lcores = 0;
  /// Size of each mbuf used to exchange unencoded and unrate-matched messages with the accelerator in bytes.
  /// Note that by default it is initialized to the maximum size supported by an mbuf.
  /// Size of each mbuf used to exchange unencoded and unrate-matched messages with the accelerator in bytes.
  /// Note that by default it is initialized to the maximum size supported by an mbuf.
  unsigned msg_mbuf_size = RTE_BBDEV_LDPC_E_MAX_MBUF;
  /// Size of each mbuf used to exchange encoded and rate-matched messages with the accelerator in bytes.
  /// Note that by default it is initialized to the maximum size supported by an mbuf.
  /// Size of each mbuf used to exchange encoded and rate-matched messages with the accelerator in bytes.
  /// Note that by default it is initialized to the maximum size supported by an mbuf.
  unsigned rm_mbuf_size = RTE_BBDEV_LDPC_E_MAX_MBUF;
  /// Number of mbufs in each memory pool.
  /// Number of mbufs in each memory pool.
  unsigned nof_mbuf = 256;
};

/// Wireless Baseband Device (bbdev) interface.

/// Wireless Baseband Device (bbdev) interface.
class bbdev_acc
{
public:
  /// Constructor.
  /// \param[in] cfg    Configuration parameters of the bbdev-based hardware-accelerator.
  /// \param[in] info   bbdev Device information.
  /// \param[in] logger OCUDU logger.
  /// Constructor.
  /// \param[in] cfg    Configuration parameters of the bbdev-based hardware-accelerator.
  /// \param[in] info   bbdev Device information.
  /// \param[in] logger OCUDU logger.
  explicit bbdev_acc(const bbdev_acc_configuration& cfg, const ::rte_bbdev_info& info_, ocudulog::basic_logger& logger);

  /// Destructor.

  /// Destructor.
  ~bbdev_acc();

  /// Returns the ID of the bbdev-based hardware-accelerator device.
  /// \return Device ID.

  /// Returns the ID of the bbdev-based hardware-accelerator device.
  /// \return Device ID.
  unsigned get_device_id() const { return id; }

  /// Returns the ID of the socket used by the bbdev-based hardware-accelerator.
  /// \return Socket ID.

  /// Returns the ID of the socket used by the bbdev-based hardware-accelerator.
  /// \return Socket ID.
  int get_socket_id() const { return info.socket_id; }

  /// Returns the number of LDPC encoder cores provided by the bbdev-based hardware-accelerator.
  /// \return Number of LDPC encoder cores.

  /// Returns the number of LDPC encoder cores provided by the bbdev-based hardware-accelerator.
  /// \return Number of LDPC encoder cores.
  unsigned get_nof_ldpc_enc_cores() const { return nof_ldpc_enc_lcores; }

  /// Returns the number of LDPC decoder cores provided by the bbdev-based hardware-accelerator.
  /// \return Number of LDPC decoder cores.

  /// Returns the number of LDPC decoder cores provided by the bbdev-based hardware-accelerator.
  /// \return Number of LDPC decoder cores.
  unsigned get_nof_ldpc_dec_cores() const { return nof_ldpc_dec_lcores; }

  /// Returns the number of FFT cores provided by the bbdev-based hardware-accelerator.
  /// \return Number of FFT cores.

  /// Returns the number of FFT cores provided by the bbdev-based hardware-accelerator.
  /// \return Number of FFT cores.
  unsigned get_nof_fft_cores() const { return nof_fft_lcores; }

  /// Returns the size of the (external) HARQ buffer size embedded in the hardware-accelerator.
  /// \return HARQ buffer size in bytes. Note that 64 bits are used to enable sizes >= 4GB.

  /// Returns the size of the (external) HARQ buffer size embedded in the hardware-accelerator.
  /// \return HARQ buffer size in bytes. Note that 64 bits are used to enable sizes >= 4GB.
  uint64_t get_harq_buff_size_bytes() const { return static_cast<uint64_t>(info.drv.harq_buffer_size) * 1024; }

  /// Returns the size of each mbuf used to exchange unencoded and unrate-matched messages with the accelerator.
  /// \return Unencoded and unrate-matched mbuf size (in bytes).

  /// Returns the size of each mbuf used to exchange unencoded and unrate-matched messages with the accelerator.
  /// \return Unencoded and unrate-matched mbuf size (in bytes).
  units::bytes get_msg_mbuf_size() const { return units::bytes(msg_mbuf_size); }

  /// Returns the size of each mbuf used to exchange encoded and rate-matched messages with the accelerator.
  /// \return Encoded and rate-matched mbuf size (in bytes).

  /// Returns the size of each mbuf used to exchange encoded and rate-matched messages with the accelerator.
  /// \return Encoded and rate-matched mbuf size (in bytes).
  units::bytes get_rm_mbuf_size() const { return units::bytes(rm_mbuf_size); }

  /// Returns the number of mbufs in each memory pool used to exchange data with the accelerator.
  /// \return Number of mbufs.

  /// Returns the number of mbufs in each memory pool used to exchange data with the accelerator.
  /// \return Number of mbufs.
  unsigned get_nof_mbuf() const { return nof_mbuf; }

  /// Returns the internal OCUDU logger.
  /// \return OCUDU logger.

  /// Returns the internal OCUDU logger.
  /// \return OCUDU logger.
  ocudulog::basic_logger& get_logger() { return logger; }

  /// \brief Reserves a free queue to be used by a specific hardware-accelerated channel processor function.
  ///
  /// \param[in] op_type Type of bbdev op.
  /// \return The identifier of the reserved queue if successful, otherwise a negative integer.

  /// \brief Reserves a free queue to be used by a specific hardware-accelerated channel processor function.
  ///
  /// \param[in] op_type Type of bbdev op.
  /// \return The identifier of the reserved queue if successful, otherwise a negative integer.
  int reserve_queue(::rte_bbdev_op_type op_type);

  /// \brief Frees a queue used by a specific hardware-accelerated channel processor function.
  ///
  /// \param[in] queue_id Identifier of the queue to be freed.

  /// \brief Frees a queue used by a specific hardware-accelerated channel processor function.
  ///
  /// \param[in] queue_id Identifier of the queue to be freed.
  void free_queue(::rte_bbdev_op_type op_type, unsigned queue_id);

  /// Returns a unique ID for an instance of an LDPC encoder using the bbdev-based accelerator.
  /// \return Encoder ID.

  /// Returns a unique ID for an instance of an LDPC encoder using the bbdev-based accelerator.
  /// \return Encoder ID.
  unsigned reserve_encoder() { return nof_ldpc_enc_instances++; }

  /// Returns a unique ID for an instance of an LDPC decoder using the bbdev-based accelerator.
  /// \return Decoder ID.

  /// Returns a unique ID for an instance of an LDPC decoder using the bbdev-based accelerator.
  /// \return Decoder ID.
  unsigned reserve_decoder() { return nof_ldpc_dec_instances++; }


private:
  /// Codeblock identifier list type.
  /// Codeblock identifier list type.
  using queue_id_list =
      concurrent_queue<unsigned, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;

  /// ID of the bbdev-based hardware-accelerator.

  /// ID of the bbdev-based hardware-accelerator.
  unsigned id;
  /// Structure providing device information.
  /// Structure providing device information.
  ::rte_bbdev_info info;
  /// Number of lcores available to the hardware-accelerated LDPC encoder (disabled if 0).
  /// Number of lcores available to the hardware-accelerated LDPC encoder (disabled if 0).
  unsigned nof_ldpc_enc_lcores;
  /// Number of lcores available to the hardware-accelerated LDPC decoder (disabled if 0).
  /// Number of lcores available to the hardware-accelerated LDPC decoder (disabled if 0).
  unsigned nof_ldpc_dec_lcores;
  /// Number of lcores available to the hardware-accelerated FFT (disabled if 0).
  /// Number of lcores available to the hardware-accelerated FFT (disabled if 0).
  unsigned nof_fft_lcores;
  /// List containing the free queue ids for hardware-acclerated LDPC encoder functions.
  /// List containing the free queue ids for hardware-acclerated LDPC encoder functions.
  queue_id_list available_ldpc_enc_queue;
  /// List containing the free queue ids for hardware-acclerated LDPC decoder functions.
  /// List containing the free queue ids for hardware-acclerated LDPC decoder functions.
  queue_id_list available_ldpc_dec_queue;
  /// List containing the free queue ids for hardware-acclerated FFT functions.
  /// List containing the free queue ids for hardware-acclerated FFT functions.
  queue_id_list available_fft_queue;
  /// Size of each mbuf used to exchange unencoded and unrate-matched messages with the accelerator in bytes.
  /// Size of each mbuf used to exchange unencoded and unrate-matched messages with the accelerator in bytes.
  unsigned msg_mbuf_size;
  /// Size of each mbuf used to exchange encoded and rate-matched messages with the accelerator in bytes.
  /// Size of each mbuf used to exchange encoded and rate-matched messages with the accelerator in bytes.
  unsigned rm_mbuf_size;
  /// Number of mbufs in each memory pool.
  /// Number of mbufs in each memory pool.
  unsigned nof_mbuf;
  /// OCUDU logger.
  /// OCUDU logger.
  ocudulog::basic_logger& logger;
  /// Number of LDPC encoder instances using this bbdev accelerator.
  /// Number of LDPC encoder instances using this bbdev accelerator.
  unsigned nof_ldpc_enc_instances;
  /// Number of LDPC decoder instances using this bbdev accelerator.
  /// Number of LDPC decoder instances using this bbdev accelerator.
  unsigned nof_ldpc_dec_instances;
};


} // namespace dpdk
} // namespace ocudu
