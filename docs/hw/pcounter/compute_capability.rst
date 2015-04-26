.. _compute-capability:

==================
Compute Capability
==================

.. contents::

Tesla
=====

======================== ===== =====
signal                    1.1   1.2
======================== ===== =====
branch                     Y     Y
cta_launched               Y     Y
divergent_branch           Y     Y
gld_coherent               Y     Y
gld_incoherent             Y     Y
gst_coherent               Y     Y
gst_incoherent             Y     Y
instructions               Y     Y
local_load                 Y     Y
local_store                Y     Y
prof_trigger_00            Y     Y
prof_trigger_01            Y     Y
prof_trigger_02            Y     Y
prof_trigger_03            Y     Y
prof_trigger_04            Y     Y
prof_trigger_05            Y     Y
prof_trigger_06            Y     Y
prof_trigger_07            Y     Y
sm_cta_launched            Y     Y
tex_cache_hit              Y     Y
tex_cache_miss             Y     Y
warp_serialize             Y     Y
gld_128b                   N     Y
gld_32b                    N     Y
gld_64b                    N     Y
gld_request                N     Y
gld_total                  N     Y
gst_128b                   N     Y
gst_32b                    N     Y
gst_64b                    N     Y
gst_request                N     Y
gst_total                  N     Y
======================== ===== =====

Fermi
=====

