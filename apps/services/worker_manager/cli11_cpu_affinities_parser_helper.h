// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// FILE: services/worker_manager/cli11_cpu_affinities_parser_helper.h (15 lines)
// Part of the apps/services infrastructure layer.

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <string>


namespace ocudu {


struct os_sched_affinity_bitmask;


void parse_affinity_mask(os_sched_affinity_bitmask& mask, const std::string& value, const std::string& property_name);


} // namespace ocudu
