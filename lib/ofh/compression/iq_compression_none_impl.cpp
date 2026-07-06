// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/iq_compression_none_impl.cpp  (89 lines)
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

#include "iq_compression_none_impl.h"
#include "packing_utils_generic.h"
#include "quantizer.h"
#include "ocudu/ocuduvec/dot_prod.h"
#include "ocudu/ofh/compression/compression_properties.h"
#include "ocudu/support/units.h"


using namespace ocudu;
using namespace ofh;


void iq_compression_none_impl::compress(span<uint8_t>                buffer,
                                        span<const cbf16_t>          iq_data,
                                        const ru_compression_params& params)
{
  // Quantizer object.
  // Quantizer object.
  quantizer q(params.data_width);

  // Number of input PRBs.

  // Number of input PRBs.
  unsigned nof_prbs = (iq_data.size() / NOF_SUBCARRIERS_PER_RB);

  // Size in bytes of one compressed PRB using the given compression parameters.

  // Size in bytes of one compressed PRB using the given compression parameters.
  unsigned prb_size = get_compressed_prb_size(params).value();


  ocudu_assert(buffer.size() >= prb_size * nof_prbs, "Output buffer doesn't have enough space to decompress PRBs");


  span<const bf16_t> float_samples(reinterpret_cast<const bf16_t*>(iq_data.data()), iq_data.size() * 2);


  unsigned in_sample_idx = 0;
  for (unsigned rb = 0; rb != nof_prbs; ++rb) {
    // Auxiliary buffer used for brain float to int16_t conversion.
    // Auxiliary buffer used for brain float to int16_t conversion.
    std::array<int16_t, NOF_SUBCARRIERS_PER_RB * 2> conv_buffer;

    // Scale input IQ data to the range [-1: +1) and convert it to int16_t.

    // Scale input IQ data to the range [-1: +1) and convert it to int16_t.
    q.to_fixed_point(conv_buffer, float_samples.subspan(in_sample_idx, NOF_SUBCARRIERS_PER_RB * 2), iq_scaling);

    // View over output bytes corresponding to the current PRB.

    // View over output bytes corresponding to the current PRB.
    span<uint8_t> out_compr_prb(&buffer[rb * prb_size], prb_size);


    bit_buffer bit_buf = bit_buffer::from_bytes(out_compr_prb);
    pack_bytes(bit_buf, conv_buffer, params.data_width);


    in_sample_idx += (NOF_SUBCARRIERS_PER_RB * 2);
  }
}


void iq_compression_none_impl::decompress(span<cbf16_t>                output,
                                          span<const uint8_t>          input,
                                          const ru_compression_params& params)
{
  // Quantizer object.
  // Quantizer object.
  quantizer q(params.data_width);

  // Number of output PRBs.

  // Number of output PRBs.
  unsigned nof_prbs = output.size() / NOF_SUBCARRIERS_PER_RB;

  // Size in bytes of one compressed PRB using the given compression parameters.

  // Size in bytes of one compressed PRB using the given compression parameters.
  unsigned prb_size = get_compressed_prb_size(params).value();


  ocudu_assert(
      input.size() >= nof_prbs * prb_size, "Input does not contain enough bytes to decompress {} PRBs", nof_prbs);


  unsigned out_idx = 0;
  for (unsigned c_prb_idx = 0, e = nof_prbs; c_prb_idx != e; ++c_prb_idx) {
    span<const uint8_t> c_prb(&input[c_prb_idx * prb_size], prb_size);


    bit_buffer_reader bits_reader = bit_buffer_reader::from_bytes(c_prb);
    for (unsigned i = 0, read_pos = 0; i != NOF_SUBCARRIERS_PER_RB; ++i) {
      int16_t re = q.sign_extend(unpack_bits(bits_reader, read_pos, params.data_width));
      int16_t im = q.sign_extend(unpack_bits(bits_reader, read_pos + params.data_width, params.data_width));
      read_pos += (params.data_width * 2);
      output[out_idx++] = {q.to_float(re), q.to_float(im)};
    }
  }
}


void iq_compression_none_impl::log_post_quantization_rms(span<const int16_t> samples)
{
  if (OCUDU_UNLIKELY(logger.debug.enabled() && !samples.empty())) {
    // Calculate and print RMS of quantized samples.
    // Calculate and print RMS of quantized samples.
    float sum_squares = ocuduvec::dot_prod(samples, samples, 0);
    float rms         = std::sqrt(sum_squares / samples.size());
    if (std::isnormal(rms)) {
      logger.debug("Quantized IQ samples RMS value of '{}'", rms);
    }
  }
}
