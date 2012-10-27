--- ./liboslexec/llvm_ops.cpp.orig	2012-10-27 17:03:52.824663726 +1030
+++ ./liboslexec/llvm_ops.cpp	2012-10-27 17:05:07.439663379 +1030
@@ -123,6 +123,14 @@
 using OIIO::isfinite;
 #endif
 
+#if defined(__FreeBSD__)
+#include <sys/param.h>
+#endif
+
+#if (defined(__FreeBSD__) && (__FreeBSD_version < 803000))
+using OIIO::log2f;
+#endif
+
 // Handy re-casting macros
 #define USTR(cstr) (*((ustring *)&cstr))
 #define MAT(m) (*(Matrix44 *)m)
