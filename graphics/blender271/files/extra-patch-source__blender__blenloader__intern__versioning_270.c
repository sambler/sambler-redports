--- ./source/blender/blenloader/intern/versioning_270.c.orig	2014-03-21 08:30:51.333537109 +1030
+++ ./source/blender/blenloader/intern/versioning_270.c	2014-03-21 08:31:13.239421038 +1030
@@ -48,6 +48,7 @@
 
 #include "readfile.h"
 
+#include <stddef.h>
 
 void blo_do_versions_270(FileData *fd, Library *UNUSED(lib), Main *main)
 {
