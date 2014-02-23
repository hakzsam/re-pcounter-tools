.. _nva5-graphics-counters:

======================
NVA5 Graphics Counters
======================

!!! Only tested on NVA5 !!!

.. contents::

The GPU signals
===============

.. _gpu-todo:
TODO
----

.. _gpu_busy/gpu_idle:
gpu_busy/gpu_idle
-----------------

Time the GPU is busy/idle.

The IA signals
==============

.. _ia-todo:
TODO
----

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

.. _geom-todo:
TODO
----

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

.. _so-todo:
TODO
----

.. _stream-out-busy:
stream_out_busy
---------------

This unit manages the writing of vertices to the frame buffer when using
stream out. If a significant number of vertices are written, this can become a
bottleneck.

The SETUP signals
=================

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

The GS signals
==============

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

The PS signals
==============

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

The SHADER signals
==================

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

The RASTER signals
==================

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

The ROP signals
===============

.. _rop-todo:
TODO
----

.. _rop-busy:
rop_busy
--------

Time the ROP unit is busy.

.. _rop-waits-for-fb:
rop_waits_for_fb
----------------

Time the ROP unit is stalled waiting for the FB unit.

.. _rop-waits-for-shader:
rop_waits_for_shader
--------------------

Time the ROP unit is stalled waiting for the shader unit.

.. _rop-samples-killed-by-earlyz-count:
rop_samples_killed_by_earlyz_count
------------------------------

Count of samples killed by the early-z stage.

.. _rop-samples-killed-by-latez-count:
rop_samples_killed_by_latez_count
-----------------------------

Count of samples killed by the late-z stage.

.. _rop-samples-in-count:
rop_samples_in_count
--------------------

Number of real samples (generated from pixels output by the rasterizer) seen
by the ROP unit.

The TEXTURE signals
===================

.. _texture-todo:
TODO
----

.. _texture-busy:
texture_busy
------------

Time the texture unit is busy.

.. _texture-waits-for-fb:
texture_waits_for_fb
--------------------

Time the texture unit is stalled waiting for the FB unit.

.. _texture-waits-for-shader:
texture_waits_for_shader
------------------------

Time the texture unit is stalled waiting for the shader unit.

.. _texture-sample-base-level-rate:
texture_sample_base_level_rate
------------------------------

Percentage of texture samples which source the base texture level.

.. _texture-sample-average-level:
texture_sample_average_level
----------------------------

Across all texture samples, the average LOD sourced.
