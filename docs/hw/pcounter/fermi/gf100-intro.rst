.. _gf100-gpu-hardware-events:

=========================
GF100 GPU Hardware events
=========================

.. contents::

Global counters
===============

GPC domain 0
-------------

- setup_primitive_count

  - desc: Count of primitives seen by the setup unit.
  - display: RAW

- ia_requests

  - desc: Number of Input Assembler requests.
  - display: RAW

- ia_l2_read_bytes

  - desc: Number of bytes returned from L2 to the Input Assembler.
  - display: RAW

- shader_busy

  - desc: Time the shader unit is busy
  - display: RATIO

- texture_busy

  - desc: Time the texture unit is busy
  - display: RATIO

- tex0_bank_conflicts_gpc0_tpcX

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW

- tex0_cache_sector_misses_gpc0_tpcX

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW

- tex0_cache_sector_queries_gpc0_tpcX

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW

- tex0_cache_texel_queries_gpc0_tpcX

  - desc: Number of texture cache queries (32b each request)
  - display: RAW

- tex1_bank_conflicts_gpc0_tpcX

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW

- tex1_bank_conflicts_gpc0_tpcX

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW

- tex1_cache_sector_misses_gpc0_tpcX

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW

- tex1_cache_sector_queries_gpc0_tpcX

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW

- shd_tex_requests

  - desc: Number of texel read requests from the shader unit.
  - display: RAW

- sm_instruction_count_domain_vsmX

  - desc: count the number ds instructions executed in GPC0.TPCX.SM
  - display: RAW

- sm_instruction_count_geometry_vsmX

  - desc: count the number gs instructions executed in GPC0.TPCX.SM
  - display: RAW

- sm_instruction_count_hull_vsmX

  - desc: count the number hs instructions executed in GPC0.TPCX.SM
  - display: RAW

- sm_instruction_count_pixel_vsmX

  - desc: count the number ps instructions executed in GPC0.TPCX.SM
  - display: RAW

- sm_instruction_count_vertex_vsmX

  - desc: count the number vs instructions executed in GPC0.TPCX.SM
  - display: RAW

- warps_launched_vsmX

  - desc: Warps launched by this VSM. Increments by 1 per warp launched.
  - display: RAW

- stream_out_bytes

  - desc: Number of bytes streamed out.
  - display: RAW

- shaded_pixel_count

  - desc: Number of rasterized pixels sent to the shading units.
  - display: RAW

- l1_local_load_hit

  - desc: Number of cache lines that hit in L1 cache for local memory load accesses. In case of perfect coalescing this increments by 1, 2, and 4 for 32, 64 and 128 bit accesses by a warp respectively.
  - display: RAW

- l1_local_load_miss

  - desc: Number of cache lines that miss in L1 cache for local memory load accesses. In case of perfect coalescing this increments by 1, 2, and 4 for 32, 64 and 128 bit accesses by a warp respectively.
  - display: RAW

- l1_local_store_hit

  - desc: Number of cache lines that hit in L1 cache for local memory store accesses. In case of perfect coalescing this increments by 1, 2, and 4 for 32, 64 and 128 bit accesses by a warp respectively.
  - display: RAW

- l1_local_store_miss

  - desc: Number of cache lines that miss in L1 cache for local memory store accesses. In case of perfect coalescing this increments by 1, 2, and 4 for 32, 64 and 128 bit accesses by a warp respectively.
  - display: RAW

- l1_global_load_hit

  - desc: Number of cache lines that hit in L1 cache for global memory load accesses. In case of perfect coalescing this increments by 1, 2, and 4 for 32, 64 and 128 bit accesses by a warp respectively.
  - display: RAW

- l1_global_load_miss

  - desc: Number of cache lines that miss in L1 cache for global memory load accesses. In case of perfect coalescing this increments by 1, 2, and 4 for 32, 64 and 128 bit accesses by a warp respectively.
  - display: RAW

- uncached_global_load_transaction

  - desc: Number of uncached global load transactions. Increments by 1 per transaction. Transaction can be 32/64/96/128B.
  - display: RAW

- global_store_transaction

  - desc: Number of global store transactions. Increments by 1 per transaction. Transaction can be 32/64/96/128B.
  - display: RAW

- l1_shared_bank_conflict

  - desc: Number of shared bank conflicts caused due to addresses for two or more shared memory requests fall in the same memory bank. Increments by N-1 and 2*(N-1) for a N-way conflict for 32 bit and 64bit shared memory accesses respectively.
  - display: RAW

- sm_cta_launched

  - desc: Number of thread blocks launched on a multiprocessor.
  - display: RAW

- elapsed_cycles_sm

  - desc: Elapsed clocks
  - display: RAW

PART domain 0
-------------

