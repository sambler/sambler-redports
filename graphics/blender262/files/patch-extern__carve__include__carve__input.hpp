--- ./extern/carve/include/carve/input.hpp.orig	2013-10-23 01:41:29.204018802 +1030
+++ ./extern/carve/include/carve/input.hpp	2013-10-23 01:41:54.296016723 +1030
@@ -17,6 +17,9 @@
 
 #pragma once
 
+#include <map>
+#include <string>
+
 #include <carve/carve.hpp>
 #include <carve/poly.hpp>
 #include <carve/mesh.hpp>
@@ -28,6 +31,50 @@
 namespace carve {
   namespace input {
 
+    typedef std::map<std::string, std::string> Options;
+
+    static inline Options opts() {
+      return Options();
+    }
+
+    static inline Options opts(const char **kv) {
+      Options r;
+      for (size_t i = 0; kv[i] != NULL; i += 2) {
+        r[kv[i]] = kv[i+1];
+      }
+      return r;
+    }
+
+    static inline Options opts(const std::string &k1, const std::string &v1) {
+      Options r;
+      r[k1] = v1;
+      return r;
+    }
+
+    static inline Options opts(const std::string &k1, const std::string &v1,
+                               const std::string &k2, const std::string &v2) {
+      Options r;
+      r[k1] = v1;
+      r[k2] = v2;
+      return r;
+    }
+
+    static inline Options opts(const std::string &k1, const std::string &v1,
+                               const std::string &k2, const std::string &v2,
+                               const std::string &k3, const std::string &v3) {
+      Options r;
+      r[k1] = v1;
+      r[k2] = v2;
+      r[k3] = v3;
+      return r;
+    }
+
+    static inline bool _bool(const std::string &str, bool _default = false) {
+      if (str == "true") return true;
+      if (str == "false") return false;
+      return _default;
+    }
+
     struct Data {
       Data() {
       }
@@ -126,12 +173,18 @@
         faceCount = 0;
       }
 
-      carve::poly::Polyhedron *create() const {
+      carve::poly::Polyhedron *create(const Options &options) const {
         return new carve::poly::Polyhedron(points, faceCount, faceIndices);
       }
 
-      carve::mesh::MeshSet<3> *createMesh() const {
-        return new carve::mesh::MeshSet<3>(points, faceCount, faceIndices);
+      carve::mesh::MeshSet<3> *createMesh(const Options &options) const {
+        Options::const_iterator i;
+        carve::mesh::MeshOptions opts;
+        i = options.find("avoid_cavities");
+        if (i != options.end()) {
+          opts.avoid_cavities(_bool((*i).second));
+        }
+        return new carve::mesh::MeshSet<3>(points, faceCount, faceIndices, opts);
       }
     };
 
@@ -159,7 +212,7 @@
         polylines.back().second.push_back(idx);
       }
 
-      carve::line::PolylineSet *create() const {
+      carve::line::PolylineSet *create(const Options &options) const {
         carve::line::PolylineSet *p = new carve::line::PolylineSet(points);
 
         for (std::list<polyline_data_t>::const_iterator i = polylines.begin();
@@ -181,7 +234,7 @@
       virtual ~PointSetData() {
       }
 
-      carve::point::PointSet *create() const {
+      carve::point::PointSet *create(const Options &options) const {
         carve::point::PointSet *p = new carve::point::PointSet(points);
         return p;
       }
@@ -214,38 +267,39 @@
       }
 
       template<typename T>
-      static inline T *create(Data *d) {
+      static inline T *create(Data *d, const Options &options = Options()) {
         return NULL;
       }
     };
 
     template<>
-    inline carve::mesh::MeshSet<3> *Input::create(Data *d) {
+    inline carve::mesh::MeshSet<3> *Input::create(Data *d, const Options &options) {
       PolyhedronData *p = dynamic_cast<PolyhedronData *>(d);
       if (p == NULL) return NULL;
-      return p->createMesh();
+      return p->createMesh(options);
     }
 
     template<>
-    inline carve::poly::Polyhedron *Input::create(Data *d) {
+    inline carve::poly::Polyhedron *Input::create(Data *d, const Options &options) {
       PolyhedronData *p = dynamic_cast<PolyhedronData *>(d);
       if (p == NULL) return NULL;
-      return p->create();
+      return p->create(options);
     }
 
     template<>
-    inline carve::line::PolylineSet *Input::create(Data *d) {
+    inline carve::line::PolylineSet *Input::create(Data *d, const Options &options) {
       PolylineSetData *p = dynamic_cast<PolylineSetData *>(d);
       if (p == NULL) return NULL;
-      return p->create();
+      return p->create(options);
     }
 
     template<>
-    inline carve::point::PointSet *Input::create(Data *d) {
+    inline carve::point::PointSet *Input::create(Data *d, const Options &options) {
       PointSetData *p = dynamic_cast<PointSetData *>(d);
       if (p == NULL) return NULL;
-      return p->create();
+      return p->create(options);
     }
 
   }
 }
+
