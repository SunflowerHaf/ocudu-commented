// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Hardware accelerated PDSCH encoder functions declaration.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc_impl.h  (55 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/hal
// Hardware Abstraction Layer (HAL) — DPDK and hardware PHY accelerator implementations. CONDITIONAL: only compiled when DPDK_FOUND=ON and a supported hardware accelerator (e.g. Intel ACC100/ACC200 via BBDEV) is present. In the standard USRP/UHD build this entire directory is excluded from compilation.
//
// Contents:
//   lib/hal/dpdk/         — DPDK EAL initialisation, mbuf pool management, BBDEV device open/config.
//   lib/hal/phy/upper/    — HW-accelerated PDSCH encoder (offloads LDPC encoding to the ACC100 FPGA) and PUSCH decoder (offloads LDPC decoding), plus external HARQ buffer context repository (stores soft bits in on-accelerator memory).
//
// When active, the HAL factories are passed into the upper PHY (lib/phy/) as hw_encoder_factory / hw_decoder_factory pointers; if nullptr, the software fallback LDPC implementations are used automatically.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Hardware accelerated PDSCH encoder functions declaration.

#pragma once


#include "ocudu/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc.h"


namespace ocudu {
namespace hal {

/// Generic hardware accelerated PDSCH encoder functions.

/// Generic hardware accelerated PDSCH encoder functions.
class hw_accelerator_pdsch_enc_impl : public hw_accelerator_pdsch_enc
{
public:
  /// Default constructor.
  /// Default constructor.
  hw_accelerator_pdsch_enc_impl() = default;

  // See hw_accelerator interface for the documentation.

  // See hw_accelerator interface for the documentation.
  void reserve_queue() override;
  // See hw_accelerator interface for the documentation.
  // See hw_accelerator interface for the documentation.
  void free_queue() override;
  // See hw_accelerator interface for the documentation.
  // See hw_accelerator interface for the documentation.
  bool enqueue_operation(span<const uint8_t> data, span<const uint8_t> aux_data = {}, unsigned cb_index = 0) override;
  // See hw_accelerator interface for the documentation.
  // See hw_accelerator interface for the documentation.
  bool dequeue_operation(span<uint8_t> data, span<uint8_t> packed_data = {}, unsigned segment_index = 0) override;
  // See hw_accelerator interface for the documentation.
  // See hw_accelerator interface for the documentation.
  void configure_operation(const hw_pdsch_encoder_configuration& config, unsigned cb_index = 0) override;
  // See hw_accelerator interface for the documentation.
  // See hw_accelerator interface for the documentation.
  bool is_cb_mode_supported() const override;
  // See hw_accelerator interface for the documentation.
  // See hw_accelerator interface for the documentation.
  unsigned get_max_supported_buff_size() const override;


private:
  /// Hardware-specific implementation of the reserve queue function.
  /// Hardware-specific implementation of the reserve queue function.
  virtual void hw_reserve_queue() = 0;
  /// Hardware-specific implementation of the free queue function.
  /// Hardware-specific implementation of the free queue function.
  virtual void hw_free_queue() = 0;
  /// Hardware-specific implementation of the enqueue_operation function.
  /// Hardware-specific implementation of the enqueue_operation function.
  virtual bool hw_enqueue(span<const uint8_t> data, unsigned cb_index) = 0;
  /// Hardware-specific implementation of the dequeue_operation function.
  /// Hardware-specific implementation of the dequeue_operation function.
  virtual bool hw_dequeue(span<uint8_t> data, span<uint8_t> packed_data, unsigned segment_index) = 0;
  /// Hardware-specific configuration function.
  /// Hardware-specific configuration function.
  virtual void hw_config(const hw_pdsch_encoder_configuration& config, unsigned cb_index) = 0;
  /// Hardware-specific CB mode quering function.
  /// Hardware-specific CB mode quering function.
  virtual bool is_hw_cb_mode_supported() const = 0;
  /// Hardware-specific maximum supported buffer size quering function.
  /// Hardware-specific maximum supported buffer size quering function.
  virtual unsigned get_hw_max_supported_buff_size() const = 0;
};


} // namespace hal
} // namespace ocudu
