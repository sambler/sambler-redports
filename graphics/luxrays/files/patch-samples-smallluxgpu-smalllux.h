--- samples/smallluxgpu/smalllux.h.orig
+++ samples/smallluxgpu/smalllux.h
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
