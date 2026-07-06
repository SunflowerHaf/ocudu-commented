// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/asn1/asn1_json_utils.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/asn1
// ASN.1 interface headers: the public types and decode/encode function declarations for all 3GPP ASN.1 message structures. Separate sub-namespaces for f1ap, ngap, e1ap, e2ap, rrc_nr, xnap, nrppa, s1ap. These headers expose only the C++ structs corresponding to each ASN.1 Information Element (IE).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "nlohmann/json.hpp"
#include "ocudu/asn1/asn1_utils.h"


namespace asn1 {


inline void to_json(nlohmann::json& out_j, const real_s& obj)
{
  out_j = obj.value;
}


inline void from_json(const nlohmann::json& in_j, real_s& obj)
{
  in_j.get_to(obj.value);
}


inline void to_json(nlohmann::ordered_json& out_j, const real_s& obj)
{
  out_j = obj.value;
}


inline void from_json(const nlohmann::ordered_json& in_j, real_s& obj)
{
  in_j.get_to(obj.value);
}


} // namespace asn1
