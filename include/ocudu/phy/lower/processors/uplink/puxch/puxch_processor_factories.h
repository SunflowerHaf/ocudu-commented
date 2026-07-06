// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/processors/uplink/puxch/puxch_processor_factories.h  (52 lines)
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
#include "ocudu/phy/lower/processors/uplink/puxch/puxch_processor.h"
#include "ocudu/phy/lower/sampling_rate.h"
#include <memory>


namespace ocudu {


class task_executor;

/// Collects the necessary parameters to create a PUxCH processor.

/// Collects the necessary parameters to create a PUxCH processor.
struct puxch_processor_configuration {
  /// Cyclic prefix.
  /// Cyclic prefix.
  cyclic_prefix cp;
  /// Subcarrier spacing.
  /// Subcarrier spacing.
  subcarrier_spacing scs;
  /// Sampling rate.
  /// Sampling rate.
  sampling_rate srate;
  /// Sector bandwidth as a number of resource blocks.
  /// Sector bandwidth as a number of resource blocks.
  unsigned bandwidth_rb;
  /// Offset of the DFT window as a fraction of the cyclic prefix [0, 1).
  /// Offset of the DFT window as a fraction of the cyclic prefix [0, 1).
  float dft_window_offset;
  /// Uplink center frequency in Hz.
  /// Uplink center frequency in Hz.
  double center_freq_Hz;
  /// Number of receive ports.
  /// Number of receive ports.
  unsigned nof_rx_ports;
};

/// Lower physical layer PUxCH processor - Factory interface.

/// Lower physical layer PUxCH processor - Factory interface.
class puxch_processor_factory
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~puxch_processor_factory() = default;

  /// Creates a lower PHY PUxCH processor.

  /// Creates a lower PHY PUxCH processor.
  virtual std::unique_ptr<puxch_processor> create(const puxch_processor_configuration& config) = 0;
};

/// \brief Creates a software based PUxCH processor factory.
///
/// \param ofdm_demod_factory OFDM demodulator factory.
/// \return A PUxCH processor factory.

/// \brief Creates a software based PUxCH processor factory.
///
/// \param ofdm_demod_factory OFDM demodulator factory.
/// \return A PUxCH processor factory.
std::shared_ptr<puxch_processor_factory>
create_puxch_processor_factory_sw(std::shared_ptr<ofdm_demodulator_factory> ofdm_demod_factory);


} // namespace ocudu
