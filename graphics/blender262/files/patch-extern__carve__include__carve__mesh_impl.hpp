--- ./extern/carve/include/carve/mesh_impl.hpp.orig	2013-10-23 01:43:52 UTC
+++ ./extern/carve/include/carve/mesh_impl.hpp
@@ -624,8 +624,7 @@
           CARVE_ASSERT(e->rev != NULL);
           e = e->rev->next;
           CARVE_ASSERT(e->v1() == emin->v1());
-          CARVE_ASSERT(e->v1()->v < e->v2()->v);
-          CARVE_ASSERT(e->v1()->v.x <= e->v2()->v.x);
+          CARVE_ASSERT(e->v1()->v <= e->v2()->v);
         } while (e != emin);
 
         double max_abs_x = 0.0;
@@ -677,7 +676,7 @@
 
     template<unsigned ndim>
     template<typename iter_t>
-    void Mesh<ndim>::create(iter_t begin, iter_t end, std::vector<Mesh<ndim> *> &meshes) {
+    void Mesh<ndim>::create(iter_t begin, iter_t end, std::vector<Mesh<ndim> *> &meshes, const MeshOptions &opts) {
       meshes.clear();
     }
 
@@ -685,15 +684,15 @@
 
     template<>
     template<typename iter_t>
-    void Mesh<3>::create(iter_t begin, iter_t end, std::vector<Mesh<3> *> &meshes) {
-      detail::FaceStitcher().create(begin, end, meshes);
+    void Mesh<3>::create(iter_t begin, iter_t end, std::vector<Mesh<3> *> &meshes, const MeshOptions &opts) {
+      detail::FaceStitcher(opts).create(begin, end, meshes);
     }
 
 
 
     template<unsigned ndim>
     template<typename iter_t>
-    void MeshSet<ndim>::_init_from_faces(iter_t begin, iter_t end) {
+    void MeshSet<ndim>::_init_from_faces(iter_t begin, iter_t end, const MeshOptions &opts) {
       typedef std::unordered_map<const vertex_t *, size_t> map_t;
       map_t vmap;
 
@@ -724,7 +723,7 @@
         } while (e != f->edge);
       }
 
-      mesh_t::create(begin, end, meshes);
+      mesh_t::create(begin, end, meshes, opts);
 
       for (size_t i = 0; i < meshes.size(); ++i) {
         meshes[i]->meshset = this;
@@ -736,7 +735,8 @@
     template<unsigned ndim>
     MeshSet<ndim>::MeshSet(const std::vector<typename MeshSet<ndim>::vertex_t::vector_t> &points,
                            size_t n_faces,
-                           const std::vector<int> &face_indices) {
+                           const std::vector<int> &face_indices,
+                           const MeshOptions &opts) {
       vertex_storage.reserve(points.size());
       std::vector<face_t *> faces;
       faces.reserve(n_faces);
@@ -756,7 +756,7 @@
         faces.push_back(new face_t(v.begin(), v.end()));
       }
       CARVE_ASSERT(p == face_indices.size());
-      mesh_t::create(faces.begin(), faces.end(), meshes);
+      mesh_t::create(faces.begin(), faces.end(), meshes, opts);
 
       for (size_t i = 0; i < meshes.size(); ++i) {
         meshes[i]->meshset = this;
@@ -766,15 +766,15 @@
 
 
     template<unsigned ndim>
-    MeshSet<ndim>::MeshSet(std::vector<face_t *> &faces) {
-      _init_from_faces(faces.begin(), faces.end());
+    MeshSet<ndim>::MeshSet(std::vector<face_t *> &faces, const MeshOptions &opts) {
+      _init_from_faces(faces.begin(), faces.end(), opts);
     }
 
 
 
     template<unsigned ndim>
-    MeshSet<ndim>::MeshSet(std::list<face_t *> &faces) {
-      _init_from_faces(faces.begin(), faces.end());
+    MeshSet<ndim>::MeshSet(std::list<face_t *> &faces, const MeshOptions &opts) {
+      _init_from_faces(faces.begin(), faces.end(), opts);
     }
 
 
@@ -1011,5 +1011,42 @@
       vertex_storage.swap(vout);
     }
 
+
+
+    template<unsigned ndim>
+    void MeshSet<ndim>::separateMeshes() {
+      size_t n;
+      typedef std::unordered_map<std::pair<mesh_t *, vertex_t *>, vertex_t *> vmap_t;
+      vmap_t vmap;
+      typename vmap_t::iterator vmap_iter;
+
+      for (face_iter i = faceBegin(); i != faceEnd(); ++i) {
+        face_t *f = *i;
+        for (typename face_t::edge_iter_t j = f->begin(); j != f->end(); ++j) {
+          edge_t &e = *j;
+          vmap[std::make_pair(f->mesh, e.vert)] = e.vert;
+        }
+      }
+
+      std::vector<vertex_t> vout;
+      vout.reserve(vmap.size());
+
+      for (n = 0, vmap_iter = vmap.begin(); vmap_iter != vmap.end(); ++vmap_iter, ++n) {
+        vout.push_back(*(*vmap_iter).second);
+        (*vmap_iter).second = & vout.back();
+      }
+
+      for (face_iter i = faceBegin(); i != faceEnd(); ++i) {
+        face_t *f = *i;
+        for (typename face_t::edge_iter_t j = f->begin(); j != f->end(); ++j) {
+          edge_t &e = *j;
+          e.vert = vmap[std::make_pair(f->mesh, e.vert)];
+        }
+      }
+
+      vertex_storage.swap(vout);
+    }
+
   }
 }
+
