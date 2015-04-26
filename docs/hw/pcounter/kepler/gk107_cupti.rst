.. _gk107-gpu-hw-events-cfg-cupti:

=====================================
GK107:GK106 GPU Hardware events CUPTI
=====================================

.. contents::

NVIDIA: 349.16-1 (Linux)

CUDA: 7.0.28-2

Global counters
===============

GPC domain 2
------------

- tex0_cache_sector_queries

  - mode: UNK5
  - pre_ctr: 0xef080700/0xffff
  - stop_ctr: 0x06050400/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000003
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex1_cache_sector_queries

  - mode: UNK5
  - pre_ctr: 0xef080700/0xffff
  - stop_ctr: 0x06050400/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex2_cache_sector_queries

  - mode: UNK5
  - pre_ctr: 0xef121100/0xffff
  - stop_ctr: 0x100f0e00/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000003
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex3_cache_sector_queries

  - mode: UNK5
  - pre_ctr: 0xef121100/0xffff
  - stop_ctr: 0x100f0e00/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex0_cache_sector_misses

  - mode: UNK5
  - pre_ctr: 0xef040300/0xffff
  - stop_ctr: 0x02010000/0xffff
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

- tex2_cache_sector_misses

  - mode: UNK5
  - pre_ctr: 0xef0e0d00/0xffff
  - stop_ctr: 0x0c0b0a00/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000003
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKB8: 0x80000000

- tex3_cache_sector_misses

  - mode: UNK5
  - pre_ctr: 0xef0e0d00/0xffff
  - stop_ctr: 0x0c0b0a00/0xffff
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0x1].TEX.PM_UNKC8: 0x80000004
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

- l2_subp2_{read/write}_sector_misses

  - mode: SIMPLE
  - signal: 0x15 (wr), 0x16 (rd)
  - PMFB[0].PM_UNK28: 0x21
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x61

- l2_subp3_{read/write}_sector_misses

  - mode: SIMPLE
  - signal: 0x15 (wr), 0x16 (rd)
  - PMFB[0].PM_UNK28: 0x31
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x61

- l2_subp0_{read/write}_l1_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102612/0x8080 (wr), 0x00102712/0x8080 (rd)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp1_{read/write}_l1_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102612/0x8080 (wr), 0x00102712/0x8080 (rd)
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x801

- l2_subp2_{read/write}_l1_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102612/0x8080 (wr), 0x00102712/0x8080 (rd)
  - PMFB[0].PM_UNK28: 0x425
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x801

- l2_subp3_{read/write}_l1_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102612/0x8080 (wr), 0x00102712/0x8080 (rd)
  - PMFB[0].PM_UNK28: 0x637
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x801

- l2_subp0_read_l1_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x803

- l2_subp1_read_l1_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x803

- l2_subp2_read_l1_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x425
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x803

- l2_subp3_read_l1_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x637
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x803

- l2_subp0_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102712/0x8080
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x601

- l2_subp1_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102712/0x8080
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x601

- l2_subp2_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102712/0x8080
  - PMFB[0].PM_UNK28: 0x425
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x601

- l2_subp3_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00102712/0x8080
  - PMFB[0].PM_UNK28: 0x637
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x601

- l2_subp0_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x603

- l2_subp1_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x213
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x603

- l2_subp2_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x425
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x603

- l2_subp3_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x18102712/0x8000
  - PMFB[0].PM_UNK28: 0x637
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x603

- l2_subp0_{read/write}_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00212712/0x8080 (rd), 0x00212612/0x8080 (wr)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x1

- l2_subp1_{read/write}_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00212712/0x8080 (rd), 0x00212612/0x8080 (wr)
  - PMFB[0].PM_UNK28: 0x13
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x1

- l2_subp2_{read/write}_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00212712/0x8080 (rd), 0x00212612/0x8080 (wr)
  - PMFB[0].PM_UNK28: 0x25
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x1

- l2_subp3_{read/write}_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00212712/0x8080 (rd), 0x00212612/0x8080 (wr)
  - PMFB[0].PM_UNK28: 0x37
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x1

- l2_subp0_total_{read/write}_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00122725/0xe0e0 (rd), 0x00122625/0xe0e0 (wr)
  - PMFB[0].PM_UNK28: 0x1
  - PMFB[0].SUBP[0].PM_UNK25C: 0x1

- l2_subp1_total_{read/write}_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00122725/0xe0e0 (rd), 0x00122625/0xe0e0 (wr)
  - PMFB[0].PM_UNK28: 0x13
  - PMFB[0].SUBP[0x1].PM_UNK25C: 0x1

- l2_subp2_total_{read/write}_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00122725/0xe0e0 (rd), 0x00122625/0xe0e0 (wr)
  - PMFB[0].PM_UNK28: 0x25
  - PMFB[0].SUBP[0x2].PM_UNK25C: 0x1

- l2_subp3_total_{read/write}_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00122725/0xe0e0 (rd), 0x00122625/0xe0e0 (wr)
  - PMFB[0].PM_UNK28: 0x37
  - PMFB[0].SUBP[0x3].PM_UNK25C: 0x1
