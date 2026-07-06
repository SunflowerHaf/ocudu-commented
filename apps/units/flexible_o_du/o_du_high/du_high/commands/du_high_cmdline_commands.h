// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: commands/du_high_cmdline_commands.h
//
// Purpose (plain English):
//   Defines the "toggle DU metrics on/off" console command for the DU High.
//
//   When the gNB is running, the operator can type a command into its console
//   to start or stop the per-UE scheduler/MAC table that is printed to stdout
//   every second. This class plugs into that command infrastructure.
//
//   The key name exposed to the user is "ue" — so pressing 't' then 'ue' on
//   the gNB console toggles the stdout UE metrics table. The actual
//   show/hide is delegated to du_metrics_consumer_stdout.
// =============================================================================

#pragma once


#include "apps/services/cmdline/stdout_metrics_command.h"
#include "apps/units/flexible_o_du/o_du_high/du_high/metrics/du_metrics_consumers.h"


namespace ocudu {

/// Application subcommand to display/hide the DU high metrics in STDOUT.

/// \brief Console subcommand to show or hide the DU High per-UE metrics table.
///
/// Implements the toggle_stdout_metrics_app_command::metrics_subcommand
/// interface, which is how the cmdline framework calls enable()/disable().
/// The name "ue" is what the operator types (e.g. "metrics ue").
class du_high_metrics_subcommand_stdout : public app_services::toggle_stdout_metrics_app_command::metrics_subcommand
{
  /// The stdout consumer object that actually does the printing.
  du_metrics_consumer_stdout& printer;


public:
  explicit du_high_metrics_subcommand_stdout(du_metrics_consumer_stdout& printer_) : printer(printer_) {}

  // See interface for documentation.

  // See interface for documentation.
  std::string_view get_name() const override { return "ue"; }

  // See interface for documentation.

  // See interface for documentation.
  void print_header() override { printer.print_header(); }

  // See interface for documentation.

  // See interface for documentation.
  void enable() override { printer.enable(); }

  // See interface for documentation.

  // See interface for documentation.
  void disable() override { printer.disable(); }
};


} // namespace ocudu
