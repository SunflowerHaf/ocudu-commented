// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/json_generators/cu_up/f1u.h
//
// Purpose (plain English):
//   Generates JSON from CU-UP F1-U (user-plane) TX/RX metrics: packet counts, bytes, latency. The F1-U carries GTP-U user data between the DU and CU-UP.
//
//   Two entry points (consistent across all generators):
//     generate()        — returns a nlohmann::json object.
//     generate_string() — dumps that object to a UTF-8 string with optional indentation.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "external/nlohmann/json.hpp"
#include "ocudu/support/timers.h"
#include <string>


namespace ocudu {


namespace ocuup {
struct f1u_tx_metrics_container;
struct f1u_rx_metrics_container;
} // namespace ocuup


namespace app_helpers {
namespace json_generators {

/// Generates a nlohmann JSON object that codifies the given F1-U metrics.

/// Generates a nlohmann JSON object that codifies the given F1-U metrics.
nlohmann::json generate(const ocuup::f1u_tx_metrics_container& tx,
                        const ocuup::f1u_rx_metrics_container& rx,
                        timer_duration                         metrics_period);

/// Generates a string in JSON format that codifies the given F1-U metrics.

/// Generates a string in JSON format that codifies the given F1-U metrics.
std::string generate_string(const ocuup::f1u_tx_metrics_container& tx,
                            const ocuup::f1u_rx_metrics_container& rx,
                            timer_duration                         metrics_period,
                            int                                    indent = -1);


} // namespace json_generators
} // namespace app_helpers
} // namespace ocudu
