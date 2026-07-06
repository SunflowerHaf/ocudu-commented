// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Hardware accelerated PDSCH encoder functions declaration.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/hal/phy/upper/channel_processors/hw_accelerator_pdsch_enc.h  (90 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/hal
// HAL (Hardware Abstraction Layer) public interface headers. CONDITIONAL: only required when building with DPDK_FOUND=ON. In the standard USRP/UHD build these headers are not included by any active code path.
//
// Contents:
//   hal/dpdk/             — DPDK EAL handle, mbuf pool, BBDEV device interfaces.
//   hal/hw_accelerator.h  — Base hardware accelerator interface (submit_op, retrieve_op, get capabilities).
//   hal/phy/upper/        — hw_accelerator_pdsch_enc (offload PDSCH LDPC encoding) and hw_accelerator_pusch_dec (offload PUSCH LDPC decoding) abstract interfaces, plus their factory types and the external HARQ buffer context repository interface.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Hardware accelerated PDSCH encoder functions declaration.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/hal/hw_accelerator.h"
#include "ocudu/ran/sch/ldpc_base_graph.h"
#include "ocudu/ran/sch/modulation_scheme.h"


namespace ocudu {
namespace hal {

/// Hardware-accelerated PDSCH encoder configuration parameters.

/// Hardware-accelerated PDSCH encoder configuration parameters.
struct hw_pdsch_encoder_configuration {
  /// Transport Block size expressed as an integer number of bits.
  /// Transport Block size expressed as an integer number of bits.
  unsigned nof_tb_bits;
  /// Transport Block CRC size expressed as an integer number of bits.
  /// Transport Block CRC size expressed as an integer number of bits.
  unsigned nof_tb_crc_bits;
  /// Base graph used for encoding/decoding the current transport block.
  /// Base graph used for encoding/decoding the current transport block.
  ldpc_base_graph_type base_graph_index;
  /// Modulation scheme.
  /// Modulation scheme.
  modulation_scheme modulation;
  /// Number of segments in the transport block.
  /// Number of segments in the transport block.
  unsigned nof_segments;
  /// Number of segments that will have a short rate-matched length.
  /// Number of segments that will have a short rate-matched length.
  unsigned nof_short_segments;
  /// Redundancy version, values in {0, 1, 2, 3}.
  /// Redundancy version, values in {0, 1, 2, 3}.
  unsigned rv;
  /// Total codeword length for short rate-matched segments in bits (Ea).
  /// Total codeword length for short rate-matched segments in bits (Ea).
  unsigned cw_length_a;
  /// Total codeword length for large rate-matched segments in bits (Eb).
  /// Total codeword length for large rate-matched segments in bits (Eb).
  unsigned cw_length_b;
  /// LDPC lifting size (z_c), as per TS38.212, Section 5.2.2.
  /// LDPC lifting size (z_c), as per TS38.212, Section 5.2.2.
  unsigned lifting_size;
  /// Length of the circular buffer in bits.
  /// Length of the circular buffer in bits.
  unsigned Ncb;
  /// Limited buffer rate matching length in bits.
  /// Limited buffer rate matching length in bits.
  unsigned Nref;
  /// Segment size expressed as an integer number of bits.
  /// Segment size expressed as an integer number of bits.
  unsigned nof_segment_bits;
  /// Number of Filler bits (n_filler = K – K’, as per TS38.212 Section 5.2.2.
  /// Number of Filler bits (n_filler = K – K’, as per TS38.212 Section 5.2.2.
  unsigned nof_filler_bits;
  /// Total codeword length after rate-matching in bits (E).
  /// Total codeword length after rate-matching in bits (E).
  unsigned rm_length;
  /// TB CRC bits.
  /// TB CRC bits.
  static_vector<uint8_t, 3> tb_crc;
  /// Operation mode of the PDSCH encoder (CB = true, TB = false [default]).
  /// Operation mode of the PDSCH encoder (CB = true, TB = false [default]).
  bool cb_mode = false;
  // Request the accelerator to attach the CB CRC.
  // Request the accelerator to attach the CB CRC.
  bool attach_cb_crc = false;
  // Request the accelerator to attach the TB CRC.
  // Request the accelerator to attach the TB CRC.
  bool attach_tb_crc = false;
  // Request to unpack the accelerator output data.
  // Request to unpack the accelerator output data.
  bool do_unpack = true;
};

/// Generic hardware accelerated PDSCH encoder functions.

/// Generic hardware accelerated PDSCH encoder functions.
class hw_accelerator_pdsch_enc : public hw_accelerator<uint8_t, uint8_t>
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~hw_accelerator_pdsch_enc() = default;

  // Reserves a hardware queue from the accelerator.

  // Reserves a hardware queue from the accelerator.
  virtual void reserve_queue() = 0;

  // Frees a hardware queue from the accelerator.

  // Frees a hardware queue from the accelerator.
  virtual void free_queue() = 0;

  /// Configures encoding operation given the common HW-oriented PDSCH encoder configuration.
  /// \param[in] config   Structure providing the configuration parameters of the PDSCH encoder.
  /// \param[in] cb_index Optional. Index of the CB for which the PDSCH encoding operation is being configured.

  /// Configures encoding operation given the common HW-oriented PDSCH encoder configuration.
  /// \param[in] config   Structure providing the configuration parameters of the PDSCH encoder.
  /// \param[in] cb_index Optional. Index of the CB for which the PDSCH encoding operation is being configured.
  virtual void configure_operation(const hw_pdsch_encoder_configuration& config, unsigned cb_index = 0) = 0;

  /// Checks if the hardware-accelerated PDSCH encoder uses CB mode or TB mode.
  /// \return True if CB mode is used, false otherwise.

  /// Checks if the hardware-accelerated PDSCH encoder uses CB mode or TB mode.
  /// \return True if CB mode is used, false otherwise.
  virtual bool is_cb_mode_supported() const = 0;

  /// Checks the maximum supported buffer size. Only used in TB mode.
  /// \return Buffer size (in bytes).

  /// Checks the maximum supported buffer size. Only used in TB mode.
  /// \return Buffer size (in bytes).
  virtual unsigned get_max_supported_buff_size() const = 0;
};


} // namespace hal
} // namespace ocudu
