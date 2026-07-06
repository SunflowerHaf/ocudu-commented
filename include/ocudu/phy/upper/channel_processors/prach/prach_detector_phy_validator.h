// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Declaration of the validator of PRACH configurations at the PHY layer.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/prach/prach_detector_phy_validator.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Declaration of the validator of PRACH configurations at the PHY layer.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/prach/prach_subcarrier_spacing.h"


namespace ocudu {

/// \brief Ensures the PRACH configuration is supported by the detector.
///
/// \param[in] format                   PRACH format.
/// \param[in] scs                      PRACH subcarrier spacing.
/// \param[in] zero_correlation_zone    PRACH zero correlation zone.
/// \param[in] nof_rx_ports             Number of receive antenna ports.
/// \return A success if the PRACH configuration is support by the detector, an error message otherwise.

/// \brief Ensures the PRACH configuration is supported by the detector.
///
/// \param[in] format                   PRACH format.
/// \param[in] scs                      PRACH subcarrier spacing.
/// \param[in] zero_correlation_zone    PRACH zero correlation zone.
/// \param[in] nof_rx_ports             Number of receive antenna ports.
/// \return A success if the PRACH configuration is support by the detector, an error message otherwise.
error_type<std::string> validate_prach_detector_phy(prach_format_type        format,
                                                    prach_subcarrier_spacing scs,
                                                    unsigned                 zero_correlation_zone,
                                                    unsigned                 nof_rx_ports);


} // namespace ocudu
