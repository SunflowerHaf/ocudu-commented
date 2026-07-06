// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/precoding/precoding_weight_matrix.h  (256 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/tensor.h"
#include "ocudu/ocuduvec/copy.h"
#include "ocudu/ocuduvec/sc_prod.h"
#include "ocudu/ocuduvec/zero.h"
#include "ocudu/ran/precoding/precoding_constants.h"


namespace ocudu {

/// Precoding matrix, consisting of complex coefficients arranged by i) transmit layers and ii) antenna ports.

/// Precoding matrix, consisting of complex coefficients arranged by i) transmit layers and ii) antenna ports.
class precoding_weight_matrix
{
public:
  /// Precoding coefficient dimensions.
  /// Precoding coefficient dimensions.
  enum class dims : unsigned { layer = 0, port, all };

  /// Default constructor - constructs a precoding weight matrix with no coefficients.

  /// Default constructor - constructs a precoding weight matrix with no coefficients.
  precoding_weight_matrix() = default;

  /// \brief Constructs a weight matrix with the desired number of layers and ports.
  ///
  /// The coefficients are set to zero.
  ///
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.

  /// \brief Constructs a weight matrix with the desired number of layers and ports.
  ///
  /// The coefficients are set to zero.
  ///
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.
  precoding_weight_matrix(unsigned nof_layers, unsigned nof_ports) : data({nof_layers, nof_ports})
  {
    ocudu_assert(nof_layers <= precoding_constants::MAX_NOF_LAYERS,
                 "The number of layers (i.e., {}) exceeds the maximum (i.e., {}).",
                 nof_layers,
                 precoding_constants::MAX_NOF_LAYERS);
    ocudu_assert(nof_ports <= precoding_constants::MAX_NOF_PORTS,
                 "The number of ports (i.e., {}) exceeds the maximum (i.e., {}).",
                 nof_ports,
                 precoding_constants::MAX_NOF_PORTS);

    // Zero all data.

    // Zero all data.
    ocuduvec::zero(data.get_data());
  }

  /// \brief Constructs a precoding weight matrix with the desired number of layers and ports.
  ///
  /// Creates a precoding weight matrix with the specified dimensions, and sets its contents to the provided weight
  /// values.
  ///
  /// \param[in] weights Precoding weight list, arranged by i) layer and ii) antenna port.
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.

  /// \brief Constructs a precoding weight matrix with the desired number of layers and ports.
  ///
  /// Creates a precoding weight matrix with the specified dimensions, and sets its contents to the provided weight
  /// values.
  ///
  /// \param[in] weights Precoding weight list, arranged by i) layer and ii) antenna port.
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.
  precoding_weight_matrix(const std::initializer_list<cf_t>& weights, unsigned nof_layers, unsigned nof_ports) :
    precoding_weight_matrix(span<const cf_t>(weights.begin(), weights.end()), nof_layers, nof_ports)
  {
  }

  /// \brief Constructs a weight matrix with the desired number of layers and ports.
  ///
  /// Creates a precoding weight matrix with the specified dimensions, and sets its contents to the provided weight
  /// values.
  ///
  /// \param[in] weights Precoding weight list, arranged by i) layer and ii) antenna port.
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.

  /// \brief Constructs a weight matrix with the desired number of layers and ports.
  ///
  /// Creates a precoding weight matrix with the specified dimensions, and sets its contents to the provided weight
  /// values.
  ///
  /// \param[in] weights Precoding weight list, arranged by i) layer and ii) antenna port.
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.
  precoding_weight_matrix(span<const cf_t> weights, unsigned nof_layers, unsigned nof_ports) :
    data({nof_layers, nof_ports})
  {
    ocudu_assert(
        weights.size() == nof_ports * nof_layers,
        "The number of weights, i.e., {}, does not match the specified matrix dimensions, i.e., {} layers, {} ports.",
        weights.size(),
        nof_layers,
        nof_ports);


    ocudu_assert(nof_layers <= precoding_constants::MAX_NOF_LAYERS,
                 "The number of layers (i.e., {}) exceeds the maximum (i.e., {}).",
                 nof_layers,
                 precoding_constants::MAX_NOF_LAYERS);
    ocudu_assert(nof_ports <= precoding_constants::MAX_NOF_PORTS,
                 "The number of ports (i.e., {}) exceeds the maximum (i.e., {}).",
                 nof_ports,
                 precoding_constants::MAX_NOF_PORTS);

    // Copy the weights into the tensor.

    // Copy the weights into the tensor.
    ocuduvec::copy(data.get_view<static_cast<unsigned>(dims::all)>({}), weights);
  }

