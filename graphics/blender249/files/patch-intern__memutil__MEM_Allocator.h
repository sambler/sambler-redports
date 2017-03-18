--- ./intern/memutil/MEM_Allocator.h.orig	2009-09-02 00:50:41 UTC
+++ ./intern/memutil/MEM_Allocator.h
@@ -26,6 +26,7 @@
 
 #include "guardedalloc/MEM_guardedalloc.h"
 #include "guardedalloc/BLO_sys_types.h"
+#include <stddef.h>
 
 #ifdef _MSC_VER
 #if _MSC_VER < 1300 // 1200 == VC++ 6.0 according to boost
