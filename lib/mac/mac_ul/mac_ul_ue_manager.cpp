// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/mac/mac_ul/mac_ul_ue_manager.cpp  (103 lines)
//
// LIBRARY: lib/mac
// Medium Access Control (MAC, TS 38.321): scheduler interface adaptor, HARQ process management, multiplexing/demultiplexing of logical channels into transport blocks, random-access (RACH) handling, and timing-advance control. Interfaces: MAC SDU to/from RLC, MAC PDU to/from the lower PHY via FAPI.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "mac_ul_ue_manager.h"
#include "ocudu/ocudulog/ocudulog.h"


using namespace ocudu;


mac_ul_ue_manager::mac_ul_ue_manager(du_rnti_table& rnti_table_) :
  logger(ocudulog::fetch_basic_logger("MAC")), rnti_table(rnti_table_)
{
}


bool mac_ul_ue_manager::add_ue(const mac_ue_create_request& request)
{
  ocudu_assert(is_crnti(request.crnti), "Invalid c-rnti={}", request.crnti);
  ocudu_assert(is_du_ue_index_valid(request.ue_index), "Invalid UE index={}", fmt::underlying(request.ue_index));

  // > Insert UE

  // > Insert UE
  if (ue_db.contains(request.ue_index)) {
    return false;
  }
  ue_db.emplace(request.ue_index, request.ue_index, request.crnti);

  // > Add UE Bearers

  // > Add UE Bearers
  if (not addmod_bearers(request.ue_index, request.bearers)) {
    logger.warning("ue={}: \"MAC UE Creation\" failed. Cause: Failed to add/mod MAC UE UL bearers",
                   fmt::underlying(request.ue_index));
    return false;
  }


  logger.debug("ue={} rnti={} proc=\"MAC UE Creation\": MAC UE UL context created successfully.",
               request.ue_index,
               request.crnti);


  return true;
}


void mac_ul_ue_manager::remove_ue(du_ue_index_t ue_index)
{
  if (not ue_db.contains(ue_index)) {
    logger.warning("ue={}: \"UE Removal\" failed. Cause: UE with provided ID does not exist",
                   fmt::underlying(ue_index));
    return;
  }
  ue_db.erase(ue_index);
}


bool mac_ul_ue_manager::addmod_bearers(du_ue_index_t                                  ue_index,
                                       const std::vector<mac_logical_channel_config>& ul_logical_channels)
{
  if (ul_logical_channels.empty()) {
    return true;
  }
  if (not ue_db.contains(ue_index)) {
    logger.error("ue={}: Interrupting DEMUX update. Cause: The provided UE ID does not exist",
                 fmt::underlying(ue_index));
    return false;
  }
  mac_ul_ue_context& u = ue_db[ue_index];


  for (const mac_logical_channel_config& channel : ul_logical_channels) {
    u.ul_bearers.insert(channel.lcid, channel.ul_bearer);
  }


  u.rrc_config_pending = true;


  return true;
}


bool mac_ul_ue_manager::remove_bearers(du_ue_index_t ue_index, span<const lcid_t> lcids)
{
  if (lcids.empty()) {
    return true;
  }
  if (not ue_db.contains(ue_index)) {
    logger.error("ue={} Interrupting DEMUX update. Cause: The provided index does not exist",
                 fmt::underlying(ue_index));
    return false;
  }
  mac_ul_ue_context& u = ue_db[ue_index];


  for (lcid_t lcid : lcids) {
    u.ul_bearers.erase(lcid);
  }


  u.rrc_config_pending = true;


  return true;
}


void mac_ul_ue_manager::handle_ue_config_applied(du_ue_index_t ue_index)
{
  if (not ue_db.contains(ue_index)) {
    // The UE was destroyed in the meantime.
    // The UE was destroyed in the meantime.
    return;
  }
  mac_ul_ue_context& u = ue_db[ue_index];

  // Mark the configuration as complete

  // Mark the configuration as complete
  u.rrc_config_pending = false;
}
