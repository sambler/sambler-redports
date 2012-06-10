--- include/fmath.h.orig	2012-06-05 03:00:16.000000000 +0930
+++ include/fmath.h	2012-06-10 09:46:33.451827283 +0930
@@ -66,6 +66,10 @@
 
 #include "version.h"
 
+#if defined(__FreeBSD__)
+#include <sys/param.h>
+#endif
+
 OIIO_NAMESPACE_ENTER
 {
 
