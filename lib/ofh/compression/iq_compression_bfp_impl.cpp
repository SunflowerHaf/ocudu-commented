// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/iq_compression_bfp_impl.cpp  (141 lines)
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

#include "iq_compression_bfp_impl.h"
#include "packing_utils_generic.h"
#include "ocudu/ocuduvec/dot_prod.h"
#include "ocudu/ofh/compression/compression_properties.h"
#include "ocudu/support/units.h"


using namespace ocudu;
using namespace ofh;


void iq_compression_bfp_impl::quantize_input(span<int16_t> out, span<const bf16_t> in)
{
  ocudu_assert(in.size() == out.size(), "Input and output spans must have the same size");

  // Quantizer object.

  // Quantizer object.
  quantizer q(Q_BIT_WIDTH);

  // Convert input to int16_t representation.

  // Convert input to int16_t representation.
  q.to_fixed_point(out, in, iq_scaling);


  if (OCUDU_UNLIKELY(logger.debug.enabled() && !out.empty())) {
    // Calculate and print RMS of quantized samples.
    // Calculate and print RMS of quantized samples.
    float sum_squares = ocuduvec::dot_prod(out, out, 0);
    float rms         = std::sqrt(sum_squares / out.size());
    if (std::isnormal(rms)) {
      logger.debug("Quantized IQ samples RMS value of '{}'", rms);
    }
  }
}


void iq_compression_bfp_impl::compress_prb_generic(span<uint8_t>       comp_prb_buffer,
                                                   span<const int16_t> input_quantized,
                                                   unsigned            data_width)
{
  // Determine maximum absolute value and the exponent.
  // Determine maximum absolute value and the exponent.
  const auto* start_it = input_quantized.begin();
  const auto* max_it   = std::max_element(start_it, start_it + NOF_SAMPLES_PER_PRB);
  const auto* min_it   = std::min_element(start_it, start_it + NOF_SAMPLES_PER_PRB);
  unsigned    max_abs  = std::max(std::abs(*max_it), std::abs(*min_it) - 1);


  uint8_t exponent = determine_exponent(max_abs, data_width);

  // Auxiliary arrays to store compressed samples before packing.

  // Auxiliary arrays to store compressed samples before packing.
  std::array<int16_t, NOF_SAMPLES_PER_PRB> compressed_samples;

  // Compress data.

  // Compress data.
  for (unsigned i = 0; i != NOF_SAMPLES_PER_PRB; ++i) {
    compressed_samples[i] = input_quantized[i] >> exponent;
  }

  // Save exponent.

  // Save exponent.
  std::memcpy(comp_prb_buffer.data(), &exponent, sizeof(exponent));
  comp_prb_buffer = comp_prb_buffer.last(comp_prb_buffer.size() - sizeof(exponent));


  bit_buffer buffer = bit_buffer::from_bytes(comp_prb_buffer);
  pack_bytes(buffer, compressed_samples, data_width);
}


void iq_compression_bfp_impl::compress(span<uint8_t>                buffer,
                                       span<const cbf16_t>          iq_data,
                                       const ru_compression_params& params)
{
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
  span<int16_t>      input_quantized_span(input_quantized.data(), float_samples_span.size());
  // Performs conversion of input brain float values to signed 16-bit integers.
  // Performs conversion of input brain float values to signed 16-bit integers.
  quantize_input(input_quantized_span, float_samples_span);


  for (unsigned i = 0; i != nof_prbs; ++i) {
    const auto* in_start_it = input_quantized.begin() + NOF_SAMPLES_PER_PRB * i;
    auto*       out_it      = &buffer[i * prb_size];
    // Compress one resource block.
    // Compress one resource block.
    compress_prb_generic({out_it, prb_size}, {in_start_it, NOF_SAMPLES_PER_PRB}, params.data_width);
  }
}


void iq_compression_bfp_impl::decompress_prb_generic(span<cbf16_t>       output,
                                                     span<const uint8_t> comp_prb,
                                                     const quantizer&    q_in,
                                                     unsigned            data_width)
{
  // Quantizer.
  // Quantizer.
  quantizer q_out(Q_BIT_WIDTH);

  // Compute scaling factor, first byte contains the exponent.

  // Compute scaling factor, first byte contains the exponent.
  uint8_t exponent = comp_prb[0];
  int16_t scaler   = 1 << exponent;


  comp_prb             = comp_prb.last(comp_prb.size() - sizeof(exponent));
  auto bit_buff_reader = bit_buffer_reader::from_bytes(comp_prb);


  for (unsigned i = 0, read_pos = 0; i != NOF_SUBCARRIERS_PER_RB; ++i) {
    int16_t re = q_in.sign_extend(unpack_bits(bit_buff_reader, read_pos, data_width));
    int16_t im = q_in.sign_extend(unpack_bits(bit_buff_reader, read_pos + data_width, data_width));
    read_pos += (data_width * 2);


    float scaled_re = q_out.to_float(re * scaler);
    float scaled_im = q_out.to_float(im * scaler);
    output[i]       = {scaled_re, scaled_im};
  }
}


void iq_compression_bfp_impl::decompress(span<cbf16_t>                iq_data,
                                         span<const uint8_t>          compressed_data,
                                         const ru_compression_params& params)
{
  // Quantizer.
  // Quantizer.
  quantizer q_in(params.data_width);

  // Number of output PRBs.

  // Number of output PRBs.
  unsigned nof_prbs = iq_data.size() / NOF_SUBCARRIERS_PER_RB;

  // Size in bytes of one compressed PRB using the given compression parameters.

  // Size in bytes of one compressed PRB using the given compression parameters.
  unsigned prb_size = get_compressed_prb_size(params).value();


  ocudu_assert(compressed_data.size() >= nof_prbs * prb_size,
               "Input does not contain enough bytes to decompress {} PRBs",
               nof_prbs);


  unsigned out_idx = 0;
  for (unsigned c_prb_idx = 0; c_prb_idx != nof_prbs; ++c_prb_idx) {
    span<const uint8_t> comp_prb(&compressed_data[c_prb_idx * prb_size], prb_size);


    span<cbf16_t> out_prb_samples = iq_data.subspan(out_idx, NOF_SUBCARRIERS_PER_RB);
    // Decompress resource block.
    // Decompress resource block.
    decompress_prb_generic(out_prb_samples, comp_prb, q_in, params.data_width);
    out_idx += NOF_SUBCARRIERS_PER_RB;
  }
}
