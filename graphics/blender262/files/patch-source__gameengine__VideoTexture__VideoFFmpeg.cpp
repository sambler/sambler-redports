--- ./source/gameengine/VideoTexture/VideoFFmpeg.cpp.orig	2013-10-23 01:14:27.463021929 +1030
+++ ./source/gameengine/VideoTexture/VideoFFmpeg.cpp	2013-10-23 01:15:31.682018907 +1030
@@ -31,7 +31,7 @@
 #ifndef __STDC_CONSTANT_MACROS
 #define __STDC_CONSTANT_MACROS
 #endif
-#include <stdint.h>
+#include <inttypes.h>
 
 
 #include "MEM_guardedalloc.h"
