// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/processors/downlink/downlink_processor_impl.h  (52 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "downlink_processor_baseband_impl.h"
#include "ocudu/adt/blocking_queue.h"
#include "ocudu/phy/lower/processors/downlink/downlink_processor.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor.h"


namespace ocudu {

/// Implements a software generic lower PHY downlink processor.

/// Implements a software generic lower PHY downlink processor.
class downlink_processor_impl : public lower_phy_downlink_processor
{
public:
  /// \brief Constructs a software generic lower PHY downlink processor that can process downlink resource grids.
  /// \param[in] pdxch_proc PDxCH processor.
  /// \param[in] config     Downlink processor configuration.
  /// \brief Constructs a software generic lower PHY downlink processor that can process downlink resource grids.
  /// \param[in] pdxch_proc PDxCH processor.
  /// \param[in] config     Downlink processor configuration.
  downlink_processor_impl(std::unique_ptr<pdxch_processor>                 pdxch_proc,
                          const downlink_processor_baseband_configuration& config);

  // See interface for documentation.

  // See interface for documentation.
  void connect(downlink_processor_notifier& notifier, pdxch_processor_notifier& pdxch_notifier) override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override { pdxch_proc->stop(); }

  // See interface for documentation.

  // See interface for documentation.
  baseband_cfo_processor& get_cfo_control() override;

  // See interface for documentation.

  // See interface for documentation.
  lower_phy_center_freq_controller& get_carrier_center_frequency_control() override;

  // See interface for documentation.

  // See interface for documentation.
  lower_phy_tx_time_offset_controller& get_tx_time_offset_control() override;

  // See interface for documentation.

  // See interface for documentation.
  pdxch_processor_request_handler& get_downlink_request_handler() override;

  // See interface for documentation.

  // See interface for documentation.
  downlink_processor_baseband& get_baseband() override;


private:
  /// PDxCH processor.
  /// PDxCH processor.
  std::unique_ptr<pdxch_processor> pdxch_proc;
  /// Baseband processor.
  /// Baseband processor.
  downlink_processor_baseband_impl downlink_proc_baseband;
};


} // namespace ocudu
