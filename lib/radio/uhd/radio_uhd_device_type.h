// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_device_type.h
 * @brief Identifies which model family of USRP hardware is connected.
 *
 * USRP devices come in several model families, each with different
 * capabilities and default parameters (master clock rate, USB/network
 * interface, channel count). This class detects the device family by
 * inspecting the "type" string UHD reports for the connected hardware
 * (e.g. UHD reports "b200" for a B210, "x300" for an X310, etc.) and
 * exposes it as a simple enum the rest of the UHD driver code can switch on.
 *
 * This matters because several parts of the driver (radio_uhd_device.h)
 * apply model-specific defaults — for example, B2xx devices use automatic
 * master clock rate selection, while X3x0/X410/N3x0/N32x devices use a
 * fixed default master clock rate and larger network frame sizes.
 */

#pragma once


#include <string>


namespace ocudu {


/**
 * @brief Identifies the connected USRP device's model family.
 */
class radio_uhd_device_type
{
public:
  /**
   * @brief The supported USRP model families.
   */
  enum class types {
    /// The device is not registered.
    /// The device type could not be determined from the mboard name.
    UNKNOWN = 0,
    /// B2xx series models: B200mini, B200mini-i, B205mini-i, B210 and B200.
    /// B2xx series models: B200mini, B200mini-i, B205mini-i, B210 and B200.
    /// USB-connected, lower cost, suitable for lab/development use.
    B2xx,
    /// USRP Embedded series: E320, E312, E310 and E313.
    /// USRP Embedded series: E320, E312, E310 and E313.
    /// Standalone embedded devices with onboard ARM processor.
    E3xx,
    /// N3x0 series models: N300 and N310.
    /// N3x0 series models: N300 and N310.
    /// Network-connected (10GbE), higher performance.
    N3x0,
    /// N32x series models: N320 and N321.
    /// N32x series models: N320 and N321.
    /// Network-connected, newer generation than N3x0.
    N32x,
    /// X3x0 series models: X300 and X310.
    /// X3x0 series models: X300 and X310.
    /// High-performance network-connected USRPs.
    X3x0,
    /// X410 model.
    /// X410 model.
    /// Latest generation high-performance network-connected USRP.
    X410
  };


  /// Default constructor: type is UNKNOWN until set.
  radio_uhd_device_type() = default;

  /**
   * @param type_  Directly sets the device type (used internally).
   */
  radio_uhd_device_type(types type_) : type(type_) {}

  /**
   * @brief Determines the device type from the motherboard name string UHD reports.
   *
   * Uses simple substring matching on the uppercased motherboard name. This is
   * a heuristic — it works because Ettus model names consistently embed their
   * series prefix in the motherboard identifier string (e.g. "B210", "X310",
   * "N321"). Note: the order of checks matters, since "N32" is checked before
   * the more general "N3" to correctly distinguish N32x from N3x0.
   *
   * @param mboard_name  The motherboard name string as reported by UHD
   *                     (e.g. from the device's "type" address key).
   */
  radio_uhd_device_type(std::string mboard_name)
  {
    for (char& c : mboard_name) {
      c = std::toupper(c);
    }


    if (mboard_name.find("B2") != std::string::npos) {
      type = types::B2xx;
    } else if (mboard_name.find("X3") != std::string::npos) {
      type = types::X3x0;
    } else if (mboard_name.find("X4") != std::string::npos) {
      type = types::X410;
    } else if (mboard_name.find("N32") != std::string::npos) {
      // Must be checked before "N3" to correctly distinguish N32x from N3x0.
      type = types::N32x;
    } else if (mboard_name.find("N3") != std::string::npos) {
      type = types::N3x0;
    } else {
      type = types::UNKNOWN;
    }
  }


  /**
   * @brief Returns a human-readable identifier string for this device type.
   *
   * Used in logging and for naming purposes elsewhere in the codebase.
   *
   * @return A static string identifying the device family.
   */
  const char* to_string() const
  {
    switch (type) {
      case types::B2xx:
        return "uhd_b200";
      case types::E3xx:
        return "uhd_e3x0";
      case types::N3x0:
        return "uhd_n300";
      case types::N32x:
        return "uhd_n320";
      case types::X3x0:
        return "uhd_x300";
      case types::X410:
        return "uhd_x400";
      case types::UNKNOWN:
      default:
        return "uhd_unknown";
    }
  }


  /// Compares two radio_uhd_device_type objects for equality.
  bool operator==(const radio_uhd_device_type& other) const { return type == other.type; }

  /// Compares this device type against a raw types enum value.
  bool operator==(const types& other) const { return type == other; }


  /// Implicit conversion to the underlying types enum, allowing direct use in switch statements.
  operator types() const { return type; }


private:
  /// The detected (or explicitly set) device family.
  types type = types::UNKNOWN;
};


} // namespace ocudu
