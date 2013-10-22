--- ./extern/carve/lib/csg_detail.hpp.orig	2013-10-23 01:51:42.367016853 +1030
+++ ./extern/carve/lib/csg_detail.hpp	2013-10-23 01:51:50.553016914 +1030
@@ -24,30 +24,32 @@
 namespace carve {
   namespace csg {
     namespace detail {
+      typedef std::map<carve::mesh::MeshSet<3>::vertex_t *,
+                       std::set<std::pair<carve::mesh::MeshSet<3>::face_t *, double> > > EdgeIntInfo;
 
-    typedef std::unordered_set<carve::mesh::MeshSet<3>::vertex_t *> VSet;
-    typedef std::unordered_set<carve::mesh::MeshSet<3>::face_t *> FSet;
+      typedef std::unordered_set<carve::mesh::MeshSet<3>::vertex_t *> VSet;
+      typedef std::unordered_set<carve::mesh::MeshSet<3>::face_t *> FSet;
 
-    typedef std::set<carve::mesh::MeshSet<3>::vertex_t *> VSetSmall;
-    typedef std::set<csg::V2> V2SetSmall;
-    typedef std::set<carve::mesh::MeshSet<3>::face_t *> FSetSmall;
+      typedef std::set<carve::mesh::MeshSet<3>::vertex_t *> VSetSmall;
+      typedef std::set<csg::V2> V2SetSmall;
+      typedef std::set<carve::mesh::MeshSet<3>::face_t *> FSetSmall;
 
-    typedef std::unordered_map<carve::mesh::MeshSet<3>::vertex_t *, VSetSmall> VVSMap;
-    typedef std::unordered_map<carve::mesh::MeshSet<3>::edge_t *, VSetSmall> EVSMap;
-    typedef std::unordered_map<carve::mesh::MeshSet<3>::face_t *, VSetSmall> FVSMap;
+      typedef std::unordered_map<carve::mesh::MeshSet<3>::vertex_t *, VSetSmall> VVSMap;
+      typedef std::unordered_map<carve::mesh::MeshSet<3>::edge_t *, EdgeIntInfo> EIntMap;
+      typedef std::unordered_map<carve::mesh::MeshSet<3>::face_t *, VSetSmall> FVSMap;
 
-    typedef std::unordered_map<carve::mesh::MeshSet<3>::vertex_t *, FSetSmall> VFSMap;
-    typedef std::unordered_map<carve::mesh::MeshSet<3>::face_t *, V2SetSmall> FV2SMap;
+      typedef std::unordered_map<carve::mesh::MeshSet<3>::vertex_t *, FSetSmall> VFSMap;
+      typedef std::unordered_map<carve::mesh::MeshSet<3>::face_t *, V2SetSmall> FV2SMap;
 
-    typedef std::unordered_map<
-      carve::mesh::MeshSet<3>::edge_t *,
-      std::vector<carve::mesh::MeshSet<3>::vertex_t *> > EVVMap;
+      typedef std::unordered_map<
+        carve::mesh::MeshSet<3>::edge_t *,
+        std::vector<carve::mesh::MeshSet<3>::vertex_t *> > EVVMap;
 
       typedef std::unordered_map<carve::mesh::MeshSet<3>::vertex_t *,
                                  std::vector<carve::mesh::MeshSet<3>::edge_t *> > VEVecMap;
 
 
-     class LoopEdges : public std::unordered_map<V2, std::list<FaceLoop *> > {
+      class LoopEdges : public std::unordered_map<V2, std::list<FaceLoop *> > {
         typedef std::unordered_map<V2, std::list<FaceLoop *> > super;
 
       public:
@@ -69,3 +71,4 @@
   }
   return o;
 }
+
