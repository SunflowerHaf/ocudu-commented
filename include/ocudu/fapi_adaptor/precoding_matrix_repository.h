// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi_adaptor/precoding_matrix_repository.h  (39 lines)
//
// INTERFACE HEADER — include/ocudu/fapi_adaptor
// FAPI adaptor interface headers: the phy_fapi_fastpath_adaptor (the in-process FAPI bridge between MAC and upper PHY in split-8), the adaptor configuration struct, and the UCI part-2 size table interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/precoding/precoding_weight_matrix.h"


namespace ocudu {
namespace fapi_adaptor {

/// \brief Precoding matrix repository.
///
/// The repository stores precoding matrices that are accessible using a precoding matrix index.

/// \brief Precoding matrix repository.
///
/// The repository stores precoding matrices that are accessible using a precoding matrix index.
class precoding_matrix_repository
{
public:
  explicit precoding_matrix_repository(std::vector<precoding_weight_matrix> repo_) : repo(std::move(repo_))
  {
    ocudu_assert(!repo.empty(), "Empty container");
  }

  /// Iterators.

  /// Iterators.
  std::vector<precoding_weight_matrix>::const_iterator begin() const { return repo.begin(); }
  std::vector<precoding_weight_matrix>::const_iterator end() const { return repo.end(); }

  /// \brief Returns the precoding matrix associated to the given index.
  ///
  /// Index value must be valid, i.e. a precoding configuration must exist in the repository for that index.

  /// \brief Returns the precoding matrix associated to the given index.
  ///
  /// Index value must be valid, i.e. a precoding configuration must exist in the repository for that index.
  const precoding_weight_matrix& get_precoding_matrix(unsigned index) const;

  /// Returns the number of precoding matrix stored in the repository.

  /// Returns the number of precoding matrix stored in the repository.
  unsigned size() const { return repo.size(); }


private:
  std::vector<precoding_weight_matrix> repo;
};


} // namespace fapi_adaptor
} // namespace ocudu
