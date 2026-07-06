// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/f1ap_ue_id_types.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>


namespace ocudu {

/// \brief GNB-CU-UE-F1AP-ID used to identify the UE in the F1AP-CU.
/// \remark See TS 38.473 Section 9.3.1.4: GNB-CU-UE-F1AP-ID valid values: (0..2^32-1).

/// \brief GNB-CU-UE-F1AP-ID used to identify the UE in the F1AP-CU.
/// \remark See TS 38.473 Section 9.3.1.4: GNB-CU-UE-F1AP-ID valid values: (0..2^32-1).
constexpr uint64_t MAX_NOF_CU_F1AP_UES = uint64_t(1) << 32;
enum class gnb_cu_ue_f1ap_id_t : uint64_t { min = 0, max = MAX_NOF_CU_F1AP_UES - 1, invalid = 0x1ffffffff };

/// Converts a GNB-CU-UE-F1AP-ID to an integer.

/// Converts a GNB-CU-UE-F1AP-ID to an integer.
constexpr uint64_t gnb_cu_ue_f1ap_id_to_uint(gnb_cu_ue_f1ap_id_t id)
{
  return static_cast<uint64_t>(id);
}

/// Converts an integer to a GNB-CU-UE-F1AP-ID type.

/// Converts an integer to a GNB-CU-UE-F1AP-ID type.
constexpr gnb_cu_ue_f1ap_id_t int_to_gnb_cu_ue_f1ap_id(uint64_t idx)
{
  return static_cast<gnb_cu_ue_f1ap_id_t>(idx);
}

/// \brief GNB-DU-UE-F1AP-ID used to identify the UE in the F1AP-DU.
/// \remark See TS 38.473 Section 9.3.1.5: GNB-DU-UE-F1AP-ID valid values: (0..2^32-1).

/// \brief GNB-DU-UE-F1AP-ID used to identify the UE in the F1AP-DU.
/// \remark See TS 38.473 Section 9.3.1.5: GNB-DU-UE-F1AP-ID valid values: (0..2^32-1).
constexpr uint64_t MAX_NOF_DU_F1AP_UES = uint64_t(1) << 32;
enum class gnb_du_ue_f1ap_id_t : uint64_t { min = 0, max = MAX_NOF_DU_F1AP_UES - 1, invalid = 0x1ffffffff };

/// Converts a GNB-DU-UE-F1AP-ID to an integer.

/// Converts a GNB-DU-UE-F1AP-ID to an integer.
constexpr uint64_t gnb_du_ue_f1ap_id_to_uint(gnb_du_ue_f1ap_id_t id)
{
  return static_cast<uint64_t>(id);
}

/// Convert an integer to a GNB-DU-UE-F1AP-ID type.

/// Convert an integer to a GNB-DU-UE-F1AP-ID type.
constexpr gnb_du_ue_f1ap_id_t int_to_gnb_du_ue_f1ap_id(uint64_t idx)
{
  return static_cast<gnb_du_ue_f1ap_id_t>(idx);
}


} // namespace ocudu
