--- include/utilities/y_alloc.h.orig	2013-09-03 17:03:17 UTC
+++ include/utilities/y_alloc.h
@@ -6,7 +6,7 @@
 #include <stdlib.h>
 #include <vector>
 #include <algorithm>
-#if !defined(WIN32) && !defined(__APPLE__)
+#if !defined(WIN32) && !defined(__APPLE__) && !defined(__FreeBSD__)
 	#include <alloca.h>
 #elif defined (__MINGW32__) //Added by DarkTide to enable mingw32 compliation
 	#include <malloc.h>
