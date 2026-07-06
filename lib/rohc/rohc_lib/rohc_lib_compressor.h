// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/rohc/rohc_lib/rohc_lib_compressor.h  (35 lines)
//
// LIBRARY: lib/rohc
// Robust Header Compression (ROHC, RFC 5795/3095): compresses repetitive IP/UDP/RTP headers on DL PDUs before PDCP transmits them over the air. Reduces overhead on low-bitrate or constrained links. Implemented in the CU-UP PDCP path.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/rohc/rohc_config.h"
#include "ocudu/rohc/rohc_compressor.h"
#include <rohc/rohc.h>
#include <rohc/rohc_comp.h>
#include <rohc/rohc_decomp.h>


namespace ocudu::rohc {


class rohc_lib_compressor : public rohc_compressor
{
public:
  rohc_lib_compressor(rohc_config cfg_);
  ~rohc_lib_compressor();
  virtual byte_buffer compress(byte_buffer packet) override;
  virtual bool        handle_feedback(byte_buffer feedback) override;


private:
  ocudulog::basic_logger& logger;


  rohc_config cfg;
  rohc_comp*  compressor = nullptr;


  std::vector<uint8_t> input_packet_buf;
  std::vector<uint8_t> input_feedback_buf;
  std::vector<uint8_t> output_packet_buf;
};


} // namespace ocudu::rohc
