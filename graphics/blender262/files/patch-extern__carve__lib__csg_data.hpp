--- ./extern/carve/lib/csg_data.hpp.orig	2013-10-23 01:51:16.547022303 +1030
+++ ./extern/carve/lib/csg_data.hpp	2013-10-23 01:51:20.805018033 +1030
@@ -30,7 +30,7 @@
   VVMap vmap;
 
   // map from intersected edge to intersection points.
-  EVSMap emap;
+  EIntMap emap;
 
   // map from intersected face to intersection points.
   FVSMap fmap;
@@ -39,7 +39,7 @@
   VFSMap fmap_rev;
 
   // created by divideEdges().
-  // holds, for each edge, a 
+  // holds, for each edge, an ordered vector of inserted vertices.
   EVVMap divided_edges;
 
   // created by faceSplitEdges.
