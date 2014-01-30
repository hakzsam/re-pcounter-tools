.. _nv50-graphics-counters:

======================
NV50 Graphics Counters
======================

!!! Only tested on NV86 and NV98 !!!

.. contents::

The IA signals
==============

All of the following signals use the single event mode.

NOTE: vertex_attribute_count is equal to input_assembler_busy without
any reasons.

+----------------------------------+-----------------+----------+
|                                  |      EVENT      |    MUX   |
+------------------------------+---+----------+------+----------+
| signal                       |SET|    SRC   |  OP  | 0x400c0c |
+==============================+===+==========+======+==========+
| input_assembler_busy         | 1 |0x68697d7e|0xf888|0x00000001|
+------------------------------+---+----------+------+----------+
| input_assembler_waits_for_fb | 1 |0x00000074|0xaaaa|0x00000001|
+------------------------------+---+----------+------+----------+
| vertex_attribute_count       | 1 |0x68697d7e|0xf888|0x00000001|
+------------------------------+---+----------+------+----------+

.. _input_assembler_busy:
input_assembler_busy
--------------------

The % of time the input assembler unit is busy. This is mainly impacted by both
the number of vertices processed as well as the size of the attributes on those
vertices. You can optimize this by reducing vertex size as much as possible and
using indexed primitives to take advantage of the vertex cache.

.. _input_assembler_waits_for_fb:
input_assembler_waits_for_fb:
-----------------------------

This is the amount of time the input assembler unit was waiting for data from
the frame buffer unit.

.. _vertex-attribute-count:
vertex_attribute_count
----------------------

The number of vertex attributes that are fetched and passed to the geometry
unit is returned in this counter. A large number of attributes (or unaligned
vertices) can hurt vertex cache performance and reduce the overall vertex
processing capabilities of the pipeline.

The GEOM signals
================

All of the following signals use the single event mode except
geom_vertex_in_count which uses the b4 event mode.

+------------------------------+-----------------+-----------------+----------------------+----------+
|                              |      START      |      EVENT      |         MPC          |   MUX    |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| signal                   |SET|    SRC   |  OP  |    SRC   |  OP  | PM_GROUP_SEL | UNK34 | 0x400c0c |
+==========================+===+==========+======+==========+======+==============+=======+==========+
| geom_busy                | 3 |          |      |0x03020100|0xf888|     0x3      |  0x1  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_waits_for_shader    | 3 |          |      |0x03020100|0x22f2|     0x3      |  0x1  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_vertex_in_count     | 1 |0xec767574|0xffff|0xecececec|0x5555|     N/A      |  N/A  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_primitive_in_count  | 1 |          |      |0x0000006e|0xaaaa|     N/A      |  N/A  |0x00000001|
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_vertex_out_count    | 1 |          |      |0x0000005d|0xaaaa|     N/A      |  N/A  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+
| geom_primitive_out_count | 1 |          |      |0x0000005c|0xaaaa|     N/A      |  N/A  |    N/A   |
+--------------------------+---+----------+------+----------+------+--------------+-------+----------+

.. _geom-busy:
geom_busy
---------

This measures the traffic from the unit that distributes vertex and geometry
work to the shader units for transforming the vertices. Draw calls with large
numbers of primitives (or many draw calls with small numbers of primitives) can
potentially cause this unit to become a bottleneck.

.. _geom-waits-for-shader:
geom_waits_for_shader
---------------------

The amount of time the geom unit spent waiting for the shader unit to be
ready to accept work.

.. _geom-vertex-in-count:
geom_vertex_in_count
--------------------

The number of vertices input to the geom unit.

.. _geom-primitive-in-count:
geom_primitive_in_count
-----------------------

The number of primitives input to the geom unit.

.. _geom-vertex-out-count:
geom_vertex_out_count
---------------------

The number of vertices coming out of the geom unit after any geometry shader
expansion.

.. _geom-primitive-out-count:
geom_primitive_out_count
------------------------

The number of primitives coming out the geom unit after any geometry shader
expansion.

The SO signals
==============

