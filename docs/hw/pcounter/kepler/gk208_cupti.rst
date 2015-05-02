.. _gk208-gpu-hw-events-cfg-cupti:

===============================
GK208 GPU Hardware events CUPTI
===============================

.. contents::

NVIDIA: 349.16-1 (Linux)

CUDA: 7.0.28-2

Global counters
===============

GPC domain 2
------------

- tex0_cache_sector_queries

  - mode: UNK5
  - pre_ctr: 0xef141300/0xffff
  - stop_ctr: 0x12111000/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000003
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex1_cache_sector_queries

  - mode: UNK5
  - pre_ctr: 0xef141300/0xffff
  - stop_ctr: 0x12111000/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex0_cache_sector_misses

  - mode: UNK5
  - pre_ctr: 0xef100f00/0xffff
  - stop_ctr: 0x0e0d0c00/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000003
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex1_cache_sector_misses

  - mode: UNK5
  - pre_ctr: 0xef040300/0xffff
  - stop_ctr: 0x02010000/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp0_gld_warp_count_32b

  - signal: 0x19
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003a
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000000
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp1_gld_warp_count_32b

  - signal: 0x19
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003a
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000010
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp0_gld_warp_count_64b

  - signal: 0x19
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003b
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000000
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp1_gld_warp_count_64b

  - signal: 0x19
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003b
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000010
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp0_gld_warp_count_128b

  - signal: 0x19
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003c
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000000
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp1_gld_warp_count_128b

  - signal: 0x19
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003c
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000010
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp0_gld_thread_count_32b

  - mode: UNK5
  - stop_ctr: 0x18171600/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003a
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000000
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp1_gld_thread_count_32b

  - mode: UNK5
  - stop_ctr: 0x18171600/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003a
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000010
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp0_gld_thread_count_64b

  - mode: UNK5
  - stop_ctr: 0x18171600/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003b
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000000
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp1_gld_thread_count_64b

  - mode: UNK5
  - stop_ctr: 0x18171600/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003b
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000010
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp0_gld_thread_count_128b

  - mode: UNK5
  - stop_ctr: 0x18171600/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003c
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000000
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- rocache_subp1_gld_thread_count_128b

  - mode: UNK5
  - stop_ctr: 0x18171600/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_A: 0x8000003c
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000010
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

PART domain 0
-------------

- fb_subp0_{read/write}_sectors

  - mode: SIMPLE
  - signal: 0x00 (rd), 0x01 (wr)
  - PBFB_BROADCAST.PM_UNK100: 0x111

- fb_subp1_{read/write}_sectors

  - mode: SIMPLE
  - signal: 0x00 (rd), 0x01 (wr)
  - PBFB_BROADCAST.PM_UNK100: 0x121

- l2_subp0_{read/write}_sector_misses

  - mode: SIMPLE
  - signal: 0x15 (wr), 0x16 (rd)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x61

- l2_subp1_{read/write}_sector_misses

  - mode: SIMPLE
  - signal: 0x15 (wr), 0x16 (rd)
  - PMFB[0].PM_UNK28: 0x11
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x61

- l2_subp0_{read/write}_l1_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102412/0x8080 (wr), 0x00102512/0x8080 (rd)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp1_{read/write}_l1_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102412/0x8080 (wr), 0x00102512/0x8080 (rd)
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x801

- l2_subp0_read_l1_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x19102512/0x8000
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x803

- l2_subp1_read_l1_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x19102512/0x8000
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x803

- l2_subp0_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102512/0x8080
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x601

- l2_subp1_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102512/0x8080
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x601

- l2_subp0_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x19102512/0x8000
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x603

- l2_subp1_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x19102512/0x8000
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x603

- l2_subp0_{read/write}_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x001f2512/0x8080 (rd), 0x001f2412/0x8080 (wr)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x1

- l2_subp1_{read/write}_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x001f2512/0x8080 (rd), 0x001f2412/0x8080 (wr)
  - PMFB[0].PM_UNK28: 0x13
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x1

- l2_subp0_total_{read/write}_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00122523/0xe0e0 (rd), 0x00122423/0xe0e0 (wr)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x1

- l2_subp1_total_{read/write}_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00122523/0xe0e0 (rd), 0x00122423/0xe0e0 (wr)
  - PMFB[0].PM_UNK28: 0x13
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x1
