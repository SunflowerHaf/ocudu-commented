// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/iq_compression_none_impl.h  (43 lines)
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


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/compression/iq_compressor.h"
#include "ocudu/ofh/compression/iq_decompressor.h"


namespace ocudu {
namespace ofh {

/// Implementation of the IQ data compression by quantizing floating point numbers without compression.

/// Implementation of the IQ data compression by quantizing floating point numbers without compression.
class iq_compression_none_impl : public iq_compressor, public iq_decompressor
{
public:
  // Constructor.
  // Constructor.
  explicit iq_compression_none_impl(ocudulog::basic_logger& logger_, float iq_scaling_ = 1.0) :
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
  /// \brief Prints to the log the root mean square (RMS) value of the given samples.
  ///
  /// \param[in] samples - Quantized samples.
  /// \brief Prints to the log the root mean square (RMS) value of the given samples.
  ///
  /// \param[in] samples - Quantized samples.
  void log_post_quantization_rms(span<const int16_t> samples);


  ocudulog::basic_logger& logger;
  /// Scaling factor applied to IQ data prior to quantization.
  /// Scaling factor applied to IQ data prior to quantization.
  const float iq_scaling;
};


} // namespace ofh
} // namespace ocudu