- fb0_subp0_read_sectors

  - desc: Number of DRAM read requests to sub partition 0 of DARM partition 0, increments by 1 for 32 byte access.
  - display: RAW

- fb0_subp1_read_sectors

  - desc: Number of DRAM read requests to sub partition 1 of DARM partition 0, increments by 1 for 32 byte access.
  - display: RAW

- fb0_subp0_write_sectors

  - desc: Number of DRAM write requests to sub partition 0 of DARM partition 0, increments by 1 for 32 byte access.
  - display: RAW

- fb0_subp1_write_sectors

  - desc: Number of DRAM write requests to sub partition 1 of DARM partition 0, increments by 1 for 32 byte access.
  - display: RAW

- fb1_subp0_read_sectors

  - desc: Number of DRAM read requests to sub partition 0 of DARM partition 1, increments by 1 for 32 byte access.
  - display: RAW

- fb1_subp1_read_sectors

  - desc: Number of DRAM read requests to sub partition 1 of DARM partition 1, increments by 1 for 32 byte access.
  - display: RAW

- fb1_subp0_write_sectors

  - desc: Number of DRAM write requests to sub partition 0 of DARM partition 1, increments by 1 for 32 byte access.
  - display: RAW

- fb1_subp1_write_sectors

  - desc: Number of DRAM write requests to sub partition 1 of DARM partition 1, increments by 1 for 32 byte access.
  - display: RAW

- l2_fb_read_bytes

  - desc: Number of fb bytes read from the l2 unit.
  - display: RAW

- l2_fb_write_bytes

  - desc: Number of fb bytes written by the l2 unit.
  - display: RAW

- l2_slice0_read_sectors_tex

  - desc: Sector reads from TEX to L2 cache in the given slice and FB partition. A sector is 32 bytes.
  - display: RAW

- l2_slice1_read_sectors_tex

  - desc: Sector reads from TEX to L2 cache in the given slice and FB partition. A sector is 32 bytes.
  - display: RAW

- l2_subp0_write_sector_misses

  - desc: Number of write misses in slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_write_sector_misses

  - desc: Number of write misses in slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_read_sector_misses

  - desc: Number of read misses in slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_read_sector_misses

  - desc: Number of read misses in slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_write_sector_queries

  - desc: Number of write requests from L1 to slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_write_sector_queries

  - desc: Number of write requests from L1 to slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_read_sector_queries

  - desc: Number of read requests from L1 to slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_read_sector_queries

  - desc: Number of read requests from L1 to slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_read_tex_sector_queries

  - desc: Number of read requests from Texture cache to slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_read_tex_sector_queries

  - desc: Number of read requests from Texture cache to slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_read_hit_sectors

  - desc: Number of read requests from L1 that hit in slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_read_hit_sectors

  - desc: Number of read requests from L1 that hit in slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_read_tex_hit_sectors

  - desc: Number of read requests from Texture cache that hit in slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_read_tex_hit_sectors

  - desc: Number of read requests from Texture cache that hit in slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_read_sysmem_sector_queries

  - desc: Number of system memory read requests to slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_read_sysmem_sector_queries

  - desc: Number of system memory read requests to slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_write_sysmem_sector_queries

  - desc: Number of system memory write requests to slice 0 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_write_sysmem_sector_queries

  - desc: Number of system memory write requests to slice 1 of L2 cache. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_total_read_sector_queries

  - desc: Total read requests to slice 0 of L2 cache. This includes requests from  L1, Texture cache, system memory. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_total_read_sector_queries

  - desc: Total read requests to slice 1 of L2 cache. This includes requests from  L1, Texture cache, system memory. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp0_total_write_sector_queries

  - desc: Total write requests to slice 0 of L2 cache. This includes requests from  L1, Texture cache, system memory. This increments by 1 for each 32-byte access.
  - display: RAW

- l2_subp1_total_write_sector_queries

  - desc: Total write requests to slice 1 of L2 cache. This includes requests from  L1, Texture cache, system memory. This increments by 1 for each 32-byte access.
  - display: RAW

PART domain 1
-------------

- rop_busy

  - desc: Time the ROP unit is busy.
  - display: RATIO

- crop_busy

  - desc: Time the crop unit is busy.
  - display: RATIO

- zrop_busy

  - desc: Time the zrop unit is busy.
  - display: RATIO

HUB domain 4
------------

- gpu_busy

  - desc: GPU is busy.
  - display: RATIO

- geom_busy

  - desc: Time the geom unit was busy.
  - display: RATIO

Local counters
==============

- local_load

  - desc: Number of executed load instructions where state space is specified as local, increments per warp on a multiprocessor.
  - display: RAW

