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

.. _vertex-shader-busy:
vertex_shader_busy
------------------

This is the % of time that shader unit 0 was busy scaled by the ratio of vertex
shader instructions to all shader type instructions
(or vertex_shader_instruction_rate). If this value is high but, for instance,
pixel_shader_busy is slow, it is an indication that you may be verte/geometry
bound. This can be from geometry that is too detailed or even from vertex
programs that are overly complex and need to be simplified. In addition, taking
advantage of the post T&L cache (by reducing vertex size and using indexed
primitives) can prevent processing the same vertices multiple times.

.. _vertex-shader-instruction-rate:
vertex_shader_instruction_rate
------------------------------

The % of all shader instructions seen on the first SM unit that were executing
vertex shaders.

GS signals
==========

.. _gs-todo:
TODO
----

.. _geometry-shader-busy:
geometry_shader_busy
--------------------

This is the % of time that shader unit 0 was busy scaled by the ratio of
geometry shader instructions to all shader type instructions (or
geometry_shader_intruction_rate).

.. _geometry-shader-instruction-rate:
geometry_shader_instruction_rate
--------------------------------

The % of all shader instructions seen on the first SM unit that were executing
geometry shaders.

PS signals
==========

.. _ps-todo:
TODO
----

.. _pixel-shader-busy:
pixel_shader_busy
-----------------

This is the % of time that shader unit 0 was busy scaled by the ratio of pixel
shader instructions to all shader type instructions (or
pixel_shader_instruction_rate). This can give you an indication of if you are
pixel bound, which can happen in high resolution settings or when pixel
programs are very complex.

.. _pixel-shader-instruction-rate:
pixel_shader_instruction_rate
-----------------------------

The % of all shader instructions seen on the first SM unit that were executing
pixel shaders.

SHADER signals
==============

.. _shader-todo:
TODO
----

.. _shader-busy:
shader_busy
-----------

Time the shader unit is busy.

.. _shader-waits-for-texture:
shader_waits_for_texture
------------------------

Time the shader unit is stalled waiting for the texture unit.

.. _shader-waits-for-geom:
shader_waits_for_geom
---------------------

Time the shader unit is stalled waiting for the geometry unit.

.. _shader-waits-for-rop:
shader_waits_for_rop
--------------------

Time the shader unit is stalled waiting for the ROP unit.

RASTER signals
==============

.. _raster-todo:
TODO
----

.. _shaded-pixel-count:
shaded_pixel_count
------------------

Counts the number of pixels generated by the rasterizer and sent to the pixel
shader units.

.. _rasterizer-tiles-killed-by-zcull-count:
rasterizer_tiles_killed_by_zcull_count
-----------------------------------

Count of tiles (each of which contain 1-8 pixels) killed by the zcull unit.

.. _rasterizer-tiles-in-count:
rasterizer_tiles_in_count
-------------------------

Count of tiles (each of which contain 1-8 pixels) seen by the rasterizer stage.

.. _rasterizer-pixels-out-count:
rasterizer_pixels_out_count
---------------------------

Number of pixels generated by the rasterizer.

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

- texture_sample_base_level_rate
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
| texture_sample_base_level_rate_0 | ? |     ?    |  ?   |      ?       |   ?   |     ?    |     ?    |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_sample_base_level_rate_1 | ? |     ?    |  ?   |      ?       |   ?   |     ?    |     ?    |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
| texture_sample_average_level     | ? |     ?    |  ?   |      ?       |   ?   |     ?    |     ?    |
+----------------------------------+---+----------+------+--------------+-------+----------+----------+
