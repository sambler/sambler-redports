--- include/lmms_math.h.orig	2015-03-08 02:47:14 UTC
+++ include/lmms_math.h
@@ -34,7 +34,7 @@
 #include <cmath>
 using namespace std;
 
-#if defined (LMMS_BUILD_WIN32) || defined (LMMS_BUILD_APPLE) 
+#if defined (LMMS_BUILD_WIN32) || defined (LMMS_BUILD_APPLE) || defined (__FreeBSD__)
 #ifndef isnanf
 #define isnanf(x)	isnan(x)
 #endif
