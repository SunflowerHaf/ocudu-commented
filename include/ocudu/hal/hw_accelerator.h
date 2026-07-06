// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Definition of an abstract interface to a hardware accelerator.
// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/hw_accelerator.h  (44 lines)
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

/// \file
/// \brief Definition of an abstract interface to a hardware accelerator.
#pragma once


#include "ocudu/adt/span.h"


namespace ocudu {
namespace hal {

/// \brief This interface provides the basic functions to enqueue and dequeue an operation to hardware accelerator.
///
/// \tparam T Type of the input data, and of the packed codeword in the case of encoders or soft-data in case of
///           decoders, to the hardware accelerator. \tparam U Type of the output data to the hardware accelerator.

/// \brief This interface provides the basic functions to enqueue and dequeue an operation to hardware accelerator.
///
/// \tparam T Type of the input data, and of the packed codeword in the case of encoders or soft-data in case of
///           decoders, to the hardware accelerator. \tparam U Type of the output data to the hardware accelerator.
template <typename T, typename U>
/// Generic hardware accelerator interface definition.
/// Generic hardware accelerator interface definition.
class hw_accelerator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~hw_accelerator() = default;

  /// \brief Enqueues an accelerated operation and provides the input data.
  ///
  /// \param[in] data      The input data to the hardware accelerator.
  /// \param[in] aux_data  Optional soft combining data typically used by hardware-accelerated decoding operations.
  /// \param[in] cb_index  Optional index of the CB within the TB.
  /// \return True if the operation was successfully enqueued, false otherwise.

  /// \brief Enqueues an accelerated operation and provides the input data.
  ///
  /// \param[in] data      The input data to the hardware accelerator.
  /// \param[in] aux_data  Optional soft combining data typically used by hardware-accelerated decoding operations.
  /// \param[in] cb_index  Optional index of the CB within the TB.
  /// \return True if the operation was successfully enqueued, false otherwise.
  virtual bool enqueue_operation(span<const T> data, span<const T> aux_data = {}, unsigned cb_index = 0) = 0;

  /// \brief Dequeues an accelerated operation and retrieves both the output data, while using a soft-buffer.
  ///
  /// \param[out] data          The output data from the hardware accelerator.
  /// \param[out] aux_data      Soft combining data for hardware-accelerated decoding operations, packed codeword for
  ///                           hardware-accelerated encoding operations.
  /// \param[in]  segment_index Optional index of the segment within the TB.
  /// \return True if the operation was successfully dequeued, false otherwise.

  /// \brief Dequeues an accelerated operation and retrieves both the output data, while using a soft-buffer.
  ///
  /// \param[out] data          The output data from the hardware accelerator.
  /// \param[out] aux_data      Soft combining data for hardware-accelerated decoding operations, packed codeword for
  ///                           hardware-accelerated encoding operations.
  /// \param[in]  segment_index Optional index of the segment within the TB.
  /// \return True if the operation was successfully dequeued, false otherwise.
  virtual bool dequeue_operation(span<U> data, span<T> aux_data = {}, unsigned segment_index = 0) = 0;
};


} // namespace hal
} // namespace ocudu
