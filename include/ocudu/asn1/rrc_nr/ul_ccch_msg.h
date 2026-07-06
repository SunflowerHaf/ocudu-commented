// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/*******************************************************************************
 *
 *                    3GPP TS ASN1 RRC NR v18.8.0 (2025-12)
 *
 ******************************************************************************/

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/asn1/rrc_nr/ul_ccch_msg.h  (140 lines)
//
// INTERFACE HEADER — include/ocudu/asn1
// ASN.1 interface headers: the public types and decode/encode function declarations for all 3GPP ASN.1 message structures. Separate sub-namespaces for f1ap, ngap, e1ap, e2ap, rrc_nr, xnap, nrppa, s1ap. These headers expose only the C++ structs corresponding to each ASN.1 Information Element (IE).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/*******************************************************************************
 *
 *                    3GPP TS ASN1 RRC NR v18.8.0 (2025-12)
 *
 ******************************************************************************/

#pragma once


#include "ocudu/asn1/asn1_utils.h"


namespace asn1 {
namespace rrc_nr {


struct rrc_setup_request_s;
struct rrc_resume_request_s;
struct rrc_reest_request_s;
struct rrc_sys_info_request_s;

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// UL-CCCH-MessageType ::= CHOICE

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// UL-CCCH-MessageType ::= CHOICE
struct ul_ccch_msg_type_c {
  struct c1_c_ {
    struct types_opts {
      enum options { rrc_setup_request, rrc_resume_request, rrc_reest_request, rrc_sys_info_request, nulltype } value;


      const char* to_string() const;
    };
    using types = enumerated<types_opts>;

    // choice methods

    // choice methods
    c1_c_() = default;
    void          set(types::options e = types::nulltype);
    types         type() const { return type_; }
    OCUDUASN_CODE pack(bit_ref& bref) const;
    OCUDUASN_CODE unpack(cbit_ref& bref);
    void          to_json(json_writer& j) const;
    // getters
    // getters
    rrc_setup_request_s& rrc_setup_request()
    {
      assert_choice_type(types::rrc_setup_request, type_, "c1");
      return c.get<rrc_setup_request_s>();
    }
    rrc_resume_request_s& rrc_resume_request()
    {
      assert_choice_type(types::rrc_resume_request, type_, "c1");
      return c.get<rrc_resume_request_s>();
    }
    rrc_reest_request_s& rrc_reest_request()
    {
      assert_choice_type(types::rrc_reest_request, type_, "c1");
      return c.get<rrc_reest_request_s>();
    }
    rrc_sys_info_request_s& rrc_sys_info_request()
    {
      assert_choice_type(types::rrc_sys_info_request, type_, "c1");
      return c.get<rrc_sys_info_request_s>();
    }
    const rrc_setup_request_s& rrc_setup_request() const
    {
      assert_choice_type(types::rrc_setup_request, type_, "c1");
      return c.get<rrc_setup_request_s>();
    }
    const rrc_resume_request_s& rrc_resume_request() const
    {
      assert_choice_type(types::rrc_resume_request, type_, "c1");
      return c.get<rrc_resume_request_s>();
    }
    const rrc_reest_request_s& rrc_reest_request() const
    {
      assert_choice_type(types::rrc_reest_request, type_, "c1");
      return c.get<rrc_reest_request_s>();
    }
    const rrc_sys_info_request_s& rrc_sys_info_request() const
    {
      assert_choice_type(types::rrc_sys_info_request, type_, "c1");
      return c.get<rrc_sys_info_request_s>();
    }
    rrc_setup_request_s&    set_rrc_setup_request();
    rrc_resume_request_s&   set_rrc_resume_request();
    rrc_reest_request_s&    set_rrc_reest_request();
    rrc_sys_info_request_s& set_rrc_sys_info_request();


  private:
    types             type_;
    choice_buffer_ptr c;
  };
  struct types_opts {
    enum options { c1, msg_class_ext, nulltype } value;
    typedef uint8_t number_type;


    const char* to_string() const;
    uint8_t     to_number() const;
  };
  using types = enumerated<types_opts>;

  // choice methods

  // choice methods
  ul_ccch_msg_type_c() = default;
  void          set(types::options e = types::nulltype);
  types         type() const { return type_; }
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
  // getters
  // getters
  c1_c_& c1()
  {
    assert_choice_type(types::c1, type_, "UL-CCCH-MessageType");
    return c;
  }
  const c1_c_& c1() const
  {
    assert_choice_type(types::c1, type_, "UL-CCCH-MessageType");
    return c;
  }
  c1_c_& set_c1();
  void   set_msg_class_ext();


private:
  types type_;
  c1_c_ c;
};

// UL-CCCH-Message ::= SEQUENCE

// UL-CCCH-Message ::= SEQUENCE
struct ul_ccch_msg_s {
  ul_ccch_msg_type_c msg;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};


} // namespace rrc_nr
} // namespace asn1
