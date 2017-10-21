--- extern/libmv/libmv/numeric/numeric.h.orig	2017-10-18 19:45:18 UTC
+++ extern/libmv/libmv/numeric/numeric.h
@@ -33,12 +33,16 @@
 #include <Eigen/QR>
 #include <Eigen/SVD>
 
-#if (defined(_WIN32) || defined(__APPLE__) || defined(__FreeBSD__)) && !defined(__MINGW64__)
-  static void sincos(double x, double *sinx, double *cosx) {
-    *sinx = sin(x);
-    *cosx = cos(x);
-  }
-#endif  // _WIN32 || __APPLE__
+#if !defined(__MINGW64__)
+#  if defined(_WIN32) || defined(__APPLE__) || \
+      (defined(__FreeBSD__) && (__FreeBSD_version < 1101504)) || \
+      defined(__NetBSD__)
+inline void sincos(double x, double *sinx, double *cosx) {
+  *sinx = sin(x);
+  *cosx = cos(x);
+}
+#  endif
+#endif  // !__MINGW64__
 
 #if (defined(WIN32) || defined(WIN64)) && !defined(__MINGW32__)
   inline long lround(double d) {
