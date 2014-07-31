--- ./src/Base/Stream.h.orig	2014-07-14 01:03:02.000000000 +0930
+++ ./src/Base/Stream.h	2014-07-29 14:42:03.561399772 +0930
@@ -29,6 +29,14 @@
 # include <stdint.h>
 #endif
 
+#undef toupper
+#undef tolower
+#undef isupper
+#undef islower
+#undef isspace
+#undef isalpha
+#undef isalnum
+
 #include <fstream>
 #include <ios>
 #include <iostream>
