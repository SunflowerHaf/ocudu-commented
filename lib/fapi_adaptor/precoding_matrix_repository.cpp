// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/precoding_matrix_repository.cpp  (15 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/fapi_adaptor/precoding_matrix_repository.h"


using namespace ocudu;
using namespace fapi_adaptor;


const precoding_weight_matrix& precoding_matrix_repository::get_precoding_matrix(unsigned index) const
{
  ocudu_assert(index < repo.size(), "Invalid precoding matrix index={}, repository size={}", index, repo.size());
  ocudu_assert(repo[index].get_nof_layers() != 0, "Invalid precoding matrix index={}", index);


  return repo[index];
}
