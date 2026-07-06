// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/csi_report/csi_report_configuration.h  (104 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/adt/bounded_integer.h"
#include "ocudu/ran/precoding/precoding_codebook_configuration.h"


namespace ocudu {

/// Maximum number of measured Resource Sets (RS) per report, as defined by the maximum value of the higher layer
/// parameter \e nrofReportedRS in IE \e CSI-ReportConfig.

/// Maximum number of measured Resource Sets (RS) per report, as defined by the maximum value of the higher layer
/// parameter \e nrofReportedRS in IE \e CSI-ReportConfig.
static constexpr unsigned csi_max_nof_reported_rs = 4;

/// Maximum number of CSI reporting subbands. The range is deduced from TS38.214 Table 5.2.1.4-2.

/// Maximum number of CSI reporting subbands. The range is deduced from TS38.214 Table 5.2.1.4-2.
static constexpr unsigned csi_max_nof_subbands = 18;

/// CSI reporting configuration type.

/// CSI reporting configuration type.
enum class csi_report_type { periodic, aperiodic };

/// \brief CSI Rank Indicator restriction type.
///
/// The RI restriction field is described in TS38.331 Section 6.3.2, Information Element \e CodebookConfig. The
/// bit-width of this field must be equal to the number of CSI-RS transmit number of antennas.

/// \brief CSI Rank Indicator restriction type.
///
/// The RI restriction field is described in TS38.331 Section 6.3.2, Information Element \e CodebookConfig. The
/// bit-width of this field must be equal to the number of CSI-RS transmit number of antennas.
using ri_restriction_type = bounded_bitset<8U>;

/// \brief CSI report quantities.
///
/// Described in TS38.331 Section 6.3.2, Information Element \e CSI-ReportConfig.

/// \brief CSI report quantities.
///
/// Described in TS38.331 Section 6.3.2, Information Element \e CSI-ReportConfig.
enum class csi_report_quantities {
  /// CSI report contains the quantities CRI, RI, PMI and wideband CQI.
  /// CSI report contains the quantities CRI, RI, PMI and wideband CQI.
  cri_ri_pmi_cqi = 0,
  /// CSI report contains the quantities CRI, RI and wideband CQI.
  /// CSI report contains the quantities CRI, RI and wideband CQI.
  cri_ri_cqi,
  /// CSI report contains the quantities CRI and RSRP.
  /// CSI report contains the quantities CRI and RSRP.
  cri_rsrp,
  /// CSI report contains the quantities SSB index, and RSRP.
  /// CSI report contains the quantities SSB index, and RSRP.
  ssb_index_rsrp,
  /// CSI report contains the quantities CRI, RI, LI, PMI and wideband CQI.
  /// CSI report contains the quantities CRI, RI, LI, PMI and wideband CQI.
  cri_ri_li_pmi_cqi,
  /// Other CSI report quantity configuration. Not supported.
  /// Other CSI report quantity configuration. Not supported.
  other
};

/// Collects Channel State Information (CSI) report subband configuration parameters.

/// Collects Channel State Information (CSI) report subband configuration parameters.
struct csi_report_subband_configuration {
  /// Enable subband CQI field.
  /// Enable subband CQI field.
  bool cqi;
  /// Enabled subband PMI field.
  /// Enabled subband PMI field.
  bool pmi;
  /// \brief Number of subbands in {5..18}.
  ///
  /// Range deduced from TS38.214 Table 5.2.1.4-2. The minimum number of subbands is 5 and the maximum 18.
  /// \brief Number of subbands in {5..18}.
  ///
  /// Range deduced from TS38.214 Table 5.2.1.4-2. The minimum number of subbands is 5 and the maximum 18.
  bounded_integer<uint8_t, 5, csi_max_nof_subbands> nof_subbands;
};

/// Collects Channel State Information (CSI) report configuration parameters.

/// Collects Channel State Information (CSI) report configuration parameters.
struct csi_report_configuration {
  /// \brief Number of CSI-RS resources in the corresponding resource set.
  ///
  /// Corresponds to parameter \f$K^\textup{SSB}_{s}\f$ as per TS38.212 Section 6.3.1.1.2 if the report
  /// quantities is set to \c csi_report_quantities::ssb_index_rsrp. Otherwise, it corresponds to parameter
  /// \f$K^\textup{CSI-RS}_{s}\f$ as per TS38.212 Section 6.3.1.1.2.
  /// \brief Number of CSI-RS resources in the corresponding resource set.
  ///
  /// Corresponds to parameter \f$K^\textup{SSB}_{s}\f$ as per TS38.212 Section 6.3.1.1.2 if the report
  /// quantities is set to \c csi_report_quantities::ssb_index_rsrp. Otherwise, it corresponds to parameter
  /// \f$K^\textup{CSI-RS}_{s}\f$ as per TS38.212 Section 6.3.1.1.2.
  unsigned nof_csi_rs_resources;
  /// \brief Number of reported Resource Sets (RS).
  ///
  /// This parameter is used for measurements quantities \c csi_report_quantities::cri_rsrp and \c
  /// csi_report_quantities::ssb_index_rsrp.
  ///
  /// The number of reported Resource Sets is given by the higher layer parameter \e nrofReportedRS if present and
  /// \e groupBasedBeamReporting is disabled in IE \e CSI-ReportConfig. Otherwise, it is set to 1.
  /// \brief Number of reported Resource Sets (RS).
  ///
  /// This parameter is used for measurements quantities \c csi_report_quantities::cri_rsrp and \c
  /// csi_report_quantities::ssb_index_rsrp.
  ///
  /// The number of reported Resource Sets is given by the higher layer parameter \e nrofReportedRS if present and
  /// \e groupBasedBeamReporting is disabled in IE \e CSI-ReportConfig. Otherwise, it is set to 1.
  bounded_integer<uint8_t, 1, csi_max_nof_reported_rs> nof_reported_rs;
  /// CSI-RS PMI codebook configuration.
  /// CSI-RS PMI codebook configuration.
  pmi_codebook_config pmi_codebook;
  /// Set to true the bits in position \f$i\f$ to enable RI reporting for \f$\upsilon + i\f$.
  /// Set to true the bits in position \f$i\f$ to enable RI reporting for \f$\upsilon + i\f$.
  ri_restriction_type ri_restriction;
  /// Select CSI report quantities.
  /// Select CSI report quantities.
  csi_report_quantities quantities;
  /// Subband configuration parameters. Set to \c std::nullopt for no subband reporting.
  /// Subband configuration parameters. Set to \c std::nullopt for no subband reporting.
  std::optional<csi_report_subband_configuration> subband;
};


inline const char* to_string(csi_report_quantities quantities)
{
  switch (quantities) {
    case csi_report_quantities::cri_ri_pmi_cqi:
      return "cri-ri-pmi-cqi";
    case csi_report_quantities::cri_ri_cqi:
      return "cri-ri-cqi";
    case csi_report_quantities::cri_rsrp:
      return "cri-rsrp";
    case csi_report_quantities::ssb_index_rsrp:
      return "ssb-index-rsrp";
    case csi_report_quantities::cri_ri_li_pmi_cqi:
      return "cri-ri-li-pmi-cqi";
    case csi_report_quantities::other:
    default:
      return "other";
  }
}


} // namespace ocudu