===================================== ===== ===== ===== ===== ===== ===== ===== ===== =====
event                                 GF100 GF104 GF106 GF108 GF110 GF114 GF116 GF117 GF119
===================================== ===== ===== ===== ===== ===== ===== ===== ===== =====
active_cycles                           Y     Y     ?     Y     Y     Y     Y     ?     Y
active_warps                            Y     Y     ?     Y     Y     Y     Y     ?     Y
atom_count                              Y     Y     ?     Y     Y     Y     Y     ?     Y
branch                                  Y     Y     ?     Y     Y     Y     Y     ?     Y
divergent_branch                        Y     Y     ?     Y     Y     Y     Y     ?     Y
elapsed_cycles_sm                       Y     Y     ?     N     Y     Y     Y     ?     Y
fb_subp0_read_sectors                   Y     Y     ?     N     Y     Y     Y     ?     Y
fb_subp0_write_sectors                  Y     Y     ?     N     Y     Y     Y     ?     Y
fb_subp1_read_sectors                   Y     Y     ?     N     Y     Y     Y     ?     Y
fb_subp1_write_sectors                  Y     Y     ?     N     Y     Y     Y     ?     Y
fb0_subp0_read_sectors                  N     N     ?     Y     N     N     N     ?     N
fb0_subp0_write_sectors                 N     N     ?     Y     N     N     N     ?     N
fb0_subp1_read_sectors                  N     N     ?     Y     N     N     N     ?     N
fb0_subp1_write_sectors                 N     N     ?     Y     N     N     N     ?     N
fb1_subp0_read_sectors                  N     N     ?     Y     N     N     N     ?     N
fb1_subp0_write_sectors                 N     N     ?     Y     N     N     N     ?     N
fb1_subp1_read_sectors                  N     N     ?     Y     N     N     N     ?     N
fb1_subp1_write_sectors                 N     N     ?     Y     N     N     N     ?     N
gld_inst_128bit                         Y     Y     ?     Y     Y     Y     Y     ?     Y
gld_inst_16bit                          Y     Y     ?     Y     Y     Y     Y     ?     Y
gld_inst_32bit                          Y     Y     ?     Y     Y     Y     Y     ?     Y
gld_inst_64bit                          Y     Y     ?     Y     Y     Y     Y     ?     Y
gld_inst_8bit                           Y     Y     ?     Y     Y     Y     Y     ?     Y
gld_request                             Y     Y     ?     Y     Y     Y     Y     ?     Y
global_store_transaction                Y     Y     ?     Y     Y     Y     Y     ?     Y
gred_count                              Y     Y     ?     Y     Y     Y     Y     ?     Y
gst_inst_128bit                         Y     Y     ?     Y     Y     Y     Y     ?     Y
gst_inst_16bit                          Y     Y     ?     Y     Y     Y     Y     ?     Y
gst_inst_32bit                          Y     Y     ?     Y     Y     Y     Y     ?     Y
gst_inst_64bit                          Y     Y     ?     Y     Y     Y     Y     ?     Y
gst_inst_8bit                           Y     Y     ?     Y     Y     Y     Y     ?     Y
gst_request                             Y     Y     ?     Y     Y     Y     Y     ?     Y
inst_executed                           Y     Y     ?     Y     Y     Y     Y     ?     Y
inst_issued                             Y     N     ?     N     Y     N     N     ?     N
inst_issued1_0                          N     Y     ?     Y     N     Y     Y     ?     Y
inst_issued1_1                          N     Y     ?     Y     N     Y     Y     ?     Y
inst_issued2_0                          N     Y     ?     Y     N     Y     Y     ?     Y
inst_issued2_1                          N     Y     ?     Y     N     Y     Y     ?     Y
l1_global_load_hit                      Y     Y     ?     Y     Y     Y     Y     ?     Y
l1_global_load_miss                     Y     Y     ?     Y     Y     Y     Y     ?     Y
l1_local_load_hit                       Y     Y     ?     Y     Y     Y     Y     ?     Y
l1_local_load_miss                      Y     Y     ?     Y     Y     Y     Y     ?     Y
l1_local_store_hit                      Y     Y     ?     Y     Y     Y     Y     ?     Y
l1_local_store_miss                     Y     Y     ?     Y     Y     Y     Y     ?     Y
l1_shared_bank_conflict                 Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_read_hit_sectors               Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_read_sector_misses             Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_read_sector_queries            Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_read_sysmem_sector_queries     Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_read_tex_hit_sectors           Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_read_tex_sector_queries        Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_total_read_sector_queries      Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_total_write_sector_queries     Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_write_sector_misses            Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_write_sector_queries           Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp0_write_sysmem_sector_queries    Y     Y     ?     Y     Y     Y     Y     ?     Y
l2_subp1_read_hit_sectors               Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_read_sector_misses             Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_read_sector_queries            Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_read_sysmem_sector_queries     Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_read_tex_hit_sectors           Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_read_tex_sector_queries        Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_total_read_sector_queries      Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_total_write_sector_queries     Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_write_sector_misses            Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_write_sector_queries           Y     Y     ?     Y     Y     Y     Y     ?     N
l2_subp1_write_sysmem_sector_queries    Y     Y     ?     Y     Y     Y     Y     ?     N
local_load                              Y     Y     ?     Y     Y     Y     Y     ?     Y
local_store                             Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_00                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_01                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_02                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_03                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_04                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_05                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_06                         Y     Y     ?     Y     Y     Y     Y     ?     Y
prof_trigger_07                         Y     Y     ?     Y     Y     Y     Y     ?     Y
shared_load                             Y     Y     ?     Y     Y     Y     Y     ?     Y
shared_store                            Y     Y     ?     Y     Y     Y     Y     ?     Y
sm_cta_launched                         Y     Y     ?     Y     Y     Y     Y     ?     Y
tex0_cache_sector_misses                Y     Y     ?     Y     Y     Y     Y     ?     Y
tex0_cache_sector_queries               Y     Y     ?     Y     Y     Y     Y     ?     Y
tex1_cache_sector_misses                N     Y     ?     Y     N     Y     Y     ?     Y
tex1_cache_sector_queries               N     Y     ?     Y     N     Y     Y     ?     Y
thread_inst_executed_0                  Y     Y     ?     Y     Y     Y     Y     ?     Y
thread_inst_executed_1                  Y     Y     ?     Y     Y     Y     Y     ?     Y
thread_inst_executed_2                  N     Y     ?     Y     N     Y     Y     ?     Y
thread_inst_executed_3                  N     Y     ?     Y     N     Y     Y     ?     Y
threads_launched                        Y     Y     ?     Y     Y     Y     Y     ?     Y
uncached_global_load_transaction        Y     Y     ?     Y     Y     Y     Y     ?     Y
warps_launched                          Y     Y     ?     Y     Y     Y     Y     ?     Y
===================================== ===== ===== ===== ===== ===== ===== ===== ===== =====
