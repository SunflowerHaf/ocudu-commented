// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_hal_factory.cpp
//
// Purpose (plain English):
//   Builds the hardware-accelerator dependencies for the DU-Low, if any are
//   configured. In your UHD/USRP build path (no DPDK), the entire DPDK-guarded
//   block below compiles out — make_du_low_hal_dependencies() then returns
//   an all-nullptr struct, and the upper PHY falls back to its pure-software
//   LDPC encoder/decoder.
//
//   When DPDK IS present:
//     * init_bbdev_hwacc() opens the Intel BBDEV card (via DPDK), configures
//       the number of encoder/decoder cores, mbuf sizes, etc.
//     * make_du_low_hal_dependencies() creates a PDSCH encoder factory
//       (if hardware PDSCH is enabled) and a PUSCH decoder factory
//       (if hardware PUSCH is enabled), along with an external HARQ buffer
//       context repository for the decoder.
// =============================================================================

#include "du_low_hal_factory.h"
#include "ocudu/ran/sch/sch_constants.h"
#ifdef DPDK_FOUND
#include "ocudu/hal/dpdk/bbdev/bbdev_acc_factory.h"
#include "ocudu/hal/phy/upper/channel_processors/hw_accelerator_factories.h"
#include "ocudu/hal/phy/upper/channel_processors/pusch/ext_harq_buffer_context_repository_factory.h"
#include "ocudu/hal/phy/upper/channel_processors/pusch/hw_accelerator_factories.h"
#include "ocudu/ocudulog/ocudulog.h"
#endif // DPDK_FOUND


using namespace ocudu;


#ifdef DPDK_FOUND
// -----------------------------------------------------------------------------
// init_bbdev_hwacc()
//   Opens the DPDK BBDEV accelerator and returns a shared handle.
//   Populates the BBDEV config from the user-facing bbdev_appconfig struct,
//   using sensible worst-case defaults if the user didn't specify sizes.
// -----------------------------------------------------------------------------
static std::shared_ptr<dpdk::bbdev_acc> init_bbdev_hwacc(const bbdev_appconfig&  bbdev_app_cfg,
                                                         ocudulog::basic_logger& logger)
{
  // Intefacing to the bbdev-based hardware-accelerator.
  dpdk::bbdev_acc_configuration bbdev_config;
  bbdev_config.id = bbdev_app_cfg.id;

  // Tell BBDEV how many LDPC encoder cores to reserve, if PDSCH accel is on.
  if (bbdev_app_cfg.pdsch_enc && bbdev_app_cfg.pdsch_enc->nof_hwacc > 0) {
    bbdev_config.nof_ldpc_enc_lcores = bbdev_app_cfg.pdsch_enc->nof_hwacc;
  }
  // Same for LDPC decoder cores if PUSCH accel is on.
  if (bbdev_app_cfg.pusch_dec && bbdev_app_cfg.pusch_dec->nof_hwacc > 0) {
    bbdev_config.nof_ldpc_dec_lcores = bbdev_app_cfg.pusch_dec->nof_hwacc;
  }
  // If no msg_mbuf size is defined, a worst-case value will be used.

  // mbuf sizing — worst-case defaults keep things simple if unset.
  bbdev_config.msg_mbuf_size = bbdev_app_cfg.msg_mbuf_size.value_or(RTE_BBDEV_LDPC_E_MAX_MBUF);
  // If no rm_mbuf size is defined, a worst-case value will be used.
  bbdev_config.rm_mbuf_size = bbdev_app_cfg.rm_mbuf_size.value_or(RTE_BBDEV_LDPC_E_MAX_MBUF);
  // If no number of mbufs is defined, a worst-case value will be used.
  // Number of mbufs = next power of 2 above the max supported CB count.
  bbdev_config.nof_mbuf = bbdev_app_cfg.nof_mbuf.value_or(static_cast<unsigned>(pow2(log2_ceil(MAX_NOF_SEGMENTS))));

  std::shared_ptr<dpdk::bbdev_acc> bbdev_acc = create_bbdev_acc(bbdev_config, logger);
  report_error_if_not(bbdev_acc, "Unable to open the {} hardware-accelerator.", bbdev_app_cfg.hwacc_type);


  return bbdev_acc;
}
#endif // DPDK_FOUND


