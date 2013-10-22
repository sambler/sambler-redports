--- ./extern/carve/include/carve/exact.hpp.orig	2013-10-23 01:37:12.486033384 +1030
+++ ./extern/carve/include/carve/exact.hpp	2013-10-23 01:37:53.407019053 +1030
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
 
 
 
