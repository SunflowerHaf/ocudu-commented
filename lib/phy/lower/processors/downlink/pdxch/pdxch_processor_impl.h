// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/processors/downlink/pdxch/pdxch_processor_impl.h  (144 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../../resource_request_pool.h"
#include "pdxch_baseband_modulator.h"
#include "pdxch_processor_modulator_notifier.h"
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_dynamic.h"
#include "ocudu/phy/lower/amplitude_controller/amplitude_controller.h"
#include "ocudu/phy/lower/modulation/ofdm_modulator.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_baseband.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_notifier.h"
#include "ocudu/phy/lower/processors/downlink/pdxch/pdxch_processor_request_handler.h"
#include "ocudu/phy/lower/processors/lower_phy_center_freq_controller.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/support/memory_pool/bounded_object_pool.h"


namespace ocudu {

/// \brief Implements a PDxCH baseband processor.
///
/// Downlink physical channel transmission requests are handled asynchronously by modulators. These notify the
/// completion of their processing via \ref pdxch_processor_modulator_notifier interface.
///
/// The modulation results are stored in a circular buffer that implements an exchange mechanism. The modulation results
/// are taken from the circular buffer when a new slot is processed through the \ref pdxch_processor_baseband interface.

/// \brief Implements a PDxCH baseband processor.
///
/// Downlink physical channel transmission requests are handled asynchronously by modulators. These notify the
/// completion of their processing via \ref pdxch_processor_modulator_notifier interface.
///
/// The modulation results are stored in a circular buffer that implements an exchange mechanism. The modulation results
/// are taken from the circular buffer when a new slot is processed through the \ref pdxch_processor_baseband interface.
class pdxch_processor_impl : public pdxch_processor,
                             private pdxch_processor_baseband,
                             private pdxch_processor_request_handler,
                             private lower_phy_center_freq_controller,
                             public pdxch_processor_modulator_notifier
{
public:
  /// Collects the necessary parameters and dependencies for creating a physical downlink channel baseband processor
  /// configuration.
  /// Collects the necessary parameters and dependencies for creating a physical downlink channel baseband processor
  /// configuration.
  struct configuration {
    subcarrier_spacing scs;
    cyclic_prefix      cp;
    sampling_rate      srate;
    unsigned           nof_tx_ports;
  };

  /// Constructs a physical downlink channel baseband processor.

  /// Constructs a physical downlink channel baseband processor.
  pdxch_processor_impl(std::unique_ptr<ofdm_symbol_modulator> modulator,
                       std::unique_ptr<amplitude_controller>  amplitude_control,
                       task_executor&                         executor,
                       const configuration&                   config) :
    logger(ocudulog::fetch_basic_logger("PHY")),
    bb_buffers(buffer_request_pool::get_request_array_size() + max_slot_modulation_concurrency + 1,
               config.nof_tx_ports,
               config.srate.to_kHz()),
    common_ofdm_modulator(std::move(modulator)),
    common_amplitude_control(std::move(amplitude_control)),
    modulators(max_slot_modulation_concurrency)
  {
    // Generate baseband modulators.
    // Generate baseband modulators.
    std::generate(modulators.begin(), modulators.end(), [this, &config, &executor]() {
      return std::make_unique<pdxch_baseband_modulator>(config.scs,
                                                        config.cp,
                                                        config.srate,
                                                        config.nof_tx_ports,
                                                        executor,
                                                        *common_ofdm_modulator,
                                                        *common_amplitude_control,
                                                        *this);
    });
  }

  // See pdxch_processor interface for documentation.

  // See pdxch_processor interface for documentation.
  void connect(pdxch_processor_notifier& notifier) override;

  // See pdxch_processor interface for documentation.

  // See pdxch_processor interface for documentation.
  void stop() override
  {
    // Signal the stop. The downlink transmission handler stops accepting transmissions.
    // Signal the stop. The downlink transmission handler stops accepting transmissions.
    stopped = true;

    // Wait for all modulators to complete their current tasks.

    // Wait for all modulators to complete their current tasks.
    std::for_each(
        modulators.begin(), modulators.end(), [](const auto& modulator) { modulator->wait_for_completion(); });
  }

  // See pdxch_processor interface for documentation.

  // See pdxch_processor interface for documentation.
  pdxch_processor_request_handler& get_request_handler() override;

  // See pdxch_processor interface for documentation.

  // See pdxch_processor interface for documentation.
  pdxch_processor_baseband& get_baseband() override;

  // See pdxch_processor interface for documentation.

  // See pdxch_processor interface for documentation.
  lower_phy_center_freq_controller& get_center_freq_control() override;


private:
  /// Maximum number of slots that can be concurrently modulated.
  /// Maximum number of slots that can be concurrently modulated.
  static constexpr unsigned max_slot_modulation_concurrency = 4;

  /// Buffer request pool alias.

  /// Buffer request pool alias.
  using buffer_request_pool = resource_request_pool<pdxch_processor_baseband::slot_result>;

  /// The request pool size must be a multiple of the modulation concurrency. This guarantees that any two slots mapping
  /// to the same pool entry (i.e. equal modulo the pool size) are also mapped to the same modulator. As each modulator
  /// serialises its completions, no two threads ever write the same \c buffer_request_pool entry concurrently.

  /// The request pool size must be a multiple of the modulation concurrency. This guarantees that any two slots mapping
  /// to the same pool entry (i.e. equal modulo the pool size) are also mapped to the same modulator. As each modulator
  /// serialises its completions, no two threads ever write the same \c buffer_request_pool entry concurrently.
  static_assert(buffer_request_pool::get_request_array_size() % max_slot_modulation_concurrency == 0,
                "Request pool size must be a multiple of the modulation concurrency to avoid concurrent writes.");

  /// Retrieves the PDxCH modulator associated to the given slot.

  /// Retrieves the PDxCH modulator associated to the given slot.
  pdxch_baseband_modulator& get_modulator(slot_point slot)
  {
    return *modulators[slot.system_slot() % modulators.size()];
  }

  // See pdxch_processor_baseband interface for documentation.

  // See pdxch_processor_baseband interface for documentation.
  pdxch_processor_baseband::slot_result process_slot(slot_context context) override;

  // See pdxch_processor_request_handler interface for documentation.

  // See pdxch_processor_request_handler interface for documentation.
  void handle_request(const shared_resource_grid& grid, const resource_grid_context& context) override;

  // See lower_phy_center_freq_controller interface for documentation.

  // See lower_phy_center_freq_controller interface for documentation.
  bool set_carrier_center_frequency(double carrier_center_frequency_Hz) override;

  // See pdxch_processor_modulator_notifier interface for documentation.

  // See pdxch_processor_modulator_notifier interface for documentation.
  void on_modulation_completion(pdxch_processor_baseband::slot_result result, resource_grid_context context) override;

  /// Physical layer logger. Used for logging errors when the number of buffers are exhausted or a modulator is busy.

  /// Physical layer logger. Used for logging errors when the number of buffers are exhausted or a modulator is busy.
  ocudulog::basic_logger& logger;
  /// Set to true when upper layers request to stop. The PDxCH processor does not accept more calls
  /// Set to true when upper layers request to stop. The PDxCH processor does not accept more calls
  std::atomic<bool> stopped = false;
  /// Physical channel baseband processor event notifier.
  /// Physical channel baseband processor event notifier.
  pdxch_processor_notifier* notifier = nullptr;
  /// Baseband buffer pool.
  /// Baseband buffer pool.
  baseband_gateway_buffer_pool bb_buffers;
  /// Common OFDM symbol modulators. It must be thread-safe.
  /// Common OFDM symbol modulators. It must be thread-safe.
  std::unique_ptr<ofdm_symbol_modulator> common_ofdm_modulator;
  /// Common amplitude controller. It must be thread-safe.
  /// Common amplitude controller. It must be thread-safe.
  std::unique_ptr<amplitude_controller> common_amplitude_control;
  /// Downlink physical channel baseband modulators.
  /// Downlink physical channel baseband modulators.
  std::vector<std::unique_ptr<pdxch_baseband_modulator>> modulators;
  /// Circular concurrent pool of transmit requests.
  /// Circular concurrent pool of transmit requests.
  buffer_request_pool requests;
};


} // namespace ocudu
