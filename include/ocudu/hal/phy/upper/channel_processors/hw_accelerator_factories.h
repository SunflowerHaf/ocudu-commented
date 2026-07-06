// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/phy/upper/channel_processors/hw_accelerator_factories.h  (37 lines)
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

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/hal/dpdk/bbdev/bbdev_acc.h"
#include "ocudu/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc.h"
#include "ocudu/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc_factory.h"


namespace ocudu {
namespace hal {

/// Configuration parameters of the bbdev-based PDSCH encoder hardware-accelerator factory.

/// Configuration parameters of the bbdev-based PDSCH encoder hardware-accelerator factory.
struct bbdev_hwacc_pdsch_enc_factory_configuration {
  /// Accelerator type.
  /// Accelerator type.
  std::string acc_type;
  /// Interfacing to a bbdev-based hardware-accelerator.
  /// Interfacing to a bbdev-based hardware-accelerator.
  std::shared_ptr<ocudu::dpdk::bbdev_acc> bbdev_accelerator;
  /// Defines if the PDSCH encoder operates in CB mode (true) or TB mode (false).
  /// Defines if the PDSCH encoder operates in CB mode (true) or TB mode (false).
  bool cb_mode = false;
  /// Defines the maximum supported TB size in bytes (CB mode will be forced for larger TBs).
  /// Only used in TB mode.
  /// Defines the maximum supported TB size in bytes (CB mode will be forced for larger TBs).
  /// Only used in TB mode.
  unsigned max_tb_size;
  /// Indicates if the accelerated function uses a dedicated hardware queue or needs to reserve one for each operation.
  /// Indicates if the accelerated function uses a dedicated hardware queue or needs to reserve one for each operation.
  bool dedicated_queue;
};

/// \brief Creates a bbdev-based PDSCH encoder hardware accelerator factory.
///
/// \param[in] cfg    Configuration parameters of the bbdev-based PDSCH encoder hardware accelerator.
/// \return A valid PDSCH encoder hardware accelerator factory on success, otherwise \c nullptr.

/// \brief Creates a bbdev-based PDSCH encoder hardware accelerator factory.
///
/// \param[in] cfg    Configuration parameters of the bbdev-based PDSCH encoder hardware accelerator.
/// \return A valid PDSCH encoder hardware accelerator factory on success, otherwise \c nullptr.
std::shared_ptr<hw_accelerator_pdsch_enc_factory>
create_bbdev_pdsch_enc_acc_factory(const bbdev_hwacc_pdsch_enc_factory_configuration& accelerator_config);


} // namespace hal
} // namespace ocudu
