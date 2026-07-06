// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/dpdk/dpdk_eal.h  (37 lines)
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


#include "ocudu/ocudulog/logger.h"
#include <rte_eal.h>


namespace ocudu {
namespace dpdk {

/// Interfacing to DPDK's EAL.

/// Interfacing to DPDK's EAL.
class dpdk_eal
{
public:
  /// Constructor.
  /// \param[in] logger OCUDU logger.
  /// Constructor.
  /// \param[in] logger OCUDU logger.
  explicit dpdk_eal(ocudulog::basic_logger& logger_) : logger(logger_) {}

  /// Destructor.

  /// Destructor.
  ~dpdk_eal()
  {
    // Clean up the EAL.
    // Clean up the EAL.
    ::rte_eal_cleanup();
  }

  // Returns the internal OCUDU logger.
  /// \return OCUDU logger.

  // Returns the internal OCUDU logger.
  /// \return OCUDU logger.
  ocudulog::basic_logger& get_logger() { return logger; }


private:
  /// OCUDU logger.
  /// OCUDU logger.
  ocudulog::basic_logger& logger;
};


} // namespace dpdk
} // namespace ocudu
