--- ./extern/carve/include/carve/exact.hpp.orig	2013-10-23 01:37:12 UTC
+++ ./extern/carve/include/carve/exact.hpp
@@ -639,9 +639,11 @@
     }
 
 
-    // XXX: not implemented yet
-    //exact_t operator+(const exact_t &a, const exact_t &b) {
-    //}
+    exact_t operator+(const exact_t &a, const exact_t &b) {
+      exact_t r;
+      sum_zeroelim(a, b, r);
+      return r;
+    }
 
 
 
