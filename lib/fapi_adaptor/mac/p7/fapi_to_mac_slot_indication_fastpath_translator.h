// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/p7/fapi_to_mac_slot_indication_fastpath_translator.h  (41 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi/p7/p7_slot_indication_notifier.h"
#include "ocudu/ocudulog/ocudulog.h"


namespace ocudu {


class mac_cell_slot_handler;


namespace fapi_adaptor {

/// \brief FAPI-to-MAC slot indication fastpath translator.
///
/// This class listens to slot-based, time-specific FAPI message events and translates them to the suitable data types
/// for the MAC layer.

/// \brief FAPI-to-MAC slot indication fastpath translator.
///
/// This class listens to slot-based, time-specific FAPI message events and translates them to the suitable data types
/// for the MAC layer.
class fapi_to_mac_slot_indication_fastpath_translator : public fapi::p7_slot_indication_notifier
{
public:
  fapi_to_mac_slot_indication_fastpath_translator(unsigned                sector_id_,
                                                  mac_cell_slot_handler&  fapi_slot_handler_,
                                                  ocudulog::basic_logger& logger_);

  // See interface for documentation.

  // See interface for documentation.
  void on_slot_indication(const fapi::slot_indication& msg) override;

  /// Sets the given cell-specific slot handler. This handler will be used to receive new slot notifications.

  /// Sets the given cell-specific slot handler. This handler will be used to receive new slot notifications.
  void set_cell_slot_handler(mac_cell_slot_handler& handler) { mac_slot_handler = &handler; }


private:
  const unsigned          sector_id;
  mac_cell_slot_handler&  fapi_slot_handler;
  mac_cell_slot_handler*  mac_slot_handler;
  ocudulog::basic_logger& logger;
};


} // namespace fapi_adaptor
} // namespace ocudu