  /// Copy constructor.

  /// Copy constructor.
  precoding_weight_matrix(const precoding_weight_matrix& other) : data({other.get_nof_layers(), other.get_nof_ports()})
  {
    // Copy the weights into the tensor.
    // Copy the weights into the tensor.
    ocuduvec::copy(data.get_view<static_cast<unsigned>(dims::all)>({}),
                   other.data.get_view<static_cast<unsigned>(dims::all)>({}));
  }

  /// \brief Overload assignment operator.
  /// \param[in] other Precoding weight matrix to copy.

  /// \brief Overload assignment operator.
  /// \param[in] other Precoding weight matrix to copy.
  precoding_weight_matrix& operator=(const precoding_weight_matrix& other)
  {
    if (this == &other) {
      return *this;
    }

    // Resize the tensor.

    // Resize the tensor.
    resize(other.get_nof_layers(), other.get_nof_ports());
    // Copy the weights into the tensor.
    // Copy the weights into the tensor.
    ocuduvec::copy(data.get_view<static_cast<unsigned>(dims::all)>({}),
                   other.data.get_view<static_cast<unsigned>(dims::all)>({}));
    return *this;
  }

  /// \brief Overload equality comparison operator.
  /// \param[in] other Precoding weight matrix to compare against.
  /// \return \c true if both precoding matrices are exactly the same, \c false otherwise.

  /// \brief Overload equality comparison operator.
  /// \param[in] other Precoding weight matrix to compare against.
  /// \return \c true if both precoding matrices are exactly the same, \c false otherwise.
  bool operator==(const precoding_weight_matrix& other) const
  {
    unsigned nof_layers = get_nof_layers();
    unsigned nof_ports  = get_nof_ports();


    if (nof_layers != other.get_nof_layers()) {
      return false;
    }
    if (nof_ports != other.get_nof_ports()) {
      return false;
    }


    for (unsigned i_layer = 0; i_layer != nof_layers; ++i_layer) {
      for (unsigned i_port = 0; i_port != nof_ports; ++i_port) {
        if (get_coefficient(i_layer, i_port) != other.get_coefficient(i_layer, i_port)) {
          return false;
        }
      }
    }


    return true;
  }

  /// Overload inequality comparison operator.

  /// Overload inequality comparison operator.
  bool operator!=(const precoding_weight_matrix& other) const { return !(*this == other); }

  /// Gets the current number of layers.

  /// Gets the current number of layers.
  unsigned get_nof_layers() const { return data.get_dimension_size(dims::layer); }

  /// Gets the current number of ports.

  /// Gets the current number of ports.
  unsigned get_nof_ports() const { return data.get_dimension_size(dims::port); }

  /// \brief Gets a read-only view of the precoding weights for a given port.
  ///
  /// \param[in] i_port Port identifier.
  /// \return The corresponding precoding weights, indexed by layer.
  /// \remark An assertion is triggered if the port identifier is greater than or equal to get_nof_ports().

  /// \brief Gets a read-only view of the precoding weights for a given port.
  ///
  /// \param[in] i_port Port identifier.
  /// \return The corresponding precoding weights, indexed by layer.
  /// \remark An assertion is triggered if the port identifier is greater than or equal to get_nof_ports().
  span<const cf_t> get_port_coefficients(unsigned i_port) const
  {
    ocudu_assert((i_port < get_nof_ports()),
                 "The requested antenna port, i.e., {}, must be smaller than the number of ports, i.e., {}.",
                 i_port,
                 get_nof_ports());


    return data.get_view({i_port});
  }

  /// \brief Gets a read-write view of the precoding weights for a given port.
  ///
  /// \param[in] i_port Port identifier.
  /// \return The corresponding precoding weights, indexed by layer.
  /// \remark An assertion is triggered if the port identifier is greater than or equal to get_nof_ports().

