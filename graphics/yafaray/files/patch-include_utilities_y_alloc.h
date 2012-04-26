--- include/utilities/y_alloc.h.orig	2012-04-25 04:04:05.000000000 +0930
+++ include/utilities/y_alloc.h	2012-04-25 20:48:16.000000000 +0930
@@ -6,7 +6,7 @@
 #include <stdlib.h>
 #include <vector>
 #include <algorithm>
-#if !defined(WIN32) && !defined(__APPLE__)
+#if !defined(WIN32) && !defined(__APPLE__) && !defined(__FreeBSD__)
 	#include <alloca.h>
 #elif defined (__MINGW32__) //Added by DarkTide to enable mingw32 compliation
 	#include <malloc.h>
