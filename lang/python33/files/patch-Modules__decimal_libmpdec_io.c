--- ./Modules/_decimal/libmpdec/io.c.orig	2013-01-02 21:15:38.414172269 +1030
+++ ./Modules/_decimal/libmpdec/io.c	2013-01-02 21:32:27.808174230 +1030
@@ -30,6 +30,13 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#if defined(__FreeBSD__)
+#include <sys/param.h>
+#if (__GNUC__) && (__FreeBSD_version >= 901000)
+/* gcc on 9.1 breaks because __GNUC_STDC_INLINE__ isn't defined */
+#define __GNUC_STDC_INLINE__  (0)
+#endif
+#endif
 #include <ctype.h>
 #include <limits.h>
 #include <assert.h>
