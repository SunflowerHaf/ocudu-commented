// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/iq_compression_bfp_impl.h  (93 lines)
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

#pragma once


#include "quantizer.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/compression/iq_compressor.h"
#include "ocudu/ofh/compression/iq_decompressor.h"
#include "ocudu/ran/resource_block.h"


namespace ocudu {
namespace ofh {

/// Implementation of the Block Floating Point IQ data compression.

/// Implementation of the Block Floating Point IQ data compression.
class iq_compression_bfp_impl : public iq_compressor, public iq_decompressor
{
public:
  // Constructor.
  // Constructor.
  explicit iq_compression_bfp_impl(ocudulog::basic_logger& logger_, float iq_scaling_ = 1.0) :
    logger(logger_), iq_scaling(iq_scaling_)
  {
  }

  // See interface for the documentation.

  // See interface for the documentation.
  virtual void
  compress(span<uint8_t> buffer, span<const cbf16_t> iq_data, const ru_compression_params& params) override;

  // See interface for the documentation.

  // See interface for the documentation.
  virtual void
  decompress(span<cbf16_t> iq_data, span<const uint8_t> compressed_data, const ru_compression_params& params) override;


protected:
  /// Number of quantized samples per resource block.
  /// Number of quantized samples per resource block.
  static constexpr size_t NOF_SAMPLES_PER_PRB = 2 * NOF_SUBCARRIERS_PER_RB;

  /// \brief Determines the exponent to be used in BFP compression.
  ///
  /// First, it determines the maximum left shift that will still preserve the original value (implemented as a counter
  /// of leading zeros without a sign bit). Then, it determines an exponent given the requested \c data_width.
  ///
  /// \param[in] in_sample  16bit input value for which the exponent is calculated.
  /// \param[in] data_width BFP compression bit width.
  /// \return An exponent to be applied to the input sample to compress it to \c data_width bits.

  /// \brief Determines the exponent to be used in BFP compression.
  ///
  /// First, it determines the maximum left shift that will still preserve the original value (implemented as a counter
  /// of leading zeros without a sign bit). Then, it determines an exponent given the requested \c data_width.
  ///
  /// \param[in] in_sample  16bit input value for which the exponent is calculated.
  /// \param[in] data_width BFP compression bit width.
  /// \return An exponent to be applied to the input sample to compress it to \c data_width bits.
  static unsigned determine_exponent(uint16_t x, unsigned data_width)
  {
    ocudu_assert(data_width != 0, "Invalid data width");
    ocudu_assert(data_width <= MAX_IQ_WIDTH, "Passed IQ data width exceeds 16 bits");


    unsigned max_shift       = MAX_IQ_WIDTH - data_width;
    unsigned lz_without_sign = max_shift;


    if ((x > 0) && (max_shift > 0)) {
      // TODO: use a wrapper that checks whether this builtin is actually available and provides a fallback option.
      // TODO: use a wrapper that checks whether this builtin is actually available and provides a fallback option.
      lz_without_sign = __builtin_clz(x) - 16U - 1U;
    }
    int raw_exp = std::min(max_shift, lz_without_sign);
    return std::max(0, static_cast<int>(MAX_IQ_WIDTH - data_width) - raw_exp);
  }

  /// \brief Compresses one resource block using the generic implementation of the algorithm
  /// from O-RAN.WG4.CUS, Annex A.1.2.
  ///
  /// \param[out] c_prb      Compressed PRB.
  /// \param input_quantized Span of quantized IQ samples of a resource block to be compressed.
  /// \param data_width      BFP compression bit width.

  /// \brief Compresses one resource block using the generic implementation of the algorithm
  /// from O-RAN.WG4.CUS, Annex A.1.2.
  ///
  /// \param[out] c_prb      Compressed PRB.
  /// \param input_quantized Span of quantized IQ samples of a resource block to be compressed.
  /// \param data_width      BFP compression bit width.
  static void compress_prb_generic(span<uint8_t> c_prb, span<const int16_t> input_quantized, unsigned data_width);

  /// \brief Decompresses one resource block using a generic implementation of the algorithm
  /// from O-RAN.WG4.CUS, Annex A.1.3.
  ///
  /// \param[out] output   Span of decompressed complex samples of a resource block (12 samples).
  /// \param[in]  comp_prb Compressed PRB IQ samples and compression parameter.
  /// \param[in]  q        Quantizer object.
  /// \param data_width    Bit width of compressed samples.

  /// \brief Decompresses one resource block using a generic implementation of the algorithm
  /// from O-RAN.WG4.CUS, Annex A.1.3.
  ///
  /// \param[out] output   Span of decompressed complex samples of a resource block (12 samples).
  /// \param[in]  comp_prb Compressed PRB IQ samples and compression parameter.
  /// \param[in]  q        Quantizer object.
  /// \param data_width    Bit width of compressed samples.
  static void
  decompress_prb_generic(span<cbf16_t> output, span<const uint8_t> comp_prb, const quantizer& q, unsigned data_width);

  /// Quantizes complex float samples using the specified bit width.
  ///
  /// \param[out] out      Quantized samples.
  /// \param[in] in        Span of input float samples.
  /// \param[in] bit_width Number of significant bits used by the quantized samples.

  /// Quantizes complex float samples using the specified bit width.
  ///
  /// \param[out] out      Quantized samples.
  /// \param[in] in        Span of input float samples.
  /// \param[in] bit_width Number of significant bits used by the quantized samples.
  void quantize_input(span<int16_t> out, span<const bf16_t> in);


private:
  ocudulog::basic_logger& logger;
  /// Scaling factor applied to IQ data prior to quantization.
  /// Scaling factor applied to IQ data prior to quantization.
  const float iq_scaling;
};


} // namespace ofh
} // namespace ocudu
