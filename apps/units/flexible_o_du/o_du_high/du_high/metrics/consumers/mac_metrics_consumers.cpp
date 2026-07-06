// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/consumers/mac_metrics_consumers.cpp
//
// Purpose (plain English):
//   Formats MAC DL timing data as a compact log line per cell. The line
//   contains: PCI, slot range covered, slot duration, voluntary/involuntary
//   context-switch counts, then five latency measurements in microseconds:
//
//     wall_clock_latency    — end-to-end slot processing time.
//     sched_latency         — time spent in the scheduler.
//     dl_tti_req_latency    — time to push the DL TTI request to the radio.
//     tx_data_req_latency   — time to push TX data to the radio.
//     ul_tti_req_latency    — time to push the UL TTI request.
//     slot_ind_dequeue_lat  — time waiting in the slot-indication queue.
//     slot_ind_msg_time_diff — age of the slot-indication message when dequeued.
//
//   Each latency shows [avg=Xusec max=Yusec max_slot=N].
// =============================================================================

#include "mac_metrics_consumers.h"
#include "ocudu/support/format/custom_formattable.h"
#include "ocudu/support/format/fmt_to_c_str.h"


using namespace ocudu;


// Helper: writes one latency entry as "[avg=Xusec max=Yusec max_slot=N]".
static void write_latency_information(fmt::memory_buffer&                              buffer,
                                      const mac_dl_cell_metric_report::latency_report& report,
                                      std::string_view                                 name,
                                      bool                                             add_space = true)
{
  fmt::format_to(std::back_inserter(buffer),
                 "{}=[avg={}usec max={}usec max_slot={}]",
                 name,
                 std::round(report.average.count() * 1e-3), // ns → µs
                 std::round(report.max.count() * 1e-3),
                 report.max_slot);


  if (add_space) {
    fmt::format_to(std::back_inserter(buffer), " ");
  }
}


void mac_metrics_consumer_log::handle_metric(const mac_dl_metric_report& report)
{
  fmt::memory_buffer buffer;


  for (unsigned i = 0, e = report.cells.size(); i != e; ++i) {
    const mac_dl_cell_metric_report& cell = report.cells[i];


    // Header line: PCI, slot range, slot count, slot duration, context switches.
    fmt::format_to(
        std::back_inserter(buffer),
        "MAC cell pci={} metrics: slots=[{}, {}{}) nof_slots={} slot_duration={}usec nof_voluntary_context_switches={} "
        "nof_involuntary_context_switches={} ",
        static_cast<unsigned>(cell.pci),
        cell.start_slot,
        cell.start_slot + cell.nof_slots,
        // Also print the number of HFN wrap-arounds. Useful for long report periods.
        // If the SFN (System Frame Number) wrapped during this period, note
        // how many times it did so. This makes long log captures easier to read.
        make_formattable([x = cell.start_slot, n = cell.nof_slots](auto& out) {
          auto nof_wrap_arounds = (x.count() + n) / x.nof_slots_per_hyper_system_frame();
          if (nof_wrap_arounds > 0) {
            return fmt::format_to(out.out(), "(+{} HFNs)", nof_wrap_arounds);
          }
          return out.out();
        }),
        cell.nof_slots,
        std::chrono::duration_cast<std::chrono::microseconds>(cell.slot_duration).count(),
        cell.count_voluntary_context_switches,
        cell.count_involuntary_context_switches);


    // Latency breakdown.
    write_latency_information(buffer, cell.wall_clock_latency, "wall_clock_latency");
    write_latency_information(buffer, cell.sched_latency, "sched_latency");
    write_latency_information(buffer, cell.dl_tti_req_latency, "dl_tti_req_latency");
    write_latency_information(buffer, cell.tx_data_req_latency, "tx_data_req_latency");
    write_latency_information(buffer, cell.ul_tti_req_latency, "ul_tti_req_latency");
    write_latency_information(buffer, cell.slot_ind_dequeue_latency, "slot_ind_dequeue_latency");
    write_latency_information(buffer, cell.slot_ind_msg_time_diff, "slot_ind_msg_time_diff", false);


    log_chan("{}", to_c_str(buffer));
    buffer.clear();
  }
}
