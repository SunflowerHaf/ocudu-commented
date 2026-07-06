// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/bbdev/bbdev_acc_factory.h  (19 lines)
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


#include "ocudu/hal/dpdk/bbdev/bbdev_acc.h"


namespace ocudu {
namespace dpdk {

/// \brief Instantiates a bbdev hardware accelerator.
///
/// \param[in] cfg    Configuration parameters of the bbdev-based hardware accelerator.
/// \param[in] logger OCUDU logger.
/// \return A pointer to a valid bbdev accelerator on success, otherwise \c nullptr.

/// \brief Instantiates a bbdev hardware accelerator.
///
/// \param[in] cfg    Configuration parameters of the bbdev-based hardware accelerator.
/// \param[in] logger OCUDU logger.
/// \return A pointer to a valid bbdev accelerator on success, otherwise \c nullptr.
std::shared_ptr<bbdev_acc> create_bbdev_acc(const bbdev_acc_configuration& cfg, ocudulog::basic_logger& logger);


} // namespace dpdk
} // namespace ocudu
