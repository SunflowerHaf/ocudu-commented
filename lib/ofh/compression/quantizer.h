// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/quantizer.h  (123 lines)
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


#include "ocudu/ocuduvec/conversion.h"
#include <cmath>
#include <cstdint>


namespace ocudu {
namespace ofh {

/// Describes quantization of floating point number in the range [-1; +1] to a fixed point number of a given bit width.

/// Describes quantization of floating point number in the range [-1; +1] to a fixed point number of a given bit width.
class quantizer
{
public:
  /// Constructor receives width in bits of a resulting fixed point number.
  /// Constructor receives width in bits of a resulting fixed point number.
  explicit quantizer(unsigned bit_width_) :
    bit_width(bit_width_), nbits_shift_sign(16U - bit_width), gain((1 << (bit_width - 1)) - 1.0f)
  {
  }

  /// \brief Quantizes a floating point value into 16-bit integer.
  ///
  /// \param[in] value A floating point value.
  /// \return Resultant quantized value.

  /// \brief Quantizes a floating point value into 16-bit integer.
  ///
  /// \param[in] value A floating point value.
  /// \return Resultant quantized value.
  int16_t to_fixed_point(float value) const
  {
    float clipped = value;
    if (std::abs(value) > 1.0) {
      clipped = std::copysign(1.0, value);
    }
    return static_cast<int16_t>(std::round(clipped * gain));
  }

  /// \brief Quantizes a brain float value into a 16-bit integer.
  ///
  /// \param[in] value A brain float value.
  /// \return Resultant quantized value.

  /// \brief Quantizes a brain float value into a 16-bit integer.
  ///
  /// \param[in] value A brain float value.
  /// \return Resultant quantized value.
  int16_t to_fixed_point(bf16_t value) const
  {
    float input_value = ocudu::to_float(value);
    return to_fixed_point(input_value);
  }

  /// \brief Quantizes a sequence of floating point values into 16bit integers.
  ///
  /// \param[out] z       Resultant quantized values.
  /// \param[in] x        Sequence of floating point values.
  /// \param[in] in_scale Scaling factor applied to the input prior conversion.
  ///
  /// \remark \c z and \c x must have the same size.

  /// \brief Quantizes a sequence of floating point values into 16bit integers.
  ///
  /// \param[out] z       Resultant quantized values.
  /// \param[in] x        Sequence of floating point values.
  /// \param[in] in_scale Scaling factor applied to the input prior conversion.
  ///
  /// \remark \c z and \c x must have the same size.
  void to_fixed_point(span<int16_t> z, span<const float> x, float in_scale) const
  {
    float scale = gain * in_scale;
    ocuduvec::convert(z, x, scale);
  }

  /// \brief Quantizes a sequence of brain float values into 16-bit integers.
  ///
  /// \param[out] z       Resultant quantized values.
  /// \param[in] x        Sequence of brain float values.
  /// \param[in] in_scale Scaling factor applied to the input prior conversion.
  ///
  /// \remark \c z and \c x must have the same size.

  /// \brief Quantizes a sequence of brain float values into 16-bit integers.
  ///
  /// \param[out] z       Resultant quantized values.
  /// \param[in] x        Sequence of brain float values.
  /// \param[in] in_scale Scaling factor applied to the input prior conversion.
  ///
  /// \remark \c z and \c x must have the same size.
  void to_fixed_point(span<int16_t> z, span<const bf16_t> x, float in_scale) const
  {
    float scale = gain * in_scale;
    ocuduvec::convert(z, x, scale);
  }

  /// \brief Converts fixed point value to floating point.
  ///
  /// \param[in] p 16-bit integer value.
  /// \return Resultant floating point value.

  /// \brief Converts fixed point value to floating point.
  ///
  /// \param[in] p 16-bit integer value.
  /// \return Resultant floating point value.
  float to_float(int p) const { return (p / gain); }

  /// \brief Converts a sequence of fixed point values to complex floating point values.
  ///
  /// \param[out] z       Resultant complex floating point values.
  /// \param[in] x        Sequence of 16-bit integer values.
  /// \param[in] in_scale Scaling factor (expected to be bigger or equal to 1) applied to the input prior conversion.
  ///
  /// \remark The size of \c x must be twice the size of \c z as \x is comprised by the quantized pairs of real and
  /// imaginary parts of complex values.

  /// \brief Converts a sequence of fixed point values to complex floating point values.
  ///
  /// \param[out] z       Resultant complex floating point values.
  /// \param[in] x        Sequence of 16-bit integer values.
  /// \param[in] in_scale Scaling factor (expected to be bigger or equal to 1) applied to the input prior conversion.
  ///
  /// \remark The size of \c x must be twice the size of \c z as \x is comprised by the quantized pairs of real and
  /// imaginary parts of complex values.
  void to_float(span<cf_t> z, span<const int16_t> x, int16_t in_scale) const
  {
    float scale = gain / in_scale;
    ocuduvec::convert(z, x, scale);
  }

  /// \brief Converts a sequence of fixed point values to complex brain floating point values.
  ///
  /// \param[out] z       Resultant complex brain floating point values.
  /// \param[in] x        Sequence of 16-bit integer values.
  /// \param[in] in_scale Scaling factor (expected to be bigger or equal to 1) applied to the input prior conversion.
  ///
  /// \remark The size of \c x must be twice the size of \c z as \x is comprised by the quantized pairs of real and
  /// imaginary parts of complex values.

  /// \brief Converts a sequence of fixed point values to complex brain floating point values.
  ///
  /// \param[out] z       Resultant complex brain floating point values.
  /// \param[in] x        Sequence of 16-bit integer values.
  /// \param[in] in_scale Scaling factor (expected to be bigger or equal to 1) applied to the input prior conversion.
  ///
  /// \remark The size of \c x must be twice the size of \c z as \x is comprised by the quantized pairs of real and
  /// imaginary parts of complex values.
  void to_brain_float(span<cbf16_t> z, span<const int16_t> x, int16_t in_scale) const
  {
    float scale = gain / in_scale;
    ocuduvec::convert(z, x, scale);
  }

  /// Sign extends the input value.

  /// Sign extends the input value.
  int16_t sign_extend(int16_t value) const
  {
    int16_t shifted = value << nbits_shift_sign;
    return shifted >> nbits_shift_sign;
  }


private:
  /// Width of fixed point number in bits.
  /// Width of fixed point number in bits.
  const unsigned bit_width;
  /// Shift for sign extention.
  /// Shift for sign extention.
  const unsigned nbits_shift_sign;
  /// Quantization gain.
  /// Quantization gain.
  const float gain;
};


} // namespace ofh
} // namespace ocudu
