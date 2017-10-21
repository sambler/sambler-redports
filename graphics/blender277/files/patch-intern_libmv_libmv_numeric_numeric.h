--- intern/libmv/libmv/numeric/numeric.h.orig	2014-04-12 00:16:41 UTC
+++ intern/libmv/libmv/numeric/numeric.h
@@ -35,8 +35,9 @@
 
 #if !defined(__MINGW64__)
 #  if defined(_WIN32) || defined(__APPLE__) || \
-      defined(__FreeBSD__) || defined(__NetBSD__)
-static void sincos(double x, double *sinx, double *cosx) {
+      (defined(__FreeBSD__) && (__FreeBSD_version < 1101504)) || \
+      defined(__NetBSD__)
+inline void sincos(double x, double *sinx, double *cosx) {
   *sinx = sin(x);
   *cosx = cos(x);
 }
