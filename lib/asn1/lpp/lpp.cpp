// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/asn1/lpp/lpp.cpp  (41 lines)
//
// LIBRARY: lib/asn1
// Auto-generated ASN.1 codec libraries for all 3GPP protocols: F1AP (TS 38.473), NGAP (TS 38.413), E1AP (TS 37.483), E2AP (O-RAN.WG3.E2AP), RRC-NR (TS 38.331), XnAP (TS 38.423), NRPPa (TS 38.455). Each is a separate static library. These files are generated from ASN.1 specifications and are very large but follow a uniform structure: one encode/decode function pair per IE.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/asn1/lpp/lpp.h"


using namespace asn1;
using namespace asn1::lpp;


const char* ellipsoid_point_s::latitude_sign_opts::to_string() const
{
  static const char* names[] = {"north", "south"};
  return convert_enum_idx(names, 2, value, "latitude_sign_e");
}

// Ellipsoid-Point ::= SEQUENCE

// Ellipsoid-Point ::= SEQUENCE
OCUDUASN_CODE ellipsoid_point_s::pack(bit_ref& bref) const
{
  HANDLE_CODE(latitude_sign.pack(bref));
  HANDLE_CODE(pack_integer(bref, degrees_latitude, (uint32_t)0u, (uint32_t)8388607u, false, false));
  HANDLE_CODE(pack_integer(bref, degrees_longitude, (int32_t)-8388608, (int32_t)8388607, false, false));


  return OCUDUASN_SUCCESS;
}


OCUDUASN_CODE ellipsoid_point_s::unpack(cbit_ref& bref)
{
  HANDLE_CODE(latitude_sign.unpack(bref));
  HANDLE_CODE(unpack_integer(degrees_latitude, bref, (uint32_t)0u, (uint32_t)8388607u, false, false));
  HANDLE_CODE(unpack_integer(degrees_longitude, bref, (int32_t)-8388608, (int32_t)8388607, false, false));


  return OCUDUASN_SUCCESS;
}
void ellipsoid_point_s::to_json(json_writer& j) const
{
  j.start_obj();
  j.write_str("latitudeSign", latitude_sign.to_string());
  j.write_int("degreesLatitude", degrees_latitude);
  j.write_int("degreesLongitude", degrees_longitude);
  j.end_obj();
}
