.. _gf108-gpu-hw-events-cfg-cupti:

===============================
GF108 GPU Hardware events CUPTI
===============================

.. contents::

NVIDIA: 349.16-1 (Linux)

CUDA: 7.0.28-2

Global counters
===============

GPC domain 0
------------

- tex0_cache_sector_queries

  - mode: EVENT_B6
  - start_ctr: 0x11100f0e/0xffff
  - event_ctr: 0xef1200ef/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKC8: 0x80000003

- tex1_cache_sector_queries

  - mode: EVENT_B6
  - start_ctr: 0x11100f0e/0xffff
  - event_ctr: 0xef1200ef/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKC8: 0x80000004

- tex0_cache_sector_misses

  - mode: EVENT_B6
  - start_ctr: 0x0d0c0b0a/0xffff
  - event_ctr: 0xef0e00ef/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKC8: 0x80000003

- tex1_cache_sector_misses

  - mode: EVENT_B6
  - start_ctr: 0x0d0c0b0a/0xffff
  - event_ctr: 0xef0e00ef/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKC8: 0x80000004

- sm_cta_launched

  - mode: SIMPLE
  - signal: 0x26
  - PGRAPH.GPC[0].TPC[0].UNK400.PM_MUX: 0x8000000e

- elapsed_cycles_sm:

  - mode: SIMPLE
  - signal: 0x00

- l1_local_load_hit

  - mode: SIMPLE
  - signal: 0x00
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000001

- l1_local_load_miss

  - mode: SIMPLE
  - signal: 0x01
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000001

- l1_local_store_hit

  - mode: SIMPLE
  - signal: 0x02
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000001

- l1_local_store_miss

  - mode: SIMPLE
  - signal: 0x03
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000001

- l1_global_load_hit

  - mode: SIMPLE
  - signal: 0x05
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000001

- l1_global_load_miss

  - mode: SIMPLE
  - signal: 0x06
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000001

- uncached_global_load_transaction

  - mode: SIMPLE
  - signal: 0x02
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000002

- global_store_transaction

  - mode: SIMPLE
  - signal: 0x03
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000002

- l1_shared_bank_conflict

  - mode: SIMPLE
  - signal: 0x00
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x80000006

PART domain 0
-------------

- fb0_subp0_read_sectors

  - mode: SIMPLE
  - signal: 0x14
  - PBFB[0].PM_UNK100: 0x111

- fb0_subp1_read_sectors

  - mode: SIMPLE
  - signal: 0x14
  - PBFB[0].PM_UNK100: 0x121

- fb0_subp0_write_sectors

  - mode: SIMPLE
  - signal: 0x15
  - PBFB[0].PM_UNK100: 0x111

- fb0_subp1_write_sectors

  - mode: SIMPLE
  - signal: 0x15
  - PBFB[0].PM_UNK100: 0x121

- fb1_subp0_read_sectors

  - mode: SIMPLE
  - signal: 0x20
  - PBFB[0x1].PM_UNK100: 0x111

- fb1_subp1_read_sectors

  - mode: SIMPLE
  - signal: 0x20
  - PBFB[0x1].PM_UNK100: 0x121

- fb1_subp0_write_sectors

  - mode: SIMPLE
  - signal: 0x21
  - PBFB[0x1].PM_UNK100: 0x111

- fb1_subp1_write_sectors

  - mode: SIMPLE
  - signal: 0x21
  - PBFB[0x1].PM_UNK100: 0x121

- l2_subp0_write_sector_misses

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0].PM_UNK28: 0xc1

- l2_subp1_write_sector_misses

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0].PM_UNK28: 0xd1

- l2_subp0_read_sector_misses

  - mode: SIMPLE
  - signal: 0x05
  - PMFB[0].PM_UNK28: 0xc1

- l2_subp1_read_sector_misses

  - mode: SIMPLE
  - signal: 0x05
  - PMFB[0].PM_UNK28: 0xd1

- l2_subp0_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013012/0x8080
  - PMFB[0].PM_UNK28: 0x1001

- l2_subp1_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013012/0x8080
  - PMFB[0].PM_UNK28: 0x1217

- l2_subp0_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0x1001

- l2_subp1_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0x1217

- l2_subp0_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0xc01

- l2_subp1_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0xe17

- l2_subp0_read_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0x1003

- l2_subp1_read_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0x1219

- l2_subp0_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0xc03

- l2_subp1_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0xe19

- l2_subp0_read_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001130d/0x8080
  - PMFB[0].PM_UNK28: 0x1

- l2_subp1_read_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001130d/0x8080
  - PMFB[0].PM_UNK28: 0x17

- l2_subp0_write_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001120d/0x8080
  - PMFB[0].PM_UNK28: 0x1

- l2_subp1_write_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001120d/0x8080
  - PMFB[0].PM_UNK28: 0x17

- l2_subp0_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000113/0x8888
  - PMFB[0].PM_UNK28: 0x1

- l2_subp1_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000113/0x8888
  - PMFB[0].PM_UNK28: 0x17

- l2_subp0_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000112/0x8888
  - PMFB[0].PM_UNK28: 0x1

- l2_subp1_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000112/0x8888
  - PMFB[0].PM_UNK28: 0x17

Local counters
==============

See gf100!
