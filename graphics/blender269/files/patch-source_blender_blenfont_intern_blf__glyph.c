--- source/blender/blenfont/intern/blf_glyph.c.orig	2013-09-01 10:16:04.000000000 +0930
+++ source/blender/blenfont/intern/blf_glyph.c	2014-12-14 15:45:10.154201047 +1030
@@ -273,8 +273,8 @@
 	g->xoff = -1;
 	g->yoff = -1;
 	bitmap = slot->bitmap;
-	g->width = bitmap.width;
-	g->height = bitmap.rows;
+	g->width = (int)bitmap.width;
+	g->height = (int)bitmap.rows;
 
 	if (g->width && g->height) {
 		if (sharp) {
