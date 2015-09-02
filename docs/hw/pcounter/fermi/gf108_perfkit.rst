.. _gf108-gpu-hw-events-cfg-perfkit:

=================================
GF108 GPU Hardware events PerfKit
=================================

.. contents::

todo: check with latest version of blob on doz!

Global counters
===============

PART domain 0
-------------

- l2_slice0_read_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f301301/0x8080
  - PMFB[0].PM_UNK28: 0x00000c01
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x0

- l2_slice1_read_sectors_tex

  - mode: EVENT_B4
  - start_src: 0x2f2e2d2c/0xffff
  - event_src: 0x4f301301/0x8080
  - PMFB[0].PM_UNK28: 0x00000e17
  - PGRAPH.GPC[0].TPC[0].L1.PM_MUX: 0x0
