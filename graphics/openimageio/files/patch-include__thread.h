--- include/thread.h.orig	2013-03-01 21:46:47.380515836 +1030
+++ include/thread.h	2013-03-01 21:46:56.456181119 +1030
@@ -98,9 +98,7 @@
 #endif
 
 #if defined(__GNUC__) && (defined(_GLIBCXX_ATOMIC_BUILTINS) || (__GNUC__ * 100 + __GNUC_MINOR__ >= 401))
-# if !USE_TBB
 # define USE_GCC_ATOMICS 1
-# endif
 #endif
 
 OIIO_NAMESPACE_ENTER