[XXX: Write an OpenGL 3.0 program which uses the GL_EXT_transform_feedback for
testing stream_out_busy]

stream_out_busy uses the single event mode.

+----------------------------------+-----------------+
|                                  |      EVENT      |
+------------------------------+---+----------+------+
| signal                       |SET|    SRC   |  OP  |
+==============================+===+==========+======+
| stream_out_busy              | 1 |0xecec5f5e|0x8888|
+------------------------------+---+----------+------+

.. _stream-out-busy:
stream_out_busy
---------------

This unit manages the writing of vertices to the frame buffer when using
stream out. If a significant number of vertices are written, this can become a
bottleneck.

The SETUP signals
=================
All of the following signals use the single event mode.

+----------------------------------+-----------------+
|                                  |      EVENT      |
+------------------------------+---+----------+------+
| signal                       |SET|    SRC   |  OP  |
+==============================+===+==========+======+
| setup_primitive_count        | 1 |0x000000d2|0xaaaa|
+------------------------------+---+----------+------+
| setup_point_count            | 1 |0xecd9d8d3|0x8080|
+------------------------------+---+----------+------+
| setup_line_count             | 1 |0xecd9d8d4|0x8080|
+------------------------------+---+----------+------+
| setup_triangle_count         | 1 |0xecd9d8d5|0x8080|
+------------------------------+---+----------+------+
| setup_primitive_culled_count | 1 |0x000000a4|0xaaaa|
+------------------------------+---+----------+------+

.. _setup-primitive-count:
setup_primitive_count
---------------------

Returns the number of primitives processed in the geometry subsystem. This
experiments counts points, lines and triangles. To count only triangles,
use the setup_triangle_count counter. Balance these counts with the number
of pixels being drawn to see if you could simplify your geometry and use
bump/displacement maps, for example.

.. _setup-point-count:
setup_point_count
-----------------

The number of points seen by the primitive setup unit (just before
rasterization).

.. _setup-line-count:
setup_line_count
----------------

The number of lines seen by the primitive setup unit (just before
rasterization).

.. _setup-triangle-count:
setup_triangle_count
--------------------

Returns the number of triangles processed in the geometry subsystem.

.. _setup-primitive-culled-count:
setup_primitive_culled_count
----------------------------

Returns the number of primitives culled in primitive setup. If you are
performing viewport culling, this gives you an indication of the accuracy
of the algorithm being used, and can give you and idea if you need to improves
this culling. This includes primitives culled when using backface culling.
Drawing a fully visible sphere on the screen should cull half of the triangles
if backface culling is turned on and all the triangles are ordered
consistently (CW or CCW).

The VS signals
==============

These signals are always on set 3.

[XXX: write me]

- vertex_shader_busy = vertex_shader_busy_ctr * shader_busy / shader_busy_ctr
- vertex_shader_instruction_rate = vertex_shader_busy_ctr * 100 / shader_busy_ctr

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

The GS signals
==============

[XXX: write me]

- geometry_shader_busy = geometry_shader_busy_ctr * shader_busy / shader_busy_ctr
- geometry_shader_instruction_rate = geometry_shader_busy_ctr * 100 / shader_busy_ctr

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

The PS signals
==============

[XXX: write me]

- pixel_shader_busy = pixel_shader_busy_ctr * shader_busy / shader_busy_ctr
- pixel_shader_instruction_rate = pixel_shader_busy_ctr * 100 / shader_busy_ctr

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

The SHADER signals
==================

All of the following signals use the single event mode.

[XXX: shader_busy and shader_waits_for_texture are strange on Nouveau...]

