--- include/thread.h.orig	2013-01-10 11:43:37.000000000 +1030
+++ include/thread.h	2013-02-03 16:52:29.991857116 +1030
@@ -98,8 +98,8 @@
 #endif
 
 #if defined(__GNUC__) && (defined(_GLIBCXX_ATOMIC_BUILTINS) || (__GNUC__ * 100 + __GNUC_MINOR__ >= 401))
-#if !defined(__FreeBSD__) || defined(__x86_64__)
-#define USE_GCC_ATOMICS
+#if !USE_TBB
+#define USE_GCC_ATOMICS 1
 #endif
 #endif
 
