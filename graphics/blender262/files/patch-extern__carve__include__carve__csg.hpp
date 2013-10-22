--- ./extern/carve/include/carve/csg.hpp.orig	2013-10-23 01:32:05.351030120 +1030
+++ ./extern/carve/include/carve/csg.hpp	2013-10-23 01:34:15.554016830 +1030
@@ -174,34 +174,34 @@
 
       void groupIntersections();
 
-      void _generateVertexVertexIntersections(carve::mesh::MeshSet<3>::vertex_t *va,
-                                              carve::mesh::MeshSet<3>::edge_t *eb);
-      void generateVertexVertexIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                             const std::vector<carve::mesh::MeshSet<3>::face_t *> &b);
+      void _generateVertexVertexIntersections(meshset_t::vertex_t *va,
+                                              meshset_t::edge_t *eb);
+      void generateVertexVertexIntersections(meshset_t::face_t *a,
+                                             const std::vector<meshset_t::face_t *> &b);
 
-      void _generateVertexEdgeIntersections(carve::mesh::MeshSet<3>::vertex_t *va,
-                                            carve::mesh::MeshSet<3>::edge_t *eb);
-      void generateVertexEdgeIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                           const std::vector<carve::mesh::MeshSet<3>::face_t *> &b);
+      void _generateVertexEdgeIntersections(meshset_t::vertex_t *va,
+                                            meshset_t::edge_t *eb);
+      void generateVertexEdgeIntersections(meshset_t::face_t *a,
+                                           const std::vector<meshset_t::face_t *> &b);
 
-      void _generateEdgeEdgeIntersections(carve::mesh::MeshSet<3>::edge_t *ea,
-                                          carve::mesh::MeshSet<3>::edge_t *eb);
-      void generateEdgeEdgeIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                         const std::vector<carve::mesh::MeshSet<3>::face_t *> &b);
+      void _generateEdgeEdgeIntersections(meshset_t::edge_t *ea,
+                                          meshset_t::edge_t *eb);
+      void generateEdgeEdgeIntersections(meshset_t::face_t *a,
+                                         const std::vector<meshset_t::face_t *> &b);
 
-      void _generateVertexFaceIntersections(carve::mesh::MeshSet<3>::face_t *fa,
-                                            carve::mesh::MeshSet<3>::edge_t *eb);
-      void generateVertexFaceIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                           const std::vector<carve::mesh::MeshSet<3>::face_t *> &b);
+      void _generateVertexFaceIntersections(meshset_t::face_t *fa,
+                                            meshset_t::edge_t *eb);
+      void generateVertexFaceIntersections(meshset_t::face_t *a,
+                                           const std::vector<meshset_t::face_t *> &b);
 
-      void _generateEdgeFaceIntersections(carve::mesh::MeshSet<3>::face_t *fa,
-                                          carve::mesh::MeshSet<3>::edge_t *eb);
-      void generateEdgeFaceIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                         const std::vector<carve::mesh::MeshSet<3>::face_t *> &b);
+      void _generateEdgeFaceIntersections(meshset_t::face_t *fa,
+                                          meshset_t::edge_t *eb);
+      void generateEdgeFaceIntersections(meshset_t::face_t *a,
+                                         const std::vector<meshset_t::face_t *> &b);
 
-      void generateIntersectionCandidates(carve::mesh::MeshSet<3> *a,
+      void generateIntersectionCandidates(meshset_t *a,
                                           const face_rtree_t *a_node,
-                                          carve::mesh::MeshSet<3> *b,
+                                          meshset_t *b,
                                           const face_rtree_t *b_node,
                                           face_pairs_t &face_pairs,
                                           bool descend_a = true);
@@ -287,7 +287,7 @@
        * @param[out] out_loops A list of grouped face loops.
        */
       void groupFaceLoops(
-        carve::mesh::MeshSet<3> *src,
+        meshset_t *src,
         FaceLoopList &face_loops,
         const detail::LoopEdges &loop_edges,
         const V2Set &no_cross,
