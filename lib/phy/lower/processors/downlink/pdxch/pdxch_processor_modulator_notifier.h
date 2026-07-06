// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/processors/downlink/pdxch/pdxch_processor_modulator_notifier.h  (29 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_dynamic.h"
#include "ocudu/phy/lower/lower_phy_baseband_metrics.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_baseband.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/support/memory_pool/bounded_object_pool.h"


namespace ocudu {

/// Physical downlink modulator notifier interface.

/// Physical downlink modulator notifier interface.
class pdxch_processor_modulator_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~pdxch_processor_modulator_notifier() = default;

  /// \brief Notifies the completion of the OFDM modulation for a given slot.
  /// \param[in] result  Baseband modulation results.
  /// \param[in] context Modulated resource grid context.

  /// \brief Notifies the completion of the OFDM modulation for a given slot.
  /// \param[in] result  Baseband modulation results.
  /// \param[in] context Modulated resource grid context.
  virtual void on_modulation_completion(pdxch_processor_baseband::slot_result result,
                                        resource_grid_context                 context) = 0;
};


} // namespace ocudu
