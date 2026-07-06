// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// FILE: helpers/f1u/f1u_config_yaml_writer.h
// Declares fill_f1u_config_yaml_schema() for the print-effective-config feature.
#pragma once

#include <yaml-cpp/yaml.h>

namespace ocudu {

struct f1u_sockets_appconfig;

/// Fills the F1-U configuration in the given YAML node.
void fill_f1u_config_yaml_schema(YAML::Node& node, const f1u_sockets_appconfig& config);

} // namespace ocudu
