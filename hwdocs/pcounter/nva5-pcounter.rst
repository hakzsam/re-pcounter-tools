.. _nva5-graphics-counters:

======================
NVA5 Graphics Counters
======================

.. contents::

GPU signals
===========

gpu_busy/gpu_idle uses the QUAD event mode.

- gpu_busy = 100% - gpu_idle
- gpu_idle = 100% - gpu_busy

+-----------------------+-----------------+
|                       |      EVENT      |
+-------------------+---+----------+------+
| signal            |SET|    SRC   |  OP  |
+===================+===+==========+======+
| gpu_busy/gpu_idle | 1 |0xecececcb|0xaaaa|
+-------------------+---+----------+------+

IA signals
==========

All of the following signals use the QUAD event mode.

NOTE: vertex_attribute_count is equal to input_assembler_busy without
any reasons.

+----------------------------------+-----------------+----------+
|                                  |      EVENT      |    MUX   |
+------------------------------+---+----------+------+----------+
| signal                       |SET|    SRC   |  OP  | 0x400c0c |
+==============================+===+==========+======+==========+
| input_assembler_busy         | 1 |0x48495a5b|0xf888|0x00000001|
+------------------------------+---+----------+------+----------+
| input_assembler_waits_for_fb | 1 |0xececec51|0xaaaa|0x00000001|
+------------------------------+---+----------+------+----------+
| vertex_attribute_count       | 1 |0x48495a5b|0xf888|0x00000001|
+------------------------------+---+----------+------+----------+

GEOM signals
============

.. _geom-todo:
TODO
----

- find out why geom_vertex_in_count does not work on Nouveau

All of the following signals use the QUAD event mode except
geom_vertex_in_count which uses the QUAD/B4 event mode.

+------------------------------+-----------------+-----------------+----------------------+----------+
|                              |      START      |      EVENT      |         MPC          |   MUX    |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| signal                   |SET|    SRC   |  OP  |    SRC   |  OP  | PM_GROUP_SEL | UNK40 | 0x400c0c |
+==========================+===+==========+======+==========+======+==============+=======+==========+
| geom_busy                | 3 |    N/A   | N/A  |0x05040100|0xf888|  0x523e2a16  |  0x1  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_waits_for_shader    | 3 |          |      |0x05040100|0x22f2|  0x523e2a16  |  0x1  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_vertex_in_count     | 1 |0xec767574|0xffff|0xecececec|0x5555|     N/A      |  N/A  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_primitive_in_count  | 1 |          |      |0xececec4e|0xaaaa|     N/A      |  N/A  |0x00000001|
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_vertex_out_count    | 1 |          |      |0xececec85|0xaaaa|     N/A      |  N/A  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_primitive_out_count | 1 |          |      |0xececec84|0xaaaa|     N/A      |  N/A  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+

SO signals
==========

.. _so-todo:
TODO
----

- Write an OpenGL 3.0 program which uses the GL_EXT_transform_feedback for
  testing stream_out_busy.

stream_out_busy uses the QUAD event mode.

+----------------------------------+-----------------+
|                                  |      EVENT      |
+------------------------------+---+----------+------+
| signal                       |SET|    SRC   |  OP  |
+==============================+===+==========+======+
| stream_out_busy              | 1 |0xecec8786|0x8888|
+------------------------------+---+----------+------+

SETUP signals
=============

All of the following signals use the QUAD event mode.

+----------------------------------+-----------------+
|                                  |      EVENT      |
+------------------------------+---+----------+------+
| signal                       |SET|    SRC   |  OP  |
+==============================+===+==========+======+
| setup_primitive_count        | 1 |0xececece0|0xaaaa|
+------------------------------+---+----------+------+
| setup_point_count            | 1 |0xece7e6e1|0x8080|
+------------------------------+---+----------+------+
| setup_line_count             | 1 |0xece7e6e2|0x8080|
+------------------------------+---+----------+------+
| setup_triangle_count         | 1 |0xece7e6e3|0x8080|
+------------------------------+---+----------+------+
| setup_primitive_culled_count | 1 |0xecececb2|0xaaaa|
+------------------------------+---+----------+------+

VS signals
==========

.. _vs-todo:
TODO
----

- vertex_shader_busy
- vertex_shader_instruction_rate

GS signals
==========

.. _gs-todo:
TODO
----

- geometry_shader_busy
- geometry_shader_instruction_rate

PS signals
==========

.. _ps-todo:
TODO
----

- pixel_shader_busy
- pixel_shader_instruction_rate


SHADER signals
==============

All the following signals use the QUAD event mode.

.. _shader-todo:
TODO
----

- shader_waits_for_rop (set 3 should always depends on MPC???)

+------------------------------+-----------------+----------------------+
|                              |      EVENT      |         MPC          |
+--------------------------+---+----------+------+--------------+-------+
| signal                   |SET|    SRC   |  OP  | PM_GROUP_SEL | UNK40 |
+==========================+===+==========+======+==============+=======+
| shader_busy              | 3 |0x208c0400|0xfefe|  0x503c2814  |  0x1  |
+--------------------------+---+----------+------+--------------+-------+
| shader_waits_for_texture | 3 |0x01000302|0x22f2|     0x1      |  0x1  |
+--------------------------+---+----------+------+--------------+-------+
| shader_waits_for_geom    | 3 |0x07060302|0x22f2|  0x523e2a16  |  0x1  |
+--------------------------+---+----------+------+--------------+-------+
| shader_waits_for_rop     | 3 |0x2c2c0100|0x2222|     N/A      |  N/A  |
+--------------------------+---+----------+------+--------------+-------+

