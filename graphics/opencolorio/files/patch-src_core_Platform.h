--- src/core/Platform.h.orig	2012-12-11 23:21:23 UTC
+++ src/core/Platform.h
@@ -85,7 +85,9 @@ OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 
 // linux/unix/posix
 #include <stdlib.h>
+#if !defined(__FreeBSD__)
 #include <alloca.h>
+#endif
 #include <string.h>
 #include <pthread.h>
 // OS for spinlock
