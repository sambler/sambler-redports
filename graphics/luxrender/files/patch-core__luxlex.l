--- ./core/luxlex.l.orig	2012-02-28 04:28:28.000000000 +1030
+++ ./core/luxlex.l	2012-02-28 16:50:09.000000000 +1030
@@ -28,6 +28,8 @@
 #define YY_NEVER_INTERACTIVE 1
 
 #include <sstream>
+/* this is only needed for gcc46? others are fine */
+#include <string.h>
 #include "lux.h"
 #include "api.h"
 #include "error.h"
