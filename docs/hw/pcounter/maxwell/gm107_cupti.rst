.. _gm107-gpu-hw-events-cfg-cupti:

===============================
GM107 GPU Hardware events CUPTI
===============================

.. contents::

NVIDIA: 349.16-1 (Linux)

CUDA: 7.0.28-1

Global counters
===============

GPC domain 5
------------

- tex0_cache_sector_queries

  - mode: 0x6
  - start_ctr: 0xefefef88/0xffff
  - pre_ctr: 0x87868584/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKB8: 0x80000000
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- tex1_cache_sector_queries

  - mode: 0x6
  - start_ctr: 0xefefef74/0xffff
  - pre_ctr: 0x73727170/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000005
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKB8: 0x80000000
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- tex0_cache_sector_misses

  - mode: 0x6
  - start_ctr: 0xefefef84/0xffff
  - pre_ctr: 0x83828180/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKB8: 0x80000000
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- tex1_cache_sector_misses

  - mode: 0x6
  - start_ctr: 0xefefef70/0xffff
  - pre_ctr: 0x6f6e6d6c/0xffff
  - PGRAPH.GPC[0].TPC[0].TEX.PM_MUX_C_D: 0x80000004
  - PGRAPH.GPC[0].TPC[0].TEX.PM_UNKB8: 0x80000000
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- elapsed_cycles_sm:

  - mode: SIMPLE
  - signal: 0x00

PART domain 0
-------------

- fb_subp0_read_sectors

  - mode: SIMPLE
  - signal: 0x00
  - PBFB_BROADCAST.PM_UNK100: 0x111
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- fb_subp1_read_sectors

  - mode: SIMPLE
  - signal: 0x00
  - PBFB_BROADCAST.PM_UNK100: 0x121
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- fb_subp0_write_sectors

  - mode: SIMPLE
  - signal: 0x01
  - PBFB_BROADCAST.PM_UNK100: 0x111
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- fb_subp1_write_sectors

  - mode: SIMPLE
  - signal: 0x01
  - PBFB_BROADCAST.PM_UNK100: 0x121
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

PART domain 1
-------------

- l2_subp0_write_sector_misses

  - mode: SIMPLE
  - signal: 0x26
  - PMFB[0]+0x550: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_write_sector_misses

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0]+0x750: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_read_sector_misses

  - mode: SIMPLE
  - signal: 0x27
  - PMFB[0]+0x550: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_read_sector_misses

  - mode: SIMPLE
  - signal: 0x05
  - PMFB[0]+0x750: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_read_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00203623/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_read_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00211401/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_write_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00203523/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_write_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00211301/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_read_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x2a203623/0x8000
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_read_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x08211401/0x8000
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_write_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x2a203523/0x8000
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_write_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x08211301/0x8000
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_read_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x00303623/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_read_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x000e1401/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_write_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x00303523/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_write_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x000e1301/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_total_read_sector_queries

  - mode: 0x7
  - start_ctr: 0x00233634/0xe0e0
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_total_read_sector_queries

  - mode: 0x7
  - start_ctr: 0x00011412/0xe0e0
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp0_total_write_sector_queries

  - mode: 0x7
  - start_ctr: 0x00233534/0xe0e0
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0]+0x550: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp1_total_write_sector_queries

  - mode: 0x7
  - start_ctr: 0x00011312/0xe0e0
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0]+0x750: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

PART domain 2
-------------

- l2_subp2_write_sector_misses

  - mode: SIMPLE
  - signal: 0x26
  - PMFB[0].SUBP_BROADCAST+0x150: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_write_sector_misses

  - mode: SIMPLE
  - signal: 0x04
  - PMFB[0].SUBP_BROADCAST+0x350: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_read_sector_misses

  - mode: SIMPLE
  - signal: 0x27
  - PMFB[0].SUBP_BROADCAST+0x150: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_read_sector_misses

  - mode: SIMPLE
  - signal: 0x05
  - PMFB[0].SUBP_BROADCAST+0x350: 0x61
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_write_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00203523/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_write_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00211301/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_read_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00203623/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_read_tex_sector_queries

  - mode: 0x7
  - start_ctr: 0x00211401/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x601
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_write_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x2a203523/0x8000
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_write_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x08211301/0x8000
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_read_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x2a203623/0x8000
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_read_tex_hit_sectors

  - mode: 0x7
  - start_ctr: 0x08211401/0x8000
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x603
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_write_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x00303523/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_write_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x000e1301/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_read_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x00303623/0x8080
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_read_sysmem_sector_queries

  - mode: 0x7
  - start_ctr: 0x000e1401/0x8080
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_total_write_sector_queries

  - mode: 0x7
  - start_ctr: 0x00233534/0xe0e0
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_total_write_sector_queries

  - mode: 0x7
  - start_ctr: 0x00011312/0xe0e0
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp2_total_read_sector_queries

  - mode: 0x7
  - start_ctr: 0x00233634/0xe0e0
  - event_ctr: 0x1b1a1918/0xffff
  - PMFB[0].SUBP_BROADCAST+0x150: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

- l2_subp3_total_read_sector_queries

  - mode: 0x7
  - start_ctr: 0x00011412/0xe0e0
  - event_ctr: 0x1f1e1d1c/0xffff
  - PMFB[0].SUBP_BROADCAST+0x350: 0x1
  - PGRAPH.DISPATCH.PM_MUX: 0x80000000

Local counters
==============

TODO (not a big priority in my infinite todolist...)
