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

See GF100!

PART domain 0
-------------

- fb_read_bytes

  - same config as fb_read_sectors but final result is fb_read_sectors * 32

- fb_read_sectors

  - fb_subp0_read_sectors + fb_subp1_read_sectors

- fb_subp0_read_sectors

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
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x07061301/0x8000
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_hit_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f071301/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_hit_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x07133001/0x8000
  - PMFB[0].PM_UNK28: 0x00001003

- l2_slice0_read_hit_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x07301301/0x8000
  - PMFB[0].PM_UNK28: 0x00000c03

- l2_slice0_read_hit_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x070d1301/0x8000
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_hit_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x070c1301/0x8000
  - PMFB[0].PM_UNK28: 0x00000003

- l2_slice0_read_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f061301/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f4f1301/0x8888
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f133001/0x8080
  - PMFB[0].PM_UNK28: 0x00001001

- l2_slice0_read_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f301301/0x8080
  - PMFB[0].PM_UNK28: 0x00000c01

- l2_slice0_read_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0d1301/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_read_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0c1301/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f061201/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f4f1201/0x8888
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f123001/0x8080
  - PMFB[0].PM_UNK28: 0x00001001

- l2_slice0_write_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f301201/0x8080
  - PMFB[0].PM_UNK28: 0x00000c01

- l2_slice0_write_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0d1201/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice0_write_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0c1201/0x8080
  - PMFB[0].PM_UNK28: 0x00000001

- l2_slice1_read_hit_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x07061301/0x8000
  - PMFB[0].PM_UNK28: 0x00000019

- l2_slice1_read_hit_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f071301/0x8080
  - PMFB[0].PM_UNK28: 0x00000019

- l2_slice1_read_hit_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x07133001/0x8000
  - PMFB[0].PM_UNK28: 0x00001219

- l2_slice1_read_hit_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x07301301/0x8000
  - PMFB[0].PM_UNK28: 0x00000e19

- l2_slice1_read_hit_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x070d1301/0x8000
  - PMFB[0].PM_UNK28: 0x00000019

- l2_slice1_read_hit_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x070c1301/0x8000
  - PMFB[0].PM_UNK28: 0x00000019

- l2_slice1_read_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f061301/0x8080
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_read_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f4f1301/0x8888
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_read_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f133001/0x8080
  - PMFB[0].PM_UNK28: 0x00001217

- l2_slice1_read_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f301301/0x8080
  - PMFB[0].PM_UNK28: 0x00000e17

- l2_slice1_read_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0d1301/0x8080
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_read_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0c1301/0x8080
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_write_sectors_atomic

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f061201/0x8080
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_write_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f4f1201/0x8888
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_write_sectors_l1

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f123001/0x8080
  - PMFB[0].PM_UNK28: 0x00001217

- l2_slice1_write_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f301201/0x8080
  - PMFB[0].PM_UNK28: 0x00000e17

- l2_slice1_write_sysmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0d1201/0x8080
  - PMFB[0].PM_UNK28: 0x00000017

- l2_slice1_write_vidmem_sectors

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f0c1201/0x8080
  - PMFB[0].PM_UNK28: 0x00000017








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

HUB domain 4
------------

- geom_busy

  - mode: SIMPLE
  - event_src: 0x6f6f2f2e/0x8888
  - PGRAPH.UNK6000.PM_MUX: 0x8000000c

- gpu_busy:

  - mode: SIMPLE
  - event_src: 0x02
  - PGRAPH.DISPATCH.PM_MUX: 0x00000007

Local counters
==============

See gf100!
