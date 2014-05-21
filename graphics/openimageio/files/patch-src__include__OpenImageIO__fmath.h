--- ./src/include/OpenImageIO/fmath.h.orig	2014-05-21 14:38:46.683229643 +0930
+++ ./src/include/OpenImageIO/fmath.h	2014-05-21 14:44:40.821230532 +0930
@@ -61,7 +61,10 @@
 #  define _UINT64_T
 # endif
 #else
-# include <stdint.h>
+#  ifndef __STDC_LIMIT_MACROS
+#    define __STDC_LIMIT_MACROS  /* needed for some defs in stdint.h */
+#  endif
+#  include <stdint.h>
 #endif
 
 #if defined(__FreeBSD__)
