// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/compression/iq_decompressor.h  (36 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/ofh
// Open Fronthaul public interface headers. CONDITIONAL: linked into the binary via a temporary dependency (see lib/ofh note) but not used at runtime in split-8. These headers define the OFH contract between the lib/ofh library and its callers (primarily lib/ru/ofh).
//
// Contents:
//   ofh/compression/      — IQ compressor/decompressor abstract interfaces and compression parameter types (scheme, data width, BFP exponent).
//   ofh/ecpri/            — eCPRI packet builder, decoder, and property types.
//   ofh/ethernet/         — Ethernet frame builder/receiver interfaces, VLAN tag types, and port configuration.
//   ofh/ofh_factories.h   — Top-level OFH sector factory.
//   ofh/ofh_sector.h      — OFH sector interface (one per radio sector/cell).
//   ofh/receiver/         — OFH uplink receiver interface (delivers received IQ).
//   ofh/serdes/           — C-plane and U-plane message serialiser interfaces.
//   ofh/timing/           — OFH timing controller interface (slot indication source).
//   ofh/transmitter/      — OFH downlink transmitter interface.
// =============================================================================

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"
#include "ocudu/ofh/compression/compression_params.h"


namespace ocudu {
namespace ofh {

/// \brief Describes the IQ data decompressor.
///
/// Deserializes compression parameters and decompresses received PRBs with compressed IQ data according to compression
/// methods specified in WG4.CUS.0 document.

/// \brief Describes the IQ data decompressor.
///
/// Deserializes compression parameters and decompresses received PRBs with compressed IQ data according to compression
/// methods specified in WG4.CUS.0 document.
class iq_decompressor
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~iq_decompressor() = default;

  /// \brief Decompress received compressed PRBs.
  ///
  /// Decompresses compressed PRBs from the input buffer according to received compression parameters and puts the
  /// results into an array of brain floating point IQ samples.
  ///
  /// \param[out] iq_data  Resulting IQ samples after decompression.
  /// \param[in]  compressed_data A span containing received compressed IQ data and compression parameters.
  /// \param[in]  params  Compression parameters.

  /// \brief Decompress received compressed PRBs.
  ///
  /// Decompresses compressed PRBs from the input buffer according to received compression parameters and puts the
  /// results into an array of brain floating point IQ samples.
  ///
  /// \param[out] iq_data  Resulting IQ samples after decompression.
  /// \param[in]  compressed_data A span containing received compressed IQ data and compression parameters.
  /// \param[in]  params  Compression parameters.
  virtual void
  decompress(span<cbf16_t> iq_data, span<const uint8_t> compressed_data, const ru_compression_params& params) = 0;
};


} // namespace ofh
} // namespace ocudu
