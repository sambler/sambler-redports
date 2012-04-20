--- ./samples/smallluxgpu/smalllux.h.orig	2012-02-26 09:20:53.000000000 +1030
+++ ./samples/smallluxgpu/smalllux.h	2012-03-10 23:02:33.000000000 +1030
@@ -27,13 +27,13 @@
 #include <fstream>
 #include <iostream>
 
-#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 #include <stddef.h>
 #include <sys/time.h>
 #elif defined (WIN32)
 #include <windows.h>
 #else
-	Unsupported Platform !!!
+#error	"Unsupported Platform !!!"
 #endif
 
 #include "luxrays/luxrays.h"
