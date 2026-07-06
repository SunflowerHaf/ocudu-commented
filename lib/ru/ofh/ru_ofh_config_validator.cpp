// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_config_validator.cpp  (85 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ru/ofh/ru_ofh_configuration.h"


using namespace ocudu;


static bool check_compression_params(const ofh::ru_compression_params& params)
{
  if (!(params.type == ofh::compression_type::none) && !(params.type == ofh::compression_type::BFP)) {
    fmt::println("Compression method '{}' is not supported. Valid values are [none,bfp]", to_string(params.type));
    return false;
  }


  if (params.type == ofh::compression_type::BFP && !(params.data_width == 8) && !(params.data_width == 9) &&
      !(params.data_width == 12) && !(params.data_width == 14) && !(params.data_width == 16)) {
    fmt::println("BFP compression bit width '{}' is not supported. Valid values are [8,9,12,14,16]", params.data_width);


    return false;
  }


  return true;
}


static bool check_eaxc_id(unsigned eaxc)
{
  bool result = eaxc < ofh::MAX_SUPPORTED_EAXC_ID_VALUE;
  if (!result) {
    fmt::println(
        "Configured eAxC id '{}' is out of range. Valid range is [0-{}]", eaxc, ofh::MAX_SUPPORTED_EAXC_ID_VALUE - 1U);
  }


  return result;
}


static bool check_eaxcs_id(const ofh::sector_configuration& config)
{
  // Check PRACH eAxC.
  // Check PRACH eAxC.
  for (auto eaxc : config.prach_eaxc) {
    if (!check_eaxc_id(eaxc)) {
      return false;
    }
  }

  // Check uplink eAxCs.

  // Check uplink eAxCs.
  for (auto eaxc : config.ul_eaxc) {
    if (!check_eaxc_id(eaxc)) {
      return false;
    }
  }

  // Check downlink eAxCs.

  // Check downlink eAxCs.
  for (auto eaxc : config.dl_eaxc) {
    if (!check_eaxc_id(eaxc)) {
      return false;
    }
  }


  return true;
}


bool ocudu::is_valid_ru_ofh_config(const ru_ofh_configuration& config)
{
  for (const auto& sector : config.sector_configs) {
    if (!check_compression_params(sector.ul_compression_params)) {
      return false;
    }


    if (!check_compression_params(sector.dl_compression_params)) {
      return false;
    }


    if (!check_compression_params(sector.prach_compression_params)) {
      return false;
    }


    if (!check_eaxcs_id(sector)) {
      return false;
    }
  }


  return true;
}
