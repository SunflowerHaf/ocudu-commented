// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/iq_compression_none_avx512.cpp  (103 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#include "iq_compression_none_avx512.h"
#include "avx512_helpers.h"
#include "packing_utils_avx512.h"
#include "quantizer.h"
#include "ocudu/ofh/compression/compression_properties.h"


using namespace ocudu;
using namespace ofh;


void iq_compression_none_avx512::compress(span<uint8_t>                buffer,
                                          span<const cbf16_t>          iq_data,
                                          const ru_compression_params& params)
{
  // Number of quantized samples per resource block.
  // Number of quantized samples per resource block.
  static constexpr size_t NOF_SAMPLES_PER_PRB = 2 * NOF_SUBCARRIERS_PER_RB;

  // Quantizer object.

  // Quantizer object.
  quantizer q(params.data_width);

  // Use generic implementation if AVX512 utils don't support requested bit width.

  // Use generic implementation if AVX512 utils don't support requested bit width.
  if (!mm512::iq_width_packing_supported(params.data_width)) {
    iq_compression_none_impl::compress(buffer, iq_data, params);
    return;
  }

  // Number of input PRBs.

  // Number of input PRBs.
  unsigned nof_prbs = (iq_data.size() / NOF_SUBCARRIERS_PER_RB);

  // Size in bytes of one compressed PRB using the given compression parameters.

  // Size in bytes of one compressed PRB using the given compression parameters.
  unsigned prb_size = get_compressed_prb_size(params).value();


  ocudu_assert(buffer.size() >= prb_size * nof_prbs, "Output buffer doesn't have enough space to decompress PRBs");

  // Auxiliary arrays used for float to fixed point conversion of the input data.

  // Auxiliary arrays used for float to fixed point conversion of the input data.
  std::array<int16_t, NOF_SAMPLES_PER_PRB * MAX_NOF_PRBS> input_quantized;


  span<const bf16_t> float_samples_span(reinterpret_cast<const bf16_t*>(iq_data.data()), iq_data.size() * 2U);
  span<int16_t>      input_quantized_span(input_quantized.data(), iq_data.size() * 2U);
  q.to_fixed_point(input_quantized_span, float_samples_span, iq_scaling);


  log_post_quantization_rms(input_quantized_span);


  unsigned        sample_idx = 0;
  const __mmask32 load_mask  = 0x00ffffff;

  // Process one PRB at a time.

  // Process one PRB at a time.
  for (unsigned rb = 0; rb != nof_prbs; ++rb) {
    // View over output bytes corresponding to the current PRB.
    // View over output bytes corresponding to the current PRB.
    span<uint8_t> out_compr_prb(&buffer[rb * prb_size], prb_size);

    // Load 16-bit IQ samples from non-aligned memory.

    // Load 16-bit IQ samples from non-aligned memory.
    __m512i rb_epi16 = _mm512_maskz_loadu_epi16(load_mask, &input_quantized[sample_idx]);

    // Pack using utility function.

    // Pack using utility function.
    mm512::pack_prb_big_endian(out_compr_prb, rb_epi16, params.data_width);


    sample_idx += NOF_SAMPLES_PER_PRB;
  }
}


void iq_compression_none_avx512::decompress(span<cbf16_t>                iq_data,
                                            span<const uint8_t>          compressed_data,
                                            const ru_compression_params& params)
{
  // Use generic implementation if AVX512 utils don't support requested bit width.
  // Use generic implementation if AVX512 utils don't support requested bit width.
  if (!mm512::iq_width_packing_supported(params.data_width)) {
    iq_compression_none_impl::decompress(iq_data, compressed_data, params);
    return;
  }

  // Number of output PRBs.

  // Number of output PRBs.
  unsigned nof_prbs = iq_data.size() / NOF_SUBCARRIERS_PER_RB;

  // Size in bytes of one compressed PRB using the given compression parameters.

  // Size in bytes of one compressed PRB using the given compression parameters.
  unsigned comp_prb_size = get_compressed_prb_size(params).value();


  ocudu_assert(compressed_data.size() >= nof_prbs * comp_prb_size,
               "Input does not contain enough bytes to decompress {} PRBs",
               nof_prbs);

  // Quantizer object.

  // Quantizer object.
  quantizer q_out(params.data_width);


  std::array<int16_t, MAX_NOF_SUBCARRIERS * 2> unpacked_iq_data;


  unsigned idx = 0;
  for (unsigned rb = 0; rb != nof_prbs; ++rb) {
    span<const uint8_t> comp_prb_buffer(&compressed_data[rb * comp_prb_size], comp_prb_size);

    // Unpack resource block.

    // Unpack resource block.
    span<int16_t> unpacked_prb_span(&unpacked_iq_data[idx], NOF_SUBCARRIERS_PER_RB * 2);
    mm512::unpack_prb_big_endian(unpacked_prb_span, comp_prb_buffer, params.data_width);


    idx += (NOF_SUBCARRIERS_PER_RB * 2);
  }


  span<int16_t> unpacked_iq_int16_span(unpacked_iq_data.data(), iq_data.size() * 2);
  // Convert to complex brain float samples.
  // Convert to complex brain float samples.
  q_out.to_brain_float(iq_data, unpacked_iq_int16_span, 1);
}