// -----------------------------------------------------------------------------
// make_du_low_hal_dependencies()
//   Public entry point. In non-DPDK builds returns an empty struct. In DPDK
//   builds, opens the BBDEV card and constructs the PDSCH-enc / PUSCH-dec
//   HW-accel factories that the upper PHY will call to offload channel
//   coding to the accelerator.
// -----------------------------------------------------------------------------
o_du_low_hal_dependencies ocudu::make_du_low_hal_dependencies(const std::optional<du_low_unit_hal_config>& hal_config)
{
  o_du_low_hal_dependencies hal_dependencies;

  // Initialize hardware-accelerator (only once and if needed).

#ifdef DPDK_FOUND
  if (hal_config && hal_config->bbdev_hwacc && !hal_config->bbdev_hwacc->hwacc_type.empty()) {
    const bbdev_appconfig&  bbdev_app_cfg = hal_config->bbdev_hwacc.value();
    ocudulog::basic_logger& hwacc_logger  = ocudulog::fetch_basic_logger("HWACC");

    // Open the accelerator card exactly once.
    auto                    accelerator   = init_bbdev_hwacc(bbdev_app_cfg, hwacc_logger);

    // Create a hardware-accelerated PDSCH encoder factory (only if needed).

    // ---- PDSCH encoder factory -------------------------------------------
    if (bbdev_app_cfg.pdsch_enc && bbdev_app_cfg.pdsch_enc->nof_hwacc > 0) {
      hal::bbdev_hwacc_pdsch_enc_factory_configuration hwacc_pdsch_enc_cfg;
      hwacc_pdsch_enc_cfg.acc_type          = bbdev_app_cfg.hwacc_type;
      hwacc_pdsch_enc_cfg.bbdev_accelerator = accelerator;
      hwacc_pdsch_enc_cfg.cb_mode           = bbdev_app_cfg.pdsch_enc->cb_mode;
      // If no maximum buffer size is defined, a worst-case value will be used.
      // Worst-case TB size if not specified.
      hwacc_pdsch_enc_cfg.max_tb_size = bbdev_app_cfg.pdsch_enc->max_buffer_size.value_or(RTE_BBDEV_LDPC_E_MAX_MBUF);
      hwacc_pdsch_enc_cfg.dedicated_queue = bbdev_app_cfg.pdsch_enc->dedicated_queue;
      hal_dependencies.hw_encoder_factory = hal::create_bbdev_pdsch_enc_acc_factory(hwacc_pdsch_enc_cfg);
    }

    // // Create a hardware-accelerated PUSCH decoder factory (only if needed).

    // ---- PUSCH decoder factory + external HARQ buffer context -----------
    if (bbdev_app_cfg.pusch_dec && bbdev_app_cfg.pusch_dec->nof_hwacc > 0) {
      hal::bbdev_hwacc_pusch_dec_factory_configuration         hwacc_pusch_dec_cfg;
      std::shared_ptr<hal::ext_harq_buffer_context_repository> harq_buffer_context = nullptr;
      hwacc_pusch_dec_cfg.acc_type                                                 = bbdev_app_cfg.hwacc_type;
      hwacc_pusch_dec_cfg.bbdev_accelerator                                        = accelerator;
      // Ask the accelerator how much HARQ buffer memory it has on-board.
      uint64_t ext_harq_buff_size          = hwacc_pusch_dec_cfg.bbdev_accelerator->get_harq_buff_size_bytes();
      hwacc_pusch_dec_cfg.force_local_harq = bbdev_app_cfg.pusch_dec->force_local_harq;
      // Set up an external HARQ buffer context repository.

      // External HARQ buffer context = per-CB metadata (offset, length, state).
      // Held either on the accelerator or (if force_local_harq) in host RAM.
      unsigned nof_cbs    = bbdev_app_cfg.pusch_dec->harq_context_size.value_or(MAX_NOF_SEGMENTS);
      harq_buffer_context = hal::create_ext_harq_buffer_context_repository(nof_cbs, ext_harq_buff_size, false);
      report_error_if_not(harq_buffer_context,
                          "Unable to create the external HARQ buffer context for the {} hardware-accelerator.",
                          bbdev_app_cfg.hwacc_type);
      hwacc_pusch_dec_cfg.harq_buffer_context = harq_buffer_context;
      hwacc_pusch_dec_cfg.dedicated_queue     = bbdev_app_cfg.pusch_dec->dedicated_queue;
      hal_dependencies.hw_decoder_factory     = hal::create_bbdev_pusch_dec_acc_factory(hwacc_pusch_dec_cfg);
    }
  }
#endif // DPDK_FOUND


  // In non-DPDK builds we fall straight through with both factory ptrs null.
  return hal_dependencies;
}