  /// \brief Gets a read-write view of the precoding weights for a given port.
  ///
  /// \param[in] i_port Port identifier.
  /// \return The corresponding precoding weights, indexed by layer.
  /// \remark An assertion is triggered if the port identifier is greater than or equal to get_nof_ports().
  span<cf_t> get_port_coefficients(unsigned i_port)
  {
    ocudu_assert((i_port < get_nof_ports()),
                 "The requested antenna port, i.e., {}, must be smaller than the number of ports, i.e., {}.",
                 i_port,
                 get_nof_ports());


    return data.get_view({i_port});
  }

  /// \brief Gets a precoding coefficient from the matrix.
  ///
  /// \param[in] i_layer Layer identifier.
  /// \param[in] i_port Port identifier.
  /// \return The precoding coefficient for the given layer and port.

  /// \brief Gets a precoding coefficient from the matrix.
  ///
  /// \param[in] i_layer Layer identifier.
  /// \param[in] i_port Port identifier.
  /// \return The precoding coefficient for the given layer and port.
  cf_t get_coefficient(unsigned i_layer, unsigned i_port) const
  {
    ocudu_assert(i_layer < get_nof_layers(),
                 "The layer identifier (i.e., {}) exceeds the maximum (i.e., {}).",
                 i_layer,
                 get_nof_layers() - 1);
    ocudu_assert(i_port < get_nof_ports(),
                 "The ports identifier (i.e., {}) exceeds the maximum (i.e., {}).",
                 i_port,
                 get_nof_ports() - 1);
    return data[{i_layer, i_port}];
  }

  /// \brief Sets a precoding coefficient in the matrix to a specified value.
  ///
  /// \param[in] i_layer Layer identifier.
  /// \param[in] i_port Port identifier.

  /// \brief Sets a precoding coefficient in the matrix to a specified value.
  ///
  /// \param[in] i_layer Layer identifier.
  /// \param[in] i_port Port identifier.
  void set_coefficient(cf_t coefficient, unsigned i_layer, unsigned i_port)
  {
    ocudu_assert(i_layer < get_nof_layers(),
                 "The layer identifier (i.e., {}) exceeds the maximum (i.e., {}).",
                 i_layer,
                 get_nof_layers() - 1);
    ocudu_assert(i_port < get_nof_ports(),
                 "The ports identifier (i.e., {}) exceeds the maximum (i.e., {}).",
                 i_port,
                 get_nof_ports() - 1);
    data[{i_layer, i_port}] = coefficient;
  }

  /// Scales all the weights by a scaling factor.

  /// Scales all the weights by a scaling factor.
  precoding_weight_matrix& operator*=(float scale)
  {
    ocuduvec::sc_prod(data.get_data(), data.get_data(), scale);
    return *this;
  }


private:
  /// \brief Resizes the number of coefficients to a desired number of layers and ports.
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.
  /// \brief Resizes the number of coefficients to a desired number of layers and ports.
  /// \param[in] nof_layers Number of layers.
  /// \param[in] nof_ports  Number of ports.
  /// \remark An assertion is triggered if the number of layers exceeds \ref precoding_constants::MAX_NOF_LAYERS.
  /// \remark An assertion is triggered if the number of ports exceeds \ref precoding_constants::MAX_NOF_PORTS.
  void resize(unsigned nof_layers, unsigned nof_ports)
  {
    ocudu_assert(nof_layers <= precoding_constants::MAX_NOF_LAYERS,
                 "The number of layers (i.e., {}) exceeds the maximum (i.e., {}).",
                 nof_layers,
                 precoding_constants::MAX_NOF_LAYERS);
    ocudu_assert(nof_ports <= precoding_constants::MAX_NOF_PORTS,
                 "The number of ports (i.e., {}) exceeds the maximum (i.e., {}).",
                 nof_ports,
                 precoding_constants::MAX_NOF_PORTS);


    data.resize({nof_layers, nof_ports});
  }

  /// Internal data storage.

  /// Internal data storage.
  static_tensor<static_cast<unsigned>(dims::all),
                cf_t,
                precoding_constants::MAX_NOF_LAYERS * precoding_constants::MAX_NOF_PORTS,
                dims>
      data;
};


} // namespace ocudu
