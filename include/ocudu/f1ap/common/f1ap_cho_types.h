// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/common/f1ap_cho_types.h  (13 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

/// \brief CHO trigger values for the inter-DU path (TS 38.473 Section 9.3.1.x).
/// Only cho_initiation and cho_replace are valid over the F1AP inter-DU interface.

/// \brief CHO trigger values for the inter-DU path (TS 38.473 Section 9.3.1.x).
/// Only cho_initiation and cho_replace are valid over the F1AP inter-DU interface.
enum class f1ap_cho_trigger { cho_initiation = 0, cho_replace };


} // namespace ocudu
