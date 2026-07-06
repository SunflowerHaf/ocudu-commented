// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_up/o_cu_up_impl.cpp  (30 lines)
//
// LIBRARY: lib/cu_up
// O-RAN Central Unit User Plane core: the PDCP layer (ciphering, integrity, header compression), SDAP (QoS flow to DRB mapping), F1-U endpoint management, N3 GTP-U endpoint, and the O-CU-UP factory. One CU-UP instance handles all UEs' user-plane data.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "o_cu_up_impl.h"


using namespace ocudu;
using namespace ocuup;


void o_cu_up_impl::start()
{
  cu_up->start();
}


void o_cu_up_impl::stop()
{
  cu_up->stop();
}


void o_cu_up_with_e2_impl::start()
{
  o_cu_up_impl::start();
  e2agent->start();
}


void o_cu_up_with_e2_impl::stop()
{
  e2agent->stop();
  o_cu_up_impl::stop();
}
