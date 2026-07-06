// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rohc/rohc_factory.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/rohc
// ROHC interface headers: rohc_compressor and rohc_decompressor interfaces, the ROHC context configuration type (max_cid, profiles), and the result type for compression/decompression operations.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/rohc/rohc_config.h"
#include <memory>


namespace ocudu::rohc {


class rohc_compressor;
class rohc_decompressor;


class rohc_factory
{
public:
  virtual ~rohc_factory()                      = default;
  rohc_factory()                               = default;
  rohc_factory(const rohc_factory&)            = delete;
  rohc_factory& operator=(const rohc_factory&) = delete;


  virtual std::unique_ptr<rohc_compressor>   create_rohc_compressor(const rohc_config& cfg) const   = 0;
  virtual std::unique_ptr<rohc_decompressor> create_rohc_decompressor(const rohc_config& cfg) const = 0;
};


std::unique_ptr<rohc_factory> create_rohc_factory();


} // namespace ocudu::rohc
