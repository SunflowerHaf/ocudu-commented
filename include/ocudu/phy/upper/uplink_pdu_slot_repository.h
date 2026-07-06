// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/uplink_pdu_slot_repository.h  (175 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/shared_resource_grid.h"
#include "ocudu/phy/upper/channel_processors/pucch/pucch_processor.h"
#include "ocudu/phy/upper/channel_processors/pusch/pusch_processor.h"
#include "ocudu/phy/upper/signal_processors/srs/srs_estimator_configuration.h"
#include "ocudu/phy/upper/uplink_processor_context.h"
#include <variant>


namespace ocudu {

/// \brief Uplink slot PDU repository.
///
/// This class registers PUSCH, PUCCH and SRS PDUs to be processed in the same slot context.

/// \brief Uplink slot PDU repository.
///
/// This class registers PUSCH, PUCCH and SRS PDUs to be processed in the same slot context.
class uplink_pdu_slot_repository
{
public:
  /// PUSCH PDU configuration.
  /// PUSCH PDU configuration.
  struct pusch_pdu {
    /// HARQ process number.
    /// HARQ process number.
    unsigned harq_id;
    /// Transport block size.
    /// Transport block size.
    units::bytes tb_size;
    /// PUSCH processor PDU.
    /// PUSCH processor PDU.
    pusch_processor::pdu_t pdu;
  };

  /// PUCCH PDU configuration.

  /// PUCCH PDU configuration.
  struct pucch_pdu {
    /// PUCCH context.
    /// PUCCH context.
    ul_pucch_context context;
    /// PUCCH configuration.
    /// PUCCH configuration.
    std::variant<pucch_processor::format0_configuration,
                 pucch_processor::format1_configuration,
                 pucch_processor::format2_configuration,
                 pucch_processor::format3_configuration,
                 pucch_processor::format4_configuration>
        config;
  };

  /// Sounding Reference Signals PDU configuration.

  /// Sounding Reference Signals PDU configuration.
  struct srs_pdu {
    /// SRS context.
    /// SRS context.
    ul_srs_context context;
    /// Actual SRS channel estimator configuration.
    /// Actual SRS channel estimator configuration.
    srs_estimator_configuration config;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~uplink_pdu_slot_repository() = default;

  /// Adds the given PUSCH PDU to the repository.

  /// Adds the given PUSCH PDU to the repository.
  virtual void add_pusch_pdu(const pusch_pdu& pdu) = 0;

  /// Adds the given PUCCH PDU to the repository.

  /// Adds the given PUCCH PDU to the repository.
  virtual void add_pucch_pdu(const pucch_pdu& pdu) = 0;

  /// Adds the given SRS PDU to the repository.

  /// Adds the given SRS PDU to the repository.
  virtual void add_srs_pdu(const srs_pdu& pdu) = 0;
};

/// \brief Unique uplink PDU slot repository.
///
/// Keeps the uplink PDU slot repository interface available for enqueuing uplink transmissions as long as it is
/// available in a scope.
///
/// The uplink PDU slot repository closes the window for accepting new PDUs when the unique instance is either destroyed
/// or released.

/// \brief Unique uplink PDU slot repository.
///
/// Keeps the uplink PDU slot repository interface available for enqueuing uplink transmissions as long as it is
/// available in a scope.
///
/// The uplink PDU slot repository closes the window for accepting new PDUs when the unique instance is either destroyed
/// or released.
class unique_uplink_pdu_slot_repository
{
public:
  /// Uplink PDU repository underlying interface.
  /// Uplink PDU repository underlying interface.
  class uplink_pdu_slot_repository_callback : public uplink_pdu_slot_repository
  {
  public:
    /// Default destructor.
    /// Default destructor.
    ~uplink_pdu_slot_repository_callback() override = default;

    /// Stops adding PDUs.

    /// Stops adding PDUs.
    virtual shared_resource_grid finish_adding_pdus() = 0;
  };

  /// Default constructor - creates an invalid uplink repository.

