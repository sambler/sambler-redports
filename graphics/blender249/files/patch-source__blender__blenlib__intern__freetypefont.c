--- ./source/blender/blenlib/intern/freetypefont.c.orig	2014-01-03 20:09:25.742033162 +1030
+++ ./source/blender/blenlib/intern/freetypefont.c	2014-01-03 20:10:10.476033554 +1030
@@ -41,7 +41,7 @@
 #include FT_GLYPH_H
 #include FT_BBOX_H
 #include FT_SIZES_H
-#include <freetype/ttnameid.h>
+#include <freetype2/ttnameid.h>
 
 #include "MEM_guardedalloc.h"
 
