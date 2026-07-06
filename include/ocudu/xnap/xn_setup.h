// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/xnap/xn_setup.h  (17 lines)
//
// INTERFACE HEADER — include/ocudu/xnap
// XnAP interface headers: xnc_connection_gateway (the Xn socket connection interface), XnAP message handler interfaces for the handover and Xn Setup procedures.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/plmn_identity.h"
#include <cstdint>


namespace ocudu::ocucp {


struct xnap_amf_region_info_item {
  plmn_identity plmn = plmn_identity::test_value();
  uint8_t       amf_region_id;
};


} // namespace ocudu::ocucp