  /// Default constructor - creates an invalid uplink repository.
  unique_uplink_pdu_slot_repository() = default;

  /// Builds a unique uplink repository from an underlying instance.

  /// Builds a unique uplink repository from an underlying instance.
  explicit unique_uplink_pdu_slot_repository(uplink_pdu_slot_repository_callback& repository_) :
    repository(&repository_)
  {
  }

  /// Disabled copy constructor.

  /// Disabled copy constructor.
  unique_uplink_pdu_slot_repository(const unique_uplink_pdu_slot_repository&) = delete;

  /// Disabled copy assignment operator.

  /// Disabled copy assignment operator.
  unique_uplink_pdu_slot_repository& operator=(const unique_uplink_pdu_slot_repository& other) = delete;

  /// Move constructor.

  /// Move constructor.
  unique_uplink_pdu_slot_repository(unique_uplink_pdu_slot_repository&& other) noexcept
  {
    release();
    repository       = other.repository;
    other.repository = nullptr;
  }

  /// Move assignment operator.

  /// Move assignment operator.
  unique_uplink_pdu_slot_repository& operator=(unique_uplink_pdu_slot_repository&& other) noexcept
  {
    release();
    repository       = other.repository;
    other.repository = nullptr;
    return *this;
  }

  /// Returns \c true if the unique repository is valid, false otherwise.

  /// Returns \c true if the unique repository is valid, false otherwise.
  bool is_valid() const { return repository != nullptr; }

  /// Default destructor - notifies the end of processing PDUs.

  /// Default destructor - notifies the end of processing PDUs.
  ~unique_uplink_pdu_slot_repository() { release(); }

  /// \brief Releases the unique uplink PDU slot repository and obtain the resource grid.
  ///
  /// The unique PDU slot repository will stop being valid after this call and it will not accept for uplink PDU until a
  /// new slot is configured.
  ///
  /// \return A shared resource grid if the repository is valid, otherwise an invalid grid.

  /// \brief Releases the unique uplink PDU slot repository and obtain the resource grid.
  ///
  /// The unique PDU slot repository will stop being valid after this call and it will not accept for uplink PDU until a
  /// new slot is configured.
  ///
  /// \return A shared resource grid if the repository is valid, otherwise an invalid grid.
  shared_resource_grid release()
  {
    shared_resource_grid grid;

    // Notify the repository that no more PDU will be queued and obtain the resource grid for the configured slot.

    // Notify the repository that no more PDU will be queued and obtain the resource grid for the configured slot.
    if (is_valid()) {
      grid = repository->finish_adding_pdus();
    }

    // Invalidate pointer to the instance. It will no longer be valid.

    // Invalidate pointer to the instance. It will no longer be valid.
    repository = nullptr;


    return grid;
  }

  /// Gets the underlying uplink PDU slot repository.

  /// Gets the underlying uplink PDU slot repository.
  uplink_pdu_slot_repository& get()
  {
    ocudu_assert(is_valid(), "Invalid repository.");
    return *repository;
  }

  /// Gets the underlying uplink PDU slot repository.

  /// Gets the underlying uplink PDU slot repository.
  uplink_pdu_slot_repository* operator->()
  {
    ocudu_assert(is_valid(), "Invalid repository.");
    return repository;
  }


private:
  /// Reference to the underlying uplink repository. Set to \c nullptr for an invalid repository.
  /// Reference to the underlying uplink repository. Set to \c nullptr for an invalid repository.
  uplink_pdu_slot_repository_callback* repository = nullptr;
};

/// Uplink slot PDU repository pool.

/// Uplink slot PDU repository pool.
class uplink_pdu_slot_repository_pool
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~uplink_pdu_slot_repository_pool() = default;

  /// Gets the uplink slot PDU repository associated to a given slot.

  /// Gets the uplink slot PDU repository associated to a given slot.
  virtual unique_uplink_pdu_slot_repository get_pdu_slot_repository(slot_point slot) = 0;
};
} // namespace ocudu
