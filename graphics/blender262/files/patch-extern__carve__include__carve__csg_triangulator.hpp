--- ./extern/carve/include/carve/csg_triangulator.hpp.orig	2013-10-23 01:36:28.671018087 +1030
+++ ./extern/carve/include/carve/csg_triangulator.hpp	2013-10-23 01:36:41.384018262 +1030
@@ -174,7 +174,7 @@
 
       double scoreQuad(edge_map_t::iterator i, edge_map_t &edge_map) {
         if (!(*i).second.first || !(*i).second.second) return -1;
-        return 0;
+        return -1;
       }
 
       carve::mesh::MeshSet<3>::face_t *mergeQuad(edge_map_t::iterator i, edge_map_t &edge_map) {
