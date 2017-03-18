--- ./extern/carve/include/carve/mesh.hpp.orig	2013-10-23 01:43:14 UTC
+++ ./extern/carve/include/carve/mesh.hpp
@@ -464,8 +464,27 @@
 
 
 
+    struct MeshOptions {
+      bool opt_avoid_cavities;
+
+      MeshOptions() :
+        opt_avoid_cavities(false) {
+      }
+
+      MeshOptions &avoid_cavities(bool val) {
+        opt_avoid_cavities = val;
+        return *this;
+      }
+    };
+
+
+
     namespace detail {
       class FaceStitcher {
+        FaceStitcher();
+        FaceStitcher(const FaceStitcher &);
+        FaceStitcher &operator=(const FaceStitcher &);
+
         typedef Vertex<3> vertex_t;
         typedef Edge<3> edge_t;
         typedef Face<3> face_t;
@@ -475,6 +494,8 @@
         typedef std::unordered_map<vpair_t, edgelist_t, carve::mesh::hash_vertex_pair> edge_map_t;
         typedef std::unordered_map<const vertex_t *, std::set<const vertex_t *> > edge_graph_t;
 
+        MeshOptions opts;
+
         edge_map_t edges;
         edge_map_t complex_edges;
 
@@ -570,6 +591,8 @@
         void build(iter_t begin, iter_t end, std::vector<Mesh<3> *> &meshes);
 
       public:
+        FaceStitcher(const MeshOptions &_opts);
+
         template<typename iter_t>
         void create(iter_t begin, iter_t end, std::vector<Mesh<3> *> &meshes);
       };
@@ -623,7 +646,7 @@
       ~Mesh();
 
       template<typename iter_t>
-      static void create(iter_t begin, iter_t end, std::vector<Mesh<ndim> *> &meshes);
+      static void create(iter_t begin, iter_t end, std::vector<Mesh<ndim> *> &meshes, const MeshOptions &opts);
 
       aabb_t getAABB() const {
         return aabb_t(faces.begin(), faces.end());
@@ -692,7 +715,7 @@
       MeshSet &operator=(const MeshSet &);
 
       template<typename iter_t>
-      void _init_from_faces(iter_t begin, iter_t end);
+      void _init_from_faces(iter_t begin, iter_t end,  const MeshOptions &opts);
 
     public:
       typedef Vertex<ndim> vertex_t;
@@ -781,13 +804,16 @@
 
       MeshSet(const std::vector<typename vertex_t::vector_t> &points,
               size_t n_faces,
-              const std::vector<int> &face_indices);
+              const std::vector<int> &face_indices,
+              const MeshOptions &opts = MeshOptions());
 
       // Construct a mesh set from a set of disconnected faces. Takes
       // posession of the face pointers.
-      MeshSet(std::vector<face_t *> &faces);
+      MeshSet(std::vector<face_t *> &faces,
+              const MeshOptions &opts = MeshOptions());
 
-      MeshSet(std::list<face_t *> &faces);
+      MeshSet(std::list<face_t *> &faces,
+              const MeshOptions &opts = MeshOptions());
 
       MeshSet(std::vector<vertex_t> &_vertex_storage,
               std::vector<mesh_t *> &_meshes);
@@ -817,6 +843,8 @@
       void collectVertices();
 
       void canonicalize();
+
+      void separateMeshes();
     };
 
 
@@ -843,3 +871,4 @@
 };
 
 #include <carve/mesh_impl.hpp>
+
