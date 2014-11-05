.. _compute-capability:

==================
Compute Capability
==================

.. contents::

Tesla:

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

Fermi:

===================================== =====
signal                                 2.0
===================================== =====
active_cycles                           Y
active_warps                            Y
atom_count                              Y
branch                                  Y
divergent_branch                        Y
elapsed_cycles_sm                       Y
fb_subp0_read_sectors                   Y
fb_subp0_write_sectors                  Y
fb_subp1_read_sectors                   Y
fb_subp1_write_sectors                  Y
gld_inst_128bit                         Y
gld_inst_16bit                          Y
gld_inst_32bit                          Y
gld_inst_64bit                          Y
gld_inst_8bit                           Y
gld_request                             Y
global_store_transaction                Y
gred_count                              Y
gst_inst_128bit                         Y
gst_inst_16bit                          Y
gst_inst_32bit                          Y
gst_inst_64bit                          Y
gst_inst_8bit                           Y
gst_request                             Y
inst_executed                           Y
inst_issued                             Y
l1_global_load_hit                      Y
l1_global_load_miss                     Y
l1_local_load_hit                       Y
l1_local_load_miss                      Y
l1_local_store_hit                      Y
l1_local_store_miss                     Y
l1_shared_bank_conflict                 Y
l2_subp0_read_hit_sectors               Y
l2_subp0_read_sector_misses             Y
l2_subp0_read_sector_queries            Y
l2_subp0_read_sysmem_sector_queries     Y
l2_subp0_read_tex_hit_sectors           Y
l2_subp0_read_tex_sector_queries        Y
l2_subp0_total_read_sector_queries      Y
l2_subp0_total_write_sector_queries     Y
l2_subp0_write_sector_misses            Y
l2_subp0_write_sector_queries           Y
l2_subp0_write_sysmem_sector_queries    Y
l2_subp1_read_hit_sectors               Y
l2_subp1_read_sector_misses             Y
l2_subp1_read_sector_queries            Y
l2_subp1_read_sysmem_sector_queries     Y
l2_subp1_read_tex_hit_sectors           Y
l2_subp1_read_tex_sector_queries        Y
l2_subp1_total_read_sector_queries      Y
l2_subp1_total_write_sector_queries     Y
l2_subp1_write_sector_misses            Y
l2_subp1_write_sector_queries           Y
l2_subp1_write_sysmem_sector_queries    Y
local_load                              Y
local_store                             Y
prof_trigger_00                         Y
prof_trigger_01                         Y
prof_trigger_02                         Y
prof_trigger_03                         Y
prof_trigger_04                         Y
prof_trigger_05                         Y
prof_trigger_06                         Y
prof_trigger_07                         Y
shared_load                             Y
shared_store                            Y
sm_cta_launched                         Y
tex0_cache_sector_misses                Y
tex0_cache_sector_queries               Y
thread_inst_executed_0                  Y
thread_inst_executed_1                  Y
threads_launched                        Y
uncached_global_load_transaction        Y
warps_launched                          Y
===================================== =====
