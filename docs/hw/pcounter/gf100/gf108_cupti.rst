.. _gf108-gpu-hw-events-cfg-cupti:

===============================
GF108 GPU Hardware events CUPTI
===============================

.. contents::

NVIDIA: 346.59-1 (Linux)

CUDA: 7.0.28-1

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
  - PMFB[0].PM_UNK28: 0x700c1

- l2_subp1_write_sector_misses

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0].PM_UNK28: 0x700d1

- l2_subp0_read_sector_misses

  - mode: SIMPLE
  - signal: 0x05
  - PMFB[0].PM_UNK28: 0x700c1

- l2_subp1_read_sector_misses

  - mode: SIMPLE
  - signal: 0x05
  - PMFB[0].PM_UNK28: 0x700d1

- l2_subp0_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013012/0x8080
  - PMFB[0].PM_UNK28: 0x71001

- l2_subp1_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013012/0x8080
  - PMFB[0].PM_UNK28: 0x71217

- l2_subp0_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0x71001

- l2_subp1_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0x71217

- l2_subp0_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0x70c01

- l2_subp1_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00013013/0x8080
  - PMFB[0].PM_UNK28: 0x70e17

- l2_subp0_read_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0x71003

- l2_subp1_read_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0x71219

- l2_subp0_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0x70c03

- l2_subp1_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x01301307/0x8000
  - PMFB[0].PM_UNK28: 0x70e19

- l2_subp0_read_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001130d/0x8080
  - PMFB[0].PM_UNK28: 0x70e01

- l2_subp1_read_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001130d/0x8080
  - PMFB[0].PM_UNK28: 0x70e17

- l2_subp0_write_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001120d/0x8080
  - PMFB[0].PM_UNK28: 0x70e01

- l2_subp1_write_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x0001120d/0x8080
  - PMFB[0].PM_UNK28: 0x70e17

- l2_subp0_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000113/0x8888
  - PMFB[0].PM_UNK28: 0x70e01

- l2_subp1_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000113/0x8888
  - PMFB[0].PM_UNK28: 0x70e17

- l2_subp0_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000112/0x8888
  - PMFB[0].PM_UNK28: 0x70e01

- l2_subp1_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x2f2e2d2c/0xffff
  - event_ctr: 0x00000112/0x8888
  - PMFB[0].PM_UNK28: 0x70e17

Local counters
==============

GPC 0, TPC 0:

All of these counters need to enable PM_MUX.

- atom_count

  - pm_sigsel_0: 0x63
  - pm_srcsel_0: 0x30

- gred_count

  - pm_sigsel_0: 0x63
  - pm_srcsel_0: 0x40

- inst_issued1_0

  - pm_sigsel_0: 0x7e
  - pm_srcsel_0: 0x10

- inst_issued2_0

  - pm_sigsel_0: 0x7e
  - pm_srcsel_0: 0x20

- inst_issued1_1

  - pm_sigsel_0: 0x7e
  - pm_srcsel_0: 0x40

- inst_issued2_1

  - pm_sigsel_0: 0x7e
  - pm_srcsel_0: 0x50

- thread_inst_executed_0
- thread_inst_executed_1
- thread_inst_executed_2
- thread_inst_executed_3

  - pm_sigsel_0: 0xa3a3a3a3 (0: a3, 1: a5, 2: a4, 3: a6)
  - pm_sigsel_1: 0xa3a3 (0: a3, 1: a5, 2: a4, 3: a6)
  - pm_srcsel_0: 0x00
  - pm_srcsel_1: 0x11
  - pm_srcsel_2: 0x22
  - pm_srcsel_3: 0x33
  - pm_srcsel_4: 0x44
  - pm_srcsel_5: 0x55

- inst_executed

  - pm_sigsel_0: 0x2d2d2d
  - pm_srcsel_0: 0x00
  - pm_srcsel_1: 0x11
  - pm_srcsel_2: 0x22

- prof_trigger_00
- prof_trigger_01
- prof_trigger_02
- prof_trigger_03
- prof_trigger_04
- prof_trigger_05
- prof_trigger_06
- prof_trigger_07

  - pm_sigsel_0: 0x01
  - pm_srcsel_0: 0x00 (0: 00, 1: 10, 2: 20, 3: 30, 4: 40, 5: 50, 6: 60, 7: 70)

- active_warps

  - pm_sigsel_0: 0x24242424
  - pm_sigsel_1: 0x2424
  - pm_srcsel_0: 0x10
  - pm_srcsel_1: 0x21
  - pm_srcsel_2: 0x32
  - pm_srcsel_3: 0x43
  - pm_srcsel_4: 0x54
  - pm_srcsel_5: 0x65

- active_cycles

  - pm_sigsel_0: 0x11
  - pm_srcsel_0: 0x00

- branch

  - pm_sigsel_0: 0x1a1a
  - pm_srcsel_0: 0x00
  - pm_srcsel_1: 0x11

- divergent_branch

  - pm_sigsel_0: 0x1919
  - pm_srcsel_0: 0x20
  - pm_srcsel_1: 0x31

- warps_launched

  - pm_sigsel_0: 0x26
  - pm_srcsel_0: 0x00

- threads_launched

  - pm_sigsel_0: 0x26262626
  - pm_sigsel_1: 0x2626
  - pm_srcsel_0: 0x10
  - pm_srcsel_1: 0x21
  - pm_srcsel_2: 0x32
  - pm_srcsel_3: 0x43
  - pm_srcsel_4: 0x54
  - pm_srcsel_5: 0x65

- local_load

  - pm_sigsel_0: 0x64
  - pm_srcsel_0: 0x20

- local_store

  - pm_sigsel_0: 0x64
  - pm_srcsel_0: 0x50

- gld_request

  - pm_sigsel_0: 0x64
  - pm_srcsel_0: 0x30

- gst_request

  - pm_sigsel_0: 0x64
  - pm_srcsel_0: 0x60

- shared_load

  - pm_sigsel_0: 0x64
  - pm_srcsel_0: 0x10

- shared_store

  - pm_sigsel_0: 0x64
  - pm_srcsel_0: 0x40

