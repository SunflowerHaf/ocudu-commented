// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/processors/adaptors/processor_handler_adaptor.h  (81 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/lower/lower_phy_downlink_handler.h"
#include "ocudu/phy/lower/lower_phy_uplink_request_handler.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_request_handler.h"
#include "ocudu/phy/lower/processors/uplink/prach/prach_processor_request_handler.h"
#include "ocudu/phy/lower/processors/uplink/puxch/puxch_processor_request_handler.h"


namespace ocudu {


class shared_resource_grid;

/// Adapts the lower physical layer handlers to the internal processors request handlers.

/// Adapts the lower physical layer handlers to the internal processors request handlers.
class processor_handler_adaptor
{
public:
  /// Constructs the lower physical layer handler adaptor from the internal processor request handlers.
  /// Constructs the lower physical layer handler adaptor from the internal processor request handlers.
  processor_handler_adaptor(pdxch_processor_request_handler& pdxch_handler,
                            prach_processor_request_handler& prach_handler,
                            puxch_processor_request_handler& puxch_handler) :
    dl_handler(pdxch_handler), ul_request_handler(prach_handler, puxch_handler)
  {
  }

  /// Gets resource grid handler.

  /// Gets resource grid handler.
  lower_phy_downlink_handler& get_downlink_handler() { return dl_handler; }

  /// Gets demodulate request handler.

  /// Gets demodulate request handler.
  lower_phy_uplink_request_handler& get_uplink_request_handler() { return ul_request_handler; }


private:
  /// Implements the lower physical layer downlink handler.
  /// Implements the lower physical layer downlink handler.
  class downlink_handler_adaptor : public lower_phy_downlink_handler
  {
  public:
    /// Connects the adaptor with the PDxCH processor handler.
    /// Connects the adaptor with the PDxCH processor handler.
    explicit downlink_handler_adaptor(pdxch_processor_request_handler& pdxch_handler_) : pdxch_handler(pdxch_handler_)
    {
    }

    // See interface for documentation.

    // See interface for documentation.
    void handle_resource_grid(const resource_grid_context& context, const shared_resource_grid& grid) override;


  private:
    /// Actual PDxCH processor request handler.
    /// Actual PDxCH processor request handler.
    pdxch_processor_request_handler& pdxch_handler;
  };

  /// Implements the lower physical layer uplink request handler.

  /// Implements the lower physical layer uplink request handler.
  class uplink_request_handler_adaptor : public lower_phy_uplink_request_handler
  {
  public:
    /// Connects the adaptor with the PRACH and PUxCH processor handlers.
    /// Connects the adaptor with the PRACH and PUxCH processor handlers.
    uplink_request_handler_adaptor(prach_processor_request_handler& prach_handler_,
                                   puxch_processor_request_handler& puxch_handler_) :
      prach_handler(prach_handler_), puxch_handler(puxch_handler_)
    {
    }

    // See interface for documentation.

    // See interface for documentation.
    void request_prach_window(const prach_buffer_context& context, shared_prach_buffer buffer) override;

    // See interface for documentation.

    // See interface for documentation.
    void request_uplink_slot(const resource_grid_context& context, const shared_resource_grid& grid) override;


  private:
    /// Actual PRACH processor request handler.
    /// Actual PRACH processor request handler.
    prach_processor_request_handler& prach_handler;
    /// Actual PUxCH processor request handler.
    /// Actual PUxCH processor request handler.
    puxch_processor_request_handler& puxch_handler;
  };


  downlink_handler_adaptor       dl_handler;
  uplink_request_handler_adaptor ul_request_handler;
};


} // namespace ocudu
