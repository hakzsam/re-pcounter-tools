.. _gf100-gpu-hardware-events:

=========================
GF100 GPU Hardware events
=========================

.. contents::

All the events are exposed by NVIDIA Perfkit on Windows.

- crop_busy

  - desc: Time the crop unit is busy
  - display: RATIO
  - domain: 11

- fb_read_req_subp2

  - desc: Number of read requests sent to the DRAM subpartition-0
  - display: RAW
  - domain: 5

- fb_read_req_subp3

  - desc: Number of read requests sent to the DRAM subpartition-1
  - display: RAW
  - domain: 5

- fb_subp0_read_sectors

  - desc: Sector reads from the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_subp0_write_sectors

  - desc: Sector writes to the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_subp1_read_sectors

  - desc: Sector reads from the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_subp1_write_sectors

  - desc: Sector writes to the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_write_req_subp2

  - desc: Number of write requests sent to the DRAM subpartition-0
  - display: RAW
  - domain: 5

- fb_write_req_subp3

  - desc: Number of write requests sent to the DRAM subpartition-1
  - display: RAW
  - domain: 5

- geom_busy

  - desc: Time the geom unit was busy
  - display: RATIO
  - domain: 18

- gpu_idle

  - desc: Time the graphics portion of the chip is idle.
  - display: RATIO
  - domain: 18

- l1_local_load_transactions_miss

  - desc: Local load transactions that miss in the L1 cache by this VSM. A transaction is 128 bytes. Increments by 0-1 per cycle.
  - display: RAW
  - domain: 1

- l2_slice0_read_sectors_tex

  - desc: Sector reads from TEX to L2 cache in the given slice and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- l2_slice1_read_sectors_tex

  - desc: Sector reads from TEX to L2 cache in the given slice and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- shader_busy
  - desc: Time the shader unit is busy

  - display: RATIO
  - domain: 1

- sm_instruction_count_domain

  - desc: count the number ds instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_geometry

  - desc: count the number gs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_hull

  - desc: count the number hs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_pixel

  - desc: count the number ps instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_vertex

  - desc: count the number vs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- tex0_bank_conflicts

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW
  - domain: 1

- tex0_cache_sector_misses

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex0_cache_sector_queries

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex0_cache_texel_queries

  - desc: Number of texture cache queries (32b each request)
  - display: RAW
  - domain: 1

- tex1_bank_conflicts

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW
  - domain: 1

- tex1_cache_sector_misses

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex1_cache_sector_queries

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- texture_busy

  - desc: Time the texture unit is busy
  - display: RATIO
  - domain: 1

- warps_launched

  - desc: Warps launched by this VSM. Increments by 1 per warp launched.
  - display: RAW
  - domain: 1

- zrop_busy

  - desc: Time the zrop unit is busy
  - display: RATIO
  - domain: 11

- fb_read_req_subp2_fb0

  - desc: Number of read requests sent to the DRAM subpartition-0
  - display: RAW
  - domain: 5

- fb_read_req_subp3_fb0

  - desc: Number of read requests sent to the DRAM subpartition-1
  - display: RAW
  - domain: 5

- fb_subp0_read_sectors_fb0

  - desc: Sector reads from the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_subp0_write_sectors_fb0

  - desc: Sector writes to the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_subp1_read_sectors_fb0

  - desc: Sector reads from the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_subp1_write_sectors_fb0

  - desc: Sector writes to the given subpartition and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- fb_write_req_subp2_fb0

  - desc: Number of write requests sent to the DRAM subpartition-0
  - display: RAW
  - domain: 5

- fb_write_req_subp3_fb0

  - desc: Number of write requests sent to the DRAM subpartition-1
  - display: RAW
  - domain: 5

- l1_local_load_transactions_miss_vsm0

  - desc: Local load transactions that miss in the L1 cache by this VSM. A transaction is 128 bytes. Increments by 0-1 per cycle.
  - display: RAW
  - domain: 1

- l1_local_load_transactions_miss_vsm1

  - desc: Local load transactions that miss in the L1 cache by this VSM. A transaction is 128 bytes. Increments by 0-1 per cycle.
  - display: RAW
  - domain: 1

- l2_slice0_read_sectors_tex_fb0

  - desc: Sector reads from TEX to L2 cache in the given slice and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- l2_slice1_read_sectors_tex_fb0

  - desc: Sector reads from TEX to L2 cache in the given slice and FB partition. A sector is 32 bytes.
  - display: RAW
  - domain: 5

