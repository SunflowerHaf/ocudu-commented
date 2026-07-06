// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc_impl.cpp  (47 lines)
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

#include "hw_accelerator_pdsch_enc_impl.h"


using namespace ocudu;
using namespace hal;


void hw_accelerator_pdsch_enc_impl::reserve_queue()
{
  hw_reserve_queue();
}


void hw_accelerator_pdsch_enc_impl::free_queue()
{
  hw_free_queue();
}


bool hw_accelerator_pdsch_enc_impl::enqueue_operation(span<const uint8_t> data,
                                                      span<const uint8_t> aux_data,
                                                      unsigned            cb_index)
{
  return hw_enqueue(data, cb_index);
}


bool hw_accelerator_pdsch_enc_impl::dequeue_operation(span<uint8_t> data,
                                                      span<uint8_t> packed_data,
                                                      unsigned      segment_index)
{
  return hw_dequeue(data, packed_data, segment_index);
}


void hw_accelerator_pdsch_enc_impl::configure_operation(const hw_pdsch_encoder_configuration& config, unsigned cb_index)
{
  hw_config(config, cb_index);
}


bool hw_accelerator_pdsch_enc_impl::is_cb_mode_supported() const
{
  return is_hw_cb_mode_supported();
}


unsigned hw_accelerator_pdsch_enc_impl::get_max_supported_buff_size() const
{
  return get_hw_max_supported_buff_size();
}
