// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2sm/e2sm_manager.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/e2sm/e2sm.h"
#include <map>


namespace ocudu {


class e2sm_manager
{
public:
  e2sm_manager(ocudulog::basic_logger& logger_);
  /// \brief Adds an e2sm service to the list of services that can be used to unpack e2sm messages.
  /// \param[in] oid The oid of the e2sm service.
  /// \param[in] e2sm_packer The interface that will be used to unpack the e2sm messages for this service
  /// \brief Adds an e2sm service to the list of services that can be used to unpack e2sm messages.
  /// \param[in] oid The oid of the e2sm service.
  /// \param[in] e2sm_packer The interface that will be used to unpack the e2sm messages for this service
  void add_e2sm_service(std::string oid, std::unique_ptr<e2sm_interface> e2sm_iface);

  /// \brief Gets the e2sm service interface associated with the given oid.
  /// \param[in] oid The oid of the e2sm service.
  /// \return The e2sm service interface associated with the given oid.

  /// \brief Gets the e2sm service interface associated with the given oid.
  /// \param[in] oid The oid of the e2sm service.
  /// \return The e2sm service interface associated with the given oid.
  e2sm_interface* get_e2sm_interface(std::string oid);

  /// \brief  Gets the e2sm service interface associated with the given ran function id.
  /// \param[in] ran_function_id  The ran function id of the e2sm service.
  /// @return  The e2sm service interface associated with the given ran function id.

  /// \brief  Gets the e2sm service interface associated with the given ran function id.
  /// \param[in] ran_function_id  The ran function id of the e2sm service.
  /// @return  The e2sm service interface associated with the given ran function id.
  e2sm_interface* get_e2sm_interface(uint16_t ran_function_id);

  /// \brief Adds a supported ran function to the list of supported ran functions.
  /// \param[in] ran_function_id The ran function id of the supported ran function.
  /// \param[in] oid The oid of the e2sm service that can be used to unpack the e2sm messages for this ran function.

  /// \brief Adds a supported ran function to the list of supported ran functions.
  /// \param[in] ran_function_id The ran function id of the supported ran function.
  /// \param[in] oid The oid of the e2sm service that can be used to unpack the e2sm messages for this ran function.
  void add_supported_ran_function(uint16_t ran_function_id, std::string oid);


private:
  std::map<std::string, std::unique_ptr<e2sm_interface>> e2sm_iface_list;
  std::map<uint16_t, std::string>                        supported_ran_functions;
  ocudulog::basic_logger&                                logger;
};
} // namespace ocudu
