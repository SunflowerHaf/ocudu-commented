// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_pcap_factory.h
//
// Purpose (plain English):
//   Creates the PCAP capture files that the O-DU High writes to during a run.
//   PCAPs are packet-capture logs that can be opened in Wireshark to see the
//   actual bytes flowing over an interface, in order, with timestamps — an
//   invaluable debugging tool.
//
//   For the DU High we support five PCAPs:
//     * F1AP  — the control-plane messages between the DU and the CU-CP
//     * F1-U  — the user-plane packets (wrapped in GTP-U) between DU and CU-UP
//     * E2AP  — messages to/from the E2 RIC agent
//     * MAC   — every MAC PDU exchanged with the UE (over the air)
//     * RLC   — every RLC PDU (below MAC, above PDCP)
//
//   Each PCAP is optional: if disabled in the YAML config, a "null" PCAP
//   object is created that silently discards everything (so the rest of the
//   code doesn't need to null-check every write). Each active PCAP is also
//   attached to a signal_observer so that SIGINT / SIGTERM flushes the file
//   cleanly before the process exits — otherwise the last few records could
//   be lost in the buffer.
// =============================================================================

#pragma once


#include "apps/services/worker_manager/pcap_executor_mapper.h"
#include "o_du_high_unit_config.h"
#include "ocudu/pcap/dlt_pcap.h"
#include "ocudu/pcap/mac_pcap.h"
#include "ocudu/pcap/rlc_pcap.h"
#include "ocudu/support/signal_observer.h"


namespace ocudu {


/// \brief Holds all PCAP writers used by the flexible O-DU + their
///        signal-handlers that flush the files on shutdown.
///
/// Note the destructor order in reset(): signal handlers are dropped first
/// (so they can't fire on a half-destroyed PCAP), then the PCAP objects
/// themselves, which close and flush their output files.
struct flexible_o_du_pcaps {
  // DLT PCAPs
  // -------------------------------------------------------------------------
  // DLT PCAPs — "Data Link Types" for control-plane protocols. Wireshark
  // uses the DLT number in the capture header to know which dissector to use.
  // -------------------------------------------------------------------------
  std::unique_ptr<dlt_pcap> f1ap; ///< F1AP control-plane between DU and CU-CP.
  std::unique_ptr<dlt_pcap> f1u; ///< F1-U user-plane (GTP-U) between DU and CU-UP.
  std::unique_ptr<dlt_pcap> e2ap; ///< E2AP messages to/from the RIC.


  // Signal observers hook into the process's signal_dispatcher so that a
  // Ctrl-C causes each PCAP to flush its buffers before the process dies.
  std::unique_ptr<signal_observer> f1ap_sig_handler;
  std::unique_ptr<signal_observer> f1u_sig_handler;
  std::unique_ptr<signal_observer> e2ap_sig_handler;

  // MAC and RLC PCAPs

  // -------------------------------------------------------------------------
  // MAC and RLC PCAPs — these have their own writer types because they carry
  // more structured metadata (frame numbers, slots, HARQ IDs, RB IDs) that
  // the DLT format doesn't cover.
  // -------------------------------------------------------------------------
  std::unique_ptr<mac_pcap> mac;
  std::unique_ptr<rlc_pcap> rlc;


  std::unique_ptr<signal_observer> mac_sig_handler;
  std::unique_ptr<signal_observer> rlc_sig_handler;

  /// \brief Destroy (close and flush) the PCAPs.

