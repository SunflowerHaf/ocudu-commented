// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/time_alignment_estimator/time_alignment_estimator_factories.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/generic_functions/generic_functions_factories.h"
#include "ocudu/phy/support/time_alignment_estimator/time_alignment_estimator.h"
#include <memory>


namespace ocudu {

/// Time alignment estimator factory interface.

/// Time alignment estimator factory interface.
class time_alignment_estimator_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~time_alignment_estimator_factory() = default;

  /// Creates a time alignment estimator.

  /// Creates a time alignment estimator.
  virtual std::unique_ptr<time_alignment_estimator> create() = 0;
};

/// Creates a time alignment estimator factory based on DFT.

/// Creates a time alignment estimator factory based on DFT.
std::shared_ptr<time_alignment_estimator_factory>
create_time_alignment_estimator_dft_factory(std::shared_ptr<dft_processor_factory> dft_proc_factory);


} // namespace ocudu
