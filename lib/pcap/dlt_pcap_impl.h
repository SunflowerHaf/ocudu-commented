// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/pcap/dlt_pcap_impl.h  (43 lines)
//
// LIBRARY: lib/pcap
// Creates and writes PCAP capture files for every protocol interface: NGAP, F1AP, E1AP, XNAP, E2AP, MAC, RLC, GTP-U (F1-U, N3). Each function returns a unique_ptr to a dlt_pcap or specialised pcap writer. Null PCAP objects (silently discard) are returned when the interface is disabled.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "backend_pcap_writer.h"
#include "ocudu/adt/byte_buffer.h"
#include "ocudu/pcap/dlt_pcap.h"


namespace ocudu {


class dlt_pcap_impl final : public dlt_pcap
{
public:
  dlt_pcap_impl(unsigned           dlt_,
                const std::string& layer_name_,
                const std::string& filename,
                const std::string& dissector,
                task_executor&     backend_exec_);


  ~dlt_pcap_impl() override;


  dlt_pcap_impl(const dlt_pcap_impl& other)            = delete;
  dlt_pcap_impl& operator=(const dlt_pcap_impl& other) = delete;
  dlt_pcap_impl(dlt_pcap_impl&& other)                 = delete;
  dlt_pcap_impl& operator=(dlt_pcap_impl&& other)      = delete;


  void flush() override;


  void close() override;


  bool is_write_enabled() const override { return writer.is_write_enabled(); }


  void push_pdu(byte_buffer pdu) override;


  void push_pdu(const_span<uint8_t> pdu) override;


private:
  ocudulog::basic_logger& logger;
  backend_pcap_writer     writer;
};


} // namespace ocudu
