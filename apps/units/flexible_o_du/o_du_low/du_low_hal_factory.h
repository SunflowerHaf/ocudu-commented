// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_hal_factory.h
//
// Purpose (plain English):
//   Public interface for building HAL (hardware-accelerator) dependencies
//   for the DU-Low.
//
//   In your USRP/UHD software build there is no hardware PHY accelerator, so
//   both fields of o_du_low_hal_dependencies come back as nullptr and the
//   upper PHY uses its pure-software LDPC encoder/decoder. This scaffolding
//   exists so that a build with an Intel ACC100 (via DPDK BBDEV) — or any
//   future accelerator card — can be dropped in without touching the rest
//   of the DU-Low code.
// =============================================================================

#pragma once


#include "du_low_config.h"
#include "ocudu/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc_factory.h"
#include "ocudu/hal/phy/upper/channel_processors/pusch/hw_accelerator_pusch_dec_factory.h"


namespace ocudu {

/// O-RAN DU low unit HAL dependencies.

/// \brief Hardware-accelerator factories the upper PHY may use.
///
/// Both are shared_ptrs so they can outlive the DU-Low object (in the DPDK
/// case the accelerator is opened once and then shared across cells).
/// A nullptr means "software fallback".
struct o_du_low_hal_dependencies {
  std::shared_ptr<hal::hw_accelerator_pdsch_enc_factory> hw_encoder_factory = nullptr;
  std::shared_ptr<hal::hw_accelerator_pusch_dec_factory> hw_decoder_factory = nullptr;
};

/// \brief Initializes the HAL depencies of the DU low unit.
/// \param[out] hal_config Struct defining the DU low HAL configuration
/// \return  Struct containing the DU low unit dependencies.

/// \brief Initialises DU-Low HAL dependencies from the (optional) HAL config.
/// \param[in] hal_config  Parsed HAL config from the YAML; may be empty.
/// \return                A struct with encoder/decoder factories, or nullptrs
///                        if HAL isn't used (or the build lacks DPDK support).
o_du_low_hal_dependencies make_du_low_hal_dependencies(const std::optional<du_low_unit_hal_config>& hal_config);


} // namespace ocudu
