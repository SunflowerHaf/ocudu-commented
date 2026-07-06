// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/prach/prach_processor_factories.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/lower/modulation/modulation_factories.h"
#include "ocudu/phy/lower/processors/uplink/prach/prach_processor.h"
#include <memory>


namespace ocudu {


class task_executor;
class sampling_rate;

/// Lower physical layer PRACH processor - Factory interface.

/// Lower physical layer PRACH processor - Factory interface.
class prach_processor_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~prach_processor_factory() = default;

  /// Creates a lower PHY PRACH processor.

  /// Creates a lower PHY PRACH processor.
  virtual std::unique_ptr<prach_processor> create() = 0;
};

/// \brief Creates a software based PRACH processor factory.
///
/// \param ofdm_prach_factory          OFDM demodulator for PRACH factory.
/// \param async_task_executor         Task executor for demodulating PRACH asynchronously.
/// \param srate                       Sampling rate.
/// \param max_nof_ports               Maximum number of PRACH reception ports.
/// \param max_nof_concurrent_requests Maximum number of concurrent PRACH processing requests.
/// \return A valid PRACH processor factory.

/// \brief Creates a software based PRACH processor factory.
///
/// \param ofdm_prach_factory          OFDM demodulator for PRACH factory.
/// \param async_task_executor         Task executor for demodulating PRACH asynchronously.
/// \param srate                       Sampling rate.
/// \param max_nof_ports               Maximum number of PRACH reception ports.
/// \param max_nof_concurrent_requests Maximum number of concurrent PRACH processing requests.
/// \return A valid PRACH processor factory.
std::shared_ptr<prach_processor_factory>
create_prach_processor_factory_sw(std::shared_ptr<ofdm_prach_demodulator_factory> ofdm_prach_factory,
                                  task_executor&                                  async_task_executor,
                                  sampling_rate                                   srate,
                                  unsigned                                        max_nof_ports,
                                  unsigned                                        max_nof_concurrent_requests);


} // namespace ocudu
