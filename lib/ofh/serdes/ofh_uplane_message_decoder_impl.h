// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/serdes/ofh_uplane_message_decoder_impl.h  (104 lines)
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
#include "ocudu/ofh/compression/iq_decompressor.h"
#include "ocudu/ofh/serdes/ofh_uplane_message_decoder.h"


namespace ocudu {
namespace ofh {


class iq_decompressor;
class network_order_binary_deserializer;

/// Open Fronthaul User-Plane section parameter for this decoder implementation.

/// Open Fronthaul User-Plane section parameter for this decoder implementation.
struct decoder_uplane_section_params {
  /// Section identifier.
  /// Section identifier.
  unsigned section_id;
  /// Resource block indicator.
  /// Resource block indicator.
  bool is_every_rb_used;
  /// Symbol number increment command.
  /// Symbol number increment command.
  bool use_current_symbol_number;
  /// Start PRB.
  /// Start PRB.
  unsigned start_prb;
  /// Number of PRBs (though a value of 0 signals more than 255 PRBs in the OFH specification, this field always
  /// contains the real amount of PRBs).
  /// Number of PRBs (though a value of 0 signals more than 255 PRBs in the OFH specification, this field always
  /// contains the real amount of PRBs).
  unsigned nof_prbs;
  /// User data compression header.
  /// User data compression header.
  ru_compression_params ud_comp_hdr;
  /// User data compression length.
  /// User data compression length.
  std::optional<unsigned> ud_comp_len;
  /// User data compression parameter.
  /// \note For simplicity, all the PRBs use the same compression parameters.
  /// User data compression parameter.
  /// \note For simplicity, all the PRBs use the same compression parameters.
  std::optional<unsigned> ud_comp_param;
};

/// Open Fronthaul User-Plane message decoder implementation.

/// Open Fronthaul User-Plane message decoder implementation.
class uplane_message_decoder_impl : public uplane_message_decoder
{
protected:
  /// Decoded status of a section.
  /// Decoded status of a section.
  enum class decoded_section_status { ok, incomplete, malformed };


public:
  uplane_message_decoder_impl(ocudulog::basic_logger&          logger_,
                              subcarrier_spacing               scs_,
                              unsigned                         nof_symbols_,
                              unsigned                         ru_nof_prbs_,
                              unsigned                         sector_id_,
                              std::unique_ptr<iq_decompressor> decompressor_) :
    logger(logger_),
    decompressor(std::move(decompressor_)),
    scs(scs_),
    nof_symbols(nof_symbols_),
    ru_nof_prbs(ru_nof_prbs_),
    sector_id(sector_id_)
  {
    ocudu_assert(decompressor, "Invalid IQ decompressor");
  }

  // See interface for documentation.

  // See interface for documentation.
  bool decode(uplane_message_decoder_results& results, span<const uint8_t> message) override;


private:
  /// Decodes the User-Plane message header and returns true on success, otherwise false.
  /// Decodes the User-Plane message header and returns true on success, otherwise false.
  bool decode_header(uplane_message_params& params, network_order_binary_deserializer& deserializer);

  /// Decodes all sections and returns true on success, otherwise false.

  /// Decodes all sections and returns true on success, otherwise false.
  bool decode_all_sections(uplane_message_decoder_results& results, network_order_binary_deserializer& deserializer);

  /// Decodes a single section and returns the decoded section status.

  /// Decodes a single section and returns the decoded section status.
  decoded_section_status decode_section(uplane_message_decoder_results&    results,
                                        network_order_binary_deserializer& deserializer);

  /// Decodes the section header and returns the decoded section status.

  /// Decodes the section header and returns the decoded section status.
  decoded_section_status decode_section_header(decoder_uplane_section_params&     results,
                                               network_order_binary_deserializer& deserializer);

  /// Decodes the compression length field and returns the decoded section status.

  /// Decodes the compression length field and returns the decoded section status.
  decoded_section_status decode_compression_length(decoder_uplane_section_params&     results,
                                                   network_order_binary_deserializer& deserializer,
                                                   const ru_compression_params&       compression_params);

  /// Decodes the IQ data from the given deserializer.

  /// Decodes the IQ data from the given deserializer.
  void decode_iq_data(uplane_section_params&             results,
                      network_order_binary_deserializer& deserializer,
                      const ru_compression_params&       compression_params);

  /// Decodes the compression header and returns the decoded section status.

  /// Decodes the compression header and returns the decoded section status.
  virtual decoded_section_status decode_compression_header(decoder_uplane_section_params&     results,
                                                           network_order_binary_deserializer& deserializer) = 0;


protected:
  ocudulog::basic_logger&          logger;
  std::unique_ptr<iq_decompressor> decompressor;
  const subcarrier_spacing         scs;
  const unsigned                   nof_symbols;
  const unsigned                   ru_nof_prbs;
  const unsigned                   sector_id;
};


} // namespace ofh
} // namespace ocudu
