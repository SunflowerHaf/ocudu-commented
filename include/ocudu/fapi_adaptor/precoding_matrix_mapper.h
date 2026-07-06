// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/precoding_matrix_mapper.h  (83 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/mac/mac_cell_result.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/csi_report/csi_report_data.h"
#include <vector>


namespace ocudu {

/// MAC PDSCH precoding information.

/// MAC PDSCH precoding information.
struct mac_pdsch_precoding_info {
  /// \brief CSI-RS report.
  ///
  /// This field is empty for omnidirectional precoding.
  /// \brief CSI-RS report.
  ///
  /// This field is empty for omnidirectional precoding.
  std::optional<precoding_matrix_indicator> report;
};


struct mac_pdcch_precoding_info {};
struct mac_ssb_precoding_info {};
struct mac_csi_rs_precoding_info {};


namespace fapi_adaptor {

/// Precoding matrix mapper codebook offset configuration.

/// Precoding matrix mapper codebook offset configuration.
struct precoding_matrix_mapper_codebook_offset_configuration {
  /// Codebook offset for the omnidirectional PDSCH.
  /// Codebook offset for the omnidirectional PDSCH.
  unsigned pdsch_omni_offset;
  /// Codebook offsets for SSB. Each entry represents a layer.
  /// Codebook offsets for SSB. Each entry represents a layer.
  std::vector<unsigned> ssb_codebook_offsets;
  /// Codebook offsets for PDSCH. Each entry represents a layer.
  /// Codebook offsets for PDSCH. Each entry represents a layer.
  std::vector<unsigned> pdsch_codebook_offsets;
  /// Codebook offsets for PDCCH. Each entry represents a layer.
  /// Codebook offsets for PDCCH. Each entry represents a layer.
  std::vector<unsigned> pdcch_codebook_offsets;
  /// Codebook offsets for CSI-RS. Each entry represents a layer.
  /// Codebook offsets for CSI-RS. Each entry represents a layer.
  std::vector<unsigned> csi_rs_codebook_offsets;
};

/// \brief Precoding matrix mapper.
///
/// Maps the given arguments to a precoding matrix index.

/// \brief Precoding matrix mapper.
///
/// Maps the given arguments to a precoding matrix index.
class precoding_matrix_mapper
{
public:
  precoding_matrix_mapper(unsigned                                                     sector_id_,
                          unsigned                                                     nof_ports_,
                          const precoding_matrix_mapper_codebook_offset_configuration& config);

  /// Maps the given MAC precoding information into a precoding matrix index.

  /// Maps the given MAC precoding information into a precoding matrix index.
  unsigned map(const mac_pdsch_precoding_info& precoding_info, unsigned nof_layers) const;

  /// Maps the given MAC precoding information into a precoding matrix index.

  /// Maps the given MAC precoding information into a precoding matrix index.
  unsigned map(const mac_pdcch_precoding_info& precoding_info) const;

  /// Maps the given MAC precoding information into a precoding matrix index.

  /// Maps the given MAC precoding information into a precoding matrix index.
  unsigned map(const mac_csi_rs_precoding_info& precoding_info) const;

  /// Maps the given MAC precoding information into a precoding matrix index.

  /// Maps the given MAC precoding information into a precoding matrix index.
  unsigned map(const mac_ssb_precoding_info& precoding_info) const;


private:
  /// Sector identifier;
  /// Sector identifier;
  const unsigned sector_id;
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// Number of ports.
  /// Number of ports.
  const unsigned nof_ports;
  /// Codebook offset for the omnidirectional PDSCH.
  /// Codebook offset for the omnidirectional PDSCH.
  unsigned pdsch_omni_offset;
  /// Codebook offsets for SSB. Each entry represents a layer.
  /// Codebook offsets for SSB. Each entry represents a layer.
  std::vector<unsigned> ssb_codebook_offsets;
  /// Codebook offsets for PDSCH. Each entry represents a layer.
  /// Codebook offsets for PDSCH. Each entry represents a layer.
  std::vector<unsigned> pdsch_codebook_offsets;
  /// Codebook offsets for PDCCH. Each entry represents a layer.
  /// Codebook offsets for PDCCH. Each entry represents a layer.
  std::vector<unsigned> pdcch_codebook_offsets;
  /// Codebook offsets for CSI-RS. Each entry represents a layer.
  /// Codebook offsets for CSI-RS. Each entry represents a layer.
  std::vector<unsigned> csi_rs_codebook_offsets;
};


} // namespace fapi_adaptor
} // namespace ocudu
