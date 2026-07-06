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
// FILE: include/ocudu/asn1/rrc_nr/ul_ccch_msg_ies.h  (329 lines)
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

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// EstablishmentCause ::= ENUMERATED

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// EstablishmentCause ::= ENUMERATED
struct establishment_cause_opts {
  enum options {
    emergency,
    high_prio_access,
    mt_access,
    mo_sig,
    mo_data,
    mo_voice_call,
    mo_video_call,
    mo_sms,
    mps_prio_access,
    mcs_prio_access,
    spare6,
    spare5,
    spare4,
    spare3,
    spare2,
    spare1,
    nulltype
  } value;


  const char* to_string() const;
};
using establishment_cause_e = enumerated<establishment_cause_opts>;

// InitialUE-Identity ::= CHOICE

// InitialUE-Identity ::= CHOICE
struct init_ue_id_c {
  struct types_opts {
    enum options { ng_5_g_s_tmsi_part1, random_value, nulltype } value;
    typedef int8_t number_type;


    const char* to_string() const;
    int8_t      to_number() const;
  };
  using types = enumerated<types_opts>;

  // choice methods

  // choice methods
  init_ue_id_c() = default;
  init_ue_id_c(const init_ue_id_c& other);
  init_ue_id_c& operator=(const init_ue_id_c& other);
  ~init_ue_id_c() { destroy_(); }
  void          set(types::options e = types::nulltype);
  types         type() const { return type_; }
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
  // getters
  // getters
  fixed_bitstring<39>& ng_5_g_s_tmsi_part1()
  {
    assert_choice_type(types::ng_5_g_s_tmsi_part1, type_, "InitialUE-Identity");
    return c.get<fixed_bitstring<39>>();
  }
  fixed_bitstring<39>& random_value()
  {
    assert_choice_type(types::random_value, type_, "InitialUE-Identity");
    return c.get<fixed_bitstring<39>>();
  }
  const fixed_bitstring<39>& ng_5_g_s_tmsi_part1() const
  {
    assert_choice_type(types::ng_5_g_s_tmsi_part1, type_, "InitialUE-Identity");
    return c.get<fixed_bitstring<39>>();
  }
  const fixed_bitstring<39>& random_value() const
  {
    assert_choice_type(types::random_value, type_, "InitialUE-Identity");
    return c.get<fixed_bitstring<39>>();
  }
  fixed_bitstring<39>& set_ng_5_g_s_tmsi_part1();
  fixed_bitstring<39>& set_random_value();


private:
  types                                type_;
  choice_buffer_t<fixed_bitstring<39>> c;


  void destroy_();
};

// RRC-PosSystemInfoRequest-r16-IEs ::= SEQUENCE

// RRC-PosSystemInfoRequest-r16-IEs ::= SEQUENCE
struct rrc_pos_sys_info_request_r16_ies_s {
  fixed_bitstring<32> requested_pos_si_list;
  fixed_bitstring<11> spare;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// ReestabUE-Identity ::= SEQUENCE

// ReestabUE-Identity ::= SEQUENCE
struct reestab_ue_id_s {
  uint32_t            c_rnti = 0;
  uint16_t            pci    = 0;
  fixed_bitstring<16> short_mac_i;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// ReestablishmentCause ::= ENUMERATED

// ReestablishmentCause ::= ENUMERATED
struct reest_cause_opts {
  enum options { recfg_fail, ho_fail, other_fail, spare1, nulltype } value;


  const char* to_string() const;
};
using reest_cause_e = enumerated<reest_cause_opts>;

// RRCReestablishmentRequest-IEs ::= SEQUENCE

// RRCReestablishmentRequest-IEs ::= SEQUENCE
struct rrc_reest_request_ies_s {
  reestab_ue_id_s    ue_id;
  reest_cause_e      reest_cause;
  fixed_bitstring<1> spare;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// RRCReestablishmentRequest ::= SEQUENCE

// RRCReestablishmentRequest ::= SEQUENCE
struct rrc_reest_request_s {
  rrc_reest_request_ies_s rrc_reest_request;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// ResumeCause ::= ENUMERATED

// ResumeCause ::= ENUMERATED
struct resume_cause_opts {
  enum options {
    emergency,
    high_prio_access,
    mt_access,
    mo_sig,
    mo_data,
    mo_voice_call,
    mo_video_call,
    mo_sms,
    rna_upd,
    mps_prio_access,
    mcs_prio_access,
    mt_sdt_v1810,
    srs_pos_cfg_or_activation_req_v1800,
    spare3,
    spare2,
    spare1,
    nulltype
  } value;


