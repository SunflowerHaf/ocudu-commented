// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/precoding_matrix_table_generator.h  (19 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi_adaptor/precoding_matrix_mapper.h"
#include "ocudu/fapi_adaptor/precoding_matrix_repository.h"
#include <memory>
#include <tuple>


namespace ocudu {
namespace fapi_adaptor {

/// Generates the precoding matrix mapper and precoding matrix repository for the given number of antenna ports.

/// Generates the precoding matrix mapper and precoding matrix repository for the given number of antenna ports.
std::pair<std::unique_ptr<precoding_matrix_mapper>, std::unique_ptr<precoding_matrix_repository>>
generate_precoding_matrix_tables(unsigned nof_antenna_ports, unsigned sector_id);


} // namespace fapi_adaptor
} // namespace ocudu
