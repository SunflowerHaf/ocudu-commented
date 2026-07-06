// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/hal/phy/upper/channel_processors/pusch/hw_accelerator_factories.cpp  (57 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/hal
// Hardware Abstraction Layer (HAL) — DPDK and hardware PHY accelerator implementations. CONDITIONAL: only compiled when DPDK_FOUND=ON and a supported hardware accelerator (e.g. Intel ACC100/ACC200 via BBDEV) is present. In the standard USRP/UHD build this entire directory is excluded from compilation.
//
// Contents:
//   lib/hal/dpdk/         — DPDK EAL initialisation, mbuf pool management, BBDEV device open/config.
//   lib/hal/phy/upper/    — HW-accelerated PDSCH encoder (offloads LDPC encoding to the ACC100 FPGA) and PUSCH decoder (offloads LDPC decoding), plus external HARQ buffer context repository (stores soft bits in on-accelerator memory).
//
// When active, the HAL factories are passed into the upper PHY (lib/phy/) as hw_encoder_factory / hw_decoder_factory pointers; if nullptr, the software fallback LDPC implementations are used automatically.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/hal/phy/upper/channel_processors/pusch/hw_accelerator_factories.h"
#include "hw_accelerator_pusch_dec_acc100_impl.h"
#include "hw_accelerator_pusch_dec_impl.h"


using namespace ocudu;
using namespace hal;


namespace {


class hw_accelerator_pusch_dec_factory_bbdev : public hw_accelerator_pusch_dec_factory
{
  /// Accelerator type.
  /// Accelerator type.
  std::string acc_type;
  /// Interfacing to a bbdev-based hardware-accelerator.
  /// Interfacing to a bbdev-based hardware-accelerator.
  std::shared_ptr<ocudu::dpdk::bbdev_acc> bbdev_accelerator;
  /// Interfacing to an external HARQ buffer context repository.
  /// Interfacing to an external HARQ buffer context repository.
  std::shared_ptr<ext_harq_buffer_context_repository> harq_buffer_context;
  /// Forces using the host memory to implement the soft-buffer.
  /// Forces using the host memory to implement the soft-buffer.
  bool force_local_harq;
  /// Indicates if the accelerated function uses a dedicated hardware queue or needs to reserve one for each operation.
  /// Indicates if the accelerated function uses a dedicated hardware queue or needs to reserve one for each operation.
  bool dedicated_queue;


public:
  explicit hw_accelerator_pusch_dec_factory_bbdev(
      const bbdev_hwacc_pusch_dec_factory_configuration& accelerator_config) :
    acc_type(accelerator_config.acc_type),
    bbdev_accelerator(std::move(accelerator_config.bbdev_accelerator)),
    harq_buffer_context(accelerator_config.harq_buffer_context),
    force_local_harq(accelerator_config.force_local_harq),
    dedicated_queue(accelerator_config.dedicated_queue)
  {
  }


  std::unique_ptr<hw_accelerator_pusch_dec> create() override
  {
    if (acc_type == "acc100" || acc_type == "acc200" || acc_type == "vrb1") {
      return std::make_unique<hw_accelerator_pusch_dec_acc100_impl>(
          bbdev_accelerator, harq_buffer_context, force_local_harq, dedicated_queue);
    }
    // Handle other accelerator types here.
    // Handle other accelerator types here.
    report_error("[HAL] unsupported hardware-accelerator type {}, supported values are 'acc100', 'acc200' and 'vrb1'",
                 acc_type);
    return {};
  }
};


} // namespace


std::shared_ptr<hw_accelerator_pusch_dec_factory>
ocudu::hal::create_bbdev_pusch_dec_acc_factory(const bbdev_hwacc_pusch_dec_factory_configuration& accelerator_config)
{
  return std::make_unique<hw_accelerator_pusch_dec_factory_bbdev>(accelerator_config);
}