  const char* to_string() const;
};
using resume_cause_e = enumerated<resume_cause_opts>;

// RRCResumeRequest-IEs ::= SEQUENCE

// RRCResumeRequest-IEs ::= SEQUENCE
struct rrc_resume_request_ies_s {
  fixed_bitstring<24> resume_id;
  fixed_bitstring<16> resume_mac_i;
  resume_cause_e      resume_cause;
  fixed_bitstring<1>  spare;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// RRCResumeRequest ::= SEQUENCE

// RRCResumeRequest ::= SEQUENCE
struct rrc_resume_request_s {
  rrc_resume_request_ies_s rrc_resume_request;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// RRCSetupRequest-IEs ::= SEQUENCE

// RRCSetupRequest-IEs ::= SEQUENCE
struct rrc_setup_request_ies_s {
  init_ue_id_c          ue_id;
  establishment_cause_e establishment_cause;
  fixed_bitstring<1>    spare;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// RRCSetupRequest ::= SEQUENCE

// RRCSetupRequest ::= SEQUENCE
struct rrc_setup_request_s {
  rrc_setup_request_ies_s rrc_setup_request;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// RRCSystemInfoRequest-IEs ::= SEQUENCE

// RRCSystemInfoRequest-IEs ::= SEQUENCE
struct rrc_sys_info_request_ies_s {
  fixed_bitstring<32> requested_si_list;
  fixed_bitstring<12> spare;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// RRCSystemInfoRequest ::= SEQUENCE

// RRCSystemInfoRequest ::= SEQUENCE
struct rrc_sys_info_request_s {
  struct crit_exts_c_ {
    struct crit_exts_future_r16_c_ {
      struct types_opts {
        enum options { rrc_pos_sys_info_request_r16, crit_exts_future, nulltype } value;


        const char* to_string() const;
      };
      using types = enumerated<types_opts>;

      // choice methods

      // choice methods
      crit_exts_future_r16_c_() = default;
      void          set(types::options e = types::nulltype);
      types         type() const { return type_; }
      OCUDUASN_CODE pack(bit_ref& bref) const;
      OCUDUASN_CODE unpack(cbit_ref& bref);
      void          to_json(json_writer& j) const;
      // getters
      // getters
      rrc_pos_sys_info_request_r16_ies_s& rrc_pos_sys_info_request_r16()
      {
        assert_choice_type(types::rrc_pos_sys_info_request_r16, type_, "criticalExtensionsFuture-r16");
        return c;
      }
      const rrc_pos_sys_info_request_r16_ies_s& rrc_pos_sys_info_request_r16() const
      {
        assert_choice_type(types::rrc_pos_sys_info_request_r16, type_, "criticalExtensionsFuture-r16");
        return c;
      }
      rrc_pos_sys_info_request_r16_ies_s& set_rrc_pos_sys_info_request_r16();
      void                                set_crit_exts_future();


    private:
      types                              type_;
      rrc_pos_sys_info_request_r16_ies_s c;
    };
    struct types_opts {
      enum options { rrc_sys_info_request, crit_exts_future_r16, nulltype } value;


      const char* to_string() const;
    };
    using types = enumerated<types_opts>;

    // choice methods

    // choice methods
    crit_exts_c_() = default;
    crit_exts_c_(const crit_exts_c_& other);
    crit_exts_c_& operator=(const crit_exts_c_& other);
    ~crit_exts_c_() { destroy_(); }
    void          set(types::options e = types::nulltype);
    types         type() const { return type_; }
    OCUDUASN_CODE pack(bit_ref& bref) const;
    OCUDUASN_CODE unpack(cbit_ref& bref);
    void          to_json(json_writer& j) const;
    // getters
    // getters
    rrc_sys_info_request_ies_s& rrc_sys_info_request()
    {
      assert_choice_type(types::rrc_sys_info_request, type_, "criticalExtensions");
      return c.get<rrc_sys_info_request_ies_s>();
    }
    crit_exts_future_r16_c_& crit_exts_future_r16()
    {
      assert_choice_type(types::crit_exts_future_r16, type_, "criticalExtensions");
      return c.get<crit_exts_future_r16_c_>();
    }
    const rrc_sys_info_request_ies_s& rrc_sys_info_request() const
    {
      assert_choice_type(types::rrc_sys_info_request, type_, "criticalExtensions");
      return c.get<rrc_sys_info_request_ies_s>();
    }
    const crit_exts_future_r16_c_& crit_exts_future_r16() const
    {
      assert_choice_type(types::crit_exts_future_r16, type_, "criticalExtensions");
      return c.get<crit_exts_future_r16_c_>();
    }
    rrc_sys_info_request_ies_s& set_rrc_sys_info_request();
    crit_exts_future_r16_c_&    set_crit_exts_future_r16();


  private:
    types                                                                type_;
    choice_buffer_t<crit_exts_future_r16_c_, rrc_sys_info_request_ies_s> c;


    void destroy_();
  };

  // member variables

  // member variables
  crit_exts_c_ crit_exts;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};


} // namespace rrc_nr
} // namespace asn1
