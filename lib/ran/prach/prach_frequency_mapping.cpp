// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ran/prach/prach_frequency_mapping.cpp  (86 lines)
//
// LIBRARY: lib/ran
// Core RAN type definitions and utility functions shared by all layers. Contains: ARFCN/frequency helpers, band lookup tables, PRACH configuration tables, PDCCH/PUCCH/PUSCH resource element calculations, slot_point arithmetic, MCS tables, LDPC/polar code constants, PCI validation, PLMN/cell-identity types, QoS/S-NSSAI types, and more. The single most widely-included library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/ran/prach/prach_frequency_mapping.h"


using namespace ocudu;


prach_frequency_mapping_information ocudu::prach_frequency_mapping_get(prach_subcarrier_spacing prach_scs,
                                                                       subcarrier_spacing       pusch_scs)
{
  prach_frequency_mapping_information result = PRACH_FREQUENCY_MAPPING_INFORMATION_RESERVED;
  switch (prach_scs) {
    case prach_subcarrier_spacing::kHz1_25:
      if (pusch_scs == subcarrier_spacing::kHz15) {
        result.nof_rb_ra = 6;
        result.k_bar     = 7;
      } else if (pusch_scs == subcarrier_spacing::kHz30) {
        result.nof_rb_ra = 3;
        result.k_bar     = 1;
      } else if (pusch_scs == subcarrier_spacing::kHz60) {
        result.nof_rb_ra = 2;
        result.k_bar     = 133;
      }
      break;
    case prach_subcarrier_spacing::kHz5:
      if (pusch_scs == subcarrier_spacing::kHz15) {
        result.nof_rb_ra = 24;
        result.k_bar     = 12;
      } else if (pusch_scs == subcarrier_spacing::kHz30) {
        result.nof_rb_ra = 12;
        result.k_bar     = 10;
      } else if (pusch_scs == subcarrier_spacing::kHz60) {
        result.nof_rb_ra = 6;
        result.k_bar     = 7;
      }
      break;
    case prach_subcarrier_spacing::kHz15:
      if (pusch_scs == subcarrier_spacing::kHz15) {
        result.nof_rb_ra = 12;
        result.k_bar     = 2;
      } else if (pusch_scs == subcarrier_spacing::kHz30) {
        result.nof_rb_ra = 6;
        result.k_bar     = 2;
      } else if (pusch_scs == subcarrier_spacing::kHz60) {
        result.nof_rb_ra = 3;
        result.k_bar     = 2;
      }
      break;
    case prach_subcarrier_spacing::kHz30:
      if (pusch_scs == subcarrier_spacing::kHz15) {
        result.nof_rb_ra = 24;
        result.k_bar     = 2;
      } else if (pusch_scs == subcarrier_spacing::kHz30) {
        result.nof_rb_ra = 12;
        result.k_bar     = 2;
      } else if (pusch_scs == subcarrier_spacing::kHz60) {
        result.nof_rb_ra = 6;
        result.k_bar     = 2;
      }
      break;
    case prach_subcarrier_spacing::kHz60:
      if (pusch_scs == subcarrier_spacing::kHz60) {
        result.nof_rb_ra = 12;
        result.k_bar     = 2;
      } else if (pusch_scs == subcarrier_spacing::kHz120) {
        result.nof_rb_ra = 6;
        result.k_bar     = 2;
      }
      break;
    case prach_subcarrier_spacing::kHz120:
      if (pusch_scs == subcarrier_spacing::kHz60) {
        result.nof_rb_ra = 24;
        result.k_bar     = 2;
      } else if (pusch_scs == subcarrier_spacing::kHz120) {
        result.nof_rb_ra = 12;
        result.k_bar     = 2;
      }
      break;
    case prach_subcarrier_spacing::invalid:
      // Ignore.
      // Ignore.
      break;
  }


  return result;
}