- local_store

  - desc: Number of executed store instructions where state space is specified as local, increments per warp on a multiprocessor.
  - display: RAW

- gld_request

  - desc: Number of executed load instructions where the state space is not specified and hence generic addressing is used, increments per warp on a multiprocessor. It can include the load operations from global,local and share state space.
  - display: RAW

- gst_request

  - desc: Number of executed store instructions where the state space is not specified and hence generic addressing is used, increments per warp on a multiprocessor. It can include the store operations to global,local and share state space.
  - display: RAW

- shared_load

  - desc: Number of executed load instructions where state space is specified as shared, increments per warp on a multiprocessor.
  - display: RAW

- shared_store

  - desc: Number of executed store instructions where state space is specified as shared, increments per warp on a multiprocessor.
  - display: RAW

- branch

  - desc: Number of branch instructions executed per warp on a multiprocessor.
  - display: RAW

- divergent_branch

  - desc: Number of divergent branches within a warp. This counter will be incremented by one if at least one thread in a warp diverges (that is, follows a different execution path) via a conditional branch.
  - display: RAW

- warps_launched

  - desc: Number of warps launched on a multiprocessor.
  - display: RAW

- threads_launched

  - desc: Number of threads launched on a multiprocessor.
  - display: RAW

- active_warps

  - desc: Accumulated number of active warps per cycle. For every cycle it increments by the number of active warps in the cycle which can be in the range 0 to 48.
  - display: RAW

- active_cycles

  - desc: Number of cycles a multiprocessor has at least one active warp.
  - display: RAW

- prof_trigger_00

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_01

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_02

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_03

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_04

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_05

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_06

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- prof_trigger_07

  - desc: User profiled generic trigger that can be inserted in any place of the code to collect the related information. Increments per warp.
  - display: RAW

- inst_executed

  - desc: Number of instructions executed, do not include replays.
  - display: RAW

- thread_inst_executed_0

  - desc: Number of instructions executed by all threads, does not include replays. For each instruction it increments by the number of threads in the warp that execute the instruction in pipeline 0.
  - display: RAW

- thread_inst_executed_2

  - desc: Number of instructions executed by all threads, does not include replays. For each instruction it increments by the number of threads in the warp that execute the instruction in pipeline 2.
  - display: RAW

- thread_inst_executed_1

  - desc: Number of instructions executed by all threads, does not include replays. For each instruction it increments by the number of threads in the warp that execute the instruction in pipeline 1.
  - display: RAW

- thread_inst_executed_3

  - desc: Number of instructions executed by all threads, does not include replays. For each instruction it increments by the number of threads in the warp that execute the instruction in pipeline 3.
  - display: RAW

- inst_issued1_0

  - desc: Number of single instruction issued per cycle in pipeline 0.
  - display: RAW

- inst_issued2_0

  - desc: Number of dual instructions issued per cycle in pipeline 0.
  - display: RAW

- inst_issued1_1

  - desc: Number of single instruction issued per cycle in pipeline 1.
  - display: RAW

- inst_issued2_1

  - desc: Number of dual instructions issued per cycle in pipeline 1.
  - display: RAW

- atom_count

  - desc: Number of warps executing atomic reduction operations for thread-to-thread communication. Increments by one if at least one thread in a warp executes the instruction
  - display: RAW

- gred_count

  - desc: Number of warps executing reduction operations on global and shared memory. Increments by one if at least one thread in a warp executes the instruction
  - display: RAW

TODO
====

- vertex_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to vertex shader threads
  - display: RAW

- hull_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to hull shader threads
  - display: RAW

- domain_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to domain shader threads
  - display: RAW

- geometry_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to geometry shader threads
  - display: RAW

- pixel_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to pixel shader threads
  - display: RAW

- shd_tex_read_bytes

  - desc: Number of bytes read from the tex unit by the shader unit.
  - display: RAW

- shd_l1_requests

  - desc: Number of l1 requests from the shader unit.
  - display: RAW

- shd_l1_read_bytes

  - desc: Number of bytes transferred from the l1 unit by the shader unit.
  - display: RAW

- tex_l2_requests

  - desc: Number of l2 read requests from the texture unit.
  - display: RAW

- tex_l2_read_bytes

  - desc: Number of bytes read from the l2 unit from the texture unit.
  - display: RAW

- l1_l2_requests

  - desc: Number of l2 requests from the l1 unit.
  - display: RAW

- l1_l2_bytes

  - desc: Number of bytes transferred to the l2 unit by the l1 unit.
  - display: RAW

- rop_l2_read_bytes

  - desc: Number of bytes read to the l2 unit by the rop unit.
  - display: RAW

- rop_l2_write_bytes

  - desc: Number of bytes written to the l2 unit by the rop unit.
  - display: RAW