  /// \brief Destroys (closes and flushes) all PCAPs in a safe order.
  ///
  /// Signal handlers are released first so they cannot fire on an already-
  /// destroyed PCAP; then the PCAP objects themselves are released, which
  /// closes their file handles and writes any buffered records to disk.
  void reset()
  {
    f1ap_sig_handler.reset();
    f1u_sig_handler.reset();
    e2ap_sig_handler.reset();
    mac_sig_handler.reset();
    rlc_sig_handler.reset();


    f1ap.reset();
    f1u.reset();
    e2ap.reset();
    mac.reset();
    rlc.reset();
  }
};

/// Creates the PCAPs of the O-RAN DU.

/// \brief Creates every PCAP writer needed by the O-DU High, honouring the
///        enable/disable and file-name settings from the YAML config.
///
/// If a PCAP is disabled, a "null" writer is substituted so the rest of the
/// code path can write unconditionally.
///
/// \param config          Parsed O-DU High config (contains the [pcap] block).
/// \param du_execs        Executor mapper — decides which thread each PCAP
///                        writer runs on (so writes don't stall the RT path).
/// \param signal_source   The process-wide signal dispatcher; each PCAP
///                        subscribes to it so SIGINT triggers a flush.
inline flexible_o_du_pcaps create_o_du_pcaps(const o_du_high_unit_config& config,
                                             du_pcap_executor_mapper&     du_execs,
                                             signal_dispatcher&           signal_source)
{
  flexible_o_du_pcaps pcaps;


  const auto& pcap_cfg = config.du_high_cfg.config.pcaps;

  // ---- F1AP PCAP (control plane) ------------------------------------------
  // If enabled → create a real writer bound to the F1AP executor.
  // If disabled → a null writer that discards records without opening a file.
  pcaps.f1ap           = pcap_cfg.f1ap.enabled ? create_f1ap_pcap(pcap_cfg.f1ap.filename, du_execs.get_f1ap_executor())
                                               : create_null_dlt_pcap();
  // Lambda captures `pcaps` by reference so that when SIGINT fires we call
  // flush() on whatever PCAP object is live at that moment.
  pcaps.f1ap_sig_handler = std::make_unique<signal_observer>(signal_source, [&pcaps]() { pcaps.f1ap->flush(); });


  // ---- F1-U PCAP (user plane / GTP-U tunnelled data) ----------------------
  pcaps.f1u             = pcap_cfg.f1u.enabled ? create_gtpu_pcap(pcap_cfg.f1u.filename, du_execs.get_f1u_executor())
                                               : create_null_dlt_pcap();
  pcaps.f1u_sig_handler = std::make_unique<signal_observer>(signal_source, [&pcaps]() { pcaps.f1u->flush(); });


  // ---- E2AP PCAP (RIC control) --------------------------------------------
  // Note the E2 PCAP toggle lives under e2_cfg, not the du_high pcaps block.
  pcaps.e2ap             = config.e2_cfg.pcaps.enabled
                               ? create_e2ap_pcap(config.e2_cfg.pcaps.filename, du_execs.get_e2ap_executor())
                               : create_null_dlt_pcap();
  pcaps.e2ap_sig_handler = std::make_unique<signal_observer>(signal_source, [&pcaps]() { pcaps.e2ap->flush(); });

  // ---- MAC PCAP -----------------------------------------------------------
  // MAC PCAPs come in two flavours:
  //   * "dlt" — a raw file readable by Wireshark's MAC-NR dissector directly.
  //   * "udp" — every MAC PDU is emitted as a UDP packet so it can be captured
  //             live on a network interface. Useful for remote debugging.
  // Any other string is a user error and aborts startup.
  if (pcap_cfg.mac.type != "dlt" && pcap_cfg.mac.type != "udp") {
    report_error("Invalid type for MAC PCAP. type={}\n", pcap_cfg.mac.type);
  }
  pcaps.mac             = pcap_cfg.mac.enabled
                              ? create_mac_pcap(pcap_cfg.mac.filename,
                                    pcap_cfg.mac.type == "dlt" ? mac_pcap_type::dlt : mac_pcap_type::udp,
                                    du_execs.get_mac_executor())
                              : create_null_mac_pcap();
  pcaps.mac_sig_handler = std::make_unique<signal_observer>(signal_source, [&pcaps]() { pcaps.mac->flush(); });


  // ---- RLC PCAP -----------------------------------------------------------
  // The rb_type option lets the user limit captures to just SRBs (signalling)
  // or just DRBs (data). "all" captures both. Anything else is a user error.
  if (pcap_cfg.rlc.rb_type != "all" && pcap_cfg.rlc.rb_type != "srb" && pcap_cfg.rlc.rb_type != "drb") {
    report_error("Invalid rb_type for RLC PCAP. rb_type={}\n", pcap_cfg.rlc.rb_type);
  }


  // The two boolean flags at the end of create_rlc_pcap() are
  //   (capture_srbs, capture_drbs).
  // They are derived from rb_type by asserting "not the excluded one".
  pcaps.rlc             = pcap_cfg.rlc.enabled ? create_rlc_pcap(pcap_cfg.rlc.filename,
                                                     du_execs.get_rlc_executor(),
                                                     pcap_cfg.rlc.rb_type != "drb", // capture SRBs?
                                                     pcap_cfg.rlc.rb_type != "srb") // capture DRBs?
                                               : create_null_rlc_pcap();
  pcaps.rlc_sig_handler = std::make_unique<signal_observer>(signal_source, [&pcaps]() { pcaps.rlc->flush(); });


  return pcaps;
}


} // namespace ocudu