- sm_instruction_count_domain_vsm0

  - desc: count the number ds instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_domain_vsm1

  - desc: count the number ds instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_geometry_vsm0

  - desc: count the number gs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_geometry_vsm1

  - desc: count the number gs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_hull_vsm0

  - desc: count the number hs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_hull_vsm1

  - desc: count the number hs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_pixel_vsm0

  - desc: count the number ps instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_pixel_vsm1

  - desc: count the number ps instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_vertex_vsm0

  - desc: count the number vs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- sm_instruction_count_vertex_vsm1

  - desc: count the number vs instructions executed in GPC0.TPC0.SM
  - display: RAW
  - domain: 1

- tex0_bank_conflicts_gpc0_tpc0

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW
  - domain: 1

- tex0_bank_conflicts_gpc0_tpc1

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW
  - domain: 1

- tex0_cache_sector_misses_gpc0_tpc0

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex0_cache_sector_misses_gpc0_tpc1

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex0_cache_sector_queries_gpc0_tpc0

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex0_cache_sector_queries_gpc0_tpc1

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex1_bank_conflicts_gpc0_tpc0

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW
  - domain: 1

- tex1_bank_conflicts_gpc0_tpc1

  - desc: Texture bank conflicts accurred while accessing data from the given texture unit in the VTPC.
  - display: RAW
  - domain: 1

- tex1_cache_sector_misses_gpc0_tpc0

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex1_cache_sector_misses_gpc0_tpc1

  - desc: Sector texture cache misses in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex1_cache_sector_queries_gpc0_tpc0

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- tex1_cache_sector_queries_gpc0_tpc1

  - desc: Sector texture cache requests in the given texture unit in the VTPC. A sector is 32 bytes.
  - display: RAW
  - domain: 1

- warps_launched_vsm0

  - desc: Warps launched by this VSM. Increments by 1 per warp launched.
  - display: RAW
  - domain: 1

- warps_launched_vsm1

  - desc: Warps launched by this VSM. Increments by 1 per warp launched.
  - display: RAW
  - domain: 1

- gpu_busy

  - desc: GPU is Busy
  - display: RATIO
  - domain: 0

- vertex_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to vertex shader threads
  - display: RAW
  - domain: 0

- hull_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to hull shader threads
  - display: RAW
  - domain: 0

- domain_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to domain shader threads
  - display: RAW
  - domain: 0

- geometry_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to geometry shader threads
  - display: RAW
  - domain: 0

- pixel_shader_instruction_rate

  - desc: Percentage of shader instructions belonging to pixel shader threads
  - display: RAW
  - domain: 0

- shaded_pixel_count

  - desc: Number of rasterized pixels sent to the shading units.
  - display: RAW
  - domain: 0

- setup_primitive_count

  - desc: Count of primitives seen by the setup unit.
  - display: RAW
  - domain: 0

- rop_busy

  - desc: Time the ROP unit is busy.
  - display: RATIO
  - domain: 0

- ia_requests

  - desc: Number of Input Assembler requests.
  - display: RAW
  - domain: 0

- ia_l2_read_bytes

  - desc: Number of bytes returned from L2 to the Input Assembler.
  - display: RAW
  - domain: 0

- shd_tex_requests

  - desc: Number of texel read requests from the shader unit.
  - display: RAW
  - domain: 0

- shd_tex_read_bytes

  - desc: Number of bytes read from the tex unit by the shader unit.
  - display: RAW
  - domain: 0

- shd_l1_requests

  - desc: Number of l1 requests from the shader unit.
  - display: RAW
  - domain: 0

- shd_l1_read_bytes

  - desc: Number of bytes transferred from the l1 unit by the shader unit.
  - display: RAW
  - domain: 0

- stream_out_bytes

  - desc: Number of bytes streamed out.
  - display: RAW
  - domain: 0

- tex_l2_requests

  - desc: Number of l2 read requests from the texture unit.
  - display: RAW
  - domain: 0

- tex_l2_read_bytes

  - desc: Number of bytes read from the l2 unit from the texture unit.
  - display: RAW
  - domain: 0

- l1_l2_requests

  - desc: Number of l2 requests from the l1 unit.
  - display: RAW
  - domain: 0

- l1_l2_bytes

  - desc: Number of bytes transferred to the l2 unit by the l1 unit.
  - display: RAW
  - domain: 0

- rop_l2_read_bytes

  - desc: Number of bytes read to the l2 unit by the rop unit.
  - display: RAW
  - domain: 0

- rop_l2_write_bytes

  - desc: Number of bytes written to the l2 unit by the rop unit.
  - display: RAW
  - domain: 0

- l2_fb_read_bytes

  - desc: Number of fb bytes read from the l2 unit.
  - display: RAW
  - domain: 0

- l2_fb_write_bytes

  - desc: Number of fb bytes written by the l2 unit.
  - display: RAW
  - domain: 0
