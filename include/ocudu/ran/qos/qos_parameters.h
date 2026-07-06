// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/qos/qos_parameters.h  (137 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/qos/arp_prio_level.h"
#include "ocudu/ran/qos/five_qi.h"
#include "ocudu/ran/qos/packet_error_rate.h"
#include "ocudu/ran/qos/qos_prio_level.h"
#include <optional>
#include <variant>


namespace ocudu {


struct dyn_5qi_descriptor {
  qos_prio_level_t         qos_prio_level;
  uint16_t                 packet_delay_budget;
  packet_error_rate_t      per;
  std::optional<five_qi_t> five_qi;
  std::optional<bool>      is_delay_critical;
  /// This parameter should be present if the GBR QoS Flow information is set.
  /// This parameter should be present if the GBR QoS Flow information is set.
  std::optional<uint16_t> averaging_win;
  /// This parameter should be present if the GBR QoS Flow information is set.
  /// This parameter should be present if the GBR QoS Flow information is set.
  std::optional<uint16_t> max_data_burst_volume;


  bool operator==(const dyn_5qi_descriptor& other) const
  {
    return qos_prio_level == other.qos_prio_level and packet_delay_budget == other.packet_delay_budget and
           per == other.per and five_qi == other.five_qi and is_delay_critical == other.is_delay_critical and
           averaging_win == other.averaging_win and max_data_burst_volume == other.max_data_burst_volume;
  }
};


struct non_dyn_5qi_descriptor {
  /// Standardized 5QI. Must contain one of the 5QIs in TS23.501, Table 5.7.4-1. The default is a non-GBR 5QI.
  /// Standardized 5QI. Must contain one of the 5QIs in TS23.501, Table 5.7.4-1. The default is a non-GBR 5QI.
  five_qi_t five_qi = uint_to_five_qi(9);
  /// Priority level, in case the default priority level specified in TS23.501, Table 5.7.4-1 is not used.
  /// Priority level, in case the default priority level specified in TS23.501, Table 5.7.4-1 is not used.
  std::optional<qos_prio_level_t> qos_prio_level;
  /// Averaging Window, in case the default value specified in TS23.501, Table 5.7.4-1 is not used.
  /// Averaging Window, in case the default value specified in TS23.501, Table 5.7.4-1 is not used.
  std::optional<uint16_t> averaging_win;
  /// \brief Maximum Data Burst Volume, in case the default value specified in TS23.501, Table 5.7.4-1 is not used.
  /// This value should only be used in delay-critical GBR DRBs.
  /// \brief Maximum Data Burst Volume, in case the default value specified in TS23.501, Table 5.7.4-1 is not used.
  /// This value should only be used in delay-critical GBR DRBs.
  std::optional<uint16_t> max_data_burst_volume;


  bool operator==(const non_dyn_5qi_descriptor& other) const
  {
    return five_qi == other.five_qi and qos_prio_level == other.qos_prio_level and
           averaging_win == other.averaging_win and max_data_burst_volume == other.max_data_burst_volume;
  }
};

/// QoS Parameters of either a dynamic or non-dynamic 5QI.

/// QoS Parameters of either a dynamic or non-dynamic 5QI.
struct qos_characteristics {
  qos_characteristics() : choice(non_dyn_5qi_descriptor{}) {}
  qos_characteristics(const non_dyn_5qi_descriptor& val) : choice(val) {}
  qos_characteristics(const dyn_5qi_descriptor& val) : choice(val) {}


  bool is_dyn_5qi() const { return std::holds_alternative<dyn_5qi_descriptor>(choice); }

  /// Retrieves the 5QI associated with the QoS characteristics.

  /// Retrieves the 5QI associated with the QoS characteristics.
  five_qi_t get_5qi() const
  {
    if (is_dyn_5qi()) {
      return get_dyn_5qi().five_qi.has_value() ? get_dyn_5qi().five_qi.value() : five_qi_t::invalid;
    }
    return get_nondyn_5qi().five_qi;
  }


  dyn_5qi_descriptor&           get_dyn_5qi() { return std::get<dyn_5qi_descriptor>(choice); }
  const dyn_5qi_descriptor&     get_dyn_5qi() const { return std::get<dyn_5qi_descriptor>(choice); }
  non_dyn_5qi_descriptor&       get_nondyn_5qi() { return std::get<non_dyn_5qi_descriptor>(choice); }
  const non_dyn_5qi_descriptor& get_nondyn_5qi() const { return std::get<non_dyn_5qi_descriptor>(choice); }