RASTER signals
==============

XXX: shaded_pixel_count uses the QUAD event mode.

The shaded_pixel_count uses 3 passes to compute its counter value. For each
pass, it uses a different mux for the register 0x408750. These values are
0x8000001c, 0x8000001d and 0x80000003.

.. _raster-todo:
TODO
----

- Find out how shaded_pixel_count is computed.
- rasterizer_tiles_killed_by_zcull_count
- rasterizer_tiles_in_count
- rasterizer_pixels_out_count

+--------------------------------------------+-----------------+-----------------+----------+----------+
|                                            |      START      |      EVENT      |   MUX    |    MUX   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| signal                                 |SET|    SRC   |  OP  |    SRC   |  OP  | 0x408750 | 0x402ca4 |
+========================================+===+==========+======+==========+======+==========+==========+
| shaded_pixel_count_0                   | 3 |     ?    |   ?  |0x2c0a0602|0xfefe| see above|     ?    |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| shaded_pixel_count_1                   | 3 |     ?    |   ?  |0x2c0b0703|0xfefe| see above|     ?    |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| shaded_pixel_count_2                   | 3 |     ?    |   ?  |0x2c090501|0xfefe| see above|     ?    |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| shaded_pixel_count_3                   | 3 |     ?    |   ?  |0x2c080400|0xfefe| see above|     ?    |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_tiles_killed_by_zcull_count | 1 |0x0a090807|0xffff|0x0c0becec|0xffff|    N/A   |    0x7   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_tiles_in_count              | 1 |0x0a090807|0xffff|0x0c0becec|0xffff|    N/A   |    N/A   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_pixels_out_count_0          | 2 |0x03020100|0xffff|0x05048c07|0xffff|0x80000016|    N/A   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_pixels_out_count_1          | 2 |    N/A   |  N/A |0x8c8c0607|0x8888|0x80000016|    N/A   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+

ROP signals
===========

.. _rop-todo:
TODO
----

- find out why rop_waits_for_fb does not work on Nouveau

All of the following signals use the QUAD event mode except
rop_samples_killed_by_earlyz_count and rop_samples_killed_by_latez_count
which use the QUAD/B6 event mode.

+----------------------------------------+-----------------+----------+
|                                        |      EVENT      |   MUX    |
+------------------------------------+---+----------+------+----------+
| signal                             |SET|    SRC   |  OP  | 0x408750 |
+====================================+===+==========+======+==========+
| rop_busy                           | 2 |0x05040302|0xf888|0x80000000|
+------------------------------------+---+----------+------+----------+
| rop_waits_for_fb                   | 2 |0x7e7f6667|0x22f2|    N/A   |
+------------------------------------+---+----------+------+----------+
| rop_waits_for_shader               | 2 |0xcccc0706|0x2222|0x80000000|
+------------------------------------+---+----------+------+----------+
| rop_samples_killed_by_earlyz_count | 2 |0x0504cc07|0xaaaa|0x8000001a|
+------------------------------------+---+----------+------+----------+
| rop_samples_killed_by_latez_count  | 2 |0x0504cc07|0xaaaa|0x8000001b|
+------------------------------------+---+----------+------+----------+
| rop_samples_in_count_0             | 2 |0xcccc0607|0x8888|0x80000015|
+------------------------------------+---+----------+------+----------+
| rop_samples_in_count_1             | 2 |0x0504cc07|0xaaaa|0x80000015|
+------------------------------------+---+----------+------+----------+

TEXTURE signals
===============

All the following signals use the QUAD event mode.

.. _texture-todo:
TODO
----

- find out how texture_sample_base_level_rate is computed
- texture_sample_average_level

+--------------------------------------+-----------------+----------------------+---------------------+
|                                      |      EVENT      |         MPC          |         MUXS        |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| signal                           |SET|    SRC   |  OP  | PM_GROUP_SEL | UNK34 | 0x408508 | 0x40851c |
+==================================+===+==========+======+==============+=======+==========+==========+
| texture_busy                     | 3 |0x2c050402|0xeaea|     0x201    |  0x1  |    N/A   |    N/A   |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_waits_for_fb             | 2 |0xcccccc3c|0xaaaa|      N/A     |  N/A  |set bit 11|set bit 11|
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_waits_for_shader         | 3 |0x2c2c0100|0x2222|      0x2     |  0x1  |    N/A   |    N/A   |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_sample_base_level_rate_0 | 2 |0x83828180|0x7fff|      N/A     |  N/A  |set bit 11|    N/A   |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_sample_base_level_rate_1 | 2 |0x83828180|0x0001|      N/A     |  N/A  |set bit 11|    N/A   |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_sample_average_level     | ? |     ?    |  ?   |      ?       |   ?   |     ?    |     ?    |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
