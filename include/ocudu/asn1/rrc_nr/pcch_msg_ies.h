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
// FILE: include/ocudu/asn1/rrc_nr/pcch_msg_ies.h  (171 lines)
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


#include "radio_bearer_cfg.h"


namespace asn1 {
namespace rrc_nr {

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// GroupPaging-r18 ::= SEQUENCE

/*******************************************************************************
 *                              Struct Definitions
 ******************************************************************************/

// GroupPaging-r18 ::= SEQUENCE
struct group_paging_r18_s {
  bool inactive_reception_allowed_r18_present = false;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// PagingUE-Identity ::= CHOICE

// PagingUE-Identity ::= CHOICE
struct paging_ue_id_c {
  struct types_opts {
    enum options { ng_5_g_s_tmsi, full_i_rnti, /*...*/ nulltype } value;
    typedef int8_t number_type;


    const char* to_string() const;
    int8_t      to_number() const;
  };
  using types = enumerated<types_opts, true>;

  // choice methods

  // choice methods
  paging_ue_id_c() = default;
  paging_ue_id_c(const paging_ue_id_c& other);
  paging_ue_id_c& operator=(const paging_ue_id_c& other);
  ~paging_ue_id_c() { destroy_(); }
  void          set(types::options e = types::nulltype);
  types         type() const { return type_; }
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
  // getters
  // getters
  fixed_bitstring<48>& ng_5_g_s_tmsi()
  {
    assert_choice_type(types::ng_5_g_s_tmsi, type_, "PagingUE-Identity");
    return c.get<fixed_bitstring<48>>();
  }
  fixed_bitstring<40>& full_i_rnti()
  {
    assert_choice_type(types::full_i_rnti, type_, "PagingUE-Identity");
    return c.get<fixed_bitstring<40>>();
  }
  const fixed_bitstring<48>& ng_5_g_s_tmsi() const
  {
    assert_choice_type(types::ng_5_g_s_tmsi, type_, "PagingUE-Identity");
    return c.get<fixed_bitstring<48>>();
  }
  const fixed_bitstring<40>& full_i_rnti() const
  {
    assert_choice_type(types::full_i_rnti, type_, "PagingUE-Identity");
    return c.get<fixed_bitstring<40>>();
  }
  fixed_bitstring<48>& set_ng_5_g_s_tmsi();
  fixed_bitstring<40>& set_full_i_rnti();


private:
  types                                type_;
  choice_buffer_t<fixed_bitstring<48>> c;


  void destroy_();
};

// PagingRecord ::= SEQUENCE

// PagingRecord ::= SEQUENCE
struct paging_record_s {
  bool           ext                 = false;
  bool           access_type_present = false;
  paging_ue_id_c ue_id;
  // ...

  // sequence methods
  // ...

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// PagingRecordList ::= SEQUENCE (SIZE (1..32)) OF PagingRecord

// PagingRecordList ::= SEQUENCE (SIZE (1..32)) OF PagingRecord
using paging_record_list_l = dyn_array<paging_record_s>;

// PagingRecord-v1700 ::= SEQUENCE

// PagingRecord-v1700 ::= SEQUENCE
struct paging_record_v1700_s {
  bool paging_cause_r17_present = false;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// PagingRecordList-v1700 ::= SEQUENCE (SIZE (1..32)) OF PagingRecord-v1700

// PagingRecordList-v1700 ::= SEQUENCE (SIZE (1..32)) OF PagingRecord-v1700
using paging_record_list_v1700_l = dyn_array<paging_record_v1700_s>;

// PagingGroupList-r17 ::= SEQUENCE (SIZE (1..32)) OF TMGI-r17

// PagingGroupList-r17 ::= SEQUENCE (SIZE (1..32)) OF TMGI-r17
using paging_group_list_r17_l = dyn_array<tmgi_r17_s>;

// PagingRecord-v1800 ::= SEQUENCE

// PagingRecord-v1800 ::= SEQUENCE
struct paging_record_v1800_s {
  bool mt_sdt_present = false;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// PagingRecordList-v1800 ::= SEQUENCE (SIZE (1..32)) OF PagingRecord-v1800

// PagingRecordList-v1800 ::= SEQUENCE (SIZE (1..32)) OF PagingRecord-v1800
using paging_record_list_v1800_l = dyn_array<paging_record_v1800_s>;

// PagingGroupList-v1800 ::= SEQUENCE (SIZE (1..32)) OF GroupPaging-r18

// PagingGroupList-v1800 ::= SEQUENCE (SIZE (1..32)) OF GroupPaging-r18
using paging_group_list_v1800_l = dyn_array<group_paging_r18_s>;

// Paging-v1800-IEs ::= SEQUENCE

// Paging-v1800-IEs ::= SEQUENCE
struct paging_v1800_ies_s {
  bool                       non_crit_ext_present = false;
  paging_record_list_v1800_l paging_record_list_v1800;
  paging_group_list_v1800_l  paging_group_list_v1800;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// Paging-v1700-IEs ::= SEQUENCE

// Paging-v1700-IEs ::= SEQUENCE
struct paging_v1700_ies_s {
  bool                       non_crit_ext_present = false;
  paging_record_list_v1700_l paging_record_list_v1700;
  paging_group_list_r17_l    paging_group_list_r17;
  paging_v1800_ies_s         non_crit_ext;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};

// Paging ::= SEQUENCE

// Paging ::= SEQUENCE
struct paging_s {
  bool                 non_crit_ext_present = false;
  paging_record_list_l paging_record_list;
  dyn_octstring        late_non_crit_ext;
  paging_v1700_ies_s   non_crit_ext;

  // sequence methods

  // sequence methods
  OCUDUASN_CODE pack(bit_ref& bref) const;
  OCUDUASN_CODE unpack(cbit_ref& bref);
  void          to_json(json_writer& j) const;
};


} // namespace rrc_nr
} // namespace asn1