  bool operator==(const qos_characteristics& other) const { return choice == other.choice; }


private:
  std::variant<non_dyn_5qi_descriptor, dyn_5qi_descriptor> choice;
};

/// \brief QoS parameters for a GBR QoS flow or GBR bearer for downlink and uplink. See TS 38.473, clause 9.3.1.46.

/// \brief QoS parameters for a GBR QoS flow or GBR bearer for downlink and uplink. See TS 38.473, clause 9.3.1.46.
struct gbr_qos_flow_information {
  /// Maximum Bit Rate in DL.
  /// Maximum Bit Rate in DL.
  uint64_t max_br_dl;
  /// Maximum Bit Rate in UL.
  /// Maximum Bit Rate in UL.
  uint64_t max_br_ul;
  /// Guaranteed Flow Bit Rate (provided there is data to deliver) in DL.
  /// Guaranteed Flow Bit Rate (provided there is data to deliver) in DL.
  uint64_t gbr_dl;
  /// Guaranteed Flow Bit Rate (provided there is data to deliver) in UL.
  /// Guaranteed Flow Bit Rate (provided there is data to deliver) in UL.
  uint64_t gbr_ul;
  /// Indicates the maximum rate for lost packets that can be tolerated in the DL. Expressed in ratio of lost packets
  /// per number of packets sent, expressed in tenth of percent.Values {0,...,1000}.
  /// Indicates the maximum rate for lost packets that can be tolerated in the DL. Expressed in ratio of lost packets
  /// per number of packets sent, expressed in tenth of percent.Values {0,...,1000}.
  std::optional<uint16_t> max_packet_loss_rate_dl;
  /// Indicates the maximum rate for lost packets that can be tolerated in the UL. Expressed in ratio of lost packets
  /// per number of packets sent, expressed in tenth of percent.Values {0,...,1000}.
  /// Indicates the maximum rate for lost packets that can be tolerated in the UL. Expressed in ratio of lost packets
  /// per number of packets sent, expressed in tenth of percent.Values {0,...,1000}.
  std::optional<uint16_t> max_packet_loss_rate_ul;


  bool operator==(const gbr_qos_flow_information& other) const
  {
    return max_br_dl == other.max_br_dl and max_br_ul == other.max_br_ul and gbr_dl == other.gbr_dl and
           max_packet_loss_rate_dl == other.max_packet_loss_rate_dl and
           max_packet_loss_rate_ul == other.max_packet_loss_rate_ul;
  }
};


struct alloc_and_retention_priority {
  /// Priority level, where highest is 1, lowest is 14, no-priority is 15. The value 0 is reserved.
  /// Priority level, where highest is 1, lowest is 14, no-priority is 15. The value 0 is reserved.
  arp_prio_level_t prio_level_arp         = 15;
  bool             may_trigger_preemption = false;
  bool             is_preemptable         = false;


  bool operator==(const alloc_and_retention_priority& other) const
  {
    return prio_level_arp == other.prio_level_arp and may_trigger_preemption == other.may_trigger_preemption and
           is_preemptable == other.is_preemptable;
  }
};


struct qos_flow_level_qos_parameters {
  /// QoS Descriptor of a dynamic or non-dynamic 5QI.
  /// QoS Descriptor of a dynamic or non-dynamic 5QI.
  qos_characteristics          qos_desc;
  alloc_and_retention_priority alloc_retention_prio;
  /// This parameter applies to GBR flows only. See TS 38.473, clause 9.3.1.45.
  /// This parameter applies to GBR flows only. See TS 38.473, clause 9.3.1.45.
  std::optional<gbr_qos_flow_information> gbr_qos_info;
  bool                                    add_qos_flow_info = false;
  /// This parameter applies to non-GBR flows only. See TS 23.501.
  /// This parameter applies to non-GBR flows only. See TS 23.501.
  bool reflective_qos_attribute_subject_to = false;


  bool operator==(const qos_flow_level_qos_parameters& other) const
  {
    return qos_desc == other.qos_desc and alloc_retention_prio == other.alloc_retention_prio and
           gbr_qos_info == other.gbr_qos_info and add_qos_flow_info == other.add_qos_flow_info and
           reflective_qos_attribute_subject_to == other.reflective_qos_attribute_subject_to;
  }
};


} // namespace ocudu
