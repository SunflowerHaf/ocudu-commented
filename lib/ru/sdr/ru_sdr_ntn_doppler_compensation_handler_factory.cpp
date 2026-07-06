// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_sdr_ntn_doppler_compensation_handler_factory.cpp
 * @brief Factory for the SDR Radio Unit's NTN Doppler compensation handler.
 *
 * NTN (Non-Terrestrial Network) deployments — base stations on satellites —
 * experience significant Doppler shift due to the satellite's orbital
 * velocity (potentially several kHz of frequency shift, far more than a
 * terrestrial deployment ever sees). This handler allows the NTN
 * configuration manager (in apps/units/.../split_helpers/) to apply
 * pre-calculated Doppler compensation values to the radio's CFO controller.
 *
 * For a standard terrestrial deployment (no NTN cells configured), this
 * handler is created but never actually invoked, since the NTN configuration
 * manager itself is only created when NTN cells are present.
 */

#include "ocudu/ru/sdr/ru_sdr_ntn_doppler_compensation_handler_factory.h"
#include "ru_sdr_ntn_doppler_compensation_handler_impl.h"


using namespace ocudu;


/**
 * @brief Creates the SDR-specific NTN Doppler compensation handler.
 *
 * @param ru_ctrl  The Radio Unit controller — provides access to the CFO
 *                 controller that will actually apply the compensation.
 * @return A unique_ptr to the constructed handler.
 */
std::unique_ptr<ocudu::ocudu_ntn::ntn_doppler_compensation_handler>
ocudu::create_ru_sdr_ntn_doppler_compensation_handler(ru_controller& ru_ctrl)
{
  auto doppler_handler = std::make_unique<ru_sdr_ntn_doppler_compensation_handler_impl>(ru_ctrl);
  return doppler_handler;
}
