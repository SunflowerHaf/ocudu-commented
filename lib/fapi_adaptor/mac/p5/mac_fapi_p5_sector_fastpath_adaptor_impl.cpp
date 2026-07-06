// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/p5/mac_fapi_p5_sector_fastpath_adaptor_impl.cpp  (40 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "mac_fapi_p5_sector_fastpath_adaptor_impl.h"
#include "ocudu/fapi_adaptor/mac/p5/mac_fapi_p5_sector_fastpath_adaptor_config.h"


using namespace ocudu;
using namespace fapi_adaptor;


mac_fapi_p5_sector_fastpath_adaptor_impl::mac_fapi_p5_sector_fastpath_adaptor_impl(
    const mac_fapi_p5_sector_fastpath_adaptor_config&       config,
    const mac_fapi_p5_sector_fastpath_adaptor_dependencies& dependencies) :
  transaction_manager({dependencies.timers, dependencies.fapi_ctrl_executor}),
  responses_handler(dependencies.logger, transaction_manager, dependencies.fapi_ctrl_executor),
  controller(mac_fapi_p5_fastpath_cell_operation_controller_impl_config{.cell_cfg = config.cell_cfg},
             mac_fapi_p5_fastpath_cell_operation_controller_impl_dependencies{
                 .logger              = dependencies.logger,
                 .p5_gateway          = dependencies.p5_gateway,
                 .transaction_manager = transaction_manager,
                 .timers              = dependencies.timers,
                 .fapi_ctrl_executor  = dependencies.fapi_ctrl_executor,
                 .mac_ctrl_executor   = dependencies.mac_ctrl_executor})
{
}


fapi::p5_responses_notifier& mac_fapi_p5_sector_fastpath_adaptor_impl::get_p5_responses_notifier()
{
  return responses_handler;
}


fapi::error_indication_notifier& mac_fapi_p5_sector_fastpath_adaptor_impl::get_error_indication_notifier()
{
  return responses_handler;
}


phy_cell_operation_controller& mac_fapi_p5_sector_fastpath_adaptor_impl::get_operation_controller()
{
  return controller;
}
