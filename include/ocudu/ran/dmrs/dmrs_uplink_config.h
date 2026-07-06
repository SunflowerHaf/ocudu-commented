// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/dmrs/dmrs_uplink_config.h  (83 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/ptrs.h"
#include <optional>


namespace ocudu {

/// Used to configure uplink demodulation reference signals for PUSCH.
/// \remark See TS 38.331, DMRS-UplinkConfig.

/// Used to configure uplink demodulation reference signals for PUSCH.
/// \remark See TS 38.331, DMRS-UplinkConfig.
struct dmrs_uplink_config {
  /// \brief DMRS related parameters for Cyclic Prefix OFDM.
  /// \brief DMRS related parameters for Cyclic Prefix OFDM.
  struct transform_precoder_disabled {
    /// UL DMRS scrambling initialization for CP-OFDM. When the field is absent the UE applies the value Physical cell
    /// ID. See TS 38.211, clause 6.4.1.1.1.1.
    /// UL DMRS scrambling initialization for CP-OFDM. When the field is absent the UE applies the value Physical cell
    /// ID. See TS 38.211, clause 6.4.1.1.1.1.
    std::optional<uint16_t> scrambling_id0;
    std::optional<uint16_t> scrambling_id1;


    bool operator==(const transform_precoder_disabled& rhs) const
    {
      return scrambling_id0 == rhs.scrambling_id0 && scrambling_id1 == rhs.scrambling_id1;
    }
    bool operator!=(const transform_precoder_disabled& rhs) const { return !(rhs == *this); }
  };

  /// \brief DMRS related parameters for DFT-s-OFDM (Transform Precoding).

  /// \brief DMRS related parameters for DFT-s-OFDM (Transform Precoding).
  struct transform_precoder_enabled {
    /// Values {0..1007}.
    /// Values {0..1007}.
    std::optional<uint16_t> n_pusch_id;
    /// For DMRS transmission with transform precoder the NW may configure group hopping by the cell-specific parameter
    /// groupHoppingEnabledTransformPrecoding in PUSCH-ConfigCommon. In this case, the NW may include this UE specific
    /// field to disable group hopping for PUSCH transmission except for Msg3.
    /// Override the configuration in PUSCH-ConfigCommon.
    /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value disabled to UE. If false, the field
    /// is absent in NR RRC and the UE uses the same hopping mode as for Msg3.
    /// For DMRS transmission with transform precoder the NW may configure group hopping by the cell-specific parameter
    /// groupHoppingEnabledTransformPrecoding in PUSCH-ConfigCommon. In this case, the NW may include this UE specific
    /// field to disable group hopping for PUSCH transmission except for Msg3.
    /// Override the configuration in PUSCH-ConfigCommon.
    /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value disabled to UE. If false, the field
    /// is absent in NR RRC and the UE uses the same hopping mode as for Msg3.
    bool is_seq_grp_hopping_disabled{false};
    /// Determines if sequence hopping is enabled for DMRS transmission with transform precoder for PUSCH transmission
    /// other than Msg3 (sequence hopping is always disabled for Msg3).
    /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value enabled to UE. If false, the field
    /// is absent in NR RRC and the UE uses the same hopping mode as for Msg3.
    /// Note: The network does not configure simultaneous group hopping and sequence hopping.
    /// Determines if sequence hopping is enabled for DMRS transmission with transform precoder for PUSCH transmission
    /// other than Msg3 (sequence hopping is always disabled for Msg3).
    /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value enabled to UE. If false, the field
    /// is absent in NR RRC and the UE uses the same hopping mode as for Msg3.
    /// Note: The network does not configure simultaneous group hopping and sequence hopping.
    bool is_seq_hopping_enabled{false};


    bool operator==(const transform_precoder_enabled& rhs) const
    {
      return n_pusch_id == rhs.n_pusch_id && is_seq_grp_hopping_disabled == rhs.is_seq_grp_hopping_disabled &&
             is_seq_hopping_enabled == rhs.is_seq_hopping_enabled;
    }
    bool operator!=(const transform_precoder_enabled& rhs) const { return !(rhs == *this); }
  };

  /// Selection of the DMRS type to be used for UL.
  /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value type2 to UE. If false, the field
  /// is absent in NR RRC and the UE uses DMRS type 1.

  /// Selection of the DMRS type to be used for UL.
  /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value type2 to UE. If false, the field
  /// is absent in NR RRC and the UE uses DMRS type 1.
  bool is_dmrs_type2{false};
  /// Position for additional DM-RS in UL (see TS 38.211, clause 6.4.1.1.3). If the field is not set, the UE applies the
  /// value pos2.
  /// Position for additional DM-RS in UL (see TS 38.211, clause 6.4.1.1.3). If the field is not set, the UE applies the
  /// value pos2.
  dmrs_additional_positions additional_positions{dmrs_additional_positions::pos2};
  /// Configures uplink PTRS.
  /// Configures uplink PTRS.
  std::optional<ptrs_uplink_config> ptrs;
  /// The maximum number of OFDM symbols for UL front loaded DMRS.
  /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value len2 to UE. If false, the field
  /// is absent in NR RRC and the UE applies value len1.
  /// If set to len2, the UE determines the actual number of DM-RS symbols by the associated DCI.
  /// The maximum number of OFDM symbols for UL front loaded DMRS.
  /// Mapping to NR RRC: If true, the field is present in NR RRC indicating value len2 to UE. If false, the field
  /// is absent in NR RRC and the UE applies value len1.
  /// If set to len2, the UE determines the actual number of DM-RS symbols by the associated DCI.
  bool                                       is_max_length_len2{false};
  std::optional<transform_precoder_disabled> trans_precoder_disabled;
  std::optional<transform_precoder_enabled>  trans_precoder_enabled;
  // TODO: Remaining

  // TODO: Remaining

  bool operator==(const dmrs_uplink_config& rhs) const
  {
    return is_dmrs_type2 == rhs.is_dmrs_type2 && additional_positions == rhs.additional_positions && ptrs == rhs.ptrs &&
           is_max_length_len2 == rhs.is_max_length_len2 && trans_precoder_disabled == rhs.trans_precoder_disabled &&
           trans_precoder_enabled == rhs.trans_precoder_enabled;
  }
  bool operator!=(const dmrs_uplink_config& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
