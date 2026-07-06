// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: commands/du_high_remote_commands.h
//
// Purpose (plain English):
//   Declares three "remote command" classes that let an operator or a RIC
//   (RAN Intelligent Controller) reconfigure a *running* gNB through the
//   HTTP remote-control interface, without restarting it.
//
//   Each command receives a JSON payload via the HTTP endpoint, validates it,
//   builds the matching internal request, and dispatches it to the DU
//   configurator (du_configurator). The configurator then applies the change
//   synchronously and returns success/failure.
//
//     ssb_modify_remote_command ("ssb_set") — changes the SSB transmit power
//       in dBm for one or more cells (identified by PLMN + NCI). Useful for
//       coverage adjustment.
//
//     rrm_policy_ratio_remote_command ("rrm_policy_ratio_set") — adjusts the
//       Radio Resource Management policy, i.e. what share of PRBs (Physical
//       Resource Blocks) each network slice (identified by PLMN + S-NSSAI)
//       gets as minimum, maximum, and dedicated allocation.
//
//     sib_update_remote_command ("sib_update") — updates SIB2/SIB3/SIB4
//       content without a cell restart. SIB2 controls cell reselection
//       thresholds; SIB3 lists intra-frequency neighbour cells; SIB4 lists
//       inter-frequency carriers. Each update increments the SIB's value_tag
//       so idle UEs know to re-read it at the next SI period.
// =============================================================================

#pragma once


#include "apps/services/remote_control/remote_command.h"
#include "ocudu/du/du_high/du_manager/du_configurator.h"


namespace ocudu {

/// Remote command that modifies the SSB parameters.

/// \brief Remote command: change the SSB block power for one or more cells.
///
/// JSON schema expected:
/// { "cells": [ { "plmn": "00101", "nci": 1, "ssb_block_power_dbm": -10 }, ... ] }
class ssb_modify_remote_command : public app_services::remote_command
{
  odu::du_configurator& configurator;


public:
  explicit ssb_modify_remote_command(odu::du_configurator& configurator_) : configurator(configurator_) {}

  // See interface for documentation.

  std::string_view get_name() const override { return "ssb_set"; }

  // See interface for documentation.
  std::string_view get_description() const override { return "Modifies the SSB parameters"; }

  // See interface for documentation.
  error_type<std::string> execute(const nlohmann::json& json) override;
};

/// Remote command that modifies the RRM policy ratio.

/// \brief Remote command: reassign PRB-share ratios between network slices.
///
/// JSON schema expected:
/// { "policies": { "resourceType": "PRB", "rRMPolicyMemberList": [...],
///                 "min_prb_policy_ratio": 20, "max_prb_policy_ratio": 100,
///                 "dedicated_ratio": 50 } }
class rrm_policy_ratio_remote_command : public app_services::remote_command
{
  odu::du_configurator& configurator;


public:
  explicit rrm_policy_ratio_remote_command(odu::du_configurator& configurator_) : configurator(configurator_) {}

  // See interface for documentation.

  std::string_view get_name() const override { return "rrm_policy_ratio_set"; }

  // See interface for documentation.
  std::string_view get_description() const override { return "Modifies the RRM policy ratio"; }

  // See interface for documentation.
  error_type<std::string> execute(const nlohmann::json& json) override;
};

/// \brief Remote command that updates SIB contents without a cell restart.
///
/// Supported SIBs: SIB2 (cell reselection), SIB3 (intra-frequency neighbors), SIB4 (inter-frequency neighbors).
/// Each update swaps the SIB content in the live cell config, increments that SIB's value_tag, repacks SIB1
/// and all SI messages, and notifies MAC and CU-CP. Idle UEs re-read the updated SIB on the next SI period.

/// \brief Remote command: update SIB2, SIB3, or SIB4 content live.
///
/// JSON schema expected:
/// { "cells": [ { "plmn": "00101", "nci": 1,
///                "sib": { "type": "sib2", "content": { ... } } } ] }
///
/// Supported SIBs: sib2 (cell reselection), sib3 (intra-freq neighbours),
/// sib4 (inter-freq carriers). Each update increments the value_tag so idle
/// UEs re-read the SIB on the next SI modification period.
class sib_update_remote_command : public app_services::remote_command
{
  odu::du_configurator& configurator;


public:
  explicit sib_update_remote_command(odu::du_configurator& configurator_) : configurator(configurator_) {}

  // See interface for documentation.

  std::string_view get_name() const override { return "sib_update"; }

  // See interface for documentation.
  std::string_view get_description() const override
  {
    return "Updates SIB2/SIB3/SIB4 content with per-SIB value_tag increment";
  }

  // See interface for documentation.
  error_type<std::string> execute(const nlohmann::json& json) override;
};


} // namespace ocudu
