// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Definition of the common functions used by all bbdeb-based hardware-accelerated channel processor
/// implementations.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/bbdev/bbdev.h  (47 lines)
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
/// \brief Definition of the common functions used by all bbdeb-based hardware-accelerated channel processor
/// implementations.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/hal/dpdk/bbdev/bbdev_acc.h"
#include <rte_bbdev.h>
#include <rte_bbdev_op.h>
#include <rte_mempool.h>


namespace ocudu {
namespace dpdk {

/// \brief bbdev initialization.
///
/// \param[in]  cfg    Configuration of the bbdev-based hardware-accelerator.
/// \param[in]  logger OCUDU logger.
/// \return BBDEV device information if successful, otherwise returns an empty structure.

/// \brief bbdev initialization.
///
/// \param[in]  cfg    Configuration of the bbdev-based hardware-accelerator.
/// \param[in]  logger OCUDU logger.
/// \return BBDEV device information if successful, otherwise returns an empty structure.
expected<::rte_bbdev_info> bbdev_start(const bbdev_acc_configuration& cfg, ocudulog::basic_logger& logger);

/// \brief bbdev shutdown management.
///
/// \param[in]  dev_id ID of the bbdev-based hardware-accelerator.
/// \param[in]  logger OCUDU logger.

/// \brief bbdev shutdown management.
///
/// \param[in]  dev_id ID of the bbdev-based hardware-accelerator.
/// \param[in]  logger OCUDU logger.
bool bbdev_stop(unsigned dev_id, ocudulog::basic_logger& logger);

/// \brief Creates a new op pool for a given hardware-accelerator device.
///
/// \param[in]  pool_name     Unique ID for the new mbuf pool.
/// \param[in]  op_type       Type of bbdev op.
/// \param[in]  nof_elements  Number of elements in the op pool.
/// \param[in]  socket        Socket used by the bbdev accelerator.
/// \param[in]  logger        OCUDU logger.
/// \return Pointer to the created op pool.

/// \brief Creates a new op pool for a given hardware-accelerator device.
///
/// \param[in]  pool_name     Unique ID for the new mbuf pool.
/// \param[in]  op_type       Type of bbdev op.
/// \param[in]  nof_elements  Number of elements in the op pool.
/// \param[in]  socket        Socket used by the bbdev accelerator.
/// \param[in]  logger        OCUDU logger.
/// \return Pointer to the created op pool.
rte_mempool* create_op_pool(const char*             pool_name,
                            ::rte_bbdev_op_type     op_type,
                            uint16_t                nof_elements,
                            int                     socket,
                            ocudulog::basic_logger& logger);


} // namespace dpdk
} // namespace ocudu
