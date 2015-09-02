.. _gf100-gpu-hw-events:

=========================
GF100 GPU Hardware events
=========================

.. contents::


NVIDIA: 352.30-3

CUDA: 7.0.28-2

Linux Graphics Debugger: 1.0

Global counters
===============

GPC domain 0
------------

- tex0_cache_sector_queries

  - mode: EVENT_B6
  - start_ctr: 0x11100f0e/0xffff
  - event_ctr: 0xef1200ef/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000005

- tex0_cache_sector_misses

  - mode: EVENT_B6
  - start_ctr: 0x0d0c0b0a/0xffff
  - event_ctr: 0xef0e00ef/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000004

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

- fb_read_bytes

  - same config as fb_read_sectors but final result is fb_read_sectors * 32

- fb_read_sectors

  - fb_subp0_read_sectors + fb_subp1_read_sectors

- fb_subp0_read_sectors

  - mode: SIMPLE
  - signal: 0x0f
  - PBFB_BROADCAST.PM_UNK100: 0x111

- fb_subp1_read_sectors

  - mode: SIMPLE
  - signal: 0x0f
  - PBFB_BROADCAST.PM_UNK100: 0x121

- fb_subp0_write_sectors

  - mode: SIMPLE
  - signal: 0x10
  - PBFB_BROADCAST.PM_UNK100: 0x111

- fb_subp1_write_sectors

  - mode: SIMPLE
  - signal: 0x10
  - PBFB_BROADCAST.PM_UNK100: 0x121

- fb_write_bytes

  - same config as fb_write_sectors but final result is fb_write_sectors * 32

- fb_write_sectors

  - fb_subp0_write_sectors + fb_subp1_write_sectors

- l2_read_bytes_mem

  - TODO

- l2_read_bytes_rop

  - TODO

- l2_read_bytes_sysmem

  - TODO

- l2_read_bytes_tex

  - TODO

- l2_read_bytes_vidmem

  - TODO

- l2_read_sectors_tex

  - TODO

- l2_slice0_read_hit_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x02282f21/0x8000
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_hit_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f022f21/0x8080
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_hit_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x022f1f21/0x8000
  - PMFB[0].PM_UNK28: 0x00001003

- l2_slice0_read_hit_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x021f2f21/0x8000
  - PMFB[0].PM_UNK28: 0x00000c03

- l2_slice0_read_hit_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x02012f21/0x8000
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_hit_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x02002f21/0x8000
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f282f21/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_miss_sectors

  - mode: SIMPLE
  - signal: 0x00
  - PMFB[0].PM_UNK28: 0x00000081

- l2_slice0_read_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f6f2f21/0x8888
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f2f1f21/0x8080
  - PMFB[0].PM_UNK28: 0x00001001

- l2_slice0_read_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f1f2f21/0x8080
  - PMFB[0].PM_UNK28: 0x00000c01

- l2_slice0_read_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f012f21/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f002f21/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x1e1d1c1b/0xffff
  - event_ctr: 0x6f6f212f/0x8888
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x1e1d1c1b/0xffff
  - event_ctr: 0x6f6f212e/0x8888
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_miss_sectors

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0].PM_UNK28: 0x00000101

- l2_slice0_write_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f282e21/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f6f2e21/0x8888
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f2e1f21/0x8080
  - PMFB[0].PM_UNK28: 0x00001001

- l2_slice0_write_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f1f2e21/0x8080
  - PMFB[0].PM_UNK28: 0x00000c01

- l2_slice0_write_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f012e21/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f002e21/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice1_read_hit_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x02282f21/0x8000
  - PMFB[0].PM_UNK28: 0x20000019

- l2_slice1_read_hit_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f022f21/0x8080
  - PMFB[0].PM_UNK28: 0x20000019

- l2_slice1_read_hit_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x022f1f21/0x8000
  - PMFB[0].PM_UNK28: 0x20001219

- l2_slice1_read_hit_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x021f2f21/0x8000
  - PMFB[0].PM_UNK28: 0x20000e19

- l2_slice1_read_hit_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x02012f21/0x8000
  - PMFB[0].PM_UNK28: 0x20000019

- l2_slice1_read_hit_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x02002f21/0x8000
  - PMFB[0].PM_UNK28: 0x20000019

- l2_slice1_read_miss_sectors

  - mode: SIMPLE
  - signal: 0x00
  - PMFB[0].PM_UNK28: 0x00000091

- l2_slice1_read_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f282f21/0x8080
  - PMFB[0].PM_UNK28: 0x20000007

- l2_slice1_read_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f6f2f21/0x8888
  - PMFB[0].PM_UNK28: 0x20000007

- l2_slice1_read_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f2f1f21/0x8080
  - PMFB[0].PM_UNK28: 0x20001207

- l2_slice1_read_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f1f2f21/0x8080
  - PMFB[0].PM_UNK28: 0x20000e07

- l2_slice1_read_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f012f21/0x8080
  - PMFB[0].PM_UNK28: 0x20000017

- l2_slice1_read_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f002f21/0x8080
  - PMFB[0].PM_UNK28: 0x20000017

- l2_slice1_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x1e1d1c1b/0xffff
  - event_ctr: 0x6f6f212f/0x8888
  - PMFB[0].PM_UNK28: 0x20000007

- l2_slice1_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x1e1d1c1b/0xffff
  - event_ctr: 0x6f6f212e/0x8888
  - PMFB[0].PM_UNK28: 0x20000007

- l2_slice1_write_miss_sectors

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0].PM_UNK28: 0x00000111

- l2_slice1_write_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f282e21/0x8080
  - PMFB[0].PM_UNK28: 0x20000007

- l2_slice1_write_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f6f2e21/0x8888
  - PMFB[0].PM_UNK28: 0x20000007

- l2_slice1_write_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f2e1f21/0x8080
  - PMFB[0].PM_UNK28: 0x20001207

- l2_slice1_write_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f1f2e21/0x8080
  - PMFB[0].PM_UNK28: 0x20000e07

- l2_slice1_write_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f012e21/0x8080
  - PMFB[0].PM_UNK28: 0x20000017

- l2_slice1_write_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x1e1d1c1b/0xffff
  - event_src: 0x6f002e21/0x8080
  - PMFB[0].PM_UNK28: 0x20000017

- l2_write_bytes_mem

  - TODO

- l2_write_bytes_rop

  - TODO

- l2_write_bytes_sysmem

  - TODO

- l2 _write_bytes_vidmem

  - TODO

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

