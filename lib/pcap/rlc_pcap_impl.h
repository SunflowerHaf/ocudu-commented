// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/pcap/rlc_pcap_impl.h  (40 lines)
//
// LIBRARY: lib/pcap
// Creates and writes PCAP capture files for every protocol interface: NGAP, F1AP, E1AP, XNAP, E2AP, MAC, RLC, GTP-U (F1-U, N3). Each function returns a unique_ptr to a dlt_pcap or specialised pcap writer. Null PCAP objects (silently discard) are returned when the interface is disabled.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "backend_pcap_writer.h"
#include "ocudu/adt/byte_buffer.h"
#include "ocudu/pcap/rlc_pcap.h"


namespace ocudu {


class rlc_pcap_impl final : public rlc_pcap
{
public:
  rlc_pcap_impl(const std::string& filename, bool capture_srb, bool capture_drb, task_executor& backend_exec);


  ~rlc_pcap_impl() override;


  rlc_pcap_impl(const rlc_pcap_impl& other)            = delete;
  rlc_pcap_impl& operator=(const rlc_pcap_impl& other) = delete;
  rlc_pcap_impl(rlc_pcap_impl&& other)                 = delete;
  rlc_pcap_impl& operator=(rlc_pcap_impl&& other)      = delete;


  void flush() override;


  void close() override;


  bool is_write_enabled() const override { return writer.is_write_enabled(); }


  void push_pdu(const pcap_rlc_pdu_context& context, const span<uint8_t> pdu) override;


  void push_pdu(const pcap_rlc_pdu_context& context, const byte_buffer_slice& pdu) override;


private:
  ocudulog::basic_logger& logger;
  bool                    srb_enabled = true;
  bool                    drb_enabled = true;
  backend_pcap_writer     writer;
};
} // namespace ocudu
