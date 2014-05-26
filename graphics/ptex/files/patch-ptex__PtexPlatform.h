--- ./ptex/PtexPlatform.h.orig	2014-05-27 02:04:52.211536293 +0930
+++ ./ptex/PtexPlatform.h	2014-05-27 02:06:45.384535527 +0930
@@ -60,7 +60,9 @@
 
 // linux/unix/posix
 #include <stdlib.h>
+#if !defined(__FreeBSD__)
 #include <alloca.h>
+#endif
 #include <string.h>
 #include <pthread.h>
 // OS for spinlock
