// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_yaml_writer.h
 * @brief Declaration for the function that serialises gNB config back to YAML format.
 *
 * While gnb_appconfig_cli11_schema.cpp handles reading YAML into the config struct,
 * this file provides the reverse: writing the current config struct back out as YAML.
 *
 * This is used in two situations:
 *   1. Debug logging — when log level is DEBUG, main() dumps the entire effective
 *      configuration (including all default values) to the log so the user can see
 *      exactly what settings are in use.
 *   2. Config introspection — tooling can call this to serialise the running config.
 */

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct gnb_appconfig;

/// Fills the given node with the gNB application configuration values.

/**
 * @brief Serialises the gNB application configuration into a YAML node.
 *
 * Populates the provided YAML::Node with all fields from gnb_appconfig,
 * including nested sub-configs (logging, metrics, threading, etc.).
 * The caller is responsible for doing something with the node afterwards
 * (e.g. calling YAML::Dump() to convert it to a string for logging).
 *
 * @param node    The YAML node to populate. Existing contents are merged/overwritten.
 * @param config  The gNB configuration to serialise.
 */
void fill_gnb_appconfig_in_yaml_schema(YAML::Node& node, const gnb_appconfig& config);


} // namespace ocudu
