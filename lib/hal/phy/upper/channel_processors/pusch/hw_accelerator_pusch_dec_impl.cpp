// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/phy/upper/channel_processors/pusch/hw_accelerator_pusch_dec_impl.cpp  (54 lines)
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

#include "hw_accelerator_pusch_dec_impl.h"


using namespace ocudu;
using namespace hal;


void hw_accelerator_pusch_dec_impl::reserve_queue()
{
  hw_reserve_queue();
}


void hw_accelerator_pusch_dec_impl::free_queue()
{
  hw_free_queue();
}


bool hw_accelerator_pusch_dec_impl::enqueue_operation(span<const int8_t> data,
                                                      span<const int8_t> soft_data,
                                                      unsigned           cb_index)
{
  return hw_enqueue(data, soft_data, cb_index);
}


bool hw_accelerator_pusch_dec_impl::dequeue_operation(span<uint8_t> data,
                                                      span<int8_t>  soft_data,
                                                      unsigned      segment_index)
{
  return hw_dequeue(data, soft_data, segment_index);
}


void hw_accelerator_pusch_dec_impl::configure_operation(const hw_pusch_decoder_configuration& config, unsigned cb_index)
{
  hw_config(config, cb_index);
}


void hw_accelerator_pusch_dec_impl::read_operation_outputs(hw_pusch_decoder_outputs& out,
                                                           unsigned                  cb_index,
                                                           unsigned                  absolute_cb_id)
{
  hw_read_outputs(out, cb_index, absolute_cb_id);
}


void hw_accelerator_pusch_dec_impl::free_harq_context_entry(unsigned absolute_cb_id)
{
  hw_free_harq_context(absolute_cb_id);
}


bool hw_accelerator_pusch_dec_impl::is_harq_external() const
{
  return hw_is_harq_external();
}
