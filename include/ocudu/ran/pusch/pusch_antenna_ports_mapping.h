// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/pusch_antenna_ports_mapping.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/srs/srs_resource_configuration.h"


namespace ocudu {

/// \brief Returns the PUSCH antenna ports mapping row index in TS 38.212, table 7.3.1.2.2-6 to 7.3.1.2.2-23.
/// \param[in] nof_layers         Number of layers.
/// \param[in] transform_precoder Set to \c true if the transform precoder is used.
/// \param[in] dmrs_cfg_type      PUSCH DM-RS configuration type.
/// \param[in] dmrs_max_len       PUSCH DM-RS maximum number of OFDM symbols.
/// \return The PUSCH antenna ports mapping row index.

/// \brief Returns the PUSCH antenna ports mapping row index in TS 38.212, table 7.3.1.2.2-6 to 7.3.1.2.2-23.
/// \param[in] nof_layers         Number of layers.
/// \param[in] transform_precoder Set to \c true if the transform precoder is used.
/// \param[in] dmrs_cfg_type      PUSCH DM-RS configuration type.
/// \param[in] dmrs_max_len       PUSCH DM-RS maximum number of OFDM symbols.
/// \return The PUSCH antenna ports mapping row index.
unsigned get_pusch_antenna_port_mapping_row_index(unsigned         nof_layers,
                                                  bool             transform_precoder,
                                                  dmrs_config_type dmrs_cfg_type,
                                                  dmrs_max_length  dmrs_max_len);

/// \brief Returns the PUSCH precoding information mapping row index in TS 38.212, table 7.3.1.1.2-2/3/4/5.
/// \param[in] nof_layers Number of layers.
/// \param[in] max_rank   Maximum number of transmission layers.
/// \param[in] tpmi       PUSCH TPMI.
/// \return The PUSCH precoding information mapping row index.

/// \brief Returns the PUSCH precoding information mapping row index in TS 38.212, table 7.3.1.1.2-2/3/4/5.
/// \param[in] nof_layers Number of layers.
/// \param[in] max_rank   Maximum number of transmission layers.
/// \param[in] tpmi       PUSCH TPMI.
/// \return The PUSCH precoding information mapping row index.
unsigned get_pusch_precoding_info_row_index(unsigned                                      nof_layers,
                                            unsigned                                      max_rank,
                                            srs_resource_configuration::one_two_four_enum nof_srs_ports,
                                            unsigned                                      tpmi);


} // namespace ocudu
