--- source/blender/blenlib/BLI_alloca.h.orig	2017-08-06 04:59:23 UTC
+++ source/blender/blenlib/BLI_alloca.h
@@ -34,8 +34,13 @@
 #endif
 
 #if defined(__GNUC__) || defined(__clang__)
+#if defined(__cplusplus) && (__cplusplus > 199711L)
+#define BLI_array_alloca(arr, realsize) \
+	(decltype(arr))alloca(sizeof(*arr) * (realsize))
+#else
 #define BLI_array_alloca(arr, realsize) \
 	(typeof(arr))alloca(sizeof(*arr) * (realsize))
+#endif
 #else
 #define BLI_array_alloca(arr, realsize) \
 	alloca(sizeof(*arr) * (realsize))
