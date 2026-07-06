// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/pcap/dlt_pcap.h  (56 lines)
//
// INTERFACE HEADER — include/ocudu/pcap
// PCAP writer interfaces: dlt_pcap (generic DLT packet capture — used for control-plane protocols), mac_pcap (MAC-layer capture with slot/HARQ metadata), rlc_pcap (RLC-layer capture with RB metadata), and the null PCAP factories (create_null_dlt_pcap() etc.) that discard all records when a PCAP is disabled.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/adt/span.h"
#include <cstdint>


namespace ocudu {


class task_executor;

/// \brief Interface class for writing a DLT PCAP to a file.

/// \brief Interface class for writing a DLT PCAP to a file.
class dlt_pcap
{
public:
  virtual ~dlt_pcap() = default;

  /// Flush all the pending writes to the PCAP file.

  /// Flush all the pending writes to the PCAP file.
  virtual void flush() = 0;

  /// Close the PCAP file.

  /// Close the PCAP file.
  virtual void close() = 0;

  /// Whether writing to the PCAP file is enabled.

  /// Whether writing to the PCAP file is enabled.
  virtual bool is_write_enabled() const = 0;

  /// Push a PDU to be written to the PCAP file.

  /// Push a PDU to be written to the PCAP file.
  virtual void push_pdu(const_span<uint8_t> pdu) = 0;

  /// Push a PDU to be written to the PCAP file.

  /// Push a PDU to be written to the PCAP file.
  virtual void push_pdu(byte_buffer pdu) = 0;
};

/// \brief Creates a layer DLT PCAP sink that writes the incoming PDUs to a pcap file.

/// \brief Creates a layer DLT PCAP sink that writes the incoming PDUs to a pcap file.
std::unique_ptr<dlt_pcap> create_null_dlt_pcap();
std::unique_ptr<dlt_pcap> create_ngap_pcap(const std::string& filename, task_executor& backend_exec);
std::unique_ptr<dlt_pcap> create_xnap_pcap(const std::string& filename, task_executor& backend_exec);
std::unique_ptr<dlt_pcap> create_f1ap_pcap(const std::string& filename, task_executor& backend_exec);
std::unique_ptr<dlt_pcap> create_e1ap_pcap(const std::string& filename, task_executor& backend_exec);
std::unique_ptr<dlt_pcap> create_gtpu_pcap(const std::string& filename, task_executor& backend_exec);
std::unique_ptr<dlt_pcap> create_e2ap_pcap(const std::string& filename, task_executor& backend_exec);

/// Null sink for DLT pcap messages. This is useful in unit tests and when the application disables pcaps.

/// Null sink for DLT pcap messages. This is useful in unit tests and when the application disables pcaps.
class null_dlt_pcap : public dlt_pcap
{
public:
  void flush() override {}
  void close() override {}
  bool is_write_enabled() const override { return false; }
  void push_pdu(const_span<uint8_t> pdu) override {}
  void push_pdu(byte_buffer pdu) override {}
};


} // namespace ocudu
