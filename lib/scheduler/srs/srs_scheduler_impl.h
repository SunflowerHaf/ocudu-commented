// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/srs/srs_scheduler_impl.h  (87 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_context/ue_repository.h"
#include "srs_scheduler.h"
#include "ocudu/ran/srs/srs_configuration.h"


namespace ocudu {


struct cell_resource_allocator;
struct cell_slot_resource_allocator;
struct srs_info;


class srs_scheduler_impl : public srs_scheduler
{
public:
  explicit srs_scheduler_impl(const cell_configuration& cell_cfg_, ue_repository& ues_);


  ~srs_scheduler_impl() override;


  void run_slot(cell_resource_allocator& res_alloc) override;

  /// Called on cell deactivation.

  /// Called on cell deactivation.
  void stop();


  void add_ue(const ue_cell_configuration& ue_cfg) override;


  void rem_ue(const ue_cell_configuration& ue_cfg) override;


  void reconf_ue(const ue_cell_configuration& new_ue_cfg, const ue_cell_configuration& old_ue_cfg) override;


  void handle_positioning_measurement_request(const positioning_measurement_request::cell_info& req) override;


  void handle_positioning_measurement_stop(rnti_t pos_rnti) override;


private:
  /// Information on currently configured SRS resources and corresponding UEs to be scheduled periodically.
  /// Information on currently configured SRS resources and corresponding UEs to be scheduled periodically.
  struct periodic_srs_info {
    rnti_t                 rnti       = rnti_t::INVALID_RNTI;
    srs_config::srs_res_id srs_res_id = srs_config::srs_res_id::MAX_NOF_SRS_RES;
  };

  // Info related with a UE context update.

  // Info related with a UE context update.
  struct ue_update {
    enum class type_t { new_ue, positioning_request, positioning_stop };


    rnti_t rnti;
    type_t type;
  };

  // Helper to fetch a UE cell config.

  // Helper to fetch a UE cell config.
  const ue_cell_configuration* get_ue_cfg(rnti_t rnti) const;
  // Helper that schedules the SRS for a given slot.
  // Helper that schedules the SRS for a given slot.
  void schedule_slot_srs(cell_slot_resource_allocator& slot_alloc);
  // Helper that schedules the SRS for UEs that were recently added or reconfigured.
  // Helper that schedules the SRS for UEs that were recently added or reconfigured.
  void schedule_updated_ues_srs(cell_resource_allocator& res_alloc);
  // Helper that allocates an SRS opportunity for a given UE.
  // Helper that allocates an SRS opportunity for a given UE.
  bool allocate_srs_opportunity(cell_slot_resource_allocator& slot_alloc,
                                const periodic_srs_info&      srs_opportunity) const;


  void add_ue_to_grid(const ue_cell_configuration& ue_cfg, bool is_reconf);


  void add_resource(rnti_t crnti, srs_periodicity period, unsigned offset, srs_config::srs_res_id res_id);
  void rem_resource(rnti_t crnti, srs_periodicity period, unsigned offset, srs_config::srs_res_id res_id);

  // Cell configuration.

  // Cell configuration.
  const cell_configuration& cell_cfg;
  ue_repository&            ues;


  ocudulog::basic_logger& logger;

  // Storage of the periodic SRSs to be scheduled in the resource grid. Each position of the vector represents a slot
  // in a ring-like structure (ie slot % WHEEL_SIZE). Each of these vector indexes/slots contains a list of periodic
  // SRS information to be scheduled in the respective slot.

  // Storage of the periodic SRSs to be scheduled in the resource grid. Each position of the vector represents a slot
  // in a ring-like structure (ie slot % WHEEL_SIZE). Each of these vector indexes/slots contains a list of periodic
  // SRS information to be scheduled in the respective slot.
  std::vector<static_vector<periodic_srs_info, MAX_SRS_PDUS_PER_SLOT>> periodic_srs_slot_wheel;

  // UEs whose configuration has been updated in between the last and current slot indications.

  // UEs whose configuration has been updated in between the last and current slot indications.
  std::vector<ue_update> updated_ues;

  // Pending positioning requests for this cell.

  // Pending positioning requests for this cell.
  std::vector<positioning_measurement_request::cell_info> pending_pos_requests;
};


} // namespace ocudu