+------------------------------+-----------------+----------------------+
|                              |      EVENT      |         MPC          |
+--------------------------+---+----------+------+--------------+-------+
| signal                   |SET|    SRC   |  OP  | PM_GROUP_SEL | UNK34 |
+==========================+===+==========+======+==============+=======+
| shader_busy              | 3 |0x2c2c0400|0xeeee|     0x10     |  0x1  |
+--------------------------+---+----------+------+--------------+-------+
| shader_waits_for_texture | 3 |0x01000302|0x22f2|     0x10     |  0x1  |
+--------------------------+---+----------+------+--------------+-------+
| shader_waits_for_geom    | 3 |0x03020100|0x22f2|     0x4      |  0x1  |
+--------------------------+---+----------+------+--------------+-------+
| shader_waits_for_rop     | 3 |0x2c2c0100|0x2222|     0x5      |  0x1  |
+--------------------------+---+----------+------+--------------+-------+

.. _shader-busy:
shader_busy
-----------

This measures the how active the unified shader unit is running any type of
shader. If you couple this information with the various
shader_instruction_rate values you can get an idea for the workload the shader
unit has and which shader types to tune if the shader unit becomes a
bottleneck.

.. _shader-waits-for-texture:
shader_waits_for_texture
------------------------

This is the amount of time that the pixel shader unit was stalled waiting for
a texture fetch. Texture stalls usually happen if textures don't have mipmaps,
if a high level of anisotropic filtering is used, or if there is poor
coherency in accessing textures.

.. _shader-waits-for-geom:
shader_waits_for_geom
---------------------

This is the amount of time the shader unit spent waiting for the geom unit to
send work.

.. _shader-waits-for-rop:
shader_waits_for_rop
--------------------

This is the % of time that the pixel shader is stalled by the raster
operations unit (ROP), waiting to blend a pixel and write it to the frame
buffer. If the application is performing a lot of alpha blending, or event if
the application has a lot of overdraw (the same pixel being written multiple
times, unblended) this can be a performance bottleneck.

The RASTER signals
==================

All of the following signals use the B6 event mode except the
shaded_pixel_count which uses the single event mode.

+--------------------------------------------+-----------------+-----------------+----------+----------+
|                                            |      START      |      EVENT      |   MUX    |    MUX   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| signal                                 |SET|    SRC   |  OP  |    SRC   |  OP  | 0x408e50 | 0x402ca4 |
+========================================+===+==========+======+==========+======+==========+==========+
| shaded_pixel_count                     | 2 |    N/A   | N/A  |0x8c020100|0x0404|0x8000001d|    N/A   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_tiles_killed_by_zcull_count | 1 |0x0a090807|0xffff|0x0c0becec|0xffff|    N/A   |    0x7   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_tiles_in_count              | 1 |0x0a090807|0xffff|0x0c0becec|0xffff|    N/A   |    N/A   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+
| rasterizer_pixels_out_count            | 2 |0x08020100|0xffff|0x8c8c0607|0x8888|0x80000016|    N/A   |
+----------------------------------------+---+----------+------+----------+------+----------+----------+

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

The ROP signals
===============

All of the following signals use the single event mode except
rop_pixels_killed_earlyz_count and rop_pixels_killed_latez_count
which use the b6 event mode.

[XXX:
- Find out how to correctly test rop_waits_for_fb.
- Find out how to reproduce rop_samples_in_count.
]

+----------------------------------------+-----------------+-----------------+----------+
|                                        |      START      |      EVENT      |   MUX    |
+------------------------------------+---+----------+------+----------+------+----------+
| signal                             |SET|    SRC   |  OP  |    SRC   |  OP  | 0x408e50 |
+====================================+===+==========+======+==========+======+==========+
| rop_busy                           | 2 |          |      |0x05040302|0xf888|0x80000000|
+------------------------------------+---+----------+------+----------+------+----------+
| rop_waits_for_fb                   | 2 |          |      |0x46473233|0x22f2|0x00000000|
+------------------------------------+---+----------+------+----------+------+----------+
| rop_waits_for_shader               | 2 |          |      |0x8c8c0706|0x2222|0x80000000|
+------------------------------------+---+----------+------+----------+------+----------+
| rop_pixels_killed_earlyz_count     | 2 |0x03020100|0xffff|0x05048c07|0xffff|0x8000001a|
+------------------------------------+---+----------+------+----------+------+----------+
| rop_samples_killed_by_latez_count  | 2 |0x03020100|0xffff|0x05048c07|0xffff|0x8000001b|
+------------------------------------+---+----------+------+----------+------+----------+
| rop_samples_in_count               | ? |          |      |    ???   |   ?  |   ???    |
+------------------------------------+---+----------+------+----------+------+----------+

