--- ./core/memory.h.orig	2012-02-28 04:28:28.000000000 +1030
+++ ./core/memory.h	2012-02-28 16:50:09.000000000 +1030
@@ -33,9 +33,9 @@
 #    define memalign(a,b) _aligned_malloc(b, a)
 #    define alloca _alloca
 #  endif
-#elif defined(__APPLE__)
+#elif defined(__APPLE__) || defined(__FreeBSD__)
 #  define memalign(a,b) valloc(b)
-#elif defined(__OpenBSD__) || defined(__FreeBSD__)
+#elif defined(__OpenBSD__)
 #  define memalign(a,b) malloc(b)
 #endif
 
