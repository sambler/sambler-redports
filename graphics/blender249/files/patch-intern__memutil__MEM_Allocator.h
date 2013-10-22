--- ./intern/memutil/MEM_Allocator.h.orig	2009-09-02 00:50:41.000000000 +0930
+++ ./intern/memutil/MEM_Allocator.h	2012-12-14 20:19:39.030422536 +1030
@@ -26,6 +26,7 @@
 
 #include "guardedalloc/MEM_guardedalloc.h"
 #include "guardedalloc/BLO_sys_types.h"
+#include <stddef.h>
 
 #ifdef _MSC_VER
 #if _MSC_VER < 1300 // 1200 == VC++ 6.0 according to boost
