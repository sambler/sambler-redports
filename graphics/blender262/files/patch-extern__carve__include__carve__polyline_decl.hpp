--- ./extern/carve/include/carve/polyline_decl.hpp.orig	2013-10-23 01:48:07 UTC
+++ ./extern/carve/include/carve/polyline_decl.hpp
@@ -138,6 +138,11 @@
       PolylineSet(const std::vector<carve::geom3d::Vector> &points);
       PolylineSet() {
       }
+      ~PolylineSet() {
+        for (line_iter i = lines.begin(); i != lines.end(); ++i) {
+          delete *i;
+        }
+      }
 
       template<typename iter_t>
       void addPolyline(bool closed, iter_t begin, iter_t end);
@@ -149,3 +154,4 @@
 
   }
 }
+
