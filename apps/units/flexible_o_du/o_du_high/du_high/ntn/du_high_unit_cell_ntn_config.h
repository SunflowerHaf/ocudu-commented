// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: ntn/du_high_unit_cell_ntn_config.h
//
// Purpose (plain English):
//   Configuration struct for Non-Terrestrial Network (NTN) cell parameters.
//   NTN is the 3GPP Release 17+ feature that lets a gNB communicate with UEs
//   through a satellite (LEO/MEO/GEO). The key challenge is enormous
//   propagation delay (hundreds of milliseconds for LEO, ~270 ms for GEO)
//   and fast-changing Doppler shifts as the satellite moves across the sky.
//
//   The fields in this struct let the gNB:
//     * Advertise satellite position and velocity to UEs so they can
//       pre-compensate Doppler themselves (ephemeris_info).
//     * Tell UEs when the current satellite will stop serving the area
//       (t_service, distance_threshold, moving_ref_location).
//     * Provide timing-advance information to pre-compensate for the
//       propagation delay (cell_specific_koffset, k_mac, ta_info).
//     * Supply the K-offset that shifts all NR timing relationships to
//       account for one-way propagation delay.
//
//   Most of these are published in SIB19 (the NTN-specific System Information
//   Block) and in dedicated NTN reconfiguration messages.
// =============================================================================

#pragma once


#include "ocudu/ntn/orbit_propagator_type.h"
#include "ocudu/ran/ntn.h"
#include <chrono>
#include <optional>
#include <variant>
#include <vector>


namespace ocudu {


/// Per-cell NTN configuration.
struct du_high_unit_cell_ntn_config {
  /// Reference location of the serving cell in geodetic coordinates format (in degrees).
  /// Geodetic location (lat/lon/alt) of the cell's reference point on Earth.
  /// Used to compute coverage geometry and UE distance checks.
  std::optional<geodetic_coordinates_t> reference_location;
  /// Distance from the serving cell reference location, as defined in TS 38.304. Each step represents 50m.

  /// Maximum distance from reference_location a UE may be before the cell
  /// considers it out of coverage. Each step is 50 m (TS 38.304).
  std::optional<unsigned> distance_threshold;
  /// Indicates the time information on when a cell provided via NTN is going to stop serving the area it is currently
  /// covering. UTC timepoint.

  /// UTC time at which this satellite cell will stop serving the current area.
  /// Broadcast in SIB19 so UEs can prepare to reselect in time.
  std::optional<std::chrono::system_clock::time_point> t_service;
  /// NTN-config values
  /// Indicate the epoch time for the NTN assistance information passed in the config file. UTC timepoint.

  /// UTC epoch timestamp for the NTN assistance information below. UEs use
  /// this to know how stale the ephemeris data is.
  std::optional<std::chrono::system_clock::time_point> epoch_timestamp;
  /// Optional offset (in SFN) between the SIB19 transmission slot and the epoch time (EpochTime IE) of the NTN
  /// assistance info. Allows sending NTN assistance information that will become valid epoch_sfn_offset number of
  /// system frames after SIB19 Tx slot.

  /// Optional SFN offset between the SIB19 transmission slot and epoch_time.
  /// Non-zero if you want to pre-announce assistance info before it becomes valid.
  std::optional<uint64_t> epoch_sfn_offset;
  /// If provided it will be used to fill the EpochTime section in SIB19.

  /// If set, overrides the epoch_time field in SIB19 directly with a
  /// pre-computed EpochTime IE value.
  std::optional<epoch_time_t> epoch_time;
  /// Scheduling offset used for timing relationships modified for NTN operation (see TS 38.213 and TS 38.300,
  /// Section 16.14.2). The unit is milliseconds.
  ///
  /// \note In the specifications, the K_offset field is expressed as a number of slots assuming a subcarrier spacing of
  /// 15 kHz (i.e., 1 slot = 1 ms). To avoid ambiguity with other subcarrier spacings, this parameter is represented in
  /// the implementation as std::chrono::milliseconds.

  /// K-offset in milliseconds: the scheduling offset that shifts all NR
  /// timing relationships (HARQ timing, PDSCH-to-HARQ, PUSCH preparation)
  /// to compensate for the one-way propagation delay. Expressed in ms
  /// because 1 slot = 1 ms at 15 kHz SCS.
  std::chrono::milliseconds cell_specific_koffset;
  /// Scheduling offset provided by network if downlink and uplink frame timing are not aligned at gNB.