.. _rop-busy:
rop_busy
--------

% of time that the ROP unit is actively doing work. This can be high if alpha
blending is turned on, of overdraw is high, etc.

.. _rop-waits-for-fb:
rop_waits_for_fb
----------------

The amount of time the blending unit spent waiting for data from the frame
buffer unit. If blending is enabled and there is a lot of traffic here (since
this is a read/modify/write operation) this can become a bottleneck.

.. _rop-waits-for-shader:
rop_waits_for_shader
--------------------

This is a measurement of how often the blending unit was waiting on new work
(fragments to be placed into the render target). If the pixel shaders are
particularly expensive, the ROP unit could be starved waiting for results.

.. _rop-pixels-killed-earlyz-count:
rop_pixels_killed_earlyz_count
------------------------------

This returns the number of pixels that were killed in the early Z hardware.
This signal will give you an idea of, for instance, a Z only pass was
successful in setting up the depth buffer.

.. _rop-samples-killed-by-latez-count:
rop_samples_killed_by_latez_count
-----------------------------

This returns the number of pixels that were killed after the pixel shader ran.
This can happen if the early Z is unable cull the pixel because of an API
setup issue like changing the Z direction or modifying Z in the pixel shader.

.. _rop-samples-in-count:
rop_samples_in_count
--------------------

Number of real samples (generated from pixels output by the rasterizer) seen
by the ROP unit.

The TEXTURE signals
===================

All of the following signals use the single event mode.

[XXX: write me]
[XXX: Find out why texture_waits_for_fb doesn't work]

+------------------------------------+-----------------+----------------------+
|                                    |      EVENT      |         MPC          |
+--------------------------------+---+----------+------+--------------+-------+
| signal                         |SET|    SRC   |  OP  | PM_GROUP_SEL | UNK34 |
+================================+===+==========+======+==============+=======+
| texture_busy                   | 3 |0x2c050402|0xeaea|     0x1110   |  0x1  |
+--------------------------------+---+----------+------+--------------+-------+
| texture_waits_for_fb           | 2 |0x0000001c|0xaaaa|     0x0      |  0x0  |
+--------------------------------+---+----------+------+--------------+-------+
| texture_waits_for_shader       | 3 |0x2c2c0100|0x2222|     0x11     |  0x1  |
+--------------------------------+---+----------+------+--------------+-------+
| texture_sample_base_level_rate | ? |    ??    |  ??  |     ??       |  ??   |
+--------------------------------+---+----------+------+--------------+-------+
| texture_sample_average_level   | ? |    ??    |  ??  |     ??       |  ??   |
+--------------------------------+---+----------+------+--------------+-------+

.. _texture-busy:
texture_busy
------------

This is a measurement of how busy the texture unit is. This covers both time
spent sampling values from the frame buffer (through the texture cache) and
the time spent computing any filtering that is enabled (like bilinear or
anisotropic). Reducing both the number of taps and the filtering level will
help to reduce any bottleneck in the texture unit.

.. _texture-waits-for-fb:
texture_waits_for_fb
--------------------

This is the amount of time the texture unit spent waiting on samples to return
from the frame buffer unit. It is a potential indication of poor texture cache
utilization.

.. _texture-waits-for-shader:
texture_waits_for_shader
------------------------

This is the amount of time the texture unit spent waiting to send results to
the shader unit. If the queue between those units gets too full (because the
shader unit isn't ready to receive thoses values), this can become a
bottleneck.

.. _texture-sample-base-level-rate:
texture_sample_base_level_rate
------------------------------

The percentage of texture samples which read from the base texture level. This
can be useful to determine if your base texture level is too large and can be
reduced to the next mipmap level.

.. _texture-sample-average-level:
texture_sample_average_level
----------------------------

The average LOD sourced across all texture reads.
