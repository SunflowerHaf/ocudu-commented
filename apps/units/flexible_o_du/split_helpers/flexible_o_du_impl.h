// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/flexible_o_du_impl.h  (63 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "flexible_o_du_metrics_aggregator.h"
#include "ocudu/du/du.h"
#include "ocudu/du/du_operation_controller.h"
#include "ocudu/du/o_du.h"
#include "ocudu/ru/ru_adapters.h"
#include <memory>


namespace ocudu {


class radio_unit;

/// \brief Flexible O-RAN DU implementation.
///
/// One O-RAN DU can handle more than one cell.

/// \brief Flexible O-RAN DU implementation.
///
/// One O-RAN DU can handle more than one cell.
class flexible_o_du_impl : public odu::du, public du_operation_controller
{
public:
  flexible_o_du_impl(unsigned nof_cells_, flexible_o_du_metrics_notifier* notifier);

  // See interface for documentation.

  // See interface for documentation.
  du_operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  // See interface for documentation.
  void start() override;

  // See interface for documentation.

  // See interface for documentation.
  void stop() override;

  /// Adds the given RU to this flexible O-RAN DU.

  /// Adds the given RU to this flexible O-RAN DU.
  void add_ru(std::unique_ptr<radio_unit> active_ru);

  /// Adds the given DU to this flexible O-RAN DU.

  /// Adds the given DU to this flexible O-RAN DU.
  void add_du(std::unique_ptr<odu::o_du> active_du);

  /// Returns the O-DU metrics notifier of this flexible O-DU implementation.

  /// Returns the O-DU metrics notifier of this flexible O-DU implementation.
  odu::o_du_metrics_notifier& get_o_du_metrics_notifier() { return odu_metrics_handler; }

  /// Getters to the adaptors.

  /// Getters to the adaptors.
  upper_phy_ru_ul_adapter&         get_upper_ru_ul_adapter() { return ru_ul_adapt; }
  upper_phy_ru_timing_adapter&     get_upper_ru_timing_adapter() { return ru_timing_adapt; }
  upper_phy_ru_error_adapter&      get_upper_ru_error_adapter() { return ru_error_adapt; }
  upper_phy_ru_dl_rg_adapter&      get_upper_ru_dl_rg_adapter() { return ru_dl_rg_adapt; }
  upper_phy_ru_ul_request_adapter& get_upper_ru_ul_request_adapter() { return ru_ul_request_adapt; }


private:
  const unsigned                   nof_cells;
  upper_phy_ru_ul_adapter          ru_ul_adapt;
  upper_phy_ru_timing_adapter      ru_timing_adapt;
  upper_phy_ru_error_adapter       ru_error_adapt;
  flexible_o_du_metrics_aggregator odu_metrics_handler;
  std::unique_ptr<odu::o_du>       du;
  std::unique_ptr<radio_unit>      ru;
  upper_phy_ru_dl_rg_adapter       ru_dl_rg_adapt;
  upper_phy_ru_ul_request_adapter  ru_ul_request_adapt;
};


} // namespace ocudu
