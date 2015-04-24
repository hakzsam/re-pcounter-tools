.. _gf119-gpu-hw-events-cfg-cupti:

===============================
GF119 GPU Hardware events CUPTI
===============================

.. contents::

NVIDIA: 349.16-1 (Linux)

CUDA: 7.0.28-2

Global counters
===============

GPC domain 0
------------

All following events use the same config as GF108, nice!

- tex0_cache_sector_queries

- tex1_cache_sector_queries

- tex0_cache_sector_misses

- tex1_cache_sector_misses

- sm_cta_launched

- elapsed_cycles_sm:

- l1_local_load_hit

- l1_local_load_miss

- l1_local_store_hit

- l1_local_store_miss

- l1_global_load_hit

- l1_global_load_miss

- uncached_global_load_transaction

- global_store_transaction

- l1_shared_bank_conflict

PART domain 0
-------------

- fb_subp0_read_sectors

  - mode: SIMPLE
  - signal: 0x00
  - PBFB[0].PM_UNK100: 0x111

- fb_subp1_read_sectors

  - mode: SIMPLE
  - signal: 0x00
  - PBFB[0].PM_UNK100: 0x121

- fb_subp0_write_sectors

  - mode: SIMPLE
  - signal: 0x01
  - PBFB[0].PM_UNK100: 0x111

- fb_subp1_write_sectors

  - mode: SIMPLE
  - signal: 0x01
  - PBFB[0].PM_UNK100: 0x121

- l2_subp0_write_sector_misses

  - mode: SIMPLE
  - signal: 0x15
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x61

- l2_subp0_read_sector_misses

  - mode: SIMPLE
  - signal: 0x16
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x61

- l2_subp0_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00121023/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp0_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00121024/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp0_read_tex_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00121024/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x601

- l2_subp0_read_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x12102418/0x8000
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x803

- l2_subp0_read_tex_hit_sectors

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x12102418/0x8000
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x603

- l2_subp0_read_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x0012241e/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp0_write_sysmem_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x0012231e/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp0_total_read_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00001224/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

- l2_subp0_total_write_sector_queries

  - mode: EVENT_B4
  - start_ctr: 0x0f0e0d0c/0xffff
  - event_ctr: 0x00001223/0x8080
  - PMFB[0].PM_UNK28: 0x70001
  - PMFB[0].SUBP[0].PM_UNK25C: 0x801

Local counters
==============

See gf100!