  /// k_MAC: additional scheduling offset if DL and UL frame timing are not
  /// aligned at the gNB (uncommon in practice).
  std::optional<unsigned> k_mac;
  /// A validity duration configured by the network for assistance information which indicates the maximum time duration
  /// (from epochTime) during which the UE can apply assistance information without having acquired new assistance
  /// information. Values {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 120, 180, 240, 900} seconds.

  /// How long (in seconds) the UE may use the current NTN assistance info
  /// without acquiring a refresh. Legal values: 5, 10, 15, 20, 25, 30, 35,
  /// 40, 45, 50, 55, 60, 120, 180, 240, 900 seconds.
  std::optional<unsigned> ntn_ul_sync_validity_dur;
  /// Whether to broadcast Ephemeris information as ECEF state vectors (if true) or ECI Orbital parameters (if false).
  /// If not provided, the value is derived from the variant of ephemeris_info.
  /// If provided and does not match the variant of ephemeris_info, the ephemeris_info is converted accordingly.

  /// If true, broadcast ephemeris as ECEF (Earth-Centred Earth-Fixed) state
  /// vectors (position + velocity). If false, use ECI orbital parameters.
  /// If absent, derived from which variant of ephemeris_info is set.
  std::optional<bool> use_state_vector;
  /// This field provides satellite ephemeris either in format of position and velocity state vector or in format of
  /// orbital parameters.

  /// The satellite's current position/velocity, in one of two formats:
  ///   * ecef_coordinates_t — position (x,y,z in metres) + velocity (vx,vy,vz in m/s).
  ///   * orbital_coordinates_t — Keplerian elements (semi-major axis, eccentricity,
  ///     inclination, RAAN, argument of perigee, true anomaly).
  std::variant<ecef_coordinates_t, orbital_coordinates_t> ephemeris_info;
  /// Network-controlled common timing advanced value, and it may include any timing offset considered necessary by the
  /// network.

  /// Network-controlled timing advance plus any additional timing offset.
  std::optional<ta_info_t> ta_info;
  /// Parameters of the feeder link used to compute the Doppler shifts.

  /// Feeder-link parameters (frequency, position of the gateway) used to
  /// compute the satellite-gateway Doppler contribution, so it can be removed
  /// from the UE's Doppler estimate.
  std::optional<feeder_link_info_t> feeder_link_info;
  /// Geodetic coordinates (in degrees) of the NTN Gateway location.

  /// Geodetic location of the NTN gateway (the ground station that connects
  /// the satellite to the core network). Used for Doppler calculations.
  std::optional<geodetic_coordinates_t> ntn_gateway_location;
  /// Indicates polarization information for downlink/uplink transmission on service link.

  /// Polarization information for DL/UL service-link transmissions.
  std::optional<ntn_polarization_t> polarization;
  /// When this field is included in SIB19, it indicates reporting of timing advanced is enabled.

  /// If set, the gNB instructs UEs to report their timing advance (enables
  /// the gNB to compute individual UE propagation delays).
  std::optional<bool> ta_report;
  /// Moving reference location for NTN Earth-moving cell (R18).

  /// Moving reference location for Earth-moving cells (Release 18):
  /// a reference point that tracks the satellite footprint as it moves.
  std::optional<geodetic_coordinates_t> moving_ref_location;
  /// Satellite switch with resynchronization parameters (R18).

  /// Parameters for satellite handover with UE resynchronisation (Release 18).
  std::optional<sat_switch_with_resync_t> sat_switch_with_resync;
  /// List of NTN neighbor cells.

  /// List of neighbouring NTN cells (for inter-satellite reselection).
  std::vector<neighbor_ntn_cell> ncells;
  /// Orbit propagator to use for ephemeris propagation. Allowed values: "rk4", "keplerian".

  /// Which orbit propagator to use when computing future satellite positions
  /// from the ephemeris. "rk4" = 4th-order Runge-Kutta (more accurate);
  /// "keplerian" = two-body Keplerian (faster, less accurate for LEO).
  ocudu_ntn::orbit_propagator_type propagator_type = ocudu_ntn::orbit_propagator_type::rk4;
};


} // namespace ocudu
