--- ./include/lmms_math.h.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./include/lmms_math.h	2014-08-29 05:37:23.596454485 +0930
@@ -33,7 +33,7 @@
 
 #include <math.h>
 
-#if defined (LMMS_BUILD_WIN32) || defined (LMMS_BUILD_APPLE) 
+#if defined (LMMS_BUILD_WIN32) || defined (LMMS_BUILD_APPLE) || defined (__FreeBSD__)
 #ifndef isnanf
 #define isnanf(x)	isnan(x)
 #endif
